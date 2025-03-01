/*==============================================================================
  Copyright (c) 2008 - 2012 Qualcomm Technologies Incorporated.
           All Rights Reserved.

$Header: //components/rel/boot.bf/3.1.2.c3/boot_images/core/dal/src/dal_asm_wrap.c#1 $

when       who     description
--------   ---     ---------------------------------------------------------- 
06/19/12   aa      Cleanup Feautrization. 
01/04/12   aa      Cleanup for older ARM architechure & WINSIM (V5 & less). 
12/11/08   ML      Implemented Atomic Ops and Move cache control to boot\dalmodenv.c
                   Implemented simulation support
==============================================================================*/
#include "DALFramework.h"
#include "dalconfig.h"

/*
   Wrapper around asm implemented functions
   Declare the following internally as they are not available for
   all architectutes
*/

/*
   LockedGetW
   Tags the address pTarget and retrieves the value pointed by pTarget
*/
uint32 DALFW_LockedGetW(volatile uint32 * pTarget);

/*
   LockedConditionalSetW
   conditionaly sets the "value" of the address pointed by pTarget:
   - if no other other address had been tagged by the current processor and
   - if no other processor has modified *pTarget then this function succeeds
   and has successfully stored the word "value" in *pTarget
*/
DALResult DALFW_LockedConditionalSetW(volatile uint32 *pTarget,  uint32 value);

uint32 DALFW_LockedExchangeW(volatile uint32 *pTarget, uint32 value)
{
    uint32 prevValue;
    do
    {
        prevValue = DALFW_LockedGetW(pTarget);
    }
    while (DALFW_LockedConditionalSetW(pTarget, value)!=DAL_SUCCESS);
    return prevValue;
}


uint32 DALFW_LockedIncrementW(volatile uint32 *pTarget)
{
    uint32 prevValue;
    do
    {
        prevValue = DALFW_LockedGetW(pTarget);
    }
    while (DALFW_LockedConditionalSetW(pTarget, ++prevValue)!=DAL_SUCCESS);
    return prevValue;
}


uint32 DALFW_LockedDecrementW(volatile uint32 *pTarget)
{
    uint32 prevValue;
    do
    {
        prevValue = DALFW_LockedGetW(pTarget);
    }
    while (DALFW_LockedConditionalSetW(pTarget, --prevValue)!=DAL_SUCCESS);
    return prevValue;
}


uint32 DALFW_LockedGetModifySetW(volatile uint32 *pTarget, uint32 AND_mask, uint32 OR_value)
{
    uint32 prevValue;
    do
    {
        prevValue = DALFW_LockedGetW(pTarget);
        prevValue = (prevValue & AND_mask) | OR_value;
    }
    while (DALFW_LockedConditionalSetW(pTarget, prevValue)!=DAL_SUCCESS);
    return prevValue;
}

uint32 DALFW_LockedCompareExchangeW(volatile uint32 *pTarget, uint32 comparand, uint32 value)
{
    uint32 prevValue;
    do
    {
        prevValue = DALFW_LockedGetW(pTarget);
        if (prevValue != comparand)
        {
            // untag it using original value and return
            DALFW_LockedConditionalSetW(pTarget, prevValue);
            return prevValue;
        }
        // try setting to new value
    }
    while (DALFW_LockedConditionalSetW(pTarget, value)!=DAL_SUCCESS);
    return value;
}

/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*-- Semi-Raw Inter CPU (i.e External shared) spinlocks ----------------------------*/
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

/*
   Keep in mind these are not raw-spin locks and intended for very low contention
   locks as while these locks are being held the running thread may be interrupted
   which will cause the other processor to loop for an undetermined amount of time.
   For such scenarios it may be necessary that instead the "Try" implementations
   be used conjunction of OS yield/sleep primitives as when used via DALGlbCtxt.

   TEST_LOCK_COUNT controls how often the test access to the shared memory occurs.
   The value must always be a power of 2.
      Use 2 to force test each time.
   This value is especially important when shared memory is Strongly-Ordered as it
   will behave as a memory barrier.
*/
#define TEST_LOCK_COUNT    64


/*--------------------------- Rest use high level exchange-----------------------*/

void DALFW_LockSpinLockExt(volatile uint32 *spinLock, uint32 pid)
{
    uint32 cnt=0;
    for (;;)
    {
        if ((cnt & (TEST_LOCK_COUNT-1))==0) //time to test?
        {
            if (0 == *spinLock)             //is the lock currently available? 
            {
                if ( DALFW_LockedExchangeW(spinLock, pid) == 0 ) // try and grab it 
                    break;
            }
        }
        cnt++;
    }
}

DALResult DALFW_TryLockSpinLockExt(volatile uint32 *spinLock, uint32 pid)
{
    uint32 cnt;
    for (cnt=0; cnt<=TEST_LOCK_COUNT; cnt++) //always tries twice
    {
        if ((cnt & (TEST_LOCK_COUNT-1))==0)   //time to test?
        {
            if (0 == *spinLock)             //is the lock currently available?  
            {
                if ( DALFW_LockedExchangeW(spinLock, pid) == 0 )  // try and grab it  
                    return DAL_SUCCESS;
            }
        }
    }
    return DAL_ERROR;
}

void DALFW_UnLockSpinLockExt(volatile uint32 *spinLock)
{
    *spinLock = 0;   // Use store instead of Atomic Operation
    //DALFW_LockedExchangeW(spinLock, 0);
}


/* raw implementations of the above */

void _raw_LockSpinLockExt(volatile uint32 *spinLock, uint32 pid)
{
    while ( DALFW_LockedExchangeW(spinLock, pid) )
        ;
}

void _raw_UnLockSpinLockExt(volatile uint32 *spinLock)
{
    DALFW_LockedExchangeW(spinLock, 0);
}

DALResult _raw_TryLockSpinLockExt(volatile uint32 *spinLock, uint32 pid)
{
    return(DALFW_LockedExchangeW(spinLock, pid)==0)?DAL_SUCCESS:DAL_ERROR;
}

/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*------------ Raw intra CPU (i.e NON-shared) spinlocks ----------------------------*/
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

void DALFW_LockSpinLock(volatile uint32 *spinLock, uint32 pid)
{
    while ( DALFW_LockedExchangeW(spinLock, pid) )
        ;
}

void DALFW_UnLockSpinLock(volatile uint32 *spinLock)
{
    DALFW_LockedExchangeW(spinLock, 0);
}

DALResult DALFW_TryLockSpinLock(volatile uint32 *spinLock, uint32 pid)
{
    return(DALFW_LockedExchangeW(spinLock, pid)==0)?DAL_SUCCESS:DAL_ERROR;
}

