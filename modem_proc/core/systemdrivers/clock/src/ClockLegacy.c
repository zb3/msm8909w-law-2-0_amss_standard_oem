/*
===========================================================================
*/
/**
  @file ClockLegacy.c 
  
  Wrapper code for legacy clock regime functions to use the new Clock DAL
  driver.
*/
/*  
  ====================================================================

  Copyright (c) 2010 Qualcomm Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 

  ==================================================================== 
  $Header: //components/rel/core.mpss/3.5.c12.3/systemdrivers/clock/src/ClockLegacy.c#1 $
  $DateTime: 2016/12/13 07:59:23 $
  $Author: mplcsds1 $
  ====================================================================
*/ 


/*=========================================================================
      Include Files
==========================================================================*/

#include "DALDeviceId.h"
#include "DALSys.h"
#include "DDIClock.h"


/*=========================================================================
      Type Definitions
==========================================================================*/


/*=========================================================================
      Data
==========================================================================*/

/*
 * Handle to the clock DAL.
 */
static   DalDeviceHandle         *hClock;


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : clk_regime_init
** =========================================================================*/

void clk_regime_init (void)
{
  DALResult                      eResult;

  /*-----------------------------------------------------------------------*/
  /* Attach to the clock DAL.                                              */
  /*-----------------------------------------------------------------------*/

  eResult = DAL_DeviceAttach(DALDEVICEID_CLOCK, &hClock);

  if (eResult != DAL_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_CLOCK, DALSYS_LOGEVENT_ERROR,
      "Unable to attach to clock DAL: %d", eResult);
    return;
  }

} /* END clk_regime_init */


/* =========================================================================
**  Function : clk_regime_init_nv
** =========================================================================*/

void clk_regime_init_nv (void)
{
  if (hClock == NULL)
  {
    clk_regime_init();
  }

  DalClock_LoadNV(hClock);

} /* END clk_regime_init_nv */
