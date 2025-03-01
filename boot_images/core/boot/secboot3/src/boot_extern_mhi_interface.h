#ifndef BOOT_EXTERN_MHI_INTERFACE_H
#define BOOT_EXTERN_MHI_INTERFACE_H

/*===========================================================================

                    BOOT EXTERN MHI DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external mhi drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2013 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
$Header: //components/rel/boot.bf/3.1.2.c3/boot_images/core/boot/secboot3/src/boot_extern_mhi_interface.h#1 $
$DateTime: 2015/09/01 00:30:35 $
$Author: pwbldsvc $
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/16/13   kedara  Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_sahara.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================

**  Function :  boot_mhi_init

** ==========================================================================
*/
/*!
 * 
 * @brief   This function initializes the MHI, PCIe hardware.
 *
 * @details This function initializes the Mhi. PCIe hardware.
 * 
 * 
 * @return  None.
 * 
 */
#ifdef FEATURE_BOOT_EXTERN_MHI_COMPLETED
  void boot_mhi_init( void );
#else
  static inline void boot_mhi_init( void )
  {
  }
#endif


/*===========================================================================

**  Function :  boot_mhi_poll

** ==========================================================================
*/
/*!
 * 
 * @brief   This function polls the hardware for events.
 *
 * @details This function polls the hardware for events.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
#ifdef FEATURE_BOOT_EXTERN_MHI_COMPLETED
  void boot_mhi_poll(void);
#else
  static inline void boot_mhi_poll(void)
  {
  }
#endif


/*===========================================================================

**  Function :  mhi_shutdown

** ==========================================================================
*/
/*!
 * 
 * @brief   This function performs a shutdown of the hardware.
 *
 * @details This function performs a shutdown of the hardware.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
#ifdef FEATURE_BOOT_EXTERN_MHI_COMPLETED
  void boot_mhi_shutdown(void);
#else
  static inline void boot_mhi_shutdown(void)
  {
  }
#endif


/*===========================================================================

**  Function :  boot_mhi_receive

** ==========================================================================
*/
/*!
 * 
 * @brief   This function receives a bulk of data upto the input length.
 *
 * @details This function will continue to poll the hardware until the receive
 *          URB is not NULL, upon which the data will be copied to the
 *          input receive buffer.
 * 
 * @param   *rx_buf     -  [IN/OUT] Receive buffer for data, must be 4 byte aligned 
 * @param   len         -  [IN    ] Length of buffer, must be multiples of max packet size
 * @param   rx_cb       -  [IN    ] Return callback function
 * @param   *err_code   -  [IN/OUT] Any error that occurs during transfer
 * @param   type        -  [IN    ] Type of packet
 * 
 * @return  Number of bytes receieved.
 * 
 */
#ifdef FEATURE_BOOT_EXTERN_MHI_COMPLETED
  uint32 boot_mhi_receive(byte *rx_buf, 
                          uint32 len, 
                          sahara_rx_cb_type rx_cb, 
                          uint32 * err_code,
                          enum boot_sahara_packet_type type );
#else
  static inline uint32 boot_mhi_receive(byte *rx_buf, 
                                     uint32 len, 
                                     sahara_rx_cb_type rx_cb, 
                                     uint32 * err_code,
                                     enum boot_sahara_packet_type type)
  {
    return 0;
  }
#endif


/*===========================================================================

**  Function :  boot_mhi_transmit

** ==========================================================================
*/
/*!
 * 
 * @brief   This function transmits a bulk of data upto the input length.
 *
 * @details This function will continue to poll the hardware until the transmit
 *          URB transfer is complete.
 * 
 * @param   *tx_buf     -  [IN/OUT] Transmit buffer for data, must be 4 byte aligned 
 * @param   len         -  [IN    ] Length of data to trasmit in bytes
 * @param   tx_cb       -  [IN    ] Transmit complete callback
 * @param   *err_code   -  [IN/OUT] Any error that occurs during transfer
 * 
 * @return  Number of bytes transmitted.
 * 
 */
#ifdef FEATURE_BOOT_EXTERN_MHI_COMPLETED
  uint32 boot_mhi_transmit(byte *tx_buf,    
                            uint32 len,
                            sahara_tx_cb_type tx_cb,
                            uint32 * err_code);
#else
  static inline uint32 boot_mhi_transmit(byte *tx_buf,    
                                        uint32 len,       
                                        sahara_tx_cb_type tx_cb, 
                                        uint32 * err_code)
  {
    return 0;
  }
#endif



/*===========================================================================

**  Function :  boot_mhi_get_max_packet_size

** ==========================================================================
*/
/*!
 * 
 * @brief   This function returns whether PCIe spec defined max packet sizes
 *          to be used
 *
 * @details Correct packet sizes are determined internally and will be
 *          returned to external interface
 *          
 * @return  Max packet sizes
 * 
 */
#ifdef FEATURE_BOOT_EXTERN_MHI_COMPLETED
  uint32 boot_mhi_get_max_packet_size(void);
#else
  static inline uint32 boot_mhi_get_max_packet_size(void)
  {
    return 0;
  }
#endif

/*===========================================================================

**  Function :  mhi_get_max_raw_data_size

** ==========================================================================
*/
/*!
 * 
 * @brief   Returns the maximum bulk transfer level size that can be requested
 *          by the client
 *
 * @details Windows only support maximum bulk transfer size of 1MB, whereas
 *          Linux supports a larger maximum 
 *          
 * @return  Max PCIe bulk transfer level size
 * 
 */
#ifdef FEATURE_BOOT_EXTERN_MHI_COMPLETED
  uint32 boot_mhi_get_max_raw_data_size(void);
#else
  static inline uint32 boot_mhi_get_max_raw_data_size(void)
  {
    return 0;
  }
#endif

#endif /* BOOT_EXTERN_MHI_INTERFACE_H */
