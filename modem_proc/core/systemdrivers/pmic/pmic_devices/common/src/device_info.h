#ifndef _DEVICE_INFO_H_
#define _DEVICE_INFO_H_

/*! \file device_info.h
*   \n
*   \brief This file contains PMIC Device Info struct and init function declarations
*   \n
*   \n &copy; Copyright 2010-2013 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/*===================================================================
                    EDIT HISTORY FOR MODULE
 This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.mpss/3.5.c12.3/systemdrivers/pmic/pmic_devices/common/src/device_info.h#1 $
$Author: mplcsds1 $

when       who     what, where, why
--------    ---     ------------------------------------------------

====================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_qc_pmic.h"


/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/
/* Maximum number of PMIC DEVICES */
#define PM_MAX_NUM_PMICS         7

/* Maximum number of PMIC SLAVE IDs */
/* Current SPMI spec supports 16 slave id */
#define PM_MAX_NUM_SLAVE_IDS     14

#define INVALID_SLAVE_ID         0xFF

typedef enum
{
    PmDeviceIndex1,
    PmDeviceIndex2,
    PmDeviceIndex3,
    PmDeviceIndex4,
    PmDeviceIndex_INVALID
}DeviceIndex;

typedef enum
{
    QcPmicDevice,
    ISLChargingDevice,
    Invalid_Device_Type
} DeviceType;

/**
  @struct pmiC_DeviceInfo
  @brief  This struct is used to store the PMIC device
          information which gets filled in Comm Info struct
          during PMIC Comm Initialization.
 */
typedef struct
{
    pm_model_type mPmicModel;
    DeviceIndex mDeviceIndex;
    uint8 mPmicAllLayerRevision;
    uint32 mSlaveId[2]; /* Each PMIC device has 2 slave ids */
    DeviceType mDeviceType;
    uint32 mMaxRegisterSize;
}pmiC_DeviceInfo;

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/

/**
 * @name pm_version_detect
 *
 * @brief This function is called to read and store the PMIC Version
 *        information. This function verifies if the PMIC device exists
 *        by reading PMIC peripheral type value and checking it's same
 *        as QC PMIC type value. Then it stores the PMIC device
 *        information such as PMIC's Model type value (Peripheral
 *        Subtype value), All Layer Revision number and Metal Revision
 *        number.
 *
 * @param None.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *          else SPMI errors
 */
pm_err_flag_type pm_version_detect(void);

/**
 * @name pm_get_slave_id
 *
 * @brief This function is called to get the slave ids of the
 *        PMIC device. Each PMIC device has 2 slave ids. To get
 *        the first slave id of the PMIC device the
 *        slave_id_index argument is 0 and for second slave id
 *        the slave_id_index argument is 1.
 *
 * @param[in]  pmic_index.Primary PMIC:0 Secondary PMIC:1
 * @param[in]  slave_id_index.Primary Slave ID:0 Secondary Slave
 *             ID :1
 * @param[out] slave_id_ptr:
 *                Variable to return to the caller with slave id
 *                value specific to the pmic device and slave id
 *                index.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Error in
 *          returning slave id.
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 */
pm_err_flag_type pm_get_slave_id(uint8 pmic_index, uint8 slave_id_index, uint32* slave_id_ptr);

/**
 * @name pm_get_num_slaves_per_pmic
 *
 * @brief This function is returns the number of slaves on a QC pmic
 *
 * @param None.
 *
 * @return  num of slaves on QC pmic on the target
 */


uint8 pm_get_num_slaves_per_pmic(void);


#endif /* _DEVICE_INFO_H_ */
