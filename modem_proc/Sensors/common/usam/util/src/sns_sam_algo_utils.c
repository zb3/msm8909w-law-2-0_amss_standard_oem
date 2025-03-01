/*============================================================================
  @file sns_sam_algo_utils.c

  Utility functions for SAM algorithms

  Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include "sns_reg_api_v02.h"
#include "sns_smgr_api_v01.h"
#include "sns_memmgr.h"
#include "sns_sam_algo_utils.h"
#include "sns_sam_algo_api.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/

#ifdef SNS_USES_ISLAND
#define SNS_SAM_UIMAGE_CODE __attribute__((section (".text.uSAM")))
#define SNS_SAM_UIMAGE_DATA __attribute__((section (".data.uSAM")))
#else
#define SNS_SAM_UIMAGE_CODE
#define SNS_SAM_UIMAGE_DATA
#endif /* USES_ISLAND */

/*============================================================================
  Function Definitions
  ===========================================================================*/

sns_sam_err
sns_sam_util_gen_smgr_buffer_req( sns_sam_sensor_data_info_req *sensorReq,
  sns_sam_enable_req *enableReqMsg )
{
  uint8_t i;
  sns_smgr_buffering_req_msg_v01 *enableReq =
    (sns_smgr_buffering_req_msg_v01*)enableReqMsg->msg.buf;

  if( sensorReq->sensorCount > 1 )
  {
    return SAM_EFAILED;
  }
  enableReqMsg->msgID = SNS_SMGR_BUFFERING_REQ_V01;
  enableReqMsg->msg.bufSize = sizeof(sns_smgr_buffering_req_msg_v01);

  enableReq->Action = SNS_SMGR_BUFFERING_ACTION_ADD_V01;

  /* Check if report rate is larger or equal to one. If it is, delete
     the fractional part to avoid the rounding error; if not, keep the
     same for supporting sub-hz reporting request. */
  enableReq->ReportRate = (sensorReq->reportRate > 0xffff)
                          ? (sensorReq->reportRate & 0xffff0000)
                          : sensorReq->reportRate;

  enableReq->SrcModule_valid = true;
  enableReq->SrcModule = SNS_SAM_MODULE;
  enableReq->Item_len = sensorReq->sensorCount;

  for( i = 0; i < sensorReq->sensorCount; i++ )
  {
    // Use factory calibrated accel, till accel autocal stabilizes
    // Since factory calibrated accelerometer is acceptable for
    // existing features, this will allow accel-autocal to be tested
    // in isolation with minimal impact on existing features
    if( SNS_SMGR_ID_ACCEL_V01 == sensorReq->sensorDbase[i].sensorId )
    {
      enableReq->Item[i].Calibration = SNS_SMGR_CAL_SEL_FACTORY_CAL_V01;
    }
    else
    {
      enableReq->Item[i].Calibration = SNS_SMGR_CAL_SEL_FULL_CAL_V01;
    }

    enableReq->Item[i].SensorId = sensorReq->sensorDbase[i].sensorId;
    enableReq->Item[i].DataType = sensorReq->sensorDbase[i].dataType;
    enableReq->Item[i].SampleQuality = sensorReq->sensorDbase[i].sampleQual;
    enableReq->Item[i].Decimation = SNS_SMGR_DECIMATION_FILTER_V01;
    enableReq->Item[i].SamplingRate =
      (uint16_t)(sensorReq->sensorDbase[i].buffered_sampleRate >> FX_QFACTOR); // delete fractional part
  }

  if( SNS_SAM_MODULE == SNS_MODULE_DSPS_SAM )
  {
    enableReq->notify_suspend_valid = true;
    enableReq->notify_suspend.proc_type = SNS_PROC_SSC_V01;
    enableReq->notify_suspend.send_indications_during_suspend = true;
  }
  else if( SNS_SAM_MODULE == SNS_MODULE_APPS_SAM )
  {
    enableReq->notify_suspend_valid = true;
    enableReq->notify_suspend.proc_type = SNS_PROC_APPS_V01;
    enableReq->notify_suspend.send_indications_during_suspend = false;
  }
  else
  {
    enableReq->notify_suspend_valid = false;
  }

  return SAM_ENONE;
}

void
sns_sam_util_gen_smgr_periodic_req( sns_sam_sensor_data_info_req *sensorReq,
  sns_sam_enable_req *enableReqMsg )
{
  uint8_t i;

  sns_smgr_periodic_report_req_msg_v01 *enableReq =
    (sns_smgr_periodic_report_req_msg_v01*)enableReqMsg->msg.buf;

  enableReqMsg->msgID = SNS_SMGR_REPORT_REQ_V01;
  enableReqMsg->msg.bufSize = sizeof(sns_smgr_periodic_report_req_msg_v01);

  enableReq->BufferFactor = 1;
  enableReq->Action = SNS_SMGR_REPORT_ACTION_ADD_V01;
  enableReq->ReportRate = (uint16_t)(sensorReq->sampleRate >> FX_QFACTOR);
  enableReq->SrcModule_valid = true;
  enableReq->SrcModule = SNS_SAM_MODULE;
  enableReq->cal_sel_valid = true;
  enableReq->cal_sel_len = sensorReq->sensorCount;
  enableReq->SampleQuality_valid = true;
  enableReq->SampleQuality_len = sensorReq->sensorCount;
  enableReq->Item_len = sensorReq->sensorCount;

  for( i = 0; i < sensorReq->sensorCount; i++ )
  {
    // Use factory calibrated accel, till accel autocal stabilizes
    // Since factory calibrated accelerometer is acceptable for
    // existing features, this will allow accel-autocal to be tested
    // in isolation with minimal impact on existing features
    if( sensorReq->sensorDbase[i].sensorId == SNS_SMGR_ID_ACCEL_V01 )
    {
      enableReq->cal_sel[i] = SNS_SMGR_CAL_SEL_FACTORY_CAL_V01;
    }
    else
    {
      enableReq->cal_sel[i] = SNS_SMGR_CAL_SEL_FULL_CAL_V01;
    }

    enableReq->Item[i].SensorId = sensorReq->sensorDbase[i].sensorId;
    enableReq->Item[i].DataType = sensorReq->sensorDbase[i].dataType;
    enableReq->SampleQuality[i] = sensorReq->sensorDbase[i].sampleQual;
    enableReq->Item[i].Decimation = SNS_SMGR_DECIMATION_FILTER_V01;
  }

  if( SNS_SAM_MODULE == SNS_MODULE_DSPS_SAM )
  {
    enableReq->notify_suspend_valid = true;
    enableReq->notify_suspend.proc_type = SNS_PROC_SSC_V01;
    enableReq->notify_suspend.send_indications_during_suspend = true;
  }
  else if( SNS_SAM_MODULE == SNS_MODULE_APPS_SAM )
  {
    enableReq->notify_suspend_valid = true;
    enableReq->notify_suspend.proc_type = SNS_PROC_APPS_V01;
    enableReq->notify_suspend.send_indications_during_suspend = false;
  }
  else
  {
    enableReq->notify_suspend_valid = false;
  }
}

SNS_SAM_UIMAGE_CODE sns_sam_err sns_sam_buffered_data_init(sns_sam_buffered_data *bufSample)
{
    SNS_OS_MEMSET( bufSample->samplePtr, 0, sizeof(bufSample->samplePtr) );
    bufSample->samplesProcessed = 0;
    bufSample->buffer_data_valid = false;
    return SAM_ENONE;
}

SNS_SAM_UIMAGE_CODE sns_sam_err
sns_sam_get_single_buffered_sample(sns_smgr_buffering_ind_msg_v01 *indPtr,
  sns_sam_buffered_data *bufSample, uint32_t *sampleIdx)
{
  uint32_t i;

  if(false == bufSample->buffer_data_valid)
  {
    bufSample->buffer_data_valid = true;
    bufSample->indPtr = indPtr;
    for( i = 0; i < indPtr->Indices_len; i++ )
    {
      uint8_t firstSampleIndex = indPtr->Indices[i].FirstSampleIdx;
      bufSample->samplePtr[i] = &indPtr->Samples[firstSampleIndex];
      bufSample->sampleCount[i] = indPtr->Indices[i].SampleCount;
      bufSample->timestamp[i] = indPtr->Indices[i].FirstSampleTimestamp;
      bufSample->sensorUID[i] = sns_sam_get_sensor_uid(indPtr->Indices[i].SensorId);
    }
  }

  bufSample->current_sample.timestamp = 0;
  bufSample->current_sample.sensorUid = 0;
  bufSample->current_sample.dimension_count = 0;

  if( bufSample->samplesProcessed < indPtr->Samples_len &&
      bufSample->indPtr == indPtr)
  {
    sns_sam_timestamp minTimestamp = 0;
    uint32_t oldestSampleIdx = 0;
    sns_smgr_buffering_sample_s_v01 * oldestSamplePtr = NULL;

    bufSample->samplesProcessed++;
   *sampleIdx = bufSample->samplesProcessed;
    for( i = 0; i < indPtr->Indices_len; i++ )
    {
      // Find first valid sample to initialize min timestamp
      if( bufSample->samplePtr[i] != NULL )
      {
        minTimestamp = bufSample->timestamp[i];
        oldestSampleIdx = i;
        break;
      }
    }

    for( i = oldestSampleIdx + 1; i < indPtr->Indices_len; i++ )
    {
      // Find first minimum based on timestamp
      if( bufSample->samplePtr[i] != NULL &&
          ((bufSample->timestamp[i] < minTimestamp && (minTimestamp - bufSample->timestamp[i] < UINT32_MAX / 2)) ||
          (bufSample->timestamp[i] > minTimestamp && (bufSample->timestamp[i] - minTimestamp > UINT32_MAX / 2)) ))
      {
        minTimestamp = bufSample->timestamp[i];
        oldestSampleIdx = i;
      }
    }

    oldestSamplePtr = bufSample->samplePtr[oldestSampleIdx];

    if( !oldestSamplePtr )
    {
      return SAM_EFAILED;
    }

    if( bufSample->sampleCount[oldestSampleIdx] > 1 )
    {
      bufSample->samplePtr[oldestSampleIdx]++;
      bufSample->timestamp[oldestSampleIdx] += ((sns_smgr_buffering_sample_s_v01 *)(bufSample->samplePtr[oldestSampleIdx]))->TimeStampOffset;
      bufSample->sampleCount[oldestSampleIdx]--;
    }
    else
    {
      bufSample->samplePtr[oldestSampleIdx] =  NULL;
      bufSample->timestamp[oldestSampleIdx] = UINT32_MAX;
    }

    bufSample->current_sample.timestamp = minTimestamp;
    bufSample->current_sample.sensorUid = bufSample->sensorUID[oldestSampleIdx];
    bufSample->current_sample.dimension_count = sns_sam_get_sensor_dimensions(bufSample->sensorUID[oldestSampleIdx]);

    if( SNS_SAM_UTIL_INVALID_SENSORINFO == bufSample->current_sample.dimension_count )
    {
      return SAM_EFAILED;
    }

    for( i = 0; i < bufSample->current_sample.dimension_count; i++ )
    {
      bufSample->current_sample.data[i] = oldestSamplePtr->Data[i];
    }

    if( oldestSamplePtr->Flags & SNS_SMGR_ITEM_FLAG_FAC_CAL_V01 ||
        oldestSamplePtr->Flags & SNS_SMGR_ITEM_FLAG_AUTO_CAL_V01 )
    {
      uint8_t accuracy = 0x06; // bits 1,2 of Flags used for accuracy

      if( oldestSamplePtr->Flags & SNS_SMGR_ITEM_FLAG_FAC_CAL_V01 )
      {
        bufSample->current_sample.cal_type = SNS_SAM_CAL_TYPE_FAC;
      }
      else if( oldestSamplePtr->Flags & SNS_SMGR_ITEM_FLAG_AUTO_CAL_V01 )
      {
        bufSample->current_sample.cal_type = SNS_SAM_CAL_TYPE_AUTO;
      }

      accuracy &= oldestSamplePtr->Flags;
      accuracy >>= 1;
      bufSample->current_sample.accuracy = accuracy;
    }
    else
    {
      bufSample->current_sample.cal_type = SNS_SAM_CAL_TYPE_UNCAL;
    }

    if( oldestSamplePtr->Flags & SNS_SMGR_ITEM_FLAG_INVALID_V01 ||
        oldestSamplePtr->Quality ==
        SNS_SMGR_ITEM_QUALITY_INVALID_FAILED_SENSOR_V01 ||
        oldestSamplePtr->Quality ==
        SNS_SMGR_ITEM_QUALITY_INVALID_NOT_READY_V01 ||
        oldestSamplePtr->Quality ==
        SNS_SMGR_ITEM_QUALITY_INVALID_SUSPENDED_V01 )
    {
      return SAM_ENOT_AVAILABLE;
    }

    return SAM_ENONE;
  }
  return SAM_EMAX;
}

SNS_SAM_UIMAGE_CODE sns_sam_err
sns_sam_process_smgr_report_ind(
  const sns_smgr_periodic_report_ind_msg_v01 *indPtr,
  sns_sam_sensor_data_s periodicSample[], uint32_t *PeriodicSampleCnt )
{
  uint32_t i, j;

  *PeriodicSampleCnt = 0;

  if( SNS_SMGR_REPORT_OK_V01 != indPtr->status )
  {
    // SNS_SAM_DEBUG2(MEDIUM, DBG_SAM_SMGR_IND_STATUS, dataReqId, indPtr->status);
    return SAM_EFAILED;
  }

  //Validate sensor data and process valid data only
  for( i = 0; i < indPtr->Item_len; i++ )
  {
    if( indPtr->Item[i].ItemFlags & SNS_SMGR_ITEM_FLAG_INVALID_V01 ||
        indPtr->Item[i].ItemQuality ==
        SNS_SMGR_ITEM_QUALITY_INVALID_FAILED_SENSOR_V01 ||
        indPtr->Item[i].ItemQuality ==
        SNS_SMGR_ITEM_QUALITY_INVALID_NOT_READY_V01 ||
        indPtr->Item[i].ItemQuality ==
        SNS_SMGR_ITEM_QUALITY_INVALID_SUSPENDED_V01 )
    {
      // SNS_SAM_DEBUG1(MEDIUM, DBG_SAM_SMGR_IND_DROPPED, dataReqId);
      return SAM_EFAILED;
    }
    else
    {
      if(*PeriodicSampleCnt < SNS_SMGR_MAX_ITEMS_PER_REPORT_V01)
      {
        periodicSample[*PeriodicSampleCnt].sensorUid =
          sns_sam_get_sensor_uid(indPtr->Item[i].SensorId);
        periodicSample[*PeriodicSampleCnt].timestamp =
          indPtr->Item[i].TimeStamp;
        periodicSample[*PeriodicSampleCnt].dimension_count =
          sns_sam_get_sensor_dimensions(periodicSample->sensorUid);

        for( j = 0; j < periodicSample[*PeriodicSampleCnt].dimension_count; j++ )
        {
            periodicSample[*PeriodicSampleCnt].data[j] =
              indPtr->Item[i].ItemData[j];
        }

        if( indPtr->Item[i].ItemFlags & SNS_SMGR_ITEM_FLAG_FAC_CAL_V01 ||
           indPtr->Item[i].ItemFlags & SNS_SMGR_ITEM_FLAG_AUTO_CAL_V01 )
        {
          uint8_t accuracy = 0x06; // bits 1,2 of Item Flag used for accuracy

          if( indPtr->Item[i].ItemFlags & SNS_SMGR_ITEM_FLAG_FAC_CAL_V01 )
          {
            periodicSample[*PeriodicSampleCnt].cal_type = SNS_SAM_CAL_TYPE_FAC;
          }
          else if( indPtr->Item[i].ItemFlags & SNS_SMGR_ITEM_FLAG_AUTO_CAL_V01 )
          {
            periodicSample[*PeriodicSampleCnt].cal_type = SNS_SAM_CAL_TYPE_AUTO;
          }

          accuracy &= indPtr->Item[i].ItemFlags;
          accuracy >>= 1;
          periodicSample[*PeriodicSampleCnt].accuracy = accuracy;
        }
        else
        {
          periodicSample[*PeriodicSampleCnt].cal_type = SNS_SAM_CAL_TYPE_UNCAL;
        }

        *PeriodicSampleCnt += 1;
      }
    }
  }

  return SAM_ENONE;
}

SNS_SAM_UIMAGE_CODE sns_sam_sensor_uid
sns_sam_get_sensor_uid( uint8_t sensorID )
{
  switch(sensorID)
  {
  case SNS_SMGR_ID_ACCEL_V01:
    return SNS_SMGR_SUID_ACCEL_1_V01;

  case SNS_SMGR_ID_GYRO_V01:
    return SNS_SMGR_SUID_GYRO_1_V01;

  case SNS_SMGR_ID_MAG_V01:
    return SNS_SMGR_SUID_MAG_1_V01;

  case SNS_SMGR_ID_PRESSURE_V01:
    return SNS_SMGR_SUID_PRESSURE_1_V01;

  case SNS_SMGR_ID_RGB_V01:
    return SNS_SMGR_SUID_RGB_1_V01;

  case SNS_SMGR_ID_SAR_V01:
    return SNS_SMGR_SUID_SAR_1_V01;

  case SNS_SMGR_ID_HALL_EFFECT_V01:
    return SNS_SMGR_SUID_HALL_EFFECT_1_V01;

  case SNS_SMGR_ID_PROX_LIGHT_V01:
    return SNS_SMGR_SUID_PROX_1_V01;

  case SNS_SMGR_ID_ULTRA_VIOLET_V01:
    return SNS_SMGR_SUID_ULTRA_VIOLET_1_V01;

  case  SNS_SMGR_ID_HEART_RATE_V01:
    return SNS_SMGR_SUID_HEART_RATE_1_V01;

  case SNS_SMGR_ID_TILT_EVENT_V01:
    return SNS_SMGR_SUID_TILT_EVENT_1_V01;
  
  case SNS_SMGR_ID_ORIENTATION_EVENT_V01:
    return SNS_SMGR_SUID_ORIENTATION_EVENT_1_V01;
  
  case SNS_SMGR_ID_TAP_V01:
    return SNS_SMGR_SUID_DOUBLE_TAP_1_V01;
  
  default:
    return 0;
  }
}

SNS_SAM_UIMAGE_CODE uint8_t
sns_sam_get_sensor_dimensions( sns_sam_sensor_uid sensorUID )
{
  switch(sensorUID)
  {
  case SNS_SMGR_SUID_ACCEL_1_V01:
    return 3;

  case SNS_SMGR_SUID_GYRO_1_V01:
    return 3;

  case SNS_SMGR_SUID_MAG_1_V01:
    return 3;

  case SNS_SMGR_SUID_PRESSURE_1_V01:
    return 1;

  case SNS_SMGR_SUID_RGB_1_V01:
    return 3;

  case SNS_SMGR_SUID_SAR_1_V01:
    return 1;

  case SNS_SMGR_SUID_HALL_EFFECT_1_V01:
    return 1;

  case SNS_SMGR_SUID_PROX_1_V01:
    return 1;

  case SNS_SMGR_SUID_ULTRA_VIOLET_1_V01:
    return 3;

  case  SNS_SMGR_SUID_HEART_RATE_1_V01:
    return 3;

  case SNS_SMGR_SUID_TILT_EVENT_1_V01:
    return 1;
  
  case SNS_SMGR_SUID_ORIENTATION_EVENT_1_V01:
    return 1;
  
  case SNS_SMGR_SUID_DOUBLE_TAP_1_V01:
    return 1;
  default:
    return SNS_SAM_UTIL_INVALID_SENSORINFO;
  }
}

SNS_SAM_UIMAGE_CODE uint8_t
sns_sam_get_sensor_id( sns_sam_sensor_uid sensorUID )
{
  switch(sensorUID)
  {
  case SNS_SMGR_SUID_ACCEL_1_V01:
    return SNS_SMGR_ID_ACCEL_V01;

  case SNS_SMGR_SUID_GYRO_1_V01:
    return SNS_SMGR_ID_GYRO_V01;

  case SNS_SMGR_SUID_MAG_1_V01:
    return SNS_SMGR_ID_MAG_V01;

  case SNS_SMGR_SUID_PRESSURE_1_V01:
    return SNS_SMGR_ID_PRESSURE_V01;

  case SNS_SMGR_SUID_RGB_1_V01:
    return SNS_SMGR_ID_RGB_V01;

  case SNS_SMGR_SUID_SAR_1_V01:
    return SNS_SMGR_ID_SAR_V01;

  case SNS_SMGR_SUID_HALL_EFFECT_1_V01:
    return SNS_SMGR_ID_HALL_EFFECT_V01;

  case SNS_SMGR_SUID_PROX_1_V01:
    return SNS_SMGR_ID_PROX_LIGHT_V01;

  case SNS_SMGR_SUID_ULTRA_VIOLET_1_V01:
    return SNS_SMGR_ID_ULTRA_VIOLET_V01;

  case SNS_SMGR_SUID_HEART_RATE_1_V01:
    return SNS_SMGR_ID_HEART_RATE_V01;
  
  case SNS_SMGR_SUID_TILT_EVENT_1_V01:
    return SNS_SMGR_ID_TILT_EVENT_V01;
  
  case SNS_SMGR_SUID_ORIENTATION_EVENT_1_V01:
    return SNS_SMGR_ID_ORIENTATION_EVENT_V01;
  
  case SNS_SMGR_SUID_DOUBLE_TAP_1_V01:
    return SNS_SMGR_ID_TAP_V01;

  default:
      return SNS_SAM_UTIL_INVALID_SENSORINFO;
  }
}

q16_t
sns_sam_calc_sample_rate( q16_t sampleRate, q16_t reportPeriod,
  q16_t defSampleRate )
{
  q16_t rv;

  if( 0 == sampleRate )
  {
    rv = defSampleRate;
  }
  else
  {
    rv = sampleRate;
  }

  if( 0 != reportPeriod )
  {
    float sample_rate = FX_FIXTOFLT_Q16_SP(rv);
    float report_rate = 1.0f / FX_FIXTOFLT_Q16_SP(reportPeriod);

    if( report_rate - sample_rate > .1 )
  {
    rv = FX_FLTTOFIX_Q16(report_rate);
    }
  }

  return rv;
}

SNS_SAM_UIMAGE_CODE bool sns_sam_limit_sensor_data_range(
  const q16_t input[SNS_SMGR_SENSOR_DIMENSION_V01],
  q16_t output[SNS_SMGR_SENSOR_DIMENSION_V01],
  q16_t maxRange)
{
  bool rv = FALSE;
  uint8_t i;

  for (i=0; i<SNS_SMGR_SENSOR_DIMENSION_V01; i++)
  {
    if (input[i] > maxRange)
    {
      output[i] = maxRange;
      rv = TRUE;
    }
    else if (input[i] < -maxRange)
    {
      output[i] = -maxRange;
      rv = TRUE;
    }
    else
    {
      output[i] = input[i];
    }
  }

  return rv;
}

