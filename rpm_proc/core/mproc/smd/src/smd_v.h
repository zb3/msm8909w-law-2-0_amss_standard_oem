#ifndef SMD_V_H
#define SMD_V_H

/*===========================================================================

             Shared Memory Driver AU Private Header File


-----------------------------------------------------------------------------
Copyright (c) 2009 Qualcomm Technologies Incorporated
All Rights Reserved. Qualcomm Proprietary and Confidential.
-----------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/rpm.bf/2.1.1/core/mproc/smd/src/smd_v.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/01/12   bt      Remove residual Block defines.
04/20/09   bfc     Initial version...Split smd.h into AU public and AU
                   private headers
===========================================================================*/


/*===========================================================================

                        INCLUDE FILES

===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================

                      TYPE DECLARATIONS
                      
===========================================================================*/
#if !defined(SMD_NUM_CHANNELS)   
#define SMD_NUM_CHANNELS             64
#endif


/* See if an SMD port is valid */
#define SMD_VALIDATE_PORT_ID( PID ) \
  do { \
    if( PID >= SMD_NUM_CHANNELS ) \
    { \
      ERR_FATAL( "Invalid SMD port id %d", PID, 0, 0 ); \
    } \
  } while(0)

#ifdef __cplusplus
}
#endif

#endif /* SMD_V_H */
