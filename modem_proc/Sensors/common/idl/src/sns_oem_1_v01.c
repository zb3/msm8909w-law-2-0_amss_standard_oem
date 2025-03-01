/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        S N S _ O E M _ 1 _ V 0 1  . C

GENERAL DESCRIPTION
  This is the file which defines the SNS_OEM_1_SVC service Data structures.

  
  Copyright (c) 2013-2016 Qualcomm Technologies, Inc. All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential


  $Header: //commercial/MPSS.JO.2.0.c1.4/Main/modem_proc/Sensors/common/idl/src/sns_oem_1_v01.c#1 $
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
 *THIS IS AN AUTO GENERATED FILE. DO NOT ALTER IN ANY WAY
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* This file was generated with Tool version 6.14.7 
   It was generated on: Tue Feb  2 2016 (Spin 0)
   From IDL File: sns_oem_1_v01.idl */

#include "stdint.h"
#include "qmi_idl_lib_internal.h"
#include "sns_oem_1_v01.h"
#include "sns_common_v01.h"


/*Type Definitions*/
static const uint8_t sns_oem_1_output_s_data_v01[] = {
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_output_s_v01, data),
  SNS_OEM_1_MAX_ITEMS_PER_OUTPUT_DATA_V01,
  QMI_IDL_OFFSET8(sns_oem_1_output_s_v01, data) - QMI_IDL_OFFSET8(sns_oem_1_output_s_v01, data_len),

  QMI_IDL_FLAG_END_VALUE
};

/*Message Definitions*/
static const uint8_t sns_oem_1_enable_req_msg_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_enable_req_msg_v01, report_period),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(sns_oem_1_enable_req_msg_v01, sample_rate) - QMI_IDL_OFFSET8(sns_oem_1_enable_req_msg_v01, sample_rate_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_enable_req_msg_v01, sample_rate)
};

static const uint8_t sns_oem_1_enable_resp_msg_data_v01[] = {
  2,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sns_oem_1_enable_resp_msg_v01, resp),
  QMI_IDL_TYPE88(1, 0),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(sns_oem_1_enable_resp_msg_v01, instance_id) - QMI_IDL_OFFSET8(sns_oem_1_enable_resp_msg_v01, instance_id_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_enable_resp_msg_v01, instance_id)
};

static const uint8_t sns_oem_1_disable_req_msg_data_v01[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_disable_req_msg_v01, instance_id)
};

static const uint8_t sns_oem_1_disable_resp_msg_data_v01[] = {
  2,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sns_oem_1_disable_resp_msg_v01, resp),
  QMI_IDL_TYPE88(1, 0),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(sns_oem_1_disable_resp_msg_v01, instance_id) - QMI_IDL_OFFSET8(sns_oem_1_disable_resp_msg_v01, instance_id_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_disable_resp_msg_v01, instance_id)
};

static const uint8_t sns_oem_1_report_ind_msg_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_report_ind_msg_v01, instance_id),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_report_ind_msg_v01, timestamp),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x03,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sns_oem_1_report_ind_msg_v01, output),
  QMI_IDL_TYPE88(0, 0)
};

static const uint8_t sns_oem_1_get_report_req_msg_data_v01[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_get_report_req_msg_v01, instance_id)
};

static const uint8_t sns_oem_1_get_report_resp_msg_data_v01[] = {
  2,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sns_oem_1_get_report_resp_msg_v01, resp),
  QMI_IDL_TYPE88(1, 0),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(sns_oem_1_get_report_resp_msg_v01, instance_id) - QMI_IDL_OFFSET8(sns_oem_1_get_report_resp_msg_v01, instance_id_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_get_report_resp_msg_v01, instance_id),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(sns_oem_1_get_report_resp_msg_v01, timestamp) - QMI_IDL_OFFSET8(sns_oem_1_get_report_resp_msg_v01, timestamp_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_get_report_resp_msg_v01, timestamp),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(sns_oem_1_get_report_resp_msg_v01, output) - QMI_IDL_OFFSET8(sns_oem_1_get_report_resp_msg_v01, output_valid)),
  0x12,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sns_oem_1_get_report_resp_msg_v01, output),
  QMI_IDL_TYPE88(0, 0)
};

static const uint8_t sns_oem_1_error_ind_msg_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_error_ind_msg_v01, error),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_oem_1_error_ind_msg_v01, instance_id)
};

static const uint8_t sns_sam_oem_1_batch_req_msg_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_sam_oem_1_batch_req_msg_v01, instance_id),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sns_sam_oem_1_batch_req_msg_v01, batch_period)
};

static const uint8_t sns_sam_oem_1_batch_resp_msg_data_v01[] = {
  2,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sns_sam_oem_1_batch_resp_msg_v01, resp),
  QMI_IDL_TYPE88(1, 0),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(sns_sam_oem_1_batch_resp_msg_v01, instance_id) - QMI_IDL_OFFSET8(sns_sam_oem_1_batch_resp_msg_v01, instance_id_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_sam_oem_1_batch_resp_msg_v01, instance_id),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(sns_sam_oem_1_batch_resp_msg_v01, max_batch_size) - QMI_IDL_OFFSET8(sns_sam_oem_1_batch_resp_msg_v01, max_batch_size_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sns_sam_oem_1_batch_resp_msg_v01, max_batch_size),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(sns_sam_oem_1_batch_resp_msg_v01, timestamp) - QMI_IDL_OFFSET8(sns_sam_oem_1_batch_resp_msg_v01, timestamp_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sns_sam_oem_1_batch_resp_msg_v01, timestamp)
};

static const uint8_t sns_sam_oem_1_batch_ind_msg_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sns_sam_oem_1_batch_ind_msg_v01, instance_id),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sns_sam_oem_1_batch_ind_msg_v01, first_report_timestamp),

  0x03,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(sns_sam_oem_1_batch_ind_msg_v01, timestamp_offsets),
  SNS_SAM_OEM_1_MAX_ITEMS_IN_BATCH_V01,
  QMI_IDL_OFFSET8(sns_sam_oem_1_batch_ind_msg_v01, timestamp_offsets) - QMI_IDL_OFFSET8(sns_sam_oem_1_batch_ind_msg_v01, timestamp_offsets_len),

  0x04,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(sns_sam_oem_1_batch_ind_msg_v01, reports),
  SNS_SAM_OEM_1_MAX_ITEMS_IN_BATCH_V01,
  QMI_IDL_OFFSET16RELATIVE(sns_sam_oem_1_batch_ind_msg_v01, reports) - QMI_IDL_OFFSET16RELATIVE(sns_sam_oem_1_batch_ind_msg_v01, reports_len),
  QMI_IDL_TYPE88(0, 0),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(sns_sam_oem_1_batch_ind_msg_v01, ind_type) - QMI_IDL_OFFSET16RELATIVE(sns_sam_oem_1_batch_ind_msg_v01, ind_type_valid)),
  0x10,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(sns_sam_oem_1_batch_ind_msg_v01, ind_type)
};

/* Type Table */
static const qmi_idl_type_table_entry  SNS_OEM_1_SVC_type_table_v01[] = {
  {sizeof(sns_oem_1_output_s_v01), sns_oem_1_output_s_data_v01}
};

/* Message Table */
static const qmi_idl_message_table_entry SNS_OEM_1_SVC_message_table_v01[] = {
  {sizeof(sns_oem_1_enable_req_msg_v01), sns_oem_1_enable_req_msg_data_v01},
  {sizeof(sns_oem_1_enable_resp_msg_v01), sns_oem_1_enable_resp_msg_data_v01},
  {sizeof(sns_oem_1_disable_req_msg_v01), sns_oem_1_disable_req_msg_data_v01},
  {sizeof(sns_oem_1_disable_resp_msg_v01), sns_oem_1_disable_resp_msg_data_v01},
  {sizeof(sns_oem_1_report_ind_msg_v01), sns_oem_1_report_ind_msg_data_v01},
  {sizeof(sns_oem_1_get_report_req_msg_v01), sns_oem_1_get_report_req_msg_data_v01},
  {sizeof(sns_oem_1_get_report_resp_msg_v01), sns_oem_1_get_report_resp_msg_data_v01},
  {sizeof(sns_oem_1_error_ind_msg_v01), sns_oem_1_error_ind_msg_data_v01},
  {sizeof(sns_sam_oem_1_batch_req_msg_v01), sns_sam_oem_1_batch_req_msg_data_v01},
  {sizeof(sns_sam_oem_1_batch_resp_msg_v01), sns_sam_oem_1_batch_resp_msg_data_v01},
  {sizeof(sns_sam_oem_1_batch_ind_msg_v01), sns_sam_oem_1_batch_ind_msg_data_v01}
};

/* Range Table */
/* No Ranges Defined in IDL */

/* Predefine the Type Table Object */
static const qmi_idl_type_table_object SNS_OEM_1_SVC_qmi_idl_type_table_object_v01;

/*Referenced Tables Array*/
static const qmi_idl_type_table_object *SNS_OEM_1_SVC_qmi_idl_type_table_object_referenced_tables_v01[] =
{&SNS_OEM_1_SVC_qmi_idl_type_table_object_v01, &sns_common_qmi_idl_type_table_object_v01};

/*Type Table Object*/
static const qmi_idl_type_table_object SNS_OEM_1_SVC_qmi_idl_type_table_object_v01 = {
  sizeof(SNS_OEM_1_SVC_type_table_v01)/sizeof(qmi_idl_type_table_entry ),
  sizeof(SNS_OEM_1_SVC_message_table_v01)/sizeof(qmi_idl_message_table_entry),
  1,
  SNS_OEM_1_SVC_type_table_v01,
  SNS_OEM_1_SVC_message_table_v01,
  SNS_OEM_1_SVC_qmi_idl_type_table_object_referenced_tables_v01,
  NULL
};

/*Arrays of service_message_table_entries for commands, responses and indications*/
static const qmi_idl_service_message_table_entry SNS_OEM_1_SVC_service_command_messages_v01[] = {
  {SNS_OEM_1_CANCEL_REQ_V01, QMI_IDL_TYPE16(1, 0), 0},
  {SNS_OEM_1_VERSION_REQ_V01, QMI_IDL_TYPE16(1, 2), 0},
  {SNS_OEM_1_ENABLE_REQ_V01, QMI_IDL_TYPE16(0, 0), 14},
  {SNS_OEM_1_DISABLE_REQ_V01, QMI_IDL_TYPE16(0, 2), 4},
  {SNS_OEM_1_GET_REPORT_REQ_V01, QMI_IDL_TYPE16(0, 5), 4},
  {SNS_SAM_OEM_1_BATCH_REQ_V01, QMI_IDL_TYPE16(0, 8), 11}
};

static const qmi_idl_service_message_table_entry SNS_OEM_1_SVC_service_response_messages_v01[] = {
  {SNS_OEM_1_CANCEL_RESP_V01, QMI_IDL_TYPE16(1, 1), 5},
  {SNS_OEM_1_VERSION_RESP_V01, QMI_IDL_TYPE16(1, 3), 17},
  {SNS_OEM_1_ENABLE_RESP_V01, QMI_IDL_TYPE16(0, 1), 9},
  {SNS_OEM_1_DISABLE_RESP_V01, QMI_IDL_TYPE16(0, 3), 9},
  {SNS_OEM_1_GET_REPORT_RESP_V01, QMI_IDL_TYPE16(0, 6), 32},
  {SNS_SAM_OEM_1_BATCH_RESP_V01, QMI_IDL_TYPE16(0, 9), 23}
};

static const qmi_idl_service_message_table_entry SNS_OEM_1_SVC_service_indication_messages_v01[] = {
  {SNS_OEM_1_REPORT_IND_V01, QMI_IDL_TYPE16(0, 4), 27},
  {SNS_OEM_1_ERROR_IND_V01, QMI_IDL_TYPE16(0, 7), 8},
  {SNS_SAM_OEM_1_BATCH_IND_V01, QMI_IDL_TYPE16(0, 10), 1523}
};

/*Service Object*/
struct qmi_idl_service_object SNS_OEM_1_SVC_qmi_idl_service_object_v01 = {
  0x06,
  0x01,
  SNS_QMI_SVC_ID_31_V01,
  1523,
  { sizeof(SNS_OEM_1_SVC_service_command_messages_v01)/sizeof(qmi_idl_service_message_table_entry),
    sizeof(SNS_OEM_1_SVC_service_response_messages_v01)/sizeof(qmi_idl_service_message_table_entry),
    sizeof(SNS_OEM_1_SVC_service_indication_messages_v01)/sizeof(qmi_idl_service_message_table_entry) },
  { SNS_OEM_1_SVC_service_command_messages_v01, SNS_OEM_1_SVC_service_response_messages_v01, SNS_OEM_1_SVC_service_indication_messages_v01},
  &SNS_OEM_1_SVC_qmi_idl_type_table_object_v01,
  0x02,
  NULL
};

/* Service Object Accessor */
qmi_idl_service_object_type SNS_OEM_1_SVC_get_service_object_internal_v01
 ( int32_t idl_maj_version, int32_t idl_min_version, int32_t library_version ){
  if ( SNS_OEM_1_SVC_V01_IDL_MAJOR_VERS != idl_maj_version || SNS_OEM_1_SVC_V01_IDL_MINOR_VERS != idl_min_version
       || SNS_OEM_1_SVC_V01_IDL_TOOL_VERS != library_version)
  {
    return NULL;
  }
  return (qmi_idl_service_object_type)&SNS_OEM_1_SVC_qmi_idl_service_object_v01;
}

