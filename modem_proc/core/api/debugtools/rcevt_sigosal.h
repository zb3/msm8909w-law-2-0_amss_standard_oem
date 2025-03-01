#ifndef RCEVT_SIGOSAL_H
#define RCEVT_SIGOSAL_H
/**
@file rcevt_sigosal.h
@brief This file contains the API for the Run Control Event Notification, LEGACY API (A-FAMILY)
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2015 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.mpss/3.5.c12.3/api/debugtools/rcevt_sigosal.h#1 $
$DateTime: 2016/12/13 07:59:23 $
$Change: 11985146 $
$Author: mplcsds1 $
===============================================================================*/

// DEPRECATED AND UNSUPPORTED

// REMEDIATION: REMOVE REFERENCES TO THIS HEADER FILE, USE RCEVT_REX.H INSTEAD.
// THIS HEADER DOES NOT PORT INTO DLL/SHARED_OBJECT USE. ALL USES MAP DIRECTLY
// TO TYPES AND API AVAILABLE WITH RCEVT_REX.H.

#include "dll_api.h"
#include "rcevt_rex.h"

typedef RCEVT_SIGEX_SIGREX RCEVT_SIGEX_SIGOSAL DLL_API_WARN_DEPRECATED; /**< OBSOLETE; CLIENTS USE RCEVT_REX.H */
typedef int RCEVT_SIGEX_TYPE_SIGOSAL_DEPRECATED DLL_API_WARN_DEPRECATED; /**< OBSOLETE; CLIENTS USE RCEVT_REX.H */
#define RCEVT_SIGEX_TYPE_SIGOSAL RCEVT_SIGEX_TYPE_SIGREX /**< OBSOLETE; CLIENTS USE RCEVT_REX.H */

#endif
