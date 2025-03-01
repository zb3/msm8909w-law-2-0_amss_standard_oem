#ifndef LTE_VARIATION_H
#define LTE_VARIATION_H

/* This file is autogenerated from the FEATURE database
 * It defines a) global features required for target=M8974 variant=AAAAANAAM and used by <lte>
 *            b) top level features used exclusively by <lte>
 *    A global feature is defined as being used by more than one SU.
 *    A top level feature is a feature that is expected to vary between build variants.
 *
 * - By including this file instead of customer.h, <lte> decouples itself from other team's cust files.
 * - Only features defined in this file vary the compilation of <lte>.
 * - At the bottom this file includes a manually maintained file owned by <lte> where <lte>
 *   can define other features that are derived from these top level features.
 * - Mainlining or eliminating global features that are not legitimate top level features will reduce
 *   the size of this file.
 */ 

/* For Phase 1 just keep customer.h and make sure it gets included first */
#include <customer.h>


#include "lte_local_defines.h"


#ifdef T_WINNT
  #error code not present
#endif

#endif /* LTE_VARIATION_H */
