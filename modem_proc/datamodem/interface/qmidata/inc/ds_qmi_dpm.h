#ifndef _DS_QMI_DPM_H
#define _DS_QMI_DPM_H
/*===========================================================================

                         D S _ Q M I _ D P M . H

DESCRIPTION

 The Data Services QMI Data Port Mapper header file.

EXTERNALIZED FUNCTIONS

   qmi_dpm_init()
     Initialize the QMI-DPM service and register with QCSI

Copyright (c) 2013 QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary
===========================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

  $Header: //commercial/MPSS.JO.2.0.c1.4/Main/modem_proc/datamodem/interface/qmidata/inc/ds_qmi_dpm.h#1 $ $DateTime: 2016/12/13 08:00:03 $ $Author: mplcsds1 $

when        who    what, where, why
--------    ---    ----------------------------------------------------------
08/14/13    bh     Created module
===========================================================================*/

#include "comdef.h"
#include "customer.h"

/*===========================================================================
  FUNCTION QMI_DPM_INIT()

  DESCRIPTION
    Initialize the QMI-DPM service and register with QCSI

  PARAMETERS
    None

  RETURN VALUE
    None

  DEPENDENCIES
    None

  SIDE EFFECTS
    None
===========================================================================*/
extern void  qmi_dpm_init
(
  void
);

#endif /* _DS_QMI_DPM_H */
