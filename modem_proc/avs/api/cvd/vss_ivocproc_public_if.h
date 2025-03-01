#ifndef __VSS_IVOCPROC_PUBLIC_IF_H__
#define __VSS_IVOCPROC_PUBLIC_IF_H__

/**
  @file vss_ivocproc_public_if.h
  @brief This file contains the APR API definitions for Core VocProc (CVP)
  module.
*/

/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      CVD_mainpage.dox file. Contact Tech Pubs for assistance.
=============================================================================*/
/*===========================================================================
Copyright (c) 2011, 2014 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

  $Header: //commercial/MPSS.JO.2.0.c1.4/Main/modem_proc/avs/api/cvd/vss_ivocproc_public_if.h#1 $
  $Author: mplcsds1 $

when        who    what, where, why
-------     ---    ----------------------------------------------------------
08/28/14    sw     (Tech Pubs) Updated with Doxygen comments from 2.0 and 2.4,
                   and edited comments for 2.6.

===========================================================================*/

#include "apr_comdef.h"

/** @addtogroup cvd_cvp_constants_macros 
@{ */

/****************************************************************************
 * VOCPROC DEFINES                                                          *
 ****************************************************************************/

/*---------------------------------------------------------------------------*
 * Vocproc Directions                                                        *
 *---------------------------------------------------------------------------*/

/** Direction is the Rx path only. */
#define VSS_IVOCPROC_DIRECTION_RX ( 0 )

/** Direction is the Tx path only. */
#define VSS_IVOCPROC_DIRECTION_TX ( 1 )

/** Direction is both the Rx and Tx paths. */
#define VSS_IVOCPROC_DIRECTION_RX_TX ( 2 )

/*--------------------------------------------------------------------------*
 * Vocproc Modes                                                            *
 *--------------------------------------------------------------------------*/

/** Mode is internal mixing.

  This mode selects an internal audio stream reference source to prevent the
  local audio playback from being transmitted to the far end.

  Indicates that the far-end reference for echo cancellation is composed by
  mixing audio and voice inside the aDSP.
*/
#define VSS_IVOCPROC_VOCPROC_MODE_EC_INT_MIXING ( 0x00010F7C )

/** Mode is external mixing.

  Indicates that the far-end reference for echo cancellation is composed by
  mixing audio and voice outside the aDSP.
 */
#define VSS_IVOCPROC_VOCPROC_MODE_EC_EXT_MIXING ( 0x00010F7D )

/*--------------------------------------------------------------------------*
 * AFE PORTS                                                                *
 *--------------------------------------------------------------------------*/

/** Default AFE port ID. This ID is applicable on both Tx and Rx paths. */
#define VSS_IVOCPROC_PORT_ID_NONE ( 0xFFFF )

/** @} */ /* end_addtogroup cvd_cvp_constants_macros */

/*--------------------------------------------------------------------------*
 * VOCPROC TOPOLOGIES                                                       *
 *--------------------------------------------------------------------------*/
/** @addtogroup cvd_cvp_topologies
@{ */

/** Pass-through topology ID. This ID is applicable to both Rx and Tx. */
#define VSS_IVOCPROC_TOPOLOGY_ID_NONE ( 0x00010F70 )

/** @cond OEM_only */
/** Tx topology ID for single-mic echo cancellation noise suppression. */
#define VSS_IVOCPROC_TOPOLOGY_ID_TX_SM_ECNS ( 0x00010F71 )

/** Tx topology ID for dual-mic Fluence@tm. */
#define VSS_IVOCPROC_TOPOLOGY_ID_TX_DM_FLUENCE ( 0x00010F72 )

/** Tx topology ID for single-mic Fluence V5. */
#define VSS_IVOCPROC_TOPOLOGY_ID_TX_SM_FLUENCEV5 ( 0x00010F73 )

/** Tx topology ID for dual-mic Fluence V5. */
#define VSS_IVOCPROC_TOPOLOGY_ID_TX_DM_FLUENCEV5 ( 0x00010F74 )

/** Tx topology ID for dual-mic Fluence V5 broadside speakerphone. */
#define VSS_IVOCPROC_TOPOLOGY_ID_TX_DM_FLUENCEV5_BROADSIDE ( 0x00010F88 )

/** Tx topology ID for quad-mic Fluence Pro. */
#define VSS_IVOCPROC_TOPOLOGY_ID_TX_QM_FLUENCE_PRO ( 0x00010F75 )

/** Tx topology ID for quad-mic Fluence Pro V2. */
#define VSS_IVOCPROC_TOPOLOGY_ID_TX_QM_FLUENCE_PROV2 ( 0x00010F87 )

/** Tx topology ID for dual-mic Snapdragon@tm Voice Plus ECNS. */
#define VSS_IVOCPROC_TOPOLOGY_ID_TX_DM_VPECNS ( 0x00010F86 )
/** @endcond */

/** Topology ID for utilizing dynamically loadable voice modules in the shared
  object voiceproc_tx.so.
  This topology must be used by modules that operate on the uplink device path.

  The supported media type is defined by the following:
   - The input and output of this topology must be signed 16-bit mono.
   - The reference signal is signed 16-bit mono.
   - Both near and far-end inputs use the same sampling rate.
*/
#define VSS_IVOCPROC_TX_SINGLE_MIC_DYNAMIC_TOPOLOGY (0x00010F83)

/** Topology ID for utilizing dynamically loadable voice modules in the shared
  object, voiceproc_tx.so.
  This topology must be used by modules that operate on the uplink device path.

  The media type supported is defined by the following:
   - The input and output of this topology must be signed 16-bit. 
   - The supported input number of channels is stereo (2), and the output
     must be mono.
   - The reference signal is signed 16-bit mono.
   - Both near and far-end inputs use the same sampling rate.
*/
#define VSS_IVOCPROC_TX_DUAL_MIC_DYNAMIC_TOPOLOGY (0x00010F84)

/** Topology ID for utilizing dynamically loadable voice modules in the shared
  object voiceproc_tx.so.
  This topology must be used by modules that operate on the uplink device path.

  The media type supported is defined by the following:
   - The input and output of this topology must be signed 16-bit. 
   - The input number of channels supported is quad (4), and the output
     must be mono.
   - The reference signal is signed 16-bit mono.
   - Both near and far-end inputs use the same sampling rate.
*/
#define VSS_IVOCPROC_TX_QUAD_MIC_DYNAMIC_TOPOLOGY (0x00010F85)

/** Default Rx topology ID for Rx processing with all available algorithms. */
#define VSS_IVOCPROC_TOPOLOGY_ID_RX_DEFAULT ( 0x00010F77 )

/** Topology ID for utilizing dynamically loadable voice modules in the shared
  object voiceproc_rx.so. 
  This topology must be used by modules that operate on the downlink device
  path.

  The input and output of this topology must be signed 16-bit mono.
*/
#define VSS_IVOCPROC_RX_DYNAMIC_TOPOLOGY (0x00010F82)

/** @} */ /* end_addtogroup cvd_cvp_topologies */

/****************************************************************************
 * CORE VOCPROC APIS                                                        *
 ****************************************************************************/

/** @ingroup cvd_cvp_cmd_create_full_ctrl_sess
  Creates a new full control vocproc session.

  @apr_msgpayload{vss_ivocproc_cmd_create_full_control_session_v2_t}
  @wktable{weak__vss__ivocproc__cmd__create__full__control__session__v2__t}

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None.
*/ /* Q2 = Async Packet Router API for MDM9x15 Interface Spec (80-N1463-2)
*/
#define VSS_IVOCPROC_CMD_CREATE_FULL_CONTROL_SESSION_V2 ( 0x000112BF )

/* Type definition for vss_ivocproc_cmd_create_full_control_session_v2_t. */
typedef struct vss_ivocproc_cmd_create_full_control_session_v2_t vss_ivocproc_cmd_create_full_control_session_v2_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_ivocproc_cmd_create_full_control_session_v2_t 
@{ */
/* Payload of the VSS_IVOCPROC_CMD_CREATE_FULL_CONTROL_SESSION_V2 command.
*/
struct vss_ivocproc_cmd_create_full_control_session_v2_t
{
  uint16_t direction;
  /**< Specifies the path on which the session is created.
    
       @values
       - #VSS_IVOCPROC_DIRECTION_RX
       - #VSS_IVOCPROC_DIRECTION_TX
       - #VSS_IVOCPROC_DIRECTION_RX_TX @tablebulletend */

  uint16_t tx_port_id;
    /**< Tx device port ID to which the vocproc connects.

         @values If a port ID is not supplied, set this field to
                 #VSS_IVOCPROC_PORT_ID_NONE */

  uint32_t tx_topology_id;
  /**< Tx topology IDs that identify the predefined algorithms required for
       the session.

  @if OEM_only
       @values
       - #VSS_IVOCPROC_TOPOLOGY_ID_TX_SM_ECNS
       - #VSS_IVOCPROC_TOPOLOGY_ID_TX_DM_FLUENCE
       - If a topology ID is not supplied, set this field to
         #VSS_IVOCPROC_TOPOLOGY_ID_NONE @tablebulletend  @endif

  @if ISV_only
       @values If a topology ID is not supplied, set this field to
         #VSS_IVOCPROC_TOPOLOGY_ID_NONE @endif */

  uint16_t rx_port_id;
  /**< Rx device port ID to which the vocproc connects.

       @values If a port ID is not supplied, set this field to
               #VSS_IVOCPROC_PORT_ID_NONE */

  uint32_t rx_topology_id;
  /**< Rx topology IDs that identify the predefined algorithms required for
       the session.

       @values
       - #VSS_IVOCPROC_TOPOLOGY_ID_RX_DEFAULT
       - If a topology ID is not supplied, set this field to
         #VSS_IVOCPROC_TOPOLOGY_ID_NONE @tablebulletend */

  uint32_t profile_id;
    /**< Voice calibration profile ID. */

  uint32_t vocproc_mode;
  /**< Specifies whether the vocproc mode is set to internal or external
       mixing.
    
       @values
       - #VSS_IVOCPROC_VOCPROC_MODE_EC_INT_MIXING
       - #VSS_IVOCPROC_VOCPROC_MODE_EC_EXT_MIXING @tablebulletend */

  uint16_t ec_ref_port_id;
  /**< Port ID to which the vocproc connects for receiving echo cancellation
       reference signal.

       @values If a port ID is not supplied, set this field to
               #VSS_IVOCPROC_PORT_ID_NONE

       This value is ignored when the vocproc_mode parameter is set to
         #VSS_IVOCPROC_VOCPROC_MODE_EC_INT_MIXING. */

#if __STDC_VERSION__ >= 199901L
  char_t session_name[];
  /**< Session name string used to identify a session that can be shared with
       passive controllers (optional).

       The string size, including the NULL termination character, is limited
       to 31 characters. */
#endif /* __STDC_VERSION__ >= 199901L */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup vss_ivocproc_cmd_create_full_control_session_v2_t */

/** @ingroup cvd_cvp_cmd_set_device
  Sets a new voice device configuration on the vocproc.

  @apr_msgpayload{vss_ivocproc_cmd_set_device_v2_t}
  @wktable{weak__vss__ivocproc__cmd__set__device__v2__t} @newpage

  @detdesc
  The configuration provided must match the direction of the vocproc. For
  example, when a vocproc is created as a Tx only direction, the Rx
  parameters are ignored.

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None.
*/
#define VSS_IVOCPROC_CMD_SET_DEVICE_V2 ( 0x000112C6 )

/* Type definition for vss_ivocproc_cmd_set_device_v2_t. */
typedef struct vss_ivocproc_cmd_set_device_v2_t vss_ivocproc_cmd_set_device_v2_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_ivocproc_cmd_set_device_v2_t 
@{ */
/* Payload of the VSS_IVOCPROC_CMD_SET_DEVICE_V2 command.
*/
struct vss_ivocproc_cmd_set_device_v2_t
{
  uint16_t tx_port_id;
  /**< Tx device port ID to which the vocproc connects.

       @values If a port ID is not supplied, set this field to
               #VSS_IVOCPROC_PORT_ID_NONE */

  uint32_t tx_topology_id;
  /**< Tx topology IDs that identify the predefined algorithms required for
       the session.

  @if OEM_only
       @values
       - #VSS_IVOCPROC_TOPOLOGY_ID_TX_SM_ECNS
       - #VSS_IVOCPROC_TOPOLOGY_ID_TX_DM_FLUENCE
       - If a topology ID is not supplied, set this field to
         #VSS_IVOCPROC_TOPOLOGY_ID_NONE @tablebulletend  @endif

  @if ISV_only
       @values If a topology ID is not supplied, set this field to
         #VSS_IVOCPROC_TOPOLOGY_ID_NONE @endif */

  uint16_t rx_port_id;
  /**< Rx device port ID to which the vocproc connects.

       @values If a port ID is not supplied, set this field to
               #VSS_IVOCPROC_PORT_ID_NONE */

  uint32_t rx_topology_id;
  /**< Rx topology IDs that identify the predefined algorithms required for
       the session.

       @values
       - #VSS_IVOCPROC_TOPOLOGY_ID_RX_DEFAULT
       - If a topology ID is not supplied, set this field to
         #VSS_IVOCPROC_TOPOLOGY_ID_NONE @tablebulletend */

  uint32_t vocproc_mode;
  /**< Specifies whether the vocproc mode is set to internal or external
       mixing.
    
       @values
       - #VSS_IVOCPROC_VOCPROC_MODE_EC_INT_MIXING
       - #VSS_IVOCPROC_VOCPROC_MODE_EC_EXT_MIXING @tablebulletend */

  uint16_t ec_ref_port_id;
  /**< Port ID to which the vocproc connects for receiving the echo
       cancellation reference signal.

       @values If a port ID is not supplied, set this field to
               #VSS_IVOCPROC_PORT_ID_NONE

       This value is ignored when vocproc_mode is set to
         #VSS_IVOCPROC_VOCPROC_MODE_EC_INT_MIXING. */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup weak_vss_ivocproc_cmd_set_device_v2_t */

/** @ingroup cvd_cvp_cmd_set_sampling_rate
  Sets the vocproc sampling rates.

  @apr_msgpayload{vss_ivocproc_cmd_set_sampling_rate_t}
  @wktable{weak__vss__ivocproc__cmd__set__sampling__rate__t}

  @detdesc
  If no sampling rates are provided to the vocproc (i.e., this command is
  not called), the operating and calibration sampling rates the
  vocproc uses are those it receives from the MVM (provided to the MVM via
  #VSS_IMVM_CMD_SET_CAL_MEDIA_TYPE or #VSS_IMVM_CMD_SET_CAL_VAR_VOC_SAMPLING_RATE).
  @par
  If sampling rates are provided to the vocproc (that is, this command is
  called), the operating and calibration sample rates the vocproc
  uses are those provided in this command.
 
  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None.
*/
#define VSS_IVOCPROC_CMD_SET_SAMPLING_RATE ( 0x00011370 )

/* Type definition for vss_ivocproc_cmd_set_sampling_rate_t. */
typedef struct vss_ivocproc_cmd_set_sampling_rate_t vss_ivocproc_cmd_set_sampling_rate_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_ivocproc_cmd_set_sampling_rate_t 
@{ */
/* Payload of the VSS_IVOCPROC_CMD_SET_SAMPLING_RATE command. */
struct vss_ivocproc_cmd_set_sampling_rate_t
{
  uint32_t rx;
  /**< Rx sampling rate. 
    
       @values 8000, 16000, 48000 Hz */

  uint32_t tx;
  /**< Tx sampling rate. 
    
       @values 8000, 16000, 48000 Hz */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup weak_vss_ivocproc_cmd_set_sampling_rate_t */

/** @ingroup cvd_cvp_cmd_enable
  Enables the vocproc.

  @apr_msgpayload
  None.

  @detdesc
  When attached to the MVM, the vocproc enters the Enable state after both the
  client and the MVM trigger the vocproc to be enabled. Otherwise, the vocproc
  is enabled by the client trigger.
  @par
  Running vocproc sessions while unattached to any MVM session is a deprecated
  behavior, and it will not be allowed in the future.

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None.
*/
#define VSS_IVOCPROC_CMD_ENABLE ( 0x000100C6 )

/** @ingroup cvd_cvp_cmd_disable
  Disables the vocproc.

  @apr_msgpayload
  None.

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None.
*/
#define VSS_IVOCPROC_CMD_DISABLE ( 0x000110E1 )


/****************************************************************************
 * DEVICE CONFIGURATION DATA APIS                                           *
 ****************************************************************************/

/** @ingroup cvd_cvp_cmd_reg_device_cfg
  Registers the memory that contains device-specific configuration data with
  the vocproc.

  The client must register device configuration data with the vocproc that
  corresponds to the device being set on the vocproc.

  @note1hang For guidelines on using shared memory, see
             Section @xref{hdr:ShMemGuidelines}.

  @apr_msgpayload{vss_ivocproc_cmd_register_device_config_t}
  @wktable{weak__vss__ivocproc__cmd__register__device__config__t}

  @par Expected buffer format
@code
<-------- 32 bits -------->

 -------------------------
| mod_id                  |
 -------------------------
| param_id                |
 -------------------------
| param_size | reserved   |
 -------------------------
| param_data              |
|                         |
| ...                     |
 ------------------------- 
| mod_id                  |
.                         .
.                         .
.                         .
@endcode

  @detdesc
  The client cannot modify this memory while it is registered, and the vocproc
  does not modify this memory while it is registered.
  The device configuration data in the registered memory is valid until it the
  memory is unregistered.
  @par
  Registering a memory region for device configuration data
  while another region is still registered causes this command to fail. @newpage
  @par
  The device configuration table expects one of the following modules:
  - #VSS_MODULE_WIDEVOICE, together with the #VSS_PARAM_RX_SAMPLING_RATE
    parameter 
  - #VSS_MODULE_FEATURE_CONFIG, together with the #VSS_PARAM_HDVOICE_CONFIG
    parameter
  @par
  The feature is turned off if one of the following conditions occurs:
  - One of the modules is not present
  - Any of the associated parameters are not present
  - The wrong parameters are specified for a module

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  The memory registered here must first be mapped with the CVD by following
  the guidelines in Section&nbsp;@xref{hdr:ShMemGuidelines}.
  @par
  The client must provide memory for the vocproc session before registering 
  device configuration data by following the guidelines in
  Section @xref{hdr:ShMemGuidelines}.
*/
#define VSS_IVOCPROC_CMD_REGISTER_DEVICE_CONFIG ( 0x00011371 )

/* Type definition for vss_ivocproc_cmd_register_device_config_t. */
typedef struct vss_ivocproc_cmd_register_device_config_t vss_ivocproc_cmd_register_device_config_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_ivocproc_cmd_register_device_config_t 
@{ */
/* Payload of the VSS_IVOCPROC_CMD_REGISTER_DEVICE_CONFIG command.
*/
struct vss_ivocproc_cmd_register_device_config_t
{

  uint32_t mem_handle;
  /**< Handle to the shared memory that holds the per-network calibration data. */

  uint64_t mem_address;
  /**< Location of calibration data. */

  uint32_t mem_size;
  /**< Size of the calibration data in bytes.

       The amount of memory allocated at mem_address must meet the requirement
       as specified in Section @xref{hdr:ShMemGuidelines}. */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup vss_ivocproc_cmd_register_device_config_t */

/** @ingroup cvd_cvp_cmd_dereg_device_cfg
  Deregisters the memory that holds device configuration data from the
  vocproc.

  @apr_msgpayload
  None.

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None.
*/
#define VSS_IVOCPROC_CMD_DEREGISTER_DEVICE_CONFIG ( 0x00011372 )


/****************************************************************************
 * CALIBRATION DATA APIS                                                    *
 ****************************************************************************/

/* Type definition for vss_ivocproc_cal_na_value_t. */
typedef union vss_ivocproc_cal_na_value_t vss_ivocproc_cal_na_value_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_ivocproc_cal_na_value_t
@{ */
/* Union for specifying a calibration column N/A value.
*/
union vss_ivocproc_cal_na_value_t
{
  uint8_t uint8_val;        /**< UINT8 N/A value. */
  uint16_t uint16_val;      /**< UINT16 N/A value. */
  uint32_t uint32_val;      /**< UINT32 N/A value. */
  uint64_t uint64_val;      /**< UINT64 N/A value. */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup weak_vss_ivocproc_cal_na_value_t */

/* Type definition for vss_ivocproc_cal_column_t. */
typedef struct vss_ivocproc_cal_column_t vss_ivocproc_cal_column_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_ivocproc_cal_column_t 
@{ */
/* Structure for specifying a calibration column.
*/
struct vss_ivocproc_cal_column_t
{
  uint32_t id;
  /**< Column ID. 
 
       @values See @xhyperref{hdr:CalibrationColumns,Calibration columns} */

  uint32_t type;
  /**< Column type. 

       @values See @xhyperref{hdr:CalibrationColumnTypes,Calibration column types} */

  vss_ivocproc_cal_na_value_t na_value;
  /**< N/A column value associated with this column ID and type.
         
       The N/A value is a reserved value indicating that the calibration data
       entry corresponding to it in the table is independent of this column
       (and therefore the data is applied irrespective of what the current
       system configuration is for this column).

       The size of na_value is dependent on the column type. @newpagetable */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup weak_vss_ivocproc_cal_column_t */

/** @ingroup cvd_cvp_cmd_reg_stat_cal_data
  Registers the memory that contains the static calibration data table with the
  vocproc.
  
  @note1hang For guidelines on using shared memory, see
             Section @xref{hdr:ShMemGuidelines}.

  @apr_msgpayload{vss_ivocproc_cmd_register_static_calibration_data_t}
  @wktablens{weak__vss__ivocproc__cmd__register__static__calibration__data__t}

  @par Calibration column structure (vss_ivocproc_cal_column_t)
  @wktable{weak__vss__ivocproc__cal__column__t} @newpage

  @par Calibration N/A value structure (vss_ivocproc_cal_na_value_t)
  @wktable{weak__vss__ivocproc__cal__na__value__t}

  @detdesc
  The static calibration data table captures calibration data for system
  configurations that do not change while the vocproc is running (e.g. network,
  Tx and Rx pre/postprocessing sampling rates).
  @par
  Static calibration data is applied when the vocproc transitions to the run
  state. Static calibration data is applied before applying the dynamic
  calibration data registered via the
  #VSS_IVOCPROC_CMD_REGISTER_DYNAMIC_CALIBRATION_DATA command.
  @par
  As part of this registration, the client provides the address, size, and handle
  of the memory containing the calibration table. The client also provides
  the columns and associated column types that the vocproc uses to form a
  key. This key is used to index into the calibration table and look up a
  matching entry.
  @par
  The columns/types must be provided in this command in the same order
  that they exist in the calibration table.
  - If no matching entry is found, calibration data is not applied.
  - If multiple matching entries are found, the order in which they are applied
    is specified in Section @xref{hdr:OrderMultiMatchingCalibEntries}.
  @par
  The currently supported order for the columns provided in this command is:
  -# #VSS_ICOMMON_CAL_COLUMN_NETWORK
  -# #VSS_ICOMMON_CAL_COLUMN_TX_PP_SAMPLING_RATE
  -# #VSS_ICOMMON_CAL_COLUMN_RX_PP_SAMPLING_RATE
  -# #VSS_ICOMMON_CAL_COLUMN_TX_VOC_OPERATING_MODE
  -# #VSS_ICOMMON_CAL_COLUMN_RX_VOC_OPERATING_MODE
  -# #VSS_ICOMMON_CAL_COLUMN_MEDIA_ID
  -# #VSS_ICOMMON_CAL_COLUMN_FEATURE
  @par
  The client cannot modify the calibration data memory while the memory is
  registered, and the vocproc does not modify this memory while the memory is
  registered. System stability problems can result if the client modifies the
  calibration data memory while it is registered.
  @par
  The calibration data at the registered memory is valid until the memory is
  deregistered.
  @par
  Registering a memory region for calibration data while another region is
  still registered causes the command to fail.

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  Any memory registered here must first be mapped with the CVD by following
  the guidelines in Section @xref{hdr:ShMemGuidelines}.
*/
#define VSS_IVOCPROC_CMD_REGISTER_STATIC_CALIBRATION_DATA ( 0x00013079 )

/* Type definition for vss_ivocproc_cmd_register_static_calibration_data_t. */
typedef struct vss_ivocproc_cmd_register_static_calibration_data_t vss_ivocproc_cmd_register_static_calibration_data_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_ivocproc_cmd_register_static_calibration_data_t 
@{ */
/* Payload of the VSS_IVOCPROC_CMD_REGISTER_STATIC_CALIBRATION_DATA command. */
/** The expected calibration data buffer format is specified in
    Section @xref{hdr:CalibrationDataFormat}.
*/
struct vss_ivocproc_cmd_register_static_calibration_data_t
{
  uint32_t cal_mem_handle;
  /**< Handle to the shared memory that holds the per-network calibration
       data. */

  uint64_t cal_mem_address;
  /**< Location of the calibration data. */

  uint32_t cal_mem_size;
  /**< Size of the calibration data in bytes.

       The amount of memory allocated at cal_mem_address must meet the
       requirement as specified in Section @xref{hdr:ShMemGuidelines}. */

  uint32_t num_columns;
  /**< Number of columns used to form the key for looking up a calibration 
       data entry. */

#if __STDC_VERSION__ >= 199901L
  vss_ivocproc_cal_column_t columns[];
  /**< Array of columns of size num_columns. The order in which the columns
       are provided here must match the order in which they exist in the
       calibration table. */
#endif /* __STDC_VERSION__ >= 199901L */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup weak_vss_ivocproc_cmd_register_calibration_data_v2_t */

/** @ingroup cvd_cvp_cmd_dereg_stat_cal_data
  Deregisters the memory that contains static calibration data from the
  vocproc.

  @apr_msgpayload
  None.

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None.
*/
#define VSS_IVOCPROC_CMD_DEREGISTER_STATIC_CALIBRATION_DATA ( 0x0001307A )


/** @ingroup cvd_cvp_cmd_reg_dyn_cal_data
  Registers the memory that contains the dynamic calibration data table with
  the vocproc.

  @note1hang For guidelines on using shared memory, see
             Section @xref{hdr:ShMemGuidelines}.

  @apr_msgpayload{vss_ivocproc_cmd_register_dynamic_calibration_data_t}
  @wktablens{weak__vss__ivocproc__cmd__register__dynamic__calibration__data__t}

  @par Calibration column structure (vss_ivocproc_cal_column_t)
  @wktable{weak__vss__ivocproc__cal__column__t} @newpage

  @par Calibration N/A value structure (vss_ivocproc_cal_na_value_t)
  @wktable{weak__vss__ivocproc__cal__na__value__t}

  @detdesc
  The dynamic calibration data table captures calibration data for system
  configurations that can change while the vocproc is running (such as Tx and
  Rx vocoder operating modes for certain vocoders, and Rx volume index).
  @par
  Dynamic calibration data is applied when the vocproc transitions to the Run
  state, and also during runtime if the system configuration changes. Dynamic
  calibration data is applied after applying the static calibration data
  registered via the #VSS_IVOCPROC_CMD_REGISTER_STATIC_CALIBRATION_DATA
  command.
  @par
  As part of this registration, the client also provides the address, size and
  handle of the memory containing the calibration table. The client also
  provides the columns and associated column types that the vocproc uses to
  form a key. This key is used to index into the calibration table and look up
  a matching entry.
  @par
  The columns and types must be provided in this command in the same order
  that they exist in the calibration table.
  - If no matching entry is found, calibration data is not applied.
  - If multiple matching entries are found, the order in which they are applied
    is specified in Section @xref{hdr:OrderMultiMatchingCalibEntries}.
  @par
  The currently supported order for the columns provided in this command is:
  -# #VSS_ICOMMON_CAL_COLUMN_NETWORK
  -# #VSS_ICOMMON_CAL_COLUMN_TX_PP_SAMPLING_RATE
  -# #VSS_ICOMMON_CAL_COLUMN_RX_PP_SAMPLING_RATE
  -# #VSS_ICOMMON_CAL_COLUMN_RX_VOLUME_INDEX
  -# #VSS_ICOMMON_CAL_COLUMN_TX_VOC_OPERATING_MODE
  -# #VSS_ICOMMON_CAL_COLUMN_RX_VOC_OPERATING_MODE
  -# #VSS_ICOMMON_CAL_COLUMN_MEDIA_ID
  -# #VSS_ICOMMON_CAL_COLUMN_FEATURE
  @par
  The client cannot modify the calibration data memory while it is
  registered, and the vocproc does not modify this memory while it is registered.
  System stability problems might result if the client modifies the calibration
  data memory while it is registered.
  @par
  The calibration data at the registered memory is valid until deregistered.
  @par
  Registering a memory region for calibration data while another region is
  still registered causes the command to fail.

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  Any memory registered here must first be mapped with the CVD by following
  the guidelines in Section @xref{hdr:ShMemGuidelines}. 
*/
#define VSS_IVOCPROC_CMD_REGISTER_DYNAMIC_CALIBRATION_DATA ( 0x0001307B )

/* Type definition for vss_ivocproc_cmd_register_dynamic_calibration_data_t. */
typedef struct vss_ivocproc_cmd_register_dynamic_calibration_data_t vss_ivocproc_cmd_register_dynamic_calibration_data_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_ivocproc_cmd_register_dynamic_calibration_data_t 
@{ */
/* Payload of the VSS_IVOCPROC_CMD_REGISTER_DYNAMIC_CALIBRATION_DATA command.	 */
/** The expected calibration data buffer format is specified in
    Section @xref{hdr:CalibrationDataFormat}.
*/
struct vss_ivocproc_cmd_register_dynamic_calibration_data_t
{
  uint32_t cal_mem_handle;
  /**< Handle to the shared memory that holds the volume calibration data. */

  uint64_t cal_mem_address;
  /**< Location of volume calibration data. */

  uint32_t cal_mem_size;
  /**< Size of the volume calibration data in bytes. The amount of memory
       allocated at cal_mem_address must meet the requirement as specified
       in Section @xref{hdr:ShMemGuidelines}. */

  uint32_t num_columns;
  /**< Number of columns used to form the key for looking up a calibration
       data entry. */

#if __STDC_VERSION__ >= 199901L
  vss_ivocproc_cal_column_t columns[];
  /**< Array of columns of size num_columns. The order in which the
       columns are provided here must match the order in which they exist
       in the calibration table. */
#endif /* __STDC_VERSION__ >= 199901L */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup weak_vss_ivocproc_cmd_register_dynamic_calibration_data_t */

/** @ingroup cvd_cvp_cmd_dereg_dyn_cal_data
  Deregisters the memory that contains dynamic calibration data from the
  vocproc.

  @apr_msgpayload
  None.

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  None.
*/
#define VSS_IVOCPROC_CMD_DEREGISTER_DYNAMIC_CALIBRATION_DATA ( 0x0001307C )


/****************************************************************************
 * VOCPROC DTMF DETECTION APIS                                              *
 ****************************************************************************/

/** @cond OEM_only */
/** @addtogroup cvd_cvp_cmd_set_tx_dtmf_detect 
@{ */
/**
  Configures Tx DTMF detection. The DTMF detection status is sent to the client
  that sent this command via #VSS_IVOCPROC_EVT_TX_DTMF_DETECTED events.

  @apr_msgpayload{vss_ivocproc_cmd_set_tx_dtmf_detection_t}
  @wktable{weak__vss__ivocproc__cmd__set__tx__dtmf__detection__t}

  @detdesc
  Only one client can request Tx DTMF detection on a given vocproc at a
  given time. When another client requests Tx DTMF detection while the
  previous client's Tx DTMF detection is still active, the request fails.

  @return
  APRV2_IBASIC_RSP_RESULT (refer to @xhyperref{Q2,[Q2]}).

  @dependencies
  A valid session must have been created.
*/
#define VSS_IVOCPROC_CMD_SET_TX_DTMF_DETECTION ( 0x00011033 )

/** DTMF detection enable flag. */
#define VSS_IVOCPROC_TX_DTMF_DETECTION_ENABLE ( 1 )

/** DTMF detection disable flag. */
#define VSS_IVOCPROC_TX_DTMF_DETECTION_DISABLE ( 0 )

/** @} */ /* end_addtogroup cvd_cvp_cmd_set_tx_dtmf_detect */

/* Type definition for vss_ivocproc_cmd_set_tx_dtmf_detection_t. */
typedef struct vss_ivocproc_cmd_set_tx_dtmf_detection_t vss_ivocproc_cmd_set_tx_dtmf_detection_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_ivocproc_cmd_set_tx_dtmf_detection_t 
@{ */
/* Payload of the VSS_IVOCPROC_CMD_SET_TX_DTMF_DETECTION command.
*/
struct vss_ivocproc_cmd_set_tx_dtmf_detection_t
{
   uint32_t enable;
   /**< Specifies whether Tx DTMF detection is enabled.
      
        @values
        - #VSS_IVOCPROC_TX_DTMF_DETECTION_ENABLE
        - #VSS_IVOCPROC_TX_DTMF_DETECTION_DISABLE @tablebulletend */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup weak_vss_ivocproc_cmd_set_tx_dtmf_detection_t */
/** @endcond */

/** @cond OEM_only */
/** @ingroup cvd_cvp_evt_tx_dtmf_detected
  Event sent by the vocproc to the client that enabled Tx DTMF detection.

  @apr_msgpayload{vss_ivocproc_evt_tx_dtmf_detected_t}
  @wktable{weak__vss__ivocproc__evt__tx__dtmf__detected__t}

  @detdesc
  This event is sent whenever DTMF has been detected on the Tx path.
  @par
  The DTMF detection feature can only be used to detect DTMF frequencies
  as listed in Section&nbsp;6 of the ITU-T Recommendation Q.23 (refer to
  @xhyperref{S2,[S2]}). Therefore, the possible values for the low_freq and
  high_freq parameters are as listed in the message payload.

  @return
  None.

  @dependencies
  A valid session must have been created.
*/ /* S2 = Technical Features of Push-button Telephone Sets (ITU-T
           Recommendation Q.23)
*/
#define VSS_IVOCPROC_EVT_TX_DTMF_DETECTED ( 0x00011034 )

/* Type definition for vss_ivocproc_evt_tx_dtmf_detected_t. */
typedef struct vss_ivocproc_evt_tx_dtmf_detected_t vss_ivocproc_evt_tx_dtmf_detected_t;

#include "apr_pack_begin.h"

/** @weakgroup weak_vss_ivocproc_evt_tx_dtmf_detected_t 
@{ */
/* Payload of the VSS_IVOCPROC_EVT_TX_DTMF_DETECTED event.
*/
struct vss_ivocproc_evt_tx_dtmf_detected_t
{
   uint16_t low_freq;
   /**< Low frequency is detected in the DTMF tone.
      
        @values 697, 770, 852, 941 Hz */

   uint16_t high_freq;
   /**< High frequency is detected in the DTMF tone.
      
        @values 1209, 1336, 1477, 1633 Hz */
}
#include "apr_pack_end.h"
;
/** @} */ /* end_weakgroup weak_vss_ivocproc_evt_tx_dtmf_detected_t */
/** @endcond */

#endif /* __VSS_IVOCPROC_PUBLIC_IF_H__ */

