/***********************************************************************
 * rfs_nodev.h
 *
 * RFS Nodev Operations.
 * Copyright (c) 2013-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 *
 * APIs to hook up stubs for RFS APIs when there is no underlying
 * Filesystem implementation.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.mpss/3.5.c12.3/storage/rfs/src/rfs_nodev.h#1 $ $DateTime: 2016/12/13 07:59:23 $ $Author: mplcsds1 $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2014-12-03   dks   Move rfs init to a task
2013-11-14   dks   Create

===========================================================================*/

#include "rfs_ops.h"

#ifndef __RFS_NODEV_H__
#define __RFS_NODEV_H__

int rfs_nodev_init (struct rfs_ops_type *base_ops);

#endif /* not __RFS_NODEV_H__ */
