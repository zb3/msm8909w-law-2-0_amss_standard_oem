#ifndef __DSS_RFCONDITIONSHANDLER_H__
#define __DSS_RFCONDITIONSHANDLER_H__

/*====================================================

FILE:  DSS_RFConditionsHandler.h

SERVICES:
   Handle network RF conditions changed events.

=====================================================

Copyright (c) 2008 Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

=====================================================*/
/*===========================================================================
  EDIT HISTORY FOR MODULE

  Please notice that the changes are listed in reverse chronological order.

  $Header: //commercial/MPSS.JO.2.0.c1.4/Main/modem_proc/datamodem/interface/dss/src/DSS_RFConditionsHandler.h#1 $
  $DateTime: 2016/12/13 08:00:03 $$Author: mplcsds1 $

  when       who what, where, why
  ---------- --- ------------------------------------------------------------
  2010-04-18 en  History added.

===========================================================================*/

#include "DSS_EventHandlerNetApp.h"

class DSSRFConditionsHandler : public DSSEventHandlerNetApp
{
protected:
   virtual void EventOccurred();
   virtual AEEResult RegisterIDL();

public:
   static DSSRFConditionsHandler* CreateInstance();
   DSSRFConditionsHandler();
};

#endif // __DSS_RFCONDITIONSHANDLER_H__
