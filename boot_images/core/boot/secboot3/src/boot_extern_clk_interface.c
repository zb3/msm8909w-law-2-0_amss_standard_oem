/*===========================================================================

                    BOOT EXTERN CLK DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external clock drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2014 - 2015 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
$Header: //components/rel/boot.bf/3.1.2.c3/boot_images/core/boot/secboot3/src/boot_extern_clk_interface.c#1 $
$DateTime: 2015/09/01 00:30:35 $
$Author: pwbldsvc $
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/08/15   jz      Call clock API to get Apps clock speed
11/21/14   sk      Added new clock api's
06/10/14   ck      Added boot_clock_get_apps_speed
02/18/14   kpa     Support booting at CLOCK_BOOT_PERF_NOMINAL
07/26/13   rj      Added new api for enabling i2C clocks
07/11/13   rj      Passing ddr type parameter to boot_pre_ddr_clock_init() 
                   function
04/03/13   sl      Add boot_clock_get_ddr_speed
12/13/12   jz      Add boot_clock_set_perf_level
09/21/12   dh      Add boot_clock_debug_init
07/31/12   dh      Add boot_clock_exit_boot
05/08/12   dh      add new clock init api
09/23/11   dh      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_extern_clk_interface.h"
#include CUST_H

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


/*===========================================================================

**  Function :  boot_clk_regime_apps_init_boot

** ==========================================================================
*/
/*!
*
*  This function initializes the apps processor clocks and ramps up
*  the processor speed to the initial one specified in the BSP.
*  It should be invoked from the apps boot loader code.
*
* 
*
* @par Dependencies Shared memory must be ready.
*
* @return  FALSE if initialization failed.
*
* @par Side Effects  The core clock and MSMC2 voltage are switched.
*
*/
boolean boot_clock_init(void)
{
#ifndef BOOT_CLK_PLAN_NOMINAL
  return Clock_Init(CLOCK_BOOT_PERF_MAX, CLOCK_BOOT_PERF_MAX);
#else
  return Clock_Init(CLOCK_BOOT_PERF_NOMINAL, CLOCK_BOOT_PERF_NOMINAL);
#endif  
  
}


/* ========================================================================
**  Function : boot_clock_pre_ddr_init
** ======================================================================*/
/*!
    Description: Configure all clocks needed for DDR configuration.

    @param None
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean boot_pre_ddr_clock_init(uint32 ddr_type)
{
  return Clock_PreDDRInit(ddr_type);
}

/* ========================================================================
**  Function : boot_pre_i2c_clock_init
** ======================================================================*/
/*!
    Description: Configure i2c clocks needed for eeprom init.

    @param None
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean boot_pre_i2c_clock_init(void)
{
  return Clock_I2CInit();
}

/* ============================================================================
**  Function : boot_dload_clock_init
** ============================================================================
*/
/*!
    This will initialize clocks for the RAMs in the system that are to be saved
    during crash dump procedures in the downloader.

    @param
      None
    @return
      None

    @dependencies
    None.

    @sa None
*/
void boot_dload_clock_init(void)
{
  Clock_InitForDownloadMode(); 
}


/* ============================================================================
**  Function : boot_clock_exit_boot
** ============================================================================
*/
/*!
    This function will disable clocks that is not needed after SBL

    @param
      None
    @return
      True if success, False otherwise

    @dependencies
    None.

    @sa None
*/
boolean boot_clock_exit_boot(void)
{
  return Clock_ExitBoot();
}


/* ============================================================================
**  Function : boot_clock_debug_init
** ============================================================================
*/
/*!

    This function is called very early in boot.  It is used for work-arounds that
    need to be done before JTAG attaches at the SBL "hold focus button" spin loop.

    @return
    TRUE -- Clean up was successful.
    FALSE -- Clean up failed.

   @dependencies
    You cannot use busywait in this function.

*/
boolean boot_clock_debug_init(void)
{
  return Clock_DebugInit();
}

/*===========================================================================
**  Function :  boot_clock_set_sys_perf_level
** ==========================================================================
*/
/*!
*
* This function Configures system to a specific perf level.
*
* @param eCPUPerfLevel [in] - CPU performance level.
*
* @return
*  TRUE -- system was configured to perf level successful.
*  FALSE -- Configuration failed.
*
* @dependencies
* None.
*
*/
boolean boot_clock_set_sys_perf_level(ClockBootPerfLevelType eCPUPerfLevel)
{
  return Clock_SetSysPerfLevel(eCPUPerfLevel);
}


/*===========================================================================
**  Function :  boot_clock_set_L2_perf_level
** ==========================================================================
*/
/*!
*
* This function Configures L2 to a specific perf level.
*
* @param eCPUPerfLevel [in] - L2 performance level.
*
* @return
*  TRUE -- L2 was configured to perf level successful.
*  FALSE -- Configuration failed.
*
* @dependencies
* None.
*
*/
boolean boot_clock_set_L2_perf_level(ClockBootPerfLevelType eCPUPerfLevel)
{
  return Clock_SetL2PerfLevel(eCPUPerfLevel);
}


/*===========================================================================
**  Function :  boot_clock_set_cpu_perf_level
** ==========================================================================
*/
/*!
*
* This function Configures CPU to a specific perf level.
*
* @param eCPUPerfLevel [in] - CPU performance level.
*
* @return
*  TRUE -- CPU was configured to perf level successful.
*  FALSE -- Configuration failed.
*
* @dependencies
* None.
*
*/
boolean boot_clock_set_cpu_perf_level(ClockBootPerfLevelType eCPUPerfLevel)
{
  return Clock_SetCPUPerfLevel(eCPUPerfLevel);
}

/*===========================================================================
**  Function :  boot_clock_get_ddr_speed
** ==========================================================================
*/
/*!
*
* This function returns DDR clock speed in KHz.
*
* @param
*   None
*
* @return
*   DDR clock speed in KHz
*
* @dependencies
*   None
*
*/
uint32 boot_clock_get_ddr_speed(void)
{
  return Clock_DDRSpeed();
}


/*===========================================================================
**  Function :  boot_clock_get_apps_speed
** ==========================================================================
*/
/*!
*
* This function returns apps clock speed in KHz.
*
* @param
*   core - Core number to get clock speed for.
*
* @return
*   Apps clock speed in KHz
*
* @dependencies
*   Should be called after clock_init 
*
*/
uint32 boot_clock_get_apps_speed(uint32 core)
{
  uint32 apps_speed = 0;
  
  Clock_GetClockFrequency(CLK_APPS,  &apps_speed);
  	
  return apps_speed;
}

/*===========================================================================
**  Function :  boot_query_bimc_clock
** ==========================================================================
*/
/*!
*
* This function lets the client query the BIMC frequency plan and the number 
  of supported frequencies.
*
* @return
*   None
*
* @dependencies
*   None
*
*/
void boot_query_bimc_clock(ClockQueryType nQuery,void* pResource)
{
 Clock_BIMCQuery(nQuery,&pResource);
}

/* =========================================================================
**  Function : boot_clock_set_bimcspeed
** =========================================================================*/
/*!
    Toggle between GPLL5/BIMC PLL if required and select the correct BIMC MUX configurations

    @param nFreqKHz - gcc_bimc_clk freq to be configured
    @return
    TRUE -- Configuration was successful.
    FALSE -- Configuration failed.

    @dependencies
    None.

    @sa None
*/
boolean boot_clock_set_bimcspeed(uint32 nFreqKHz)
{
 return Clock_SetBIMCSpeed(nFreqKHz);
}

/* ============================================================================
**  Function : boot_clock_InitUSB
** ============================================================================
*/
/*!
    Configure USB clocks.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean boot_clock_InitUSB(void)
{
 return Clock_InitUSB();
}

/* ============================================================================
**  Function : boot_clock_DisableUSB
** ============================================================================
*/
/*!
    Disable USB clocks.

    @param None.
    @return
    TRUE -- Disable was successful.
    FALSE -- Disable failed.

    @dependencies
    None.

    @sa None
*/
boolean boot_clock_DisableUSB(void)
{
 return Clock_DisableUSB();
}

/* ============================================================================
**  Function : boot_clock_set_sdc_clock_freq
** ============================================================================
*/
/*!
    Configure SDC clock to a specific perf level.

    @param eClockPerfLevel   -  [IN] SDC Clock perf level
           eClock            -  [IN] SDC clock to configure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
boolean boot_clock_set_sdc_clock_freq(ClockBootPerfLevelType ePerfLevel, ClockSDCType eClock)
{
 return Clock_SetSDCClockFrequency(ePerfLevel, eClock);
}

/* ============================================================================
**  Function : boot_clock_set_sdc_clock_freqExt
** ============================================================================
*/
/*!
    Configure SDC clock to a specific perf level.

    @param eClockPerfLevel   -  [IN] Clock frequency level
           eClock            -  [IN] SDC clock to configure
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
uint32 boot_clock_set_sdc_clock_freqExt(uint32 nFreqKHz, ClockSDCType eClock)
{
 return Clock_SetSDCClockFrequencyExt(nFreqKHz, eClock);
}
 
/* ============================================================================
**	Function : boot_clock_disable_UARTClock
** ============================================================================
*/
/*!
	Disable specific UART clock.

	@param    eClock       -	[IN] UART clock to Disable
	@return
	TRUE -- Clock disable was successful.
	FALSE -- Clock disable failed.

	@dependencies
	None.

	@sa None
*/
boolean boot_clock_disable_UARTClock(ClockUARTType eClock)
{
 return Clock_DisableUARTClock(eClock);
}

/* ============================================================================
**	Function : boot_clock_SetUARTClockFrequency
** ============================================================================
*/
/*!
	Configure UART clock to a specific perf level.

	@param    ePerfLevel    -	[IN] UART Clock perf level
		      eClock	-	[IN] UART clock to configure
	@return
	TRUE -- Initialization was successful.
	FALSE -- Initialization failed.

	@dependencies
	None.

	@sa None
*/
boolean boot_clock_SetUARTClockFrequency
(
  ClockBootPerfLevelType ePerfLevel,
  ClockUARTType eClock
)
{
 return Clock_SetUARTClockFrequency(ePerfLevel, eClock);
}

