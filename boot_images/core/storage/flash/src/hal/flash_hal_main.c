/*====================================================================
 *
 * FILE: flash_hal_main.c
 *
 * SERVICES: Interface for Flash HAL
 *
 * DESCRIPTION: This file contain interce APIs for Flash HAL
 *
 * PUBLIC CLASSES AND STATIC FUNCTIONS:
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:
 *
 * Copyright (c) 2008-2012, 2015 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  $Header: //components/rel/boot.bf/3.1.2.c3/boot_images/core/storage/flash/src/hal/flash_hal_main.c#1 $ $DateTime: 2015/09/01 00:30:35 $ $Author: pwbldsvc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 01/28/15     sb      Fix Klocwork errors
 * 08/07/12     sv      cleanups
 * 07/27/12     sv      Remove 2x mode codes
 * 02/28/12     sv      Fix Klocwork error
 * 12/14/11     eo      Add optimized transfer steps values
 * 05/18/11     bb      Optimize flash hal
 * 05/18/11     jz      Remove hard-coded address cycles and clock cycle gap
 * 02/16/11     sb      Removing OneNAND support
 * 07/30/10     jz      Added 2X support and call to flash_hal_set_ctlr_mode()
 * 07/30/10     eo      Clear hal_status in predef function API
 * 01/10/10     mm      Support for real two plane program
 * 01/07/10     eo      Add support to reduce flash driver code size
 * 09/25/09     mh      Add flash_hal_link_ctlr_data()
 * 08/11/09     bb      Support for HAL optimized copy API for NAND
 * 07/27/09     jz      Updated to support XMEMC based OneNAND
 * 07/20/09     mh      Add support for setting/getting  ctlr mode of operation
 * 06/14/09     eo      Support for OneNAND HAL optimizations
 * 05/29/09     mh      Use the renamed nandc, sflashc init APIs
 * 04/28/09     bb      Support for HAL optimization with predefined APIs
 * 03/13/09     bb      Add updates to post process list function
 * 03/30/08     bb      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "flash_hal_main.h"
#include "flashi_hal_common.h"

/*====================================================================
 *
 *          S T A T I C   V A R I A B L E   D E F I N I T I O N S
 *
 ====================================================================*/

/* The "HAL Module Versioning" as per the HAL Specification */
#define FLASH_HAL_MAJOR_VER         0x01               /* 8 bits  */
#define FLASH_HAL_MINOR_VER         0x01               /* 8 bits  */
#define FLASH_HAL_BUILD_VER         0x000C             /* 16 bits */
#define FLASH_HAL_VERSION_STRING    "FLASH HAL v1.0.0" /* Version */

/* Mandatory Hal Module Versioning, but this is not used. */
#define FLASH_HAL_VERSION_CODE (( FLASH_HAL_MAJOR_VER << 24)  \
                               | (FLASH_HAL_MINOR_VER << 16)  \
                               | (FLASH_HAL_BUILD_VER << 0))

/* Flash Operation Sequence */
struct flash_hal_cmd_seq flash_hal_op_seq;

/* Flash Devices */
flash_hal_dev_info  flash_hal_devices[FLASH_HAL_DEVICE_MAX];

/* Flash operation list */
struct flash_hal_op_list hal_op_list;


/* ====================================================================
 *
 *        F L A S H   H A L   M A N D A T O R Y   A P I S
 *
 * ==================================================================*/

/*
 * Initializes flash HAL .
 */
void flash_hal_init(char **version)
{
  *version = FLASH_HAL_VERSION_STRING;
}

/*
 * Reset the flash HAL to  default state
 */
void flash_hal_reset(uint32 dev_id)
{
  /* Not implemented */
}

/*
 * Save the hardware status of flash HAL
 */
void flash_hal_save(uint32 dev_id)
{
  /* Not implemented */
}

/*
 * Restore the hardware status of flash HAL
 */
void flash_hal_restore(uint32 dev_id)
{
  /* Not implemented */
}

/* ====================================================================
 *
 *        F L A S H   H A L   C O N F I G U R A T I O N   A P I S
 *
 * ==================================================================*/

/*
 * Initializes flash device client in HAL and assigns a unique logical
 * device ID to it.
 */
void flash_hal_dev_init(const struct flash_hal_dev_config *dev_cfg,
  uint32 *dev_id, enum flash_hal_status *status)
{
  flash_hal_dev_info *dev_info;

  *status = FLASH_HAL_FAIL;
  *dev_id = FLASH_HAL_DEFAULT_DEVICE_ID;

  dev_info = &flash_hal_devices[FLASH_HAL_DEFAULT_DEVICE_ID];
  dev_info->dev_id = FLASH_HAL_DEFAULT_DEVICE_ID;

  /* Initialize the NAND controller */
  hal_nandc_init(dev_cfg, dev_info, status);
}

/*
 * De-Initializes flash device client in HAL.
 */
void flash_hal_dev_deinit(uint32 dev_id)
{
  if (FLASH_HAL_DEVICE_MAX > dev_id)
  {
    flash_hal_devices[dev_id].ctlr_ops.flash_hal_close(
      &flash_hal_devices[dev_id]);
    hal_nandc_deinit(&flash_hal_devices[dev_id]);
  }
}

/*
 * Sets hardware ECC coverage state in flash HAL.
 */
void flash_hal_set_ecc_state(uint32 dev_id,
  enum flash_hal_ecc_state ecc_state)
{
  flash_hal_devices[dev_id].config.ecc_state = ecc_state;
  flash_hal_devices[dev_id].config.config_is_needed = TRUE;
}


/*
 * Sets hardware ECC length to be used with the flash device.
 */
void flash_hal_set_ecc_length(uint32 dev_id,
  enum flash_hal_ecc_length ecc_len_bits)
{
  flash_hal_devices[dev_id].config.ecc_len_bits = ecc_len_bits;
  flash_hal_devices[dev_id].config.config_is_needed = TRUE;
}

/*
 * Sets page size of the underlying flash device in flash HAL.
 */
void flash_hal_set_page_size(uint32 dev_id,
  enum flash_hal_page_size page_size_bytes)
{
  flash_hal_devices[dev_id].config.page_size_bytes = page_size_bytes;
  flash_hal_devices[dev_id].config.config_is_needed = TRUE;
}

/*
 * Sets spare size (if applicable) of the underlying flash device in flash HAL.
 */
void flash_hal_set_spare_size(uint32 dev_id,
  enum flash_hal_spare_size spare_size_bytes)
{
  flash_hal_devices[dev_id].config.spare_size_bytes = spare_size_bytes;
  flash_hal_devices[dev_id].config.config_is_needed = TRUE;
}

/*
 * Sets device access width in flash HAL.
 */
void flash_hal_set_dev_width(uint32 dev_id, enum flash_hal_dev_width width)
{
  flash_hal_devices[dev_id].config.width = width;
  flash_hal_devices[dev_id].config.config_is_needed = TRUE;
}

/*
 * Sets number of address cycles of the device in flash HAL.
 */
void flash_hal_set_address_cycles(uint32 dev_id,
  uint32 row_count, uint32 col_count)
{
  flash_hal_devices[dev_id].config.row_count = row_count;
  flash_hal_devices[dev_id].config.col_count = col_count;
}

/*
 * Sets the gap in the number of clock cycles
 * between a read/write command to when BSY goes active low
 * for the device in flash HAL.
 */
void flash_hal_set_clk_cycle_gap(uint32 dev_id,
  uint32 clk_rate_mhz, uint32 wb_ns)
{
  /* Formula: EVEN( Roundup(max(tRB, tWB)/T) - 2)/2
   * gap is a zero-based value:
   * 0x0: 2 clock cycle gap
   * 0x1: 4 clock cycle gap
   * 0x2: 6 clock cycle gap
   * ...
   * 0x3F: 128 clock cycle gap
   */
  uint32 gap = clk_rate_mhz * wb_ns * 0.001 + 0.9;
  gap = (((gap + 1) & 0xFE) - 2) >> 1;

  /* Call the config specific HAL function to set clock cycle gap */
  if (flash_hal_devices[dev_id].ctlr_ops.flash_hal_set_clk_cycle_gap != NULL)
  {
    flash_hal_devices[dev_id].ctlr_ops.flash_hal_set_clk_cycle_gap(gap);
  }
}

/* ====================================================================
 *
 *          F L A S H   H A L   C A P A B I L I T Y   A P I S
 *
 * ==================================================================*/

/*
 * Returns page layout configured by flash HAL.
 */
void flash_hal_get_page_layout(uint32 dev_id,
  struct flash_hal_page_layout **layout)
{
  flash_hal_devices[dev_id].ctlr_ops.flash_hal_get_page_layout(
    &flash_hal_devices[dev_id].config, layout);
}

/* ====================================================================
 *
 *   F L A S H   H A L   O P E R A T I O N   C O M M O N   A P I S
 *
 * ==================================================================*/

/*
 * Indicates beginning of a flash HAL operation.
 */
void flash_hal_begin_op(uint32 dev_id, void *ws_buffer,
  uint32 ws_buf_len_bytes)
{
  /* Clear the HAL status */
  hal_status = FLASH_HAL_NO_ERROR;

  /* Initialize HAL workspace buffer */
  flash_hal_init_ws_buffer(ws_buffer, ws_buf_len_bytes);

  flash_hal_devices[dev_id].ctlr_ops.flash_hal_begin_op(
    &flash_hal_devices[dev_id].config, ws_buffer, ws_buf_len_bytes);
}

/*
 * Indicates end of a flash HAL operation.
 */
void flash_hal_end_op(uint32 dev_id)
{
  flash_hal_devices[dev_id].ctlr_ops.flash_hal_end_op(
    &flash_hal_devices[dev_id].config);
}

/*
 * This API returns the list of hardware read/write operations to the
 * caller (driver), according to the driver requested operation.
 * The returned set may be used to generate DM sequence to perform the
 * flash operation.
 *
 */
void flash_hal_get_op_list(uint32 dev_id, struct flash_hal_op_list **op_list,
  enum flash_hal_status *status)
{
  if (FLASH_HAL_DMA_ENABLE != hal_dma_state)
  {
    *status = FLASH_HAL_FAIL;
  }
  else
  {
    flash_hal_dev_info  *dev_info;

    dev_info = &flash_hal_devices[dev_id];

    /* Check for any previous HAL errors, if error return */
    *status = (FLASH_HAL_NO_ERROR != hal_status) ?
      FLASH_HAL_FAIL : FLASH_HAL_SUCCESS;

    /* Do configure, if anything to configure */
    if ((TRUE == dev_info->config.config_is_needed) &&
        (FLASH_HAL_SUCCESS == *status))
    {
      dev_info->ctlr_ops.flash_hal_configure(&flash_hal_devices[dev_id].config,
        status);
    }

    /* Execute the sequence. If the dm state is enabled in HAL,
       flash_hal_transfer generates a list of register writes
       and reads instead of actual reads and writes */
    if ((dev_info->config.seq_cnt > 0) && (FLASH_HAL_SUCCESS == *status))
    {
      dev_info->ctlr_ops.flash_hal_transfer(&flash_hal_devices[dev_id].config,
        &flash_hal_op_seq, status);
    }

    /* Return the list generated during transfer */
    if (FLASH_HAL_SUCCESS == *status)
    {
      hal_op_list.op_list_count = ws_buffer_info.op_list_cnt;
      hal_op_list.op_list = &ws_buffer_info.op_list[0];
      hal_op_list.pp_list_count = ws_buffer_info.post_list_cnt;
      hal_op_list.pp_list = &ws_buffer_info.post_list[0];

      *op_list = &hal_op_list;
    }
  }
}

/*
 * Post processes operation list after data mover processing.
 */
void flash_hal_post_process_op_list(uint32 dev_id,
  struct flash_hal_op_list *op_list, enum flash_hal_status *status)
{
  flash_hal_dev_info  *dev_info;

  dev_info = &flash_hal_devices[dev_id];

  dev_info->ctlr_ops.flash_hal_post_process_op_list(&dev_info->config,
    op_list, status);
}

/*
 * Execute the flash operation when not using data mover.
 */
void flash_hal_exec_op(uint32 dev_id, enum flash_hal_status *status)
{
  flash_hal_dev_info  *dev_info;

  dev_info = &flash_hal_devices[dev_id];

  /* Check for any previous HAL errors, if error return */
  *status = (FLASH_HAL_NO_ERROR != hal_status) ?
    FLASH_HAL_FAIL : FLASH_HAL_SUCCESS;

  /* Do configure, if anything to configure */
  if ((TRUE == dev_info->config.config_is_needed) &&
      (FLASH_HAL_SUCCESS == *status))
  {
    dev_info->ctlr_ops.flash_hal_configure(&flash_hal_devices[dev_id].config,
      status);
  }

  if ((dev_info->config.seq_cnt > 0) && (FLASH_HAL_SUCCESS == *status))
  {
    dev_info->ctlr_ops.flash_hal_transfer(&flash_hal_devices[dev_id].config,
      &flash_hal_op_seq, status);
  }
}

/*
 * Returns memory required by the predefined APIs
 *
 */
void flash_hal_get_predef_mem_usage (uint32 dev_id, uint32 no_of_pages,
  uint32 *mem_use)
{
  flash_hal_dev_info  *dev_info;

  dev_info = &flash_hal_devices[dev_id];

  dev_info->ctlr_ops.flash_hal_get_predef_mem_usage(
    &flash_hal_devices[dev_id].config, no_of_pages, mem_use);
}

/*
 * Initialize pre-defined sequences support
 */
void flash_hal_predef_init(uint32 dev_id, struct flash_hal_predef_init_data
  *init_data, uint32 *used_buff_size, enum flash_hal_status *status)
{
  flash_hal_dev_info  *dev_info;

  dev_info = &flash_hal_devices[dev_id];

  dev_info->ctlr_ops.flash_hal_predef_init(dev_info,
      init_data, used_buff_size, status);
}

/*
 * Optimized flash HAL read ID
 */
void flash_hal_read_id(uint32 dev_id, struct flash_hal_buffer_desc
  *buff_desc, struct flash_hal_predef_op_list **op_list, enum flash_hal_status
  *status)
{
  flash_hal_dev_info  *dev_info;

  hal_status = FLASH_HAL_NO_ERROR;

  dev_info = &flash_hal_devices[dev_id];

  dev_info->ctlr_ops.flash_hal_read_id(dev_info, buff_desc, op_list, status);
}

/*
 * Optimized flash HAL ONFI ID read
 */
void flash_hal_read_onfi_id(uint32 dev_id, struct flash_hal_predef_onfi_data
  *probe_data, struct flash_hal_predef_op_list **op_list, enum flash_hal_status
  *status)
{
  flash_hal_dev_info  *dev_info;

  hal_status = FLASH_HAL_NO_ERROR;

  dev_info = &flash_hal_devices[dev_id];

  dev_info->ctlr_ops.flash_hal_read_onfi_id(dev_info, probe_data, op_list, status);
}

/*
 * Optimized flash HAL read parameter page
 */
void flash_hal_read_param_page(uint32 dev_id, struct flash_hal_predef_onfi_data
  *page_data, struct flash_hal_predef_op_list **op_list, enum flash_hal_status
  *status)
{
  flash_hal_dev_info  *dev_info;

  hal_status = FLASH_HAL_NO_ERROR;

  dev_info = &flash_hal_devices[dev_id];

  dev_info->ctlr_ops.flash_hal_read_param_page(dev_info, page_data,
    op_list, status);
}

/*
 * Optimized flash HAL read page
 */
void flash_hal_read_page(uint32 dev_id, struct flash_hal_predef_page_data
  *page_data, struct flash_hal_predef_op_list **op_list, enum flash_hal_status
  *status)
{
  flash_hal_dev_info  *dev_info;

  hal_status = FLASH_HAL_NO_ERROR;

  dev_info = &flash_hal_devices[dev_id];

  dev_info->ctlr_ops.flash_hal_read_page(dev_info,
    page_data, op_list, status);
}


/*
 * Optimized flash HAL read bad block marker
 */
void flash_hal_read_bb_marker(uint32 dev_id, struct
  flash_hal_predef_spare_data *page_data, struct flash_hal_predef_op_list
  **op_list, enum flash_hal_status *status)
{
  flash_hal_dev_info  *dev_info;

  hal_status = FLASH_HAL_NO_ERROR;

  dev_info = &flash_hal_devices[dev_id];
  dev_info->ctlr_ops.flash_hal_read_bb_marker(dev_info,
    page_data, op_list, status);
}

/*
 * Optimized flash HAL write page
 */
void flash_hal_write_page(uint32 dev_id, struct flash_hal_predef_page_data
  *page_data, struct flash_hal_predef_op_list **op_list, enum flash_hal_status
  *status)
{
  flash_hal_dev_info  *dev_info;

  hal_status = FLASH_HAL_NO_ERROR;

  dev_info = &flash_hal_devices[dev_id];
  dev_info->ctlr_ops.flash_hal_write_page(dev_info,
    page_data, op_list, status);
}

/*
 * Optimized flash HAL erase block
 */
void flash_hal_erase_block(uint32 dev_id, struct flash_hal_predef_block_data
  *block_data, struct flash_hal_predef_op_list **op_list, enum flash_hal_status
  *status)
{
  flash_hal_dev_info  *dev_info;

  hal_status = FLASH_HAL_NO_ERROR;

  dev_info = &flash_hal_devices[dev_id];
  dev_info->ctlr_ops.flash_hal_erase_block(dev_info,
    block_data, op_list, status);
}

/*
 * Flash HAL set transfer steps config data
 */
void flash_hal_set_xfer_cfg(uint32 dev_id,
  struct flash_hal_xfer_cfg *cfg_data,
  enum flash_hal_status *status)
{
  flash_hal_dev_info  *dev_info;

  hal_status = FLASH_HAL_NO_ERROR;

  dev_info = &flash_hal_devices[dev_id];

  /* If the API is not defined, return failure. */
  if (NULL == dev_info->ctlr_ops.flash_hal_set_xfer_cfg)
  {
    *status = FLASH_HAL_OP_NOT_SUPPORTED;
  }
  else
  {
    dev_info->ctlr_ops.flash_hal_set_xfer_cfg(dev_info,
      cfg_data, status);
  }
}

