/*==============================================================================

    S E N S O R S   AMBIENT LIGHT AND PROXIMITY  D R I V E R

DESCRIPTION

   Implements the driver for the AL3320 ALS(Light) and Proximity Sensor

Copyright (c) 2013-2014 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential
==============================================================================*/
/*==============================================================================

                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

$Header: //commercial/MPSS.JO.2.0.c1.4/Main/modem_proc/Sensors/dd/qcom/src/sns_dd_alsprx_al3320_ext.c#1 $


when         who     what, where, why
----------   ---     -----------------------------------------------------------
06/06/14     MW      init() function signal register fix
09/23/13     yh      Initial version of driver for AL3320
==============================================================================*/


/*============================================================================
                                INCLUDE FILES
============================================================================*/
#include "sns_dd_alsprx_al3320_priv.h"
#include "sns_ddf_attrib.h"
#include "sns_ddf_common.h"
#include "sns_ddf_comm.h"
#include "sns_ddf_driver_if.h"
#include "sns_ddf_smgr_if.h"
#include "sns_ddf_util.h"
#include "sns_ddf_memhandler.h"
#include "sns_ddf_signal.h"
#include "sns_memmgr.h"

#ifndef DDK
#include "log_codes.h"
#include "sns_log_types.h"
#include "sns_log_api.h"
#include "sns_debug_str.h"
#include "sns_debug_api.h"
#endif

#define REG_FIXED_NV_SIZE_128      128

/*============================================================================
                            STATIC VARIABLE DEFINITIONS
============================================================================*/
static const sns_ddf_sensor_e sns_dd_alsprx_sensor_types[2] =
{
  SNS_DDF_SENSOR__NONE,
  SNS_DDF_SENSOR_AMBIENT
};

/*=============================================================================
                           STATIC FUNCTION PROTOTYPES
==============================================================================*/

extern sns_ddf_driver_if_s sns_alsprx_al3320b_driver_fn_list;
extern void sns_dd_al3320b_set_default_reg_values(sns_dd_alsprx_state_t* dd_ptr);
extern void sns_dd_al3320b_set_reg_values_from_nv(sns_dd_alsprx_state_t* state);

/*===========================================================================
FUNCTION      sns_dd_alsprx_al3320b_init

DESCRIPTION   init
===========================================================================*/
sns_ddf_status_e sns_dd_alsprx_al3320b_init(
                                            sns_ddf_handle_t*        dd_ptr,
                                            sns_ddf_handle_t         smgr_handle,
                                            sns_ddf_nv_params_s*     reg_params,
                                            sns_ddf_device_access_s  device_info[],
                                            uint32_t                 num_devices,
                                            sns_ddf_memhandler_s*    memhandler,
                                            sns_ddf_sensor_e*        sensors[],
                                            uint32_t*                num_sensors
                                            )
{
    sns_ddf_status_e       status = SNS_DDF_SUCCESS;
    sns_dd_alsprx_state_t* ptr;

    if ( (dd_ptr == NULL)      ||
         (num_sensors == NULL) ||
         (sensors == NULL) )
    {
        DDF_MSG_0(HIGH, "invalid param");
        return SNS_DDF_EINVALID_PARAM;
    }

    status = sns_ddf_malloc((void**)&ptr, sizeof(sns_dd_alsprx_state_t));
    if ( status != SNS_DDF_SUCCESS )
    {
        return status;
    }

    ptr->smgr_handle = smgr_handle;
    ptr->int_gpio    = device_info->first_gpio;

    status = sns_ddf_open_port(&ptr->port_handle, &device_info->port_config);
    if ( status != SNS_DDF_SUCCESS )
    {
        return status;
    }

    device_info->port_config.bus_config.i2c->dev_type = SNS_DDF_I2C_DEVICE_DEFAULT;
    status = sns_ddf_open_port(&ptr->ZBW_port_handle, &device_info->port_config);
    if( status != SNS_DDF_SUCCESS )
    {
        return status;
    }

    /* Fill out output parameters*/
    *num_sensors = 2;
    *sensors     = (sns_ddf_sensor_e *)sns_dd_alsprx_sensor_types;
    *dd_ptr      = (sns_ddf_handle_t) ptr;

    /* Check to see if IRQ's are enabled*/
    if(sns_ddf_signal_irq_enabled() && (ptr->int_gpio != 0xFFFF))
    {
        /* IRQ's are enabled, register the irq*/
        status = sns_ddf_signal_register(ptr->int_gpio,
                                         *dd_ptr,
                                         &sns_alsprx_al3320b_driver_fn_list,
                                         SNS_DDF_SIGNAL_IRQ_FALLING);

        if( status != SNS_DDF_SUCCESS )
        {
            return status;
        }
    }

     ptr->nv_db_size =0;
     bool data_from_registry = false;
     sns_dd_al3320b_set_default_reg_values(ptr);

    /* Recall NV parameters, if any*/
    if(reg_params)
    {
        DDF_MSG_0(HIGH, "yes registry params available");
        if ( (reg_params->status   == SNS_DDF_SUCCESS) &&
             (reg_params->data_len >= sizeof(sns_dd_nv_db_type)))
        {
            DDF_MSG_0(HIGH, "registry params match nv db type");
            sns_dd_nv_db_type *nv_ptr = (sns_dd_nv_db_type *)reg_params->data;
            if ( (nv_ptr->lsc_num  == AL3320B_MAGIC_NUM) &&
                 (nv_ptr->drv_ID          == AL3320B_DRIVER_ID))
            {
                /* update value from NV parameters*/
                DDF_MSG_0(HIGH, "magic number for AL3320B verified");
                data_from_registry = true;
                ptr->nv_db_size = reg_params->data_len;

                SNS_OS_MEMCOPY(&ptr->sns_dd_alsprx_common_db.nv_db, nv_ptr, sizeof(sns_dd_nv_db_type));
                DDF_MSG_0(HIGH, "in registry params past memcopy");

                sns_dd_al3320b_set_reg_values_from_nv(ptr);
                DDF_MSG_0(HIGH, "setting defaults from nv");
            }
        }

        if (!data_from_registry)
        {
            DDF_MSG_0(HIGH, "No registry data");
            ptr->nv_db_size = REG_FIXED_NV_SIZE_128;
            ptr->sns_dd_alsprx_common_db.nv_db.visible_ratio = SNS_REG_ITEM_ALP_VISIBLE_LIGHT_TRANS_RATIO;
            ptr->sns_dd_alsprx_common_db.nv_db.ir_ratio = SNS_REG_ITEM_ALP_IR_LIGHT_TRANS_RATIO;
            ptr->sns_dd_alsprx_common_db.nv_db.dc_offset = SNS_REG_ITEM_ALP_DC_OFFSET;
            ptr->sns_dd_alsprx_common_db.nv_db.thresh_near = SNS_REG_ITEM_ALP_NEAR_THRESHOLD;
            ptr->sns_dd_alsprx_common_db.nv_db.thresh_far = SNS_REG_ITEM_ALP_FAR_THRESHOLD;
            ptr->sns_dd_alsprx_common_db.nv_db.prx_factor = SNS_REG_ITEM_ALP_PRX_FACTOR;
            ptr->sns_dd_alsprx_common_db.nv_db.als_factor  = SNS_REG_ITEM_ALP_ALS_FACTOR;
            ptr->sns_dd_alsprx_common_db.nv_db.lsc_num = (uint32_t)AL3320B_MAGIC_NUM;
            ptr->sns_dd_alsprx_common_db.nv_db.drv_ID  = (uint32_t)AL3320B_DRIVER_ID;
            ptr->sns_dd_alsprx_common_db.nv_db.calibratePhone = AL3320B_ALS_CALI;
            ptr->sns_dd_alsprx_common_db.nv_db.device = AL3320B_ALS_DEVICE;
            ptr->sns_dd_alsprx_common_db.nv_db.calLuxLower = AL3320B_ALS_CAL_LOW;
            ptr->sns_dd_alsprx_common_db.nv_db.calLuxUpper = AL3320B_ALS_CAL_UP;
            ptr->sns_dd_alsprx_common_db.nv_db.luxCorrection = AL3320B_ALS_LUX_COR;
            ptr->sns_dd_alsprx_common_db.nv_db.ALS_thresh_high = AL3320B_ALS_THR;
            ptr->sns_dd_alsprx_common_db.nv_db.ALS_thresh_low = AL3320B_ALS_THR;

            DDF_MSG_0(HIGH, "Set defaults for registry data");
            /* Writing the same values above to the part*/
            sns_dd_al3320b_set_reg_values_from_nv(ptr);
            DDF_MSG_0(HIGH, "Registry Updated, sending the same values sent to registry to part");
        }

        if ( (reg_params) && (!data_from_registry) )
        {
           DDF_MSG_0(HIGH, "before notify");
           sns_ddf_smgr_notify_event(smgr_handle, SNS_DDF_SENSOR_AMBIENT,SNS_DDF_EVENT_UPDATE_REGISTRY_GROUP);
           DDF_MSG_0(HIGH, "after notify");
        }
    }

    return status;
}

/*===========================================================================
FUNCTION      sns_dd_alsprx_al3320b_get_attrib

DESCRIPTION   sensor get attrib
===========================================================================*/
sns_ddf_status_e sns_dd_alsprx_al3320b_get_attrib
(
  sns_ddf_handle_t      handle,
  sns_ddf_sensor_e      sensor,
  sns_ddf_attribute_e   attrib,
  sns_ddf_memhandler_s* memhandler,
  void**                value,
  uint32_t*             num_elems
)
{
  sns_dd_alsprx_state_t*    state = (sns_dd_alsprx_state_t *)handle;
  sns_ddf_status_e          status = SNS_DDF_SUCCESS;
  sns_ddf_registry_group_s  *reg_group;
  sns_ddf_power_info_s*     power_ptr;
  uint32_t*                 odr_ptr;

  sns_ddf_resolution_adc_s* resp;
  uint8_t                   *reg_group_data;
  sns_ddf_driver_info_s     *driver_info_ptr;
  sns_ddf_driver_info_s     driver_info_l = {
    "AL3320B",  /* name */
    1           /* version */
  };

  sns_ddf_device_info_s *device_info_ptr;
  sns_ddf_device_info_s  device_info_l = {
    "ALS",   /* name */
    "LSC",   /* vendor */
    "AL3320B",  /* model */
    1           /* version */
  };

  if ( (handle == NULL)      ||
       (memhandler == NULL) )
  {
    return SNS_DDF_EINVALID_PARAM;
  }

  switch ( attrib )
  {
    case SNS_DDF_ATTRIB_DRIVER_INFO:
      if ( (driver_info_ptr = sns_ddf_memhandler_malloc(memhandler, sizeof(sns_ddf_driver_info_s))) == NULL )
      {
        return SNS_DDF_ENOMEM;
      }
      *driver_info_ptr = driver_info_l; /* Is memcopy needed because of strings */
      *(sns_ddf_driver_info_s**)value = driver_info_ptr;
      *num_elems = 1;
      break;

    case SNS_DDF_ATTRIB_DEVICE_INFO:
      if ( (device_info_ptr = sns_ddf_memhandler_malloc(memhandler, sizeof(sns_ddf_device_info_s))) == NULL )
      {
        return SNS_DDF_ENOMEM;
      }
      *device_info_ptr = device_info_l;
      *(sns_ddf_device_info_s**)value = device_info_ptr; /* Is memcopy needed instead? */
      *num_elems = 1;
      break;

     case SNS_DDF_ATTRIB_RANGE:
    {
      sns_ddf_range_s *device_ranges;
      if( (*value = sns_ddf_memhandler_malloc(memhandler,
                      sizeof(sns_ddf_range_s)))  == NULL)
      {
          return SNS_DDF_ENOMEM;
      }
      device_ranges = *value;
      *num_elems = 1;
      device_ranges->min = FX_FLTTOFIX_Q16(0);
      device_ranges->max = FX_FLTTOFIX_Q16(6291);
      break;
    }

    case SNS_DDF_ATTRIB_RESOLUTION_ADC:
    {
      if ( (resp = sns_ddf_memhandler_malloc(memhandler, sizeof(sns_ddf_resolution_adc_s))) == NULL )
      {
        return SNS_DDF_ENOMEM;
      }
      *num_elems = 1;
      resp->bit_len = AL3320B_ALS_BITS;
      resp->max_freq = AL3320B_ALS_FREQ;
      *value = resp;
      break;
    }

    case SNS_DDF_ATTRIB_RESOLUTION:
    {
      sns_ddf_resolution_t* resp;
      if ( (resp = sns_ddf_memhandler_malloc(memhandler, sizeof(sns_ddf_resolution_t))) == NULL )
      {
        return SNS_DDF_ENOMEM;
      }
      DDF_MSG_0(HIGH, "in get_attr resolution");
      *num_elems = 1;

      *resp = AL3320B_DD_ALS_RES;
      *value = resp;
      break;
    }

    case SNS_DDF_ATTRIB_POWER_INFO:
      if ( (power_ptr = sns_ddf_memhandler_malloc(memhandler, sizeof(sns_ddf_power_info_s))) == NULL )
      {
        return SNS_DDF_ENOMEM;
      }
      *num_elems = 1;
      power_ptr->active_current   = AL3320B_DD_ALS_PWR;
      power_ptr->lowpower_current = AL3320B_DD_ALSPRX_LO_PWR;
      *(sns_ddf_power_info_s **)value = power_ptr;
      break;

    case SNS_DDF_ATTRIB_ODR:
      if ( (odr_ptr = sns_ddf_memhandler_malloc(memhandler, sizeof(uint32_t))) == NULL )
      {
        return SNS_DDF_ENOMEM;
      }
      *num_elems = 1;
      *odr_ptr   = state->chip.setup.als.odr;
      *(uint32_t **)value = odr_ptr;
      break;

    case SNS_DDF_ATTRIB_REGISTRY_GROUP:
      reg_group = sns_ddf_memhandler_malloc(memhandler,sizeof(*reg_group));
      if (reg_group == NULL)
      {
        return SNS_DDF_ENOMEM;
      }

      if (state->nv_db_size == 0)
      {
        reg_group->group_data = NULL;
        reg_group->size = 0;
      }
      else
      {
        reg_group_data = sns_ddf_memhandler_malloc(memhandler, state->nv_db_size);
        if (reg_group_data == NULL)
        {
          return SNS_DDF_ENOMEM;
        }
        SNS_OS_MEMCOPY(reg_group_data, &state->sns_dd_alsprx_common_db.nv_db, sizeof(sns_dd_nv_db_type));
        reg_group->group_data = reg_group_data;
        reg_group->size = state->nv_db_size;
      }

      *value = reg_group;
      *num_elems = 1;
      return SNS_DDF_SUCCESS;

      default:
      /* do nothing */
      break;
  }

  return status;
}
