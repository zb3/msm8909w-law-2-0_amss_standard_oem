#ifndef SLIM_SERVICE_STATUS_H
#define SLIM_SERVICE_STATUS_H
/**
  @file
  @brief Utility for SLIM providers.

  This module is an utility tool for SLIM providers to keep track of service
  status.
  @ingroup slim_CoreProviderStatus
*/

/*============================================================================
               Copyright (c) 2014-2015 QUALCOMM Atheros, Inc.
               All Rights Reserved.
               Qualcomm Atheros Confidential and Proprietary
============================================================================*/
/* $Header: //commercial/MPSS.JO.2.0.c1.4/Main/modem_proc/gps/gnss/slim/common/core/inc/slim_service_status.h#1 $ */

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "slim_provider_data.h"
#include "slim_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

//! @addtogroup slim_CoreProviderStatus
//! @{

//! @todo Extend this API to handle recoverable service state change errors.

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/*! Enumeration for services that support multiplexing and define a rate in the
reporting request.
*/
typedef enum
{
  eSLIM_SERVICE_STATUS_RATE_NONE = -1,
  /**< Invalid */

  eSLIM_SERVICE_STATUS_RATE_ACCEL = 0,
  /**< Accelerometer */
  eSLIM_SERVICE_STATUS_RATE_ACCEL_TEMP,
  /**< Accelerometer temperature */
  eSLIM_SERVICE_STATUS_RATE_GYRO,
  /**< Gyro */
  eSLIM_SERVICE_STATUS_RATE_GYRO_TEMP,
  /**< Gyro temperature */
  eSLIM_SERVICE_STATUS_RATE_MAG_CALIB,
  /**< Calibrated magnetometer */
  eSLIM_SERVICE_STATUS_RATE_MAG_UNCALIB,
  /**< Uncalibrated magnetometer */
  eSLIM_SERVICE_STATUS_RATE_BARO,
  /**< Barometer */

  eSLIM_SERVICE_STATUS_RATE_COUNT,
  /**< Service count */

  eSLIM_SERVICE_STATUS_RATE_MAX = 2147483647 /* Force 32bit */
} slim_ServiceStatusRateEnumType;

/*! Struct for service rate data */
typedef struct
{
  uint16_t w_SampleCount;
  /**< Samples per batch */

  uint16_t w_ReportRate;
  /**< Batches per second */
} slim_ServiceStatusRateStructType;

/*! Struct for service status data */
typedef struct slim_ServiceStatusStructType
{
  slimServiceEnumT e_Service;
  /**< SLIM Service */
  int8 b_ClientCount;
  /**< Current client count for the service. */
  slim_ServiceMtDataStructType z_MtOffset;
  /**< Mt offset for service time-sync. */

  /* These configuration parameters are used only by device sensor data */
  uint16 w_ReportRateHz;
  /**< Current configuration for sample rate */
  uint16 w_SampleCount;
  /**< Current configuration for batch count */

} slim_ServiceStatusStructType;

/*! Struct for provider client data */
typedef struct slim_ProviderClientStatusStructType
{
  slimClientHandleT p_Handle;
  /**< Client handle */
  boolean b_Open;
  /**< TRUE if connection is open. */
  slimAvailableServiceMaskT q_EnabledServiceMask;
  /**< Mask of enabled services. */

  slim_ServiceStatusRateStructType z_ServiceRates[eSLIM_SERVICE_STATUS_RATE_COUNT];
  /**< Service rates requested by client. */

} slim_ProviderClientStatusStructType;

/*! Struct for provider service status data */
typedef struct slim_ProviderStatusStructType
{
  slim_ServiceStatusStructType *pz_StatusArray;
  /**< Pointer to the array of status objects. */
  uint32 q_ServiceCount;
  /**< Count of the status array objects. */
  slim_ProviderClientStatusStructType z_ClientData[SLIM_CLIENT_MAX_COUNT];
  /**< Client status. */

} slim_ProviderStatusStructType;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/**
@brief Initializes provider service status struct.

Function initializes provider service status struct.

@param[in] pz_ProviderStatus Pointer to the provider status.
@param[in] q_ServiceCount    Count of services supported by the provider. It is
                             number of elements in @a pz_ProviderStatus array.
@param[in] q_SupportedServiceMask Mask of supported services.
*/
void slim_ServiceStatusInitialize
(
  slim_ProviderStatusStructType *pz_ProviderStatus,
  uint32 q_ServiceCount,
  slimAvailableServiceMaskT q_SupportedServiceMask
);

/**
@brief Resets all services and time sync data

Function marks all services as disabled and resets time sync data. This
is done to handle case when provider looses service connectivity and needs
prepare for later use.

@param[in] pz_ProviderStatus Pointer to the provider status.
*/
void slim_ServiceStatusReset
(
  slim_ProviderStatusStructType *pz_ProviderStatus
);

/**
@brief Resets one service and it's time sync data

Function marks service as disabled and resets time sync data. This is done to
handle case when provider looses service connectivity and needs prepare for
later use.

@param[in] pz_ProviderStatus Pointer to the provider status.
@param[in] e_Service Service to reset.
*/
void slim_ServiceStatusResetService
(
  slim_ProviderStatusStructType *pz_ProviderStatus,
  slimServiceEnumT e_Service
);

/**
@brief Adds client to the provider status client registry.

Function adds client to the provider status client registry. Should be called
when SLIM client opens a provider connection.

@param[in] pz_ProviderStatus Pointer to the provider status.
@param[in] p_Handle          SLIM client handle.
*/
void slim_ServiceStatusAddClient
(
  slim_ProviderStatusStructType *pz_ProviderStatus,
  slimClientHandleT p_Handle
);

/**
@brief Removes client from the provider status client registry.

Function removes client from the provider status client registry. Should be called
when SLIM client closes a provider connection.

@param[in] pz_ProviderStatus Pointer to the provider status.
@param[in] p_Handle          SLIM client handle.
*/
void slim_ServiceStatusRemoveClient
(
  slim_ProviderStatusStructType *pz_ProviderStatus,
  slimClientHandleT p_Handle
);

/**
@brief Enables service for the given client.

Function sets service enabled for the given client.

@param[in] pz_ProviderStatus Pointer to the provider status.
@param[in] e_Service         SLIM service.
@param[in] b_Enable          TRUE if service was enabled.
@param[in] p_Handle          SLIM client handle.
*/
void slim_ServiceStatusEnable
(
  slim_ProviderStatusStructType *pz_ProviderStatus,
  slimServiceEnumT e_Service,
  boolean b_Enable,
  slimClientHandleT p_Handle
);

/**
@brief Enables service for the given client.

Function sets service enabled for the given client. Stores also service
reporting rates.

@param[in] pz_ProviderStatus   Pointer to the provider status.
@param[in] e_Service           SLIM service.
@param[in] b_Enable            TRUE if service was enabled.
@param[in] w_BatchRateHz       Used batch rate (for device sensor data).
@param[in] w_SampleCount       Used sample count (for device sensor data).
@param[in] w_ClientBatchRateHz Client batch rate (for device sensor data).
@param[in] w_ClientSampleCount Client sample count (for device sensor data).
@param[in] p_Handle            SLIM client handle.
*/
void slim_ServiceStatusEnableForRate
(
  slim_ProviderStatusStructType *pz_ProviderStatus,
  slimServiceEnumT e_Service,
  boolean b_Enable,
  uint16 w_BatchRateHz,
  uint16 w_SampleCount,
  uint16 w_ClientBatchRateHz,
  uint16 w_ClientSampleCount,
  slimClientHandleT p_Handle
);

/**
@brief Checks if service is enabled currently for the given client.

Function checks if service is enabled currently for the given client.

@param[in] pz_ProviderStatus Pointer to the provider status.
@param[in] p_Handle          SLIM client handle.
@param[in] e_Service         SLIM service.

@retval TRUE  if service is enabled for the given client.
@retval FALSE if the service is not enabled for the given client.
*/
boolean slim_ServiceStatusIsEnabled
(
  slim_ProviderStatusStructType *pz_ProviderStatus,
  slimClientHandleT p_Handle,
  slimServiceEnumT e_Service
);

/**
@brief Checks if requested service can be enabled or disabled for the given
       client.

Function checks if requested service can be enabled or disabled for the given
client.

@param[in]  pz_ProviderStatus Pointer to the provider status.
@param[in]  p_Handle          SLIM client handle.
@param[in]  e_Service         SLIM service.
@param[in]  b_Enable          TRUE, if service should be enabled.
@param[out] pb_SendRequestOut To this variable is stored whether the request
                              shall be sent to the remote provider or not.

@return eSLIM_SUCCESS if enable request can be done. Otherwise SLIM error code.
*/
slimErrorEnumT slim_ServiceStatusCanEnable
(
  slim_ProviderStatusStructType *pz_ProviderStatus,
  slimClientHandleT p_Handle,
  slimServiceEnumT e_Service,
  boolean b_Enable,
  boolean *pb_SendRequestOut
);

/**
@brief Checks if requested service can be enabled or disabled for the given
       client.

Function checks if requested service can be enabled or disabled for the given
client. Checks also the if the given reporting rate exceeds the current one.

@param[in]  pz_ProviderStatus       Pointer to the provider status.
@param[in]  p_Handle                SLIM client handle.
@param[in]  e_Service               SLIM service.
@param[in]  b_Enable                TRUE, if service should be enabled.
@param[in]  w_BatchRateHz           Requested batch rate (for rate service).
@param[in]  w_SampleCount           Requested sample count (for rate service).
@param[out] pb_SendRequestOut       To this variable is stored whether the
                                    request shall be sent to the remote
                                    provider or not.
@param[out] pb_SendEnableRequestOut To this variable is stored whether the
                                    request should be sent as an enable request
                                    to the remote provider or not.

@return eSLIM_SUCCESS if enable request can be done. Otherwise SLIM error code.
*/
slimErrorEnumT slim_ServiceStatusCanEnableForRate
(
  slim_ProviderStatusStructType *pz_ProviderStatus,
  slimClientHandleT p_Handle,
  slimServiceEnumT e_Service,
  boolean b_Enable,
  uint16 w_BatchRateHz,
  uint16 w_SampleCount,
  boolean *pb_SendRequestOut,
  boolean *pb_SendEnableRequestOut
);

/**
@brief Adjusts sample rate and batch count for the given service.

Function adjusts sample rate and batch count for the given service.

@param[in] pz_ProviderStatus  Pointer to the provider status.
@param[in] e_Service          SLIM service.
@param[in] p_Handle           SLIM client handle.
@param[in] pw_ReportRateHz    New sample rate.
@param[in] pw_SampleCount     New batch count.
*/
void slim_ServiceStatusGetSampleRate
(
  const slim_ProviderStatusStructType *pz_ProviderStatus,
  slimServiceEnumT e_Service,
  slimClientHandleT p_Handle,
  uint16 *pw_ReportRateHz,
  uint16 *pw_SampleCount
);

/**
@brief Provides timesync mt offset for the given SLIM service.

Function provides timesync mt offset for the given SLIM service.

@param[in]  pz_ProviderStatus Pointer to the provider status.
@param[in]  e_Service         SLIM service.
@param[out] pz_MtOffsetOut    Pointer to mt offset. Data is stored to this
                              variable if found.

@return TRUE if mt data was found. FALSE otherwise.
*/
boolean slim_ServiceStatusGetMtOffset
(
  const slim_ProviderStatusStructType *pz_ProviderStatus,
  slimServiceEnumT e_Service,
  slim_ServiceMtDataStructType *pz_MtOffsetOut
);

/**
@brief Sets timesync mt offset for the given SLIM service.

Function sets timesync mt offset for the given SLIM service.

@param[in] pz_ProviderStatus Pointer to the provider status.
@param[in] e_Service         SLIM service. If eSLIM_SERVICE_NONE, data is
                             applied to all services.
@param[in] pz_MtOffset       Pointer to mt offset to be set.
*/
void slim_ServiceStatusSetMtOffset
(
  slim_ProviderStatusStructType *pz_ProviderStatus,
  slimServiceEnumT e_Service,
  const slim_ServiceMtDataStructType *pz_MtOffset
);

/**
@brief Dispatches data indication to all registered clients.

Function dispatches data indication to all registered clients.

@param[in] pz_ProviderStatus Pointer to the provider status.
@param[in] e_Provider        SLIM provider.
@param[in] e_Service         SLIM service.
@param[in] e_Error           SLIM error.
@param[in] e_MessageId       SLIM message id.
@param[in] w_DataSize        Size of the payload.
@param[in] p_Data            Pointer to the payload.

@sa slim_CoreDispatchData
*/
void slim_ServiceStatusDispatchDataToRegistered
(
  const slim_ProviderStatusStructType *pz_ProviderStatus,
  slim_ProviderEnumType e_Provider,
  slimServiceEnumT e_Service,
  slimErrorEnumT e_Error,
  slimMessageIdEnumT e_MessageId,
  uint16 w_DataSize,
  const void *p_Data
);

//! @}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SLIM_SERVICE_STATUS_H */
