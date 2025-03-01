#ifndef __VSS_ILOG_PRIVATE_IF_H__
#define __VSS_ILOG_PRIVATE_IF_H__

/*
  Copyright (C) 2014 QUALCOMM Technologies, Inc.
  All Rights reserved.
  Qualcomm Technologies, Inc. Confidential and Proprietary.

   $Header: //commercial/MPSS.JO.2.0.c1.4/Main/modem_proc/audio_avs/vsd/inc/private/vss_ilog_private_if.h#1 $
   $Author: mplcsds1 $
*/

/****************************************************************************
 * APIS                                              *
 ****************************************************************************/
 /**
  Command used to perform logging in CVD_CAL_LOGGER thread context.

  @par Payload
  #cvd_cal_log_async_log_t
  
  @return 

  @dependencies
  None.
 
  @comments
  
*/

#include "cvd_cal_log_i.h"

#define CVD_CAL_LOG_CMD_LOG_ASYNC ( 0x0000BEEF )

/** @brief Type definition for #cvd_cal_log_async_log_t.
*/
typedef struct cvd_cal_log_async_log_t cvd_cal_log_async_log_t;

#include "apr_pack_begin.h"

/** @brief Payload structure for the #CVD_CAL_LOG_CMD_LOG_ASYNC command.
*/
struct cvd_cal_log_async_log_t
{
  uint16_t log_code;
  uint32_t log_size;
  void* log_payload;
  cvd_cal_log_cal_container_t container;
}
#include "apr_pack_end.h"
;

#endif /* __VSS_ILOG_PRIVATE_IF_H__ */

