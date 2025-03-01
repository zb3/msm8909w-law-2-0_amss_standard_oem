/*======================================================

FILE:  DSS_ApnParamChangedHandler.cpp

GENERAL DESCRIPTION:
   Implementation of DSS_ApnParamChangedHandler functions

=====================================================

Copyright (c) 2014 Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

=====================================================*/
/*===========================================================================
  EDIT HISTORY FOR MODULE

  Please notice that the changes are listed in reverse chronological order.

  $Header: //commercial/MPSS.JO.2.0.c1.4/Main/modem_proc/datamodem/interface/dss/src/DSS_ApnParamChangedHandler.cpp#1 $
  $DateTime: 2016/12/13 08:00:03 $
  $Author: mplcsds1 $

  when       who what, where, why
  ---------- --- ------------------------------------------------------------
  2014-07-20 sb  Created module.

===========================================================================*/

#include "DSS_ApnParamChangedHandler.h"
#include "DSS_Common.h"
#include "DSS_IDSNetworkScope.h"
#include "ds_Net_INetworkExt.h"

using namespace ds::Net;

DSSApnParamChangedHandler::DSSApnParamChangedHandler()
{
   mEventType = EVENT_HANDLER_APN_PARAM_CHANGE;
}

void DSSApnParamChangedHandler::EventOccurred()
{
   if (mpHandlerDataClone->mpEventData->bReg) {
      dss_iface_ioctl_event_info_union_type eventInfo;
      memset(&eventInfo, 0, sizeof(dss_iface_ioctl_event_info_union_type));
      AEEResult res = mpParent->GetApnParamInfo(&eventInfo.changed_apn_param_info);
      if (AEE_SUCCESS != res)
      {
        LOG_MSG_ERROR_1("DSSApnParamChangedHandler::EventOccurred(): "
                       "GetApnParams() failed: %d", res);
          return;
      }
      DispatchCB(DSS_IFACE_IOCTL_APN_PARAM_CHANGE_EV, mpHandlerDataClone->mpEventData, &eventInfo);
   }
}

AEEResult DSSApnParamChangedHandler::RegisterIDL()
{
   DSSIDSNetworkScope IDSNetworkScope;
   INetworkExt *piNetworkExt = 0;
   AEEResult res = AEE_SUCCESS;
   DSSWeakRefScope WeakRefScope;
   IQI* pRegObj = NULL;

   if(!WeakRefScope.Init(mpParent)) {
      return AEE_EFAILED;
   }

   IDS_ERR_RET(IDSNetworkScope.Init(mpParent));

   IDS_ERR_RET(IDSNetworkScope.Fetch()->QueryInterface(AEEIID_INetworkExt,
                                                       (void**)&piNetworkExt));

   LOG_MSG_INFO1_1("DSSApnParamChangedHandler::RegisterIDL(): "
                   "Registering to QDS_EV_APN_PARM_EV, NetworkExt obj 0x%p",
                   piNetworkExt);
   res = piNetworkExt->OnStateChange(mpSignal, NetworkExtEvent::QDS_EV_APN_PARAM_EV, &pRegObj);
   // regObj mechanism is currently not in effect by dsnet layer. 
   // No need for DSS to hold the allocated object to maintain the event registration. 
   // For design simplicity we release the regObj immediately.
   // If and when dsnet layer enforces the registration object concept this code need to be adapted accordingly.
   DSSCommon::ReleaseIf(&pRegObj);

   DSSCommon::ReleaseIf((IQI**)&piNetworkExt);

   return res;
}

DSSApnParamChangedHandler* DSSApnParamChangedHandler::CreateInstance()
{
   return new DSSApnParamChangedHandler;
}

