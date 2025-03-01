
/******************************************************************************
  @file    qcril_qmi_ota_daemon.c
  @brief   a seperate thread for upgrading MBN in EFS

  DESCRIPTION
    Provide a seperate thread for updgrading MBN in modem EFS, and trigger
    modem SSR if needed

  ---------------------------------------------------------------------------

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------
******************************************************************************/

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utils/Log.h>
#include "pdc_utils.h"
#include "mbn_utils.h"
#include "qcril_db.h"
#include "qcril_mbn_db.h"
#include "qcril_mbn_sw_update.h"
#include "qcril_mbn_ota_file_list.h"
#include "qcrili.h"

#define MAX_SUBS                    3
#define OEM_VERSION_LENGTH          4

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "MBN_OTA"

/* MBN info in EFS */
struct efs_modem_config_info {
    struct pdc_config_pdc_info  config_id;
    struct pdc_config_item_info config_info;
    uint32_t                    is_current:1;
    uint32_t                    sub:3;
    uint32_t                    is_matched:1;
};

static void dump_mbn_list_info(struct efs_modem_config_info* p_modem_list, int n_list)
{
    int idx, subs;
    uint32_t len;
    char *tmp_str;

    if (!p_modem_list || !n_list) {
        RLOGI("no MBN in modem EFS.");
        return;
    }

    len = (PDC_CONFIG_DESC_SIZE_MAX_V01 > PDC_CONFIG_ID_SIZE_MAX_V01) ?
        PDC_CONFIG_DESC_SIZE_MAX_V01 : PDC_CONFIG_ID_SIZE_MAX_V01;
    len += 1;
    if ((tmp_str = malloc(len)) == NULL) {
        RLOGE("Failed to alloc memory to hold config_id/config_desc for dump purpose");
        return;
    }

    RLOGI("current MBNs in modem EFS:");
    for (idx = 0; idx < n_list; idx++) {
        /* show config_id */
        len = (p_modem_list[idx].config_id.config_id_len < PDC_CONFIG_ID_SIZE_MAX_V01) ?
            p_modem_list[idx].config_id.config_id_len : PDC_CONFIG_ID_SIZE_MAX_V01;
        memcpy(tmp_str, p_modem_list[idx].config_id.config_id, len);
        tmp_str[len] = '\0';
        RLOGI("%2d: config_id: %s", idx, tmp_str);
        /* show config_desc */
        if (p_modem_list[idx].config_info.config_desc_valid) {
            len = (p_modem_list[idx].config_info.config_desc_len < PDC_CONFIG_DESC_SIZE_MAX_V01) ?
                p_modem_list[idx].config_info.config_desc_len : PDC_CONFIG_DESC_SIZE_MAX_V01;
            memcpy(tmp_str, p_modem_list[idx].config_info.config_desc, len);
            tmp_str[len] = '\0';
            RLOGI("    config_desc: %s", tmp_str);
        }
        if (p_modem_list[idx].config_info.config_version_valid) {
            RLOGI("    config_version: 0x%x", p_modem_list[idx].config_info.config_version);
        }
        if (p_modem_list[idx].is_current) {
            RLOGI("    This config is activated with SUBs:");
            for (subs = 0; subs < MAX_SUBS; subs++) {
                if (p_modem_list[idx].sub & (1 << subs))
                    RLOGI("    SUB%d", subs);
            }
        }
    }

    free(tmp_str);
}

static void dump_local_file_list(struct local_modem_config_info* p_list, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        RLOGI("file_name: %s, version: 0x%08x, is_matched: %d",
            p_list[i].file_name, p_list[i].version, p_list[i].is_matched);
    }

}

static inline int is_config_activated(struct pdc_config_pdc_info *config_id,
                    struct pdc_config_pdc_info *config_ids_per_sub, uint32_t *p_sub_mask)
{
    uint32_t i, sub_idx, sub_mask = 0;

    if (!config_id || !config_ids_per_sub)
        return 0;
    for (sub_idx = 0; sub_idx < MAX_SUBS; sub_idx++) {
        if (config_id->config_id_len != config_ids_per_sub[sub_idx].config_id_len)
            continue;
        for (i = 0; i < config_id->config_id_len; i++) {
            if (config_id->config_id[i] != config_ids_per_sub[sub_idx].config_id[i])
                break;
        }
        if (i == config_id->config_id_len)
            sub_mask |= (1 << sub_idx);
    }

    *p_sub_mask = sub_mask;
    return (!!sub_mask);
}

/* This function will generate all MBN list and their infos, querying from modem side
 * Note: this function will allocate memory for modem_list, need to free it after use
 */

static int get_modem_list(struct efs_modem_config_info **p_modem_list)
{
    uint32_t i, sub_mask, index = 0;
    struct efs_modem_config_info *modem_list;
    struct pdc_config_list_info config_list;
    struct pdc_config_item_info config_info;
    struct pdc_config_pdc_info config_ids_per_sub[MAX_SUBS];
    int result, is_activated;

    /* set NULL as default */
    *p_modem_list = NULL;

    /* get config_id lists from modem side */
    if ((result = pdc_get_config_lists(&config_list)) != PDC_SUCCESS) {
        RLOGE("Failed to get config list from modem, error code: %d", result);
        return result;
    }

    /* allocate memory to hold configuration info */
    modem_list = (struct efs_modem_config_info*)malloc(
                        sizeof(struct efs_modem_config_info) * config_list.num_configs);
    if (modem_list == NULL) {
        RLOGE("Failed to allocate memeory to hold modem list");
        return PDC_ERROR;
    }
    memset(modem_list, 0, sizeof(struct efs_modem_config_info) * config_list.num_configs);

    /* get current config for each sub */
    for (i = 0; i < MAX_SUBS; i++) {
        result = pdc_get_current_config(config_ids_per_sub + i,  PDC_CONFIG_TYPE_MODEM_SW_V01, i);
        if (result == PDC_NOT_AVAIL) {
            /* no selected MBN on this SUB */
            config_ids_per_sub[i].config_id_len = 0;
        } else if (result != PDC_SUCCESS) {
            RLOGE("failed to get current config for SUB %d", i);
            config_ids_per_sub[i].config_id_len = 0;
        }
    }

    /* go over the list, fill the config_info in the table and mark current activated config */
    index = 0;
    for (i = 0; i < (uint32_t)config_list.num_configs; i++) {
        result = pdc_get_config_info(&config_list.config_item[i], &config_info, PDC_CONFIG_TYPE_MODEM_SW_V01);
        if (result == PDC_SUCCESS) {
            /* check if it is activated */
            is_activated = (is_config_activated(&config_list.config_item[i], config_ids_per_sub, &sub_mask));
            modem_list[index].config_id = config_list.config_item[i];
            modem_list[index].config_info = config_info;
            modem_list[index].is_current = is_activated;
            modem_list[index].sub = sub_mask;
            index++;
        } else {
            RLOGE("Failed to get config info");
            free(modem_list);
            return PDC_ERROR;
        }
    }

    *p_modem_list = modem_list;
    return index;
}

/* Generate an unique config_id
 * config_id: using OTA_"filepath"_date as a temporary solution
 * for long term: Using an algorithm to generate (like QPST??)
 */
static int generate_config_id(char* mbn_file, struct pdc_config_pdc_info* config_id)
{
    size_t ret;
    struct timeval tv;
#define MAX_TIME_STRING_LENGTH     64
    char time_str[MAX_TIME_STRING_LENGTH];

    strlcpy((char*)config_id->config_id, "OTA_", PDC_CONFIG_ID_SIZE_MAX_V01);
    ret = strlcat((char*)config_id->config_id, mbn_file, PDC_CONFIG_ID_SIZE_MAX_V01);
    if (ret >= PDC_CONFIG_ID_SIZE_MAX_V01) {
        RLOGW("boundary exceeds when generate config_id");
        config_id->config_id_len = strlen((char*)config_id->config_id);
        return PDC_SUCCESS;
    }
    gettimeofday(&tv, NULL);
    snprintf(time_str, MAX_TIME_STRING_LENGTH, "%ld:%ld", tv.tv_sec, tv.tv_usec);
    ret = strlcat((char*)config_id->config_id, time_str, PDC_CONFIG_ID_SIZE_MAX_V01);
    if (ret >= PDC_CONFIG_ID_SIZE_MAX_V01)
        RLOGW("boundary exceeds when generate config_id");

    config_id->config_id_len = strlen((char*)config_id->config_id);
    return PDC_SUCCESS;
}

/* OEM version format
 * 0x AA BB CC DD
 * 0xAA = 0x02 .. Modem family  (0x01=Nikel, 0x02=Dime, 0x03=Triton, 0x04=Bolt, 0x05=Jolokia(8909), 0x06=Thor)
 * 0xBB = 0x01 .. OEM can modify this field for differing from base version
 * 0xCC = 0x20 .. Major version = Carrier index = 32
 * 0xDD = Carrier Minor version
 */
static inline int is_same_type_mbn(const char* version_local, const char* version_remote)
{
    /* AA == AA, CC == CC */
    return ((version_local[1] == version_remote[1])
               && (version_local[3] == version_remote[3]));
}

static int load_new_mbn(char *mbn_file, struct pdc_config_pdc_info *p_new_config_id)
{
    int ret_val = PDC_ERROR;

    if (generate_config_id(mbn_file, p_new_config_id) == PDC_SUCCESS) {
        ret_val = pdc_load_config(mbn_file, p_new_config_id, PDC_CONFIG_TYPE_MODEM_SW_V01);
    }

    return ret_val;
}

void* qmi_ril_mbn_ota_thread_proc(void* empty_param)
{
    struct efs_modem_config_info *p_modem_list = NULL;
    struct local_modem_config_info *p_local_list = NULL;
    struct pdc_config_pdc_info new_config_id;
    uint32_t deleted_activated_info_per_sub[MAX_SUBS];
    int n_modem_list, n_local_file;
    int is_all_in_local_matched;
    int is_mbn_refresh_support;
    int new_selected_sub;
    int idx, sub, i, j;
    int ret_val;

    /* avoid the "unused" warning */
    QCRIL_NOTUSED(empty_param);

    /* initialize QMI PDC */
    if (pdc_init() != PDC_SUCCESS)
        return (void*)PDC_ERROR;

    /* load MBN into database if needed */
    if (qcril_mbn_sw_load_to_db() != E_SUCCESS)
        return (void*)PDC_ERROR;

    /* query modem configuration info */
    n_modem_list = get_modem_list(&p_modem_list);
    if (n_modem_list == PDC_NOT_AVAIL) {
        n_modem_list = 0;
    } else if (n_modem_list < 0) {
        return (void*)PDC_ERROR;
    }

    /* query local file list info */
    n_local_file = qcril_get_mbn_file_list(&p_local_list);
    if (n_local_file <= 0) {
        n_local_file = 0;
        RLOGI("Failed to get local file list");
    }
    /*
     * find the matched MBN between local list and that in EFS
     * for these matched MBNs, keep it untouched
     */
    is_all_in_local_matched = 1;
    for (i = 0; i < n_local_file; i++) {
        for (j = 0; j < n_modem_list; j++) {
            if (p_local_list[i].version == p_modem_list[j].config_info.config_version) {
                p_local_list[i].is_matched = 1;
                p_modem_list[j].is_matched = 1;
                break;
            }
        }
        if (j >= n_modem_list)
            is_all_in_local_matched = 0;
    }
    RLOGI("is_all_in_local_matched: %d", is_all_in_local_matched);

    /* for debug purpose */
    dump_mbn_list_info(p_modem_list, n_modem_list);
    dump_local_file_list(p_local_list, n_local_file);

    /* If all matched, return directly */
    if (is_all_in_local_matched && (n_local_file == n_modem_list)) {
        RLOGI("MBNs in EFS and APSS side are exact matched, skip...");
        return (void*)PDC_SUCCESS;
    }

    is_mbn_refresh_support = qmi_ril_is_feature_supported(QMI_RIL_FEATURE_MBN_REFRESH);
    RLOGI("is_mbn_refresh_support: %d", is_mbn_refresh_support);
    if (is_mbn_refresh_support) {
        ret_val = pdc_enable_auto_selection(0, 0);
        ret_val = pdc_enable_auto_selection(0, 1);
    }

    memset(deleted_activated_info_per_sub, 0, MAX_SUBS);
    /* Delete the MBNs in EFS that are not matched */
    for (idx = 0; idx < n_modem_list; idx++) {
        if (!p_modem_list[idx].is_matched) {
            /* If this MBN is not activated, delete it directly */
            if (!p_modem_list[idx].is_current) {
                ret_val = pdc_delete_config(&p_modem_list[idx].config_id, PDC_CONFIG_TYPE_MODEM_SW_V01);
                if (ret_val != PDC_SUCCESS) {
                    RLOGE("Failed to delete the MBN with config_id: %s", p_modem_list[idx].config_id.config_id);
                }
            } else {
                /* if MBN refresh is not supported, delete the activate MBN after deactivation.
                 * And the deleted activated info is recorded in array deleted_activated_info_per_sub;
                 */
                if (!is_mbn_refresh_support) {
                    for (sub = 0; sub < MAX_SUBS; sub++) {
                        if (p_modem_list[idx].sub & (1 << sub)) {
                            pdc_deactivate_config(sub, PDC_CONFIG_TYPE_MODEM_SW_V01);
                            deleted_activated_info_per_sub[sub] = p_modem_list[idx].config_info.config_version;
                        }
                    }
                    ret_val = pdc_delete_config(&p_modem_list[idx].config_id, PDC_CONFIG_TYPE_MODEM_SW_V01);
                    if (ret_val != PDC_SUCCESS) {
                        RLOGE("Failed to delete the MBN with config_id: %s", p_modem_list[idx].config_id.config_id);
                    }
                }
            }
        }
    }

    /* Upload local MBNs to EFS that are not matched */
    new_selected_sub = -1;
    for (idx = 0; idx < n_local_file; idx++) {
        if (!p_local_list[idx].is_matched) {
            ret_val = load_new_mbn(p_local_list[idx].file_name, &new_config_id);
            if (ret_val != PDC_SUCCESS) {
                RLOGE("Failed to load new MBN: %s, error code: %d", p_local_list[idx].file_name, ret_val);
            } else {
                if (!is_mbn_refresh_support) {
                    for (sub = 0; sub < MAX_SUBS; sub++) {
                        if ((deleted_activated_info_per_sub[sub] != 0) &&
                                (is_same_type_mbn((char*)&p_local_list[idx].version,
                                (char*)&deleted_activated_info_per_sub[sub]))) {
                            pdc_select_config(&new_config_id, PDC_CONFIG_TYPE_MODEM_SW_V01, sub);
                            new_selected_sub = sub;
                        }
                    }
                }
            }
        }
    }

    /* Enable MBN auto selection. Ignore the errors */
    if (is_mbn_refresh_support) {
        ret_val = pdc_enable_auto_selection(1, 0);
        ret_val = pdc_enable_auto_selection(1, 1);
    } else {
        /* activated if needed */
        /* if refresh is not supported, just need to activate one of the sub
         * to trigger modem restart */
        if (new_selected_sub != -1)
            pdc_activate_config(PDC_CONFIG_TYPE_MODEM_SW_V01, new_selected_sub);
    }

    if (p_modem_list)
        free(p_modem_list);
    if (p_local_list)
        free(p_local_list);

    return (void*)PDC_SUCCESS;
}
