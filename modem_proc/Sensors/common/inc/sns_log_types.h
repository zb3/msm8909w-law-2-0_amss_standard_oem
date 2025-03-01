#ifndef SNS_LOG_TYPES_H
#define SNS_LOG_TYPES_H

/*============================================================================

@file
  sns_log_types.h

@brief
  Contains type definitions for sensors logs.

  Copyright (c) 2010-2016 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/

/*=====================================================================
                 INCLUDE FILES
=======================================================================*/

#include <stddef.h>
#include "sns_log_types_public.h"

/* HD22 related changes under SENSORS_DD_DEV_FLAG */
#ifndef SENSORS_DD_DEV_FLAG
#include "sns_common.h"
#include "log_codes.h"
#include "log.h"
#endif // SENSORS_DD_DEV_FLAG

/************************************************************************
 The following new log codes are assigned by the Diag team
 However correspoding changes have yet been made in "log_codes.h"
 For now we need to define them here so code can compile, however they
 must be removed once Diag team check in the changes in "log_codes.h"
************************************************************************/

#ifndef LOG_SNS_IOD_CONFIG_C
#define LOG_SNS_IOD_CONFIG_C                  0x1918
#endif
#ifndef LOG_SNS_IOD_RESULT_C
#define LOG_SNS_IOD_RESULT_C                  0x1919
#endif
#ifndef LOG_SNS_IOD_REPORT_C
#define LOG_SNS_IOD_REPORT_C                  0x191A
#endif
#ifndef LOG_SNS_IOD_AUTOCAL_CONFIG_C
#define LOG_SNS_IOD_AUTOCAL_CONFIG_C          0x191B
#endif
#ifndef LOG_SNS_IOD_AUTOCAL_RESULT_C
#define LOG_SNS_IOD_AUTOCAL_RESULT_C          0x191C
#endif
#ifndef LOG_SNS_IOD_AUTOCAL_REPORT_C
#define LOG_SNS_IOD_AUTOCAL_REPORT_C          0x191D
#endif

#ifndef LOG_SNS_EEW_CONFIG_C
# define LOG_SNS_EEW_CONFIG_C                         ((0x96F) + LOG_1X_BASE_C)
# define LOG_SNS_EEW_RESULT_C                         ((0x970) + LOG_1X_BASE_C)
# define LOG_SNS_EEW_RESULT2_C                        ((0x971) + LOG_1X_BASE_C)
# define LOG_SNS_EEW_REPORT_C                         ((0x972) + LOG_1X_BASE_C)
#endif

#ifndef LOG_SNS_ALTCHG_CONFIG_C
# define LOG_SNS_ALTCHG_CONFIG_C                      ((0x973) + LOG_1X_BASE_C)
# define LOG_SNS_ALTCHG_RESULT_C                      ((0x974) + LOG_1X_BASE_C)
# define LOG_SNS_ALTCHG_RESULT2_C                     ((0x975) + LOG_1X_BASE_C)
# define LOG_SNS_ALTCHG_REPORT_C                      ((0x976) + LOG_1X_BASE_C)
#endif

#ifndef LOG_SNS_ARW_CORE_CONFIG_C
# define LOG_SNS_ARW_CORE_CONFIG_C                    ((0x977) + LOG_1X_BASE_C)
# define LOG_SNS_ARW_CORE_RESULT_C                    ((0x978) + LOG_1X_BASE_C)
# define LOG_SNS_ARW_CORE_RESULT2_C                   ((0x979) + LOG_1X_BASE_C)
# define LOG_SNS_ARW_CORE_REPORT_C                    ((0x97A) + LOG_1X_BASE_C)
#endif

#ifndef LOG_SNS_ARW_CONFIG_C
# define LOG_SNS_ARW_CONFIG_C                         ((0x97B) + LOG_1X_BASE_C)
# define LOG_SNS_ARW_RESULT_C                         ((0x97C) + LOG_1X_BASE_C)
# define LOG_SNS_ARW_REPORT_C                         ((0x97D) + LOG_1X_BASE_C)
#endif

/*=======================================================================
                  INTERNAL DEFINITIONS AND TYPES
========================================================================*/

/** Maximum size of payload */
#define SNS_LOG_MAX_SIZE  (2048 - 64)   /* Make this value to be same as SMR_MAX_BODY_LEN */

/** Sensors internal log ids
 *  should be maintained in sync with SNS_LOG_QXDM_ID */

#define SNS_TIMESTAMP_DSPS  0
#define SNS_TIMESTAMP_APPS  1
#define SNS_TIMESTAMP_MODEM 2

typedef enum {
   SNS_LOG_SENSOR1_REQUEST,
   SNS_LOG_SENSOR1_RESPONSE,
   SNS_LOG_SENSOR1_INDICATION,
   SNS_LOG_SMR_REQUEST,
   SNS_LOG_SMR_RESPONSE,
   SNS_LOG_SMR_INDICATION,
   SNS_LOG_CONVERTED_SENSOR_DATA,
   SNS_LOG_QMD_CONFIG,
   SNS_LOG_QMD_RESULT,
   SNS_LOG_QMD_REPORT,
   SNS_LOG_DSPS_PWR,
   SNS_LOG_RAW_I2C_DATA,
   SNS_LOG_FNS_CONFIG,
   SNS_LOG_FNS_RESULT,
   SNS_LOG_FNS_REPORT,
   SNS_LOG_BTE_CONFIG,
   SNS_LOG_BTE_RESULT,
   SNS_LOG_BTE_REPORT,
   SNS_LOG_GYRO_CAL_CONFIG,
   SNS_LOG_GYRO_CAL_RESULT,
   SNS_LOG_GYRO_CAL_REPORT,
   SNS_LOG_QUAT_CONFIG,
   SNS_LOG_QUAT_RESULT,
   SNS_LOG_QUAT_REPORT,
   SNS_LOG_GRAVITY_CONFIG,
   SNS_LOG_GRAVITY_RESULT,
   SNS_LOG_GRAVITY_REPORT,
   SNS_LOG_DRV_MD_IRQ,
   SNS_LOG_MAG_CAL_CONFIG,
   SNS_LOG_MAG_CAL_RESULT,
   SNS_LOG_MAG_CAL_REPORT,
   SNS_LOG_ROTATION_VECTOR_CONFIG,
   SNS_LOG_ROTATION_VECTOR_RESULT,
   SNS_LOG_ROTATION_VECTOR_REPORT,
   SNS_LOG_FMV_CONFIG,
   SNS_LOG_FMV_QUAT_UPDATE,
   SNS_LOG_FMV_MAG_UPDATE,
   SNS_LOG_FMV_GYRO_UPDATE,
   SNS_LOG_FMV_REPORT,
   SNS_LOG_TIME_REPORT,
   SNS_LOG_BASIC_GESTURES_CONFIG,
   SNS_LOG_BASIC_GESTURES_RESULT,
   SNS_LOG_BASIC_GESTURES_REPORT,
   SNS_LOG_FACING_CONFIG,
   SNS_LOG_FACING_RESULT,
   SNS_LOG_FACING_REPORT,
   SNS_LOG_INTEG_ANGLE_CONFIG,
   SNS_LOG_INTEG_ANGLE_REPORT,
   SNS_LOG_INTEG_ANGLE_RESULT,
   SNS_LOG_GYRO_TAP_CONFIG,
   SNS_LOG_GYRO_TAP_REPORT,
   SNS_LOG_GYRO_TAP_RESULT,
   SNS_LOG_ACCEL_CAL_CONFIG,
   SNS_LOG_ACCEL_CAL_RESULT,
   SNS_LOG_ACCEL_CAL_REPORT,
   SNS_LOG_PED_CONFIG,
   SNS_LOG_PED_RESULT,
   SNS_LOG_PED_REPORT,
   SNS_LOG_PAM_CONFIG,
   SNS_LOG_PAM_REPORT,
   SNS_LOG_PAM_RESULT,
   SNS_LOG_SENSOR_FIFO_EVENT,
   SNS_LOG_CMC_CONFIG,
   SNS_LOG_CMC_REPORT,
   SNS_LOG_CMC_RESULT,
   SNS_LOG_CMC_RESULT2,
   SNS_LOG_DISTANCE_BOUND_CONFIG,
   SNS_LOG_DISTANCE_BOUND_REPORT,
   SNS_LOG_DISTANCE_BOUND_RESULT,
   SNS_LOG_SMD_CONFIG,
   SNS_LOG_SMD_RESULT,
   SNS_LOG_SMD_REPORT,
   SNS_LOG_LATENCY_SAMPLING_POLL,
   SNS_LOG_LATENCY_SAMPLING_DRI,
   SNS_LOG_LATENCY_DELIVERY,
   SNS_LOG_GAME_ROTATION_VECTOR_CONFIG,
   SNS_LOG_GAME_ROTATION_VECTOR_RESULT,
   SNS_LOG_GAME_ROTATION_VECTOR_REPORT,
   SNS_LOG_QMAG_CAL_CONFIG,
   SNS_LOG_QMAG_CAL_RESULT,
   SNS_LOG_QMAG_CAL_REPORT,
   SNS_LOG_UIMG_MODE,
   SNS_LOG_GEOMAG_ROT_VEC_CONFIG,
   SNS_LOG_GEOMAG_ROT_VEC_RESULT,
   SNS_LOG_GEOMAG_ROT_VEC_REPORT,
   SNS_LOG_TILT_DETECTOR_CONFIG,
   SNS_LOG_TILT_DETECTOR_RESULT,
   SNS_LOG_TILT_DETECTOR_REPORT,
   SNS_LOG_QHEART_CONFIG,
   SNS_LOG_QHEART_RESULT,
   SNS_LOG_QHEART_REPORT,
   SNS_LOG_TILT_W_DETECTOR_CONFIG,
   SNS_LOG_TILT_W_DETECTOR_RESULT,
   SNS_LOG_TILT_W_DETECTOR_REPORT,
   SNS_LOG_SNS_GENERIC_MESSAGE, 
   SNS_LOG_IOD_CONFIG,
   SNS_LOG_IOD_RESULT,
   SNS_LOG_IOD_REPORT,
   SNS_LOG_IOD_AUTOCAL_CONFIG,
   SNS_LOG_IOD_AUTOCAL_RESULT,
   SNS_LOG_IOD_AUTOCAL_REPORT,
   SNS_LOG_EEW_CONFIG_C,
   SNS_LOG_EEW_RESULT_C,
   SNS_LOG_EEW_RESULT2_C,
   SNS_LOG_EEW_REPORT_C,
   SNS_LOG_ALTCHG_CONFIG_C,
   SNS_LOG_ALTCHG_RESULT_C,
   SNS_LOG_ALTCHG_RESULT2_C,
   SNS_LOG_ALTCHG_REPORT_C,
   SNS_LOG_ARW_CORE_CONFIG_C,
   SNS_LOG_ARW_CORE_RESULT_C,
   SNS_LOG_ARW_CORE_RESULT2_C,
   SNS_LOG_ARW_CORE_REPORT_C,
   SNS_LOG_ARW_CONFIG_C,
   SNS_LOG_ARW_RESULT_C,
   SNS_LOG_ARW_REPORT_C,
   SNS_LOG_NUM_IDS
} sns_log_id_e;

/** QXDM global log id
    should be maintained in sync with sns_log_id */
#define SNS_LOG_QXDM_ID             \
{                                   \
   LOG_SNS_SENSOR1_REQUEST_C,       \
   LOG_SNS_SENSOR1_RESPONSE_C,      \
   LOG_SNS_SENSOR1_INDICATION_C,    \
   LOG_SNS_SMR_REQUEST_C,           \
   LOG_SNS_SMR_RESPONSE_C,          \
   LOG_SNS_SMR_INDICATION_C,        \
   LOG_CONVERTED_SENSOR_DATA_C,     \
   LOG_SNS_QMD_CONFIG_C,            \
   LOG_SNS_QMD_RESULT_C,            \
   LOG_SNS_QMD_REPORT_C,            \
   LOG_SNS_DSPS_PWR_C,              \
   LOG_SNS_RAW_I2C_DATA_C,          \
   LOG_SNS_FNS_CONFIG_C,            \
   LOG_SNS_FNS_RESULT_C,            \
   LOG_SNS_FNS_REPORT_C,            \
   LOG_SNS_BTE_CONFIG_C,            \
   LOG_SNS_BTE_RESULT_C,            \
   LOG_SNS_BTE_REPORT_C,            \
   LOG_SNS_GYRO_SIMP_CAL_CONFIG_C,  \
   LOG_SNS_GYRO_SIMP_CAL_RESULT_C,  \
   LOG_SNS_GYRO_SIMP_CAL_REPORT_C,  \
   LOG_SNS_QUAT_CONFIG_C,           \
   LOG_SNS_QUAT_RESULT_C,           \
   LOG_SNS_QUAT_REPORT_C,           \
   LOG_SNS_GRAVITY_CONFIG_C,        \
   LOG_SNS_GRAVITY_RESULT_C,        \
   LOG_SNS_GRAVITY_REPORT_C,        \
   LOG_SNS_DRV_MD_IRQ_C,            \
   LOG_SNS_MAG_CAL_CONFIG_C,        \
   LOG_SNS_MAG_CAL_RESULT_C,        \
   LOG_SNS_MAG_CAL_REPORT_C,        \
   LOG_SNS_ROTATION_VECTOR_CONFIG_C,\
   LOG_SNS_ROTATION_VECTOR_RESULT_C,\
   LOG_SNS_ROTATION_VECTOR_REPORT_C,\
   LOG_SNS_FMV_CONFIG_C,            \
   LOG_SNS_FMV_QUAT_UPDATE_C,       \
   LOG_SNS_FMV_MAG_UPDATE_C,        \
   LOG_SNS_FMV_GYRO_UPDATE_C,       \
   LOG_SNS_FMV_REPORT_C,            \
   LOG_SNS_TIME_SERVICE_OFFSETS_C,  \
   LOG_SNS_BASIC_GESTURES_CONFIG_C, \
   LOG_SNS_BASIC_GESTURES_RESULT_C, \
   LOG_SNS_BASIC_GESTURES_REPORT_C, \
   LOG_SNS_FACING_CONFIG_C,         \
   LOG_SNS_FACING_RESULT_C,         \
   LOG_SNS_FACING_REPORT_C,         \
   LOG_INTEG_ANGLE_CONFIG_C,        \
   LOG_INTEG_ANGLE_REPORT_C,        \
   LOG_INTEG_ANGLE_RESULT_C,        \
   LOG_GTAP_CONFIG_C,               \
   LOG_GTAP_REPORT_C,               \
   LOG_GTAP_RESULT_C,               \
   LOG_SNS_ACCEL_CAL_CONFIG_C,      \
   LOG_SNS_ACCEL_CAL_RESULT_C,      \
   LOG_SNS_ACCEL_CAL_REPORT_C,      \
   LOG_SNS_PED_CONFIG_C,            \
   LOG_SNS_PED_RESULT_C,            \
   LOG_SNS_PED_REPORT_C,            \
   LOG_PAM_CONFIG_C,                \
   LOG_PAM_REPORT_C,                \
   LOG_PAM_RESULT_C,                \
   LOG_SENSOR_FIFO_EVENT_C,         \
   LOG_SNS_CMC_CONFIG_C,            \
   LOG_SNS_CMC_REPORT_C,            \
   LOG_SNS_CMC_RESULT_C,            \
   LOG_SNS_CMC_RESULT2_C,           \
   LOG_SNS_DB_CONFIG_C,             \
   LOG_SNS_DB_REPORT_C,             \
   LOG_SNS_DB_RESULT_C,             \
   LOG_SNS_SMD_CONFIG_C,            \
   LOG_SNS_SMD_RESULT_C,            \
   LOG_SNS_SMD_REPORT_C,            \
   LOG_SNS_LATENCY_SAMPLING_POLL_C, \
   LOG_SNS_LATENCY_SAMPLING_DRI_C,  \
   LOG_SNS_LATENCY_DELIVERY_C,      \
   LOG_SNS_GAME_ROTATION_VECTOR_CONFIG_C,  \
   LOG_SNS_GAME_ROTATION_VECTOR_RESULT_C,  \
   LOG_SNS_GAME_ROTATION_VECTOR_REPORT_C,  \
   LOG_SNS_QMAG_CAL_CONFIG_C,  \
   LOG_SNS_QMAG_CAL_RESULT_C,  \
   LOG_SNS_QMAG_CAL_REPORT_C,  \
   LOG_SNS_UIMG_MODE_C,        \
   LOG_SNS_GEOMAG_ROT_VEC_CONFIG_C, \
   LOG_SNS_GEOMAG_ROT_VEC_RESULT_C, \
   LOG_SNS_GEOMAG_ROT_VEC_REPORT_C, \
   LOG_SNS_TILT_DETECTOR_CONFIG_C,  \
   LOG_SNS_TILT_DETECTOR_RESULT_C,  \
   LOG_SNS_TILT_DETECTOR_REPORT_C,  \
   SNS_LOG_QHEART_CONFIG_C,\
   SNS_LOG_QHEART_RESULT_C,\
   SNS_LOG_QHEART_REPORT_C,\
   LOG_SNS_TILT_W_DETECTOR_CONFIG_C,\
   LOG_SNS_TILT_W_DETECTOR_RESULT_C,\
   LOG_SNS_TILT_W_DETECTOR_REPORT_C,\
   LOG_SNS_GENERIC_MESSAGE_C,  \
   LOG_SNS_IOD_CONFIG_C,  \
   LOG_SNS_IOD_RESULT_C,  \
   LOG_SNS_IOD_REPORT_C,  \
   LOG_SNS_IOD_AUTOCAL_CONFIG_C,  \
   LOG_SNS_IOD_AUTOCAL_RESULT_C,  \
   LOG_SNS_IOD_AUTOCAL_REPORT_C,  \
   LOG_SNS_EEW_CONFIG_C,  \
   LOG_SNS_EEW_RESULT_C,  \
   LOG_SNS_EEW_RESULT2_C,  \
   LOG_SNS_EEW_REPORT_C,  \
   LOG_SNS_ALTCHG_CONFIG_C,  \
   LOG_SNS_ALTCHG_RESULT_C,  \
   LOG_SNS_ALTCHG_RESULT2_C,  \
   LOG_SNS_ALTCHG_REPORT_C,  \
   LOG_SNS_ARW_CORE_CONFIG_C,  \
   LOG_SNS_ARW_CORE_RESULT_C,  \
   LOG_SNS_ARW_CORE_RESULT2_C,  \
   LOG_SNS_ARW_CORE_REPORT_C,  \
   LOG_SNS_ARW_CONFIG_C,  \
   LOG_SNS_ARW_RESULT_C,  \
   LOG_SNS_ARW_REPORT_C  \
};



#if defined(_WIN32)
#pragma pack(push,1)
#endif

/**
   sns_log_smr_pkt_s
   This type is used to log requests routed through the Sensor Message
   Router.
   It is used for the following log types:
   LOG_SNS_SMR_REQUEST_C
   LOG_SNS_SMR_RESPONSE_C
   LOG_SNS_SMR_INDICATION_C
 */
typedef PACK(struct) {
  log_hdr_type   log_type;          /**< Type, as defined in log_codes.h */
  uint8_t        version;           /**< Set to SNS_LOG_STRUCT_VERSION */
  uint8_t        logging_processor; /**< 1 == Modem; 2 == Apps; 3 == DSPS */
  uint64_t       timestamp;         /**< Timestamp the log was created */
  uint8_t        dst_module;        /**< SMR Destination Module, defined in
                                       sns_common.h */
  uint8_t        src_module;        /**< SMR Source Module, defined in
                                       sns_common.h */
  uint8_t        priority;          /**< Message Priority. */
  uint8_t        txn_id;            /**< Transaction ID chosen by the client */
  uint8_t        ext_client_id;     /**< External client ID */
  uint8_t        svc_num;           /**< QMI Service number */
  uint16_t       msg_id;            /**< Message ID, as defined by the service */
  uint8_t        msg_type;          /**< Message Type */
  uint16_t       pkt_size;          /**< Size of the pkt field. */
  uint8_t        pkt[1];            /**< The QMI-encoded message, of length
                                       pkt_size. */
} sns_log_smr_pkt_s;

/**
 * sns_log_qmd_irq_s
 * This type logs motion detection interrupt
 * LOG_SNS_QMD_IRQ
 */
#define SNS_LOG_MD_IRQ_VERSION 1
typedef PACK(struct) {
    log_hdr_type  log_type;      /**< Type, as defined in log_codes.h */
    uint8_t       version;       /**< version of the log packet */
    uint64_t      timestamp;     /**< time when the interrupt was detected */
    uint16_t      threshold;     /**< threshold, in milliG for motion detect */
} sns_log_md_irq_s;

/**
   sns_log_pwr_report_s
   This type logs power on/off state of the DSPS
   SNS_LOG_DSPS_PWR
*/
#ifndef DSPS_RPM_SUPPORT
/* No RPM support */
  #define SNS_LOG_DSPS_PWR_VERSION 1

/* These defines are used for the Power State */
  #define SNS_LOG_DSPS_PWR_ST_OFF 0
  #define SNS_LOG_DSPS_PWR_ST_ON  1
#else
/* RPM support */
  #define SNS_LOG_DSPS_PWR_VERSION 2

/* These defines are used for the Power State */
  #define SNS_LOG_DSPS_PWR_ST_HIBERNATION 0
  #define SNS_LOG_DSPS_PWR_ST_DORMANT     1
  #define SNS_LOG_DSPS_PWR_ST_LOW         2
  #define SNS_LOG_DSPS_PWR_ST_HIGH        3
  #define SNS_LOG_DSPS_PWR_ST_UNKNOWN     4
#endif /* DSPS_RPM_SUPPORT */


typedef PACK(struct) {
   log_hdr_type log_type;        /**< Type, as defined in log_codes.h */
   uint8_t      version;         /**< version of the log packet */
   uint64_t     timestamp;       /**< time when the state changed */
   uint32_t     powerstate;      /**< Power state, as defined above */
} sns_log_dsps_pwr_s;

/**
   sns_log_raw_i2c_data_s
   This type is used to log the data for I2C read or write operation.
   It is used for the following log types:
   LOG_SNS_RAW_I2C_DATA_C
 */
#define SNS_LOG_RAW_I2C_DATA_VERSION 1
#define SNS_LOG_MAX_RAW_I2C_PAYLOAD 57
typedef PACK(struct) {
  log_hdr_type log_type;         /**< Type, as defined in log_codes.h */
  uint8_t      version;          /**< version of the log packet */
  uint64_t     timestamp;        /**< time when the I2C transcation completed */
  uint8_t      i2c_op;           /**< i2c operation code */
  uint8_t      status;           /**< i2c operation status */
  uint8_t      slv_addr;         /**< i2c slave device address */
  uint8_t      reg_addr;         /**< i2c register address for the operation */
  uint8_t      data_len;         /**< length of i2c data payload */
  uint8_t      data_buf[SNS_LOG_MAX_RAW_I2C_PAYLOAD]; /**< sensor data */
} sns_log_raw_i2c_data_s;

#define SNS_LOG_FNS_CONFIG_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;            /* Version                */
  uint8_t      timestamp_type;     /* type of timestamp      */
  uint64_t     timestamp;          /* timestamp              */
  uint32_t     sample_rate;        /* Sampling rate          */
  uint32_t     facing_angle_thresh;/* facing angle threshold */
  uint32_t     basic_sleep;        /* basic sleep param      */
  uint32_t     basic_shake_thresh; /* basic shake threshold  */
  uint32_t     timeout;            /* Timeout for algo       */
  uint32_t     ic_param_1;         /* internal config param  */
  uint32_t     ic_param_2;         /* internal config param  */
  uint32_t     ic_param_3;         /* internal config param  */
  uint32_t     ic_param_4;         /* internal config param  */
  uint8_t      algo_instance_id;   /* algorithm instance id  */
} sns_log_fns_config_s;



#define SNS_LOG_FNS_RESULT_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;            /* Version                */
  uint8_t      timestamp_type;     /* type of timestamp      */
  uint64_t     timestamp;          /* timestamp              */

  int32_t      accel_x;           /* acceleration along x axis */
  int32_t      accel_y;           /* acceleration along y axis */
  int32_t      accel_z;           /* acceleration along z axis */
  uint8_t      fns_result;        /* algo result               */
  uint8_t      fns_state;         /* algo state                */
  uint8_t      axis_state;        /* axis algo state           */
  uint8_t      algo_inst_id;      /* algo instance id          */
} sns_log_fns_result_s;

#define SNS_LOG_FNS_REPORT_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;            /* Version                */
  uint8_t      timestamp_type;     /* type of timestamp      */
  uint64_t     timestamp;          /* timestamp              */

  int32_t      report_id;         /* report id               */
  uint8_t      report_type;       /* report type             */
  uint8_t      client_id;         /* client id               */
  uint8_t      fns_result;        /* algo result             */
  uint8_t      algo_inst_id;      /* algo instance id        */
} sns_log_fns_report_s;

#define SNS_LOG_BTE_CONFIG_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;            /* Version                    */
  uint8_t      timestamp_type;     /* type of timestamp          */
  uint64_t     timestamp;          /* timestamp                  */
  uint32_t     sample_rate;        /* Sampling rate              */
  uint32_t     facing_angle_thresh;/* facing angle threshold     */
  uint32_t     horiz_angle_thresh; /* horizontal angle threshold */
  uint32_t     vert_angle_thresh;  /* vertical angle threshold   */
  uint32_t     prox_enabled;       /* proximity enabled          */
  uint32_t     ic_param_1;         /* internal config param      */
  uint32_t     ic_param_2;         /* internal config param      */
  uint32_t     ic_param_3;         /* internal config param      */
  uint32_t     ic_param_4;         /* internal config param      */
  uint8_t      algo_instance_id;   /* algorithm instance id      */
} sns_log_bte_config_s;

#define SNS_LOG_BTE_RESULT_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;           /* Version                   */
  uint8_t      timestamp_type;    /* type of timestamp         */
  uint64_t     timestamp;         /* timestamp                 */

  int32_t      accel_x;           /* acceleration along x axis */
  int32_t      accel_y;           /* acceleration along y axis */
  int32_t      accel_z;           /* acceleration along z axis */
  int32_t      proximity;         /* proximity                 */
  uint8_t      bte_result;        /* algo result               */
  uint8_t      bte_state;         /* algo state                */
  uint8_t      axis_state;        /* axis algo state           */
  uint8_t      algo_inst_id;      /* algo instance id          */
} sns_log_bte_result_s;

#define SNS_LOG_BTE_REPORT_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;           /* Version                 */
  uint8_t      timestamp_type;    /* type of timestamp       */
  uint64_t     timestamp;         /* timestamp               */

  int32_t      report_id;         /* report id               */
  uint8_t      report_type;       /* report type             */
  uint8_t      client_id;         /* client id               */
  uint8_t      bte_result;        /* algo result             */
  uint8_t      algo_inst_id;      /* algo instance id        */
} sns_log_bte_report_s;

#define SNS_LOG_GYRO_CAL_CONFIG_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;        /**< Type, as defined in log_codes.h */
   uint8_t      version;         /**< version of the log packet */
   uint64_t     timestamp;       /**< time when the sensor data was sampled */
   int32_t      sample_rate;     /**< gyroscope sampling rate */
   uint8_t      algo_inst_id;    /**< algorithm instance id */
} sns_log_gyro_cal_config_s;

#define SNS_LOG_GYRO_CAL_RESULT_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;         /**< Type, as defined in log_codes.h */
   uint8_t      version;          /**< version of the log packet */
   uint64_t     timestamp;        /**< time when sensor data was sampled */
   int32_t      gyro_x;           /**< gyro measurement along x axis */
   int32_t      gyro_y;           /**< gyro measurement along y axis */
   int32_t      gyro_z;           /**< gyro measurement along z axis */
   int32_t      gyro_zero_bias_x; /**< gyro x axis zero bias estimate */
   int32_t      gyro_zero_bias_y; /**< gyro y axis zero bias estimate */
   int32_t      gyro_zero_bias_z; /**< gyro z axis zero bias estimate */
   uint8_t      algo_inst_id;     /**< algorithm instance id */
} sns_log_gyro_cal_result_s;

#define SNS_LOG_GYRO_CAL_REPORT_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;              /**< Type, as defined in log_codes.h */
   uint8_t      version;               /**< version of the log packet */
   uint64_t     timestamp;             /**< time when sensor data sampled */
   int32_t      gyro_x;                /**< gyro measurement along x axis */
   int32_t      gyro_y;                /**< gyro measurement along y axis */
   int32_t      gyro_z;                /**< gyro measurement along z axis */
   int32_t      gyro_zero_bias_corr_x; /**< gyro x axis zero bias correction */
   int32_t      gyro_zero_bias_corr_y; /**< gyro y axis zero bias correction */
   int32_t      gyro_zero_bias_corr_z; /**< gyro z axis zero bias correction */
} sns_log_gyro_cal_report_s;

#define SNS_LOG_ACCEL_CAL_CONFIG_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;        /**< Type, as defined in log_codes.h */
   uint8_t      version;         /**< version of the log packet */
   uint64_t     timestamp;       /**< time when the sensor data was sampled */
   int32_t      sample_rate;     /**< gyroscope sampling rate */
   uint8_t      algo_inst_id;    /**< algorithm instance id */
} sns_log_accel_cal_config_s;

#define SNS_LOG_ACCEL_CAL_RESULT_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;         /**< Type, as defined in log_codes.h */
   uint8_t      version;          /**< version of the log packet */
   uint64_t     timestamp;        /**< time when sensor data was sampled */
   int32_t      accel_x;           /**< accel measurement along x axis */
   int32_t      accel_y;           /**< accel measurement along y axis */
   int32_t      accel_z;           /**< accel measurement along z axis */
   int32_t      temp;              /**< temp measurement */
   int32_t      accel_zero_bias_x; /**< accel x axis zero bias estimate */
   int32_t      accel_zero_bias_y; /**< accel y axis zero bias estimate */
   int32_t      accel_zero_bias_z; /**< accel z axis zero bias estimate */
   int32_t      accel_scale_factor_x; /**< accel x axis scale factor estimate */
   int32_t      accel_scale_factor_y; /**< accel y axis scale factor estimate */
   int32_t      accel_scale_factor_z; /**< accel z axis scale factor estimate */
   uint8_t      algo_inst_id;     /**< algorithm instance id */
} sns_log_accel_cal_result_s;

#define SNS_LOG_ACCEL_CAL_REPORT_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;              /**< Type, as defined in log_codes.h */
   uint8_t      version;               /**< version of the log packet */
   uint64_t     timestamp;             /**< time when sensor data sampled */
   int32_t      accel_x;                /**< accel measurement along x axis */
   int32_t      accel_y;                /**< accel measurement along y axis */
   int32_t      accel_z;                /**< accel measurement along z axis */
   int32_t      temp;              /**< temp measurement */
   int32_t      accel_zero_bias_x; /**< accel x axis zero bias estimate */
   int32_t      accel_zero_bias_y; /**< accel y axis zero bias estimate */
   int32_t      accel_zero_bias_z; /**< accel z axis zero bias estimate */
   int32_t      accel_scale_factor_x; /**< accel x axis scale factor estimate */
   int32_t      accel_scale_factor_y; /**< accel y axis scale factor estimate */
   int32_t      accel_scale_factor_z; /**< accel z axis scale factor estimate */
   double       cal_report_decision; /**< 1:report sent to Smgr 0: report not sent */
   double       temp_op_min; /**< [deg] lower limit of the current operational temperature range*/
   double       count_kf_update; /**< number of KF updates for the current operational bin*/
   double       covar_accel_x_bias; /**< [milliG^2] KF covariance for Accel X Bias*/
   double       covar_accel_y_bias; /**< [milliG^2] KF covariance for Accel Y Bias*/
   double       covar_accel_z_bias; /**< [milliG^2] KF covariance for Accel Z Bias*/
   double       covar_accel_x_sf; /**< [milliG^2] KF covariance for Accel X SF*/
   double       covar_accel_y_sf; /**< [milliG^2] KF covariance for Accel Y SF*/
   double       covar_accel_z_sf; /**< [milliG^2] KF covariance for Accel Z SF*/
   double       kf_accel_x_bias; /**< [milliG] KF Bias X Estimate*/
   double       kf_accel_y_bias; /**< [milliG] KF Bias Y Estimate*/
   double       kf_accel_z_bias; /**< [milliG] KF Bias Z Estimate*/
   double       kf_accel_x_sf; /**< [milliG] KF SF X Estimate*/
   double       kf_accel_y_sf; /**< [milliG] KF SF Y Estimate*/
   double       kf_accel_z_sf; /**< [milliG] KF SF Z Estimate*/
} sns_log_accel_cal_report_s;

#define SNS_LOG_MAG_CAL_CONFIG_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;              /**< Type, as defined in log_codes.h */
   uint8_t      version;               /**< Version of the log packet       */
   uint8_t      timestamp_type;        /**< type of timestamp               */
   uint64_t     timestamp;             /**< timestamp of mag cal config  */
   uint32_t     report_period;         /**< gravity vector report period    */
   uint32_t     sample_rate;           /**< mag sampling rate         */
   uint8_t      algo_inst_id;          /**< algorithm instance id           */
} sns_log_mag_cal_config_s;

#define SNS_LOG_MAG_CAL_RESULT_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;         /**< Type, as defined in log_codes.h */
   uint8_t      version;          /**< Version of the log packet       */
   uint8_t      timestamp_type;   /**< type of timestamp               */
   uint64_t     timestamp;        /**< timestamp of quaternion result  */
   int32_t      mag_x;            /**< raw mag measurement along x_axis   */
   int32_t      mag_y;            /**< raw mag measurement along y_axis   */
   int32_t      mag_z;            /**< raw mag measurement along z_axis   */
   int32_t      magcal[3];        /**< calibrated mag result        */
   int32_t      magcalbias[3];    /**< bias offset result        */
   uint8_t      accuracy;         /**< accuracy of the calibrated sample */
   uint8_t      algo_inst_id;     /**< algorithm instance id           */
} sns_log_mag_cal_result_s;

#define SNS_LOG_MAG_CAL_REPORT_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;         /**< Type, as defined in log_codes.h */
   uint8_t      version;          /**< Version of the log packet       */
   uint8_t      timestamp_type;   /**< type of timestamp               */
   uint64_t     timestamp;        /**< timestamp of quaternion report  */
   int32_t      report_id;        /**< report id                       */
   uint8_t      report_type;      /**< report type                     */
   uint8_t      client_id;        /**< client id                       */
   int32_t      magcal[3];        /**< calibrated mag result        */
   int32_t      magcalbias[3];    /**< bias offset result        */
   uint8_t      accuracy;         /**< accuracy of the calibrated sample */
   uint8_t      algo_inst_id;     /**< algorithm instance id           */
}sns_log_mag_cal_report_s;

#define SNS_LOG_QMAG_CAL_CONFIG_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;              /**< Type, as defined in log_codes.h */
   uint8_t      version;               /**< Version of the log packet       */
   uint8_t      timestamp_type;        /**< type of timestamp               */
   uint64_t     timestamp;             /**< timestamp of mag cal config  */
   uint32_t     sample_rate_mag;           /**< mag sampling rate         */
   uint32_t     sample_rate_accel;        /**< accel sampling rate         */
   
   uint8_t      cal_algo_type;           /**< calibration algorithm type   */
   float        cal_cycle_rate;          /**< calibration cycle rate           */
} sns_log_qmag_cal_config_s;

#define SNS_LOG_QMAG_CAL_RESULT_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;         /**< Type, as defined in log_codes.h */
   uint8_t      version;          /**< Version of the log packet       */
   uint8_t      timestamp_type;        /**< type of timestamp               */
   uint64_t     timestamp;        /**< timestamp of quaternion result  */
   uint8_t      input_type;      /**< input data type, 0 means mag, 1 means accel */
   int32_t      input_mag_x;
   int32_t      input_mag_y;
   int32_t      input_mag_z;
   int32_t      input_accel_x;
   int32_t      input_accel_y;
   int32_t      input_accel_z;

   double       accel_input_variance;
   double       mag_input_variance;
   float        offset_HI_unfiltered_x;
   float        offset_HI_unfiltered_y;
   float        offset_HI_unfiltered_z;
   float        radius_HI;
   uint8_t      unfiltered_accuracy;
   uint8_t      accuracy_published;         /**< scale 0-4, 0 = fail, 4 = highest accuracy*/ 

   uint8_t      cal_algo_type;
   int32_t      mag_zero_bias_x; 
   int32_t      mag_zero_bias_y; 
   int32_t      mag_zero_bias_z; 
   uint32_t     offset_time;      // that will be equal to input sensor time

   uint8_t      hard_reset;
   uint8_t      soft_reset;

} sns_log_qmag_cal_result_s;

#define SNS_LOG_QMAG_CAL_REPORT_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;              /**< Type, as defined in log_codes.h */
   uint8_t      version;               /**< version of the log packet */
   uint8_t      timestamp_type;        /**< type of timestamp               */
   uint64_t     timestamp;             /**< time when sensor data sampled */
   int32_t      qmag_x;                /**< mag measurement along x axis */
   int32_t      qmag_y;                /**< mag measurement along y axis */
   int32_t      qmag_z;                /**< mag measurement along z axis */
   int32_t      qmag_zero_bias_corr_x; /**< mag x axis zero bias correction */
   int32_t      qmag_zero_bias_corr_y; /**< mag y axis zero bias correction */
   int32_t      qmag_zero_bias_corr_z; /**< mag z axis zero bias correction */
} sns_log_qmag_cal_report_s;

/**
   sns_log_time_report_s
   This type logs current timestamp offsets between processors
   LOG_SNS_TIME_SERVICE_OFFSETS_C
 */
#define SNS_LOG_TIME_REPORT_VERSION 1
typedef PACK(struct) {
   log_hdr_type log_type;    /**< Type, as defined in log_codes.h */
   uint8_t version;          /**< version of the log packet */
   int64_t apps_dsps_offset; /**< Signed offset (in ns) from the Apps processor to the DSPS timestamp. */
   int64_t apps_mdm_offset;  /**< Signed offset (in ns) from the Apps processor to the Modem timestamp.d */
} sns_log_time_report_s;

#define SNS_LOG_INTEG_ANGLE_CONFIG_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;           /**< Version                  */
  uint8_t      timestamp_type;    /**< type of timestamp        */
  uint64_t     timestamp;         /**< timestamp                */
  int32_t      sample_rate;       /**< Sampling Rate, Hz, Q16   */
  int32_t      clip_threshold;    /**< Clip threshold, rad, Q16 */
  uint8_t      algo_inst_id;      /**< algo instance id         */
} sns_log_integ_angle_config_s;

#define SNS_LOG_INTEG_ANGLE_RESULT_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;           /**< Version                    */
  uint8_t      timestamp_type;    /**< type of timestamp          */
  uint64_t     timestamp;         /**< timestamp                  */
  int32_t      g[3];              /**< gyro samples, rad/s Q16    */
  int32_t      ia[3];             /**< integrated angle , rad Q16 */
  uint8_t      algo_inst_id;      /**< algo instance id           */
} sns_log_integ_angle_result_s;

#define SNS_LOG_INTEG_ANGLE_REPORT_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;           /**< Version                    */
  uint8_t      timestamp_type;    /**< type of timestamp          */
  uint64_t     timestamp;         /**< timestamp                  */
  int32_t      report_id;         /**< report id                  */
  uint8_t      report_type;       /**< report type                */
  uint8_t      client_id;         /**< client id                  */
  int32_t      ia[3];             /**< integrated angle , rad Q16 */
  uint8_t      algo_inst_id;      /**< algo instance id           */
}sns_log_integ_angle_report_s;

#define SNS_LOG_GYRO_TAP_CONFIG_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;           /**< Version            */
  uint8_t      timestamp_type;    /**< type of timestamp  */
  uint64_t     timestamp;         /**< timestamp          */
  int32_t      sample_rate;
  int32_t      tap_time_win;
  int32_t      tap_time_sleep;
  int32_t      tap_dir_win;
  int32_t      accel_tap_thr;
  int32_t      lr_accel_jerk_min_thresh_min;
  int32_t      lr_gyro_jerk_min_thresh_min;
  int32_t      tb_accel_jerk_min_thr;
  int32_t      tb_gyro_jerk_min_thr;
  int32_t      jerk_win;
  int32_t      lr_accel_rat_jerk_yx;
  int32_t      lr_accel_rat_jerk_yz;
  int32_t      lr_gyro_rat_jerk_zy;
  int32_t      lr_gyro_rat_jerk_zx;
  int32_t      tb_accel_rat_jerk_xy;
  int32_t      tb_accel_rat_jerk_xz;
  int32_t      tb_gyro_rat_jerk_yx;
  int32_t      tb_gyro_rat_jerk_yz;
  int32_t      tb_accel_z_thresh;
  int32_t      tb_accel_z_rat_zx;
  int32_t      tb_accel_z_rat_zy;
  int32_t      ori_change_win;
  int32_t      ori_check_win;
  int32_t      ori_change_thr;
  int32_t      z_axis_inc;
  int32_t      loaded_axis_3_valid;
  int32_t      lr_min_accel_jerk_thresh_min;
  int32_t      lr_max_accel_jerk_thresh_min;
  int32_t      lr_min_gyro_jerk_thresh_min;
  int32_t      lr_max_gyro_jerk_thresh_min;
  int32_t      mild_accel_tap_thresh;
  int32_t      loaded_z_axis_anamoly;
  int32_t      ori_change_reject_mode;
  int32_t      stress_right_left;
  uint8_t      algo_inst_id;      /**< algo instance id   */
}sns_log_gyro_tap_config_s;

#define SNS_LOG_GYRO_TAP_RESULT_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;           /**< Version                    */
  uint8_t      timestamp_type;    /**< type of timestamp          */
  uint64_t     timestamp;         /**< timestamp                  */
  int32_t      g[3];              /**< gyro samples, rad/s Q16    */
  int32_t      a[3];              /**< accel samples, m/s/s   Q16 */
  int32_t      tap_event;         /**< tap event type             */
  int32_t      algo_state;        /**< reserved                   */
  uint8_t      algo_inst_id;      /**< algo instance id           */
} sns_log_gyro_tap_result_s;

#define SNS_LOG_GYRO_TAP_REPORT_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;           /**< Version                    */
  uint8_t      timestamp_type;    /**< type of timestamp          */
  uint64_t     timestamp;         /**< timestamp                  */
  int32_t      report_id;         /**< report id                  */
  uint8_t      report_type;       /**< report type                */
  uint8_t      client_id;         /**< client id                  */
  int32_t      tap_event;         /**< tap event type             */
  uint8_t      algo_inst_id;      /**< algo instance id           */
}sns_log_gyro_tap_report_s;

#define SNS_LOG_PAM_CONFIG_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;              /* version of the log packet*/
  uint8_t      timestamp_type;       /* type of timestamp  */
  uint64_t     timestamp;            /* timestamp in clock ticks*/
  uint32_t     measurement_period;   /* measurement period in seconds*/
  uint32_t     step_count_threshold; /* reporting threshold in steps*/
  uint32_t     sample_rate;         /* sample rate in Q16 Hz*/
  uint8_t      duty_cycle_on_percent;/* percentage of time for which algo is active*/
  uint8_t      algo_inst_id;         /* algorithm instance id   */
} sns_log_pam_config_s;

#define SNS_LOG_PAM_RESULT_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;                      /* version of the log packet */
  uint8_t      timestamp_type;               /* type of timestamp          */
  uint64_t     timestamp;                    /* timestamp in clock ticks*/
  int32_t      pedometer_step_count;         /*step count input from pedometer*/
  uint8_t      motion_state;                 /*motion state input from amd*/
  uint8_t      data_type;                    /*input type*/
  int32_t      pedometer_last_step_count;    /*last step count input from pedometer*/
  int32_t      pam_current_step_count;       /*current step count computed by pam*/
  int32_t      pam_last_reported_step_count; /*step count last reported by pam*/
  uint8_t      pam_report_decision;          /*0- don't report, 1- report*/
  uint8_t      algo_inst_id;                 /* algorithm instance id   */
} sns_log_pam_result_s;

#define SNS_LOG_PAM_REPORT_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;           /* version of the log packet */
  uint8_t      timestamp_type;    /* type of timestamp          */
  uint64_t     timestamp;         /* timestamp in clock ticks*/
  int32_t      step_count;        /* step count or current device motion state */
  uint8_t      algo_inst_id;      /* algo instance id           */
}sns_log_pam_report_s;

/**
   sns_log_fifo_event_s
   This type is used to log FIFO event. It
   is used for the following log types: LOG_SENSOR_FIFO_EVENT_C
 */

typedef enum
{
  SNS_DDF_FIFO_ENABLED =0,
  SNS_DDF_FIFO_DISABLED =1,
  SNS_DDF_FIFO_AVAILABLE =2,
  SNS_DDF_FIFO_WM_INT =3,
  SNS_DDF_FIFO_OVERFLOW =4,
  SNS_DDF_FIFO_ODR_CHANGED=5,
  SNS_DDF_FIFO_READ_WM=6,
  SNS_DDF_FIFO_READ_FLUSH=7,
  SNS_DDF_FIFO_DRAIN=8
} sns_fifo_event_e;

#define SNS_LOG_FIFO_EVENT_VERSION 2
typedef PACK(struct) {
  log_hdr_type  log_type;                     /**< Type, as defined in log_codes.h                  */
  uint8_t       version;                      /**< version of the log packet                        */
  uint64_t      timestamp;                    /**< Time in SSC ticks when the sensor event happened */
  uint32_t      sensor_id;                    /**< smgr sensor id of the sensor being logged        */
  uint8_t       fifo_event;                   /**< FIFO Event as specified in sns_fifo_event_e      */
  uint8_t       watermark_depth;              /**< water mark (num of samples )                     */
  uint16_t      odr;                          /**< current ODR                                      */
  uint8_t       hw_watermark_int_supported;   /**< if hardware watermark is supported               */
  uint16_t      max_watermark;                /**< maximum watermark supported by the sensor        */
} sns_log_fifo_event_s;

#define SNS_LOG_LATENCY_SAMPLING_POLL_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_typel;
  uint8_t     version;           /* Version                    */
  uint64_t    timestamp;         /* timestamp                  */
  int32_t      sensor_id;         /* sensor id                  */
  uint64_t     data_timestamp;    /* data timestamp             */
  int64_t      sampling_latency;  /* sampling latency           */
  int64_t      polling_latency;   /* polling latency            */
}sns_log_latency_sampling_poll_s;
 
#define SNS_LOG_LATENCY_SAMPLING_DRI_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_typel;
  uint8_t      version;                /* Version                    */
  uint64_t     timestamp;              /* timestamp                  */
  int32_t      sensor_id;              /* sensor id                  */
  uint64_t     data_timestamp;         /* data timestamp             */
  int64_t      sampling_latency;       /* sampling latency           */
  int64_t      dri_get_data_latency;   /* getting data latency       */
}sns_log_latency_sampling_dri_s;
 
#define SNS_LOG_LATENCY_DELIVERY_VERSION 1
typedef PACK(struct) {
  log_hdr_type log_typel;
  uint8_t      version;                /* Version                    */
  uint64_t     timestamp;              /* timestamp                  */
  int32_t      sensor_id;              /* sensor id                  */
  int64_t      data_timestamp;         /* data timestamp             */
  int64_t      delivery_latency;       /* delivery latency           */
}sns_log_latency_delivery_s; 

#define SNS_LOG_UIMG_MODE_VERSION 3
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;                    /**< Version, this version == 3                                   */
  uint32_t     state_vote_status;          /**< Each client vote status when vote decision changes
                                                Each client is allocated 4 bits to represent vote
                                                4 LSB is reserved for sns_pm's overall decision
                                                (0001) Micro Image
                                                (0010) Big Image
                                                (0100) No Client */
  /* All timestamps are in SSC ticks */
  uint64_t     state_vote_timestamp;       /**< timestamp of this vote                                         */
  uint64_t     bigImage_entry_ts;          /**< if bigImage vote, ts of bigImage entry, reserved otherwise     */
  uint64_t     last_uimg_vote_ts;          /**< timestamp of last uImage vote                                  */
  uint64_t     first_uimg_entry_ts;        /**< if bigImage vote, time of entry into uimg, reserved otherwise  */
  uint64_t     time_spent_in_uimg;         /**< if bigImage vote, time we were in uImage, reserved otherwise   */
  uint32_t     num_exits_from_uimg;        /**< if bigImage vote, how many times did we exit the state because 
                                                of reasons other than the SENSORS PM voting for an exit        */

}sns_log_uimg_mode_s;


#define SNS_LOG_GENERIC_MSG_VERSION 0
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;          /**< Version, this version == 0                                     */
  uint64_t     time_stamp;       /**< Time stamp when the log packet was created                     */
  uint8_t      user_id;          /**< Unique id to distinguish user (device driver or algo etc.)     */
  uint8_t      file_id;          /**< Unique id to distinguish log packets from different files      */
  uint16_t     line_id;          /**< Unique id to distinguish log packets within same file          */
  uint8_t      sensor_id;        /**< Unique id to distinguish multiple sensor types (if any)        */
  uint32_t     validity_mask;    /**< 32-bit field indicating validity of msg items in log packet    */
  uint64_t     msg_item_1_val;   /**< Message or data item #1                                        */
  uint64_t     msg_item_2_val;   /**< Message or data item #2                                        */
  uint32_t     msg_item_3_val;   /**< Message or data item #3                                        */
  uint32_t     msg_item_4_val;   /**< Message or data item #4                                        */
}sns_log_generic_msg_s;


#define SNS_LOG_IFMC_RESULT_VERSION 255
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;                      /* version of the log packet */
  uint8_t      timestamp_type;               /* type of timestamp          */
  uint64_t     timestamp;                    /* timestamp in SSC ticks*/

  uint8_t      input_type;

  uint8_t      input_smd_motion_state;
  uint8_t      input_ped_step_event;
  uint8_t      input_qmd_motion_state;
  int32_t      input_accel[3];                     /* accel input (x, y, z), m/s^2, Q16 */
  int32_t      input_gyro[3];                     /* gyro input (x, y, z), rad/s, Q16 */

  float        state_accel_var;
  uint8_t      state_cmc_motion_state;
  uint8_t      state_smd_motion_state;
  uint64_t     state_cum_num_turns;
  uint8_t      state_may_be_walking;
  uint8_t      state_step_count;
  float        state_obs_prob[7];
  float        state_belief[7];
  uint8_t      state_ifmc_label;
  uint8_t      state_run_autocorr;

  uint32_t     output_timestamp;
  uint8_t      output_motion_state;
  float        output_motion_state_probability;
  uint8_t      output_gyro_on;

  uint8_t      algo_inst_id;                 /* algorithm instance id   */
  uint8_t      accel_on;
} sns_log_ifmc_result_s;

#define SNS_LOG_IFMC_REPORT_VERSION 255
typedef PACK(struct) {
  log_hdr_type log_type;
  uint8_t      version;                      /* version of the log packet */
  uint8_t      timestamp_type;               /* type of timestamp          */
  uint64_t     timestamp;                    /* timestamp in SSC ticks*/

  uint8_t      output_motion_state;
  float        output_motion_state_probability;
  uint8_t      output_gyro_on;

  uint8_t      algo_inst_id;                 /* algorithm instance id   */
} sns_log_ifmc_report_s;

#if defined(_WIN32)
#pragma pack(pop)
#endif

#endif /* SNS_LOG_TYPES_H */
