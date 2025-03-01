/***********************************************************************
 * rfs_rfsa.h
 *
 * RFS wrapper for RFS_ACCESS
 * Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 *
 * APIs to hook up RFS_ACCESS APIs under RFS API layer.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.mpss/3.5.c12.3/storage/rfs/src/rfs_rfsa.h#1 $ $DateTime: 2016/12/13 07:59:23 $ $Author: mplcsds1 $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-12-03   dks   Move rfs init to a task
2014-04-02   dks   Create

===========================================================================*/

#ifndef __RFS_RFSA_H__
#define __RFS_RFSA_H__

#include "rfs_ops.h"

#ifdef FEATURE_RFS_USE_RFSA

int rfs_rfsa_init (struct rfs_ops_type *base_ops);

#endif

#endif /* not __RFS_RFSA_H__ */
