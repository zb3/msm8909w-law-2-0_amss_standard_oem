#ifndef __VSS_COMMON_DEPRECATED_PUBLIC_IF_H__
#define __VSS_COMMON_DEPRECATED_PUBLIC_IF_H__

/**
  @file vss_common_deprecated_public_if.h
  @brief This file contains the APR API definitions that are common among
  modules.
*/

/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      CVD_mainpage.dox file. Contact Tech Pubs for assistance.
=============================================================================*/
/*===========================================================================
Copyright (c) 2012-2015 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

  $Header: //commercial/MPSS.JO.2.0.c1.4/Main/modem_proc/avs/api/cvd/vss_common_deprecated_public_if.h#1 $
  $Author: mplcsds1 $

when        who    what, where, why
-------     ---    ----------------------------------------------------------
04/29/15    aim    (CVD) Updated with deprecated G711 media ID's.
08/27/14     sw    (Tech Pubs) Updated with Doxygen comments from 2.0.

===========================================================================*/

#include "apr_comdef.h"
#include "vss_common_public_if.h"

/** @addtogroup cvd_common_deprecated
@{ */

/*--------------------------------------------------------------------------*
 * NETWORK DEFINITIONS                                                      *
 *--------------------------------------------------------------------------*/
/** @name Network IDs
    @xreflabel{hdr:DeprecatedNetworkIDs}
@{ */

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_NONE. \n
  Default network ID. */
#define VSS_NETWORK_ID_DEFAULT ( 0x00010037 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_CDMA. \n
  CDMA narrowband network ID. */
#define VSS_NETWORK_ID_CDMA_NB ( 0x00010021 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_CDMA. \n
  CDMA wideband network ID. */
#define VSS_NETWORK_ID_CDMA_WB ( 0x00010022 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_CDMA. \n
  CDMA WideVoice network ID. */
#define VSS_NETWORK_ID_CDMA_WV ( 0x00011100 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_GSM. \n
  GSM narrowband network ID. */
#define VSS_NETWORK_ID_GSM_NB ( 0x00010023 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_GSM. \n
  GSM wideband network ID. */
#define VSS_NETWORK_ID_GSM_WB ( 0x00010024 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_GSM. \n
  GSM WideVoice network ID. */
#define VSS_NETWORK_ID_GSM_WV ( 0x00011101 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_WCDMA. \n
  WCDMA narrowband network ID. */
#define VSS_NETWORK_ID_WCDMA_NB ( 0x00010025 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_WCDMA. \n
  WCDMA wideband network ID. */
#define VSS_NETWORK_ID_WCDMA_WB ( 0x00010026 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_WCDMA. \n
  WCDMA WideVoice network ID. */
#define VSS_NETWORK_ID_WCDMA_WV ( 0x00011102 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_VOIP. \n
  VoIP narrowband network ID. */
#define VSS_NETWORK_ID_VOIP_NB ( 0x00011240 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_VOIP. \n
  VoIP wideband network ID. */
#define VSS_NETWORK_ID_VOIP_WB ( 0x00011241 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_VOIP. \n
  VoIP WideVoice network ID. */
#define VSS_NETWORK_ID_VOIP_WV ( 0x00011242 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_LTE. \n
  LTE narrowband network ID. */
#define VSS_NETWORK_ID_LTE_NB ( 0x00011324 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_LTE. \n
  LTE wideband network ID. */
#define VSS_NETWORK_ID_LTE_WB ( 0x00011325 )

/** Deprecated. Use #VSS_ICOMMON_CAL_NETWORK_ID_LTE. \n
  LTE WideVoice network ID. */
#define VSS_NETWORK_ID_LTE_WV ( 0x00011326 )

/** @} */ /* end_name_group Network IDs */

/*--------------------------------------------------------------------------*
 * MEDIA TYPE DEFINITIONS                                                   *
 *--------------------------------------------------------------------------*/
/** @name Media type IDs
@{ */

/** @cond OEM_only */
/** Deprecated. Use #VSS_MEDIA_ID_13K. \n
  CDMA variable 13K vocoder format. */
#define VSS_MEDIA_ID_13K_MODEM ( 0x00010FC1 )

/** Deprecated. Use #VSS_MEDIA_ID_EVRC. \n
  CDMA Enhanced Variable Rate Vocoder (EVRC) format. */
#define VSS_MEDIA_ID_EVRC_MODEM ( 0x00010FC2 )

/** Deprecated. Use #VSS_MEDIA_ID_4GV_NB. \n
  CDMA 4th generation NB vocoder format. */
#define VSS_MEDIA_ID_4GV_NB_MODEM ( 0x00010FC3 )

/** Deprecated. Use #VSS_MEDIA_ID_4GV_WB. \n
  CDMA 4th generation WB vocoder format. */
#define VSS_MEDIA_ID_4GV_WB_MODEM ( 0x00010FC4 )

/** Deprecated. Use #VSS_MEDIA_ID_4GV_NW. \n
  CDMA 4th generation Narrow-Wide (NW) vocoder format. */
#define VSS_MEDIA_ID_4GV_NW_MODEM ( 0x00010FC5 )

/** Deprecated. Use #VSS_MEDIA_ID_AMR_NB. \n
  Universal Mobile Telecommunications System (UMTS) AMR-NB vocoder. */
#define VSS_MEDIA_ID_AMR_NB_MODEM ( 0x00010FC6 )

/** Deprecated. Use #VSS_MEDIA_ID_AMR_WB. \n
  UMTS AMR-WB vocoder format. */
#define VSS_MEDIA_ID_AMR_WB_MODEM ( 0x00010FC7 )

/** Deprecated. Use #VSS_MEDIA_ID_EFR. \n
  GSM enhanced full rate vocoder format. */
#define VSS_MEDIA_ID_EFR_MODEM ( 0x00010FC8 )

/** Deprecated. Use #VSS_MEDIA_ID_FR. \n
  GSM full rate vocoder format. */
#define VSS_MEDIA_ID_FR_MODEM ( 0x00010FC9 )

/** Deprecated. Use #VSS_MEDIA_ID_HR. \n
  GSM half rate vocoder format. */
#define VSS_MEDIA_ID_HR_MODEM ( 0x00010FCA )
/** @endcond */

/** Deprecated. Use #VSS_MEDIA_ID_PCM_8_KHZ. \n
  Linear PCM vocoder modem format; mono, 16 bits, little endian, 8 kHz. */
#define VSS_MEDIA_ID_PCM_NB ( 0x00010FCB )

/** Deprecated. Use #VSS_MEDIA_ID_PCM_16_KHZ. \n
  Linear PCM vocoder modem format; mono, 16 bits, little endian, 16 kHz.
  @if ISV_only @newpage @endif */
#define VSS_MEDIA_ID_PCM_WB ( 0x00010FCC )

/** Deprecated. Use #VSS_MEDIA_ID_G711_ALAW_V2. \n
 	G.711 a-law vocoder format; contains two 10 ms vocoder frames. */
#define VSS_MEDIA_ID_G711_ALAW ( 0x00010FCD )

/** Deprecated. Use #VSS_MEDIA_ID_G711_MULAW_V2. \n
	G.711 mu-law vocoder format; contains two 10 ms vocoder frames. */
#define VSS_MEDIA_ID_G711_MULAW ( 0x00010FCE )

/** Deprecated. G.711 linear PCM vocoder is not supported. 
  G.711 linear PCM vocoder format. */
#define VSS_MEDIA_ID_G711_LINEAR ( 0x00010FCF )

/** @} */ /* end_name_group Deprecated Media Type IDs */


/****************************************************************************
 * CALIBRATION FRAMEWORK DEFINITIONS                                        *
 ****************************************************************************/

/*--------------------------------------------------------------------------*
 * CALIBRATION COLUMN IDS                                                   *
 *--------------------------------------------------------------------------*/

/** @name Calibration column IDs
@{ */

/** Deprecated. Use #VSS_ICOMMON_CAL_COLUMN_VOLUME_INDEX. \n
  Column volume index. */
#define VSS_ICOMMON_CAL_COLUMN_VOLUME_INDEX ( 0x00011358 )

/** Deprecated. Use #VSS_ICOMMON_CAL_COLUMN_RX_SAMPLING_RATE. \n
  Column Rx sampling rate. */
#define VSS_ICOMMON_CAL_COLUMN_RX_SAMPLING_RATE ( 0x00011351 )

/** Deprecated. Use #VSS_ICOMMON_CAL_COLUMN_TX_SAMPLING_RATE. \n
  Column Tx sampling rate. @newpage */
#define VSS_ICOMMON_CAL_COLUMN_TX_SAMPLING_RATE ( 0x00011352 )

/** @} */ /* end_name_group Calibration column IDs */


/****************************************************************************
 * NETWORK SYSTEM APIS                                                      *
 ****************************************************************************/

/** @name Network system
@{ */
/** Deprecated. Use #VSS_IMVM_CMD_SET_CAL_NETWORK.

  Sets the network type.

  @apr_msgpayload{vss_icommon_cmd_set_network_t}
  @wktable{weak__vss__icommon__cmd__set__network__t}

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None. @newpage
*/
#define VSS_ICOMMON_CMD_SET_NETWORK ( 0x0001119C )               
/** @} */ /* end_name Deprecated commands */

/* Type definition for vss_icommon_cmd_set_network_t. */
typedef struct vss_icommon_cmd_set_network_t vss_icommon_cmd_set_network_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_icommon_cmd_set_network_t 
@{ */
/* Payload of the the #VSS_ICOMMON_CMD_SET_NETWORK command.
*/
struct vss_icommon_cmd_set_network_t
{
  uint32_t network_id;
  /**< Network ID.

       @values See @xhyperref{hdr:DeprecatedNetworkIDs,Deprecated Network IDs} */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup vss_icommon_cmd_set_network_t */

/** @} */ /* end_name Network system */

/****************************************************************************
 * VOICE TIMING APIS                                                        *
 ****************************************************************************/
/** @name Voice timing
@{ */

/** Deprecated. Use #VSS_ICOMMON_CMD_SET_VOICE_TIMING_V2. 

  Sets the voice timing parameters. 
   
  @apr_msgpayload{vss_icommon_cmd_set_voice_timing_t}
  @wktable{weak__vss__icommon__cmd__set__voice__timing__t}

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None.
*/
#define VSS_ICOMMON_CMD_SET_VOICE_TIMING ( 0x000111E0 )
/** @} */ /* end_name Deprecated commands */

/* Type definition for vss_icommon_cmd_set_voice_timing_t. */
typedef struct vss_icommon_cmd_set_voice_timing_t vss_icommon_cmd_set_voice_timing_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_icommon_cmd_set_voice_timing_t 
@{ */
/* Payload structure for the VSS_ICOMMON_CMD_SET_VOICE_TIMING command.
*/
struct vss_icommon_cmd_set_voice_timing_t
{
  uint16_t mode;
  /**< Vocoder frame synchronization mode.
    
       @values
       - 0 -- No frame synchronization
       - 1 -- Hard VFR; a 20 ms VFR interrupt @tablebulletend */

  uint16_t enc_offset;
    /**< Offset in microseconds from the VFR to deliver a Tx vocoder
       packet.

       @values < 20000 microseconds. */

  uint16_t dec_req_offset;
  /**< Offset in microseconds from the VFR to request for an Rx vocoder
       packet.

       @values < 20000 microseconds. */

  uint16_t dec_offset;
  /**< Offset in microseconds from the VFR to indicate the deadline to
       receive a Rx vocoder packet.

       @values < 20000 microseconds.

       Rx vocoder packets received after this deadline are not guaranteed to
       be processed.  */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup weak_vss_icommon_cmd_set_voice_timing_t  */
/** @} */ /* end_name Voice timing */
/** @} */ /* end_addtogroup cvd_common_deprecated */


#endif /* __VSS_COMMON_DEPRECATED_PUBLIC_IF_H__ */

