
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

              Diag Legacy Service Mapping DLL

GENERAL DESCRIPTION

Implementation of entry point and Initialization functions for Diag_LSM.dll.


EXTERNALIZED FUNCTIONS
DllMain
Diag_LSM_Init
Diag_LSM_DeInit

INITIALIZATION AND SEQUENCING REQUIREMENTS


# Copyright (c) 2007-2011, 2015 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

$Header:

when       who    what, where, why
--------   ---    ----------------------------------------------------------
10/01/08   SJ     Created

===========================================================================*/

#include "ts_linux.h"
#include "string.h"
#include "errno.h"
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include "diag_lsm.h"

#define TIME_SYNC_PARAM "/sys/module/diagchar/parameters/timestamp_switch"
extern unsigned long long time_get_from_timetick();

static unsigned long long get_time_of_day()
{
	struct timeval tv;
	unsigned long long seconds, microseconds;
	gettimeofday(&tv, NULL);
	seconds = (unsigned long long)tv.tv_sec;
	/* Offset to sync timestamps between Modem & Apps Proc.
	Number of seconds between Jan 1, 1970 & Jan 6, 1980 */
	seconds = seconds - (10*365+5+2)*24*60*60 ;
	seconds = seconds * 1000;
	microseconds = (unsigned long long)tv.tv_usec;
	microseconds = microseconds/1000;
	seconds = seconds + microseconds;
	seconds = seconds*4;
	seconds = seconds/5;
	seconds = seconds << 16;
	return seconds;
}

/*===========================================================================

FUNCTION    ts_get

DESCRIPTION
  This extracts time from the system and feeds the pointer passed in.

DEPENDENCIES
  None.

RETURN VALUE
  none

SIDE EFFECTS
  None

===========================================================================*/

void ts_get (void *timestamp)
{
		char *temp1;
		char *temp2;
		unsigned long long seconds;
		int i, fd_param = -1, ret, time_stamp_switch = 0;
		int time_sync_param[1];
		long long int qtimer_secs;
		time_sync_param[0] = 0;

		fd_param = open(TIME_SYNC_PARAM, O_RDONLY);
		if (fd_param < 0) {
			DIAG_LOGE("ts_get: could not open file: %s\n", strerror(errno));
			goto default_ts;
		}
		ret = read(fd_param, time_sync_param, 1);
                if (ret < 0) {
                        DIAG_LOGE("ts_get: Unable to read file: %s\n", strerror(errno));
			close(fd_param);
                        goto default_ts;
                }
		close(fd_param);
		time_stamp_switch = time_sync_param[0] - '0';
		switch (time_stamp_switch) {
		case 0:
		default:
			seconds = get_time_of_day();
			break;
		case 1:
			seconds = time_get_from_timetick();
			break;
		}
		temp1 = (char *) (timestamp);
		temp2 = (char *) &(seconds);
		/*
		 * This is assuming that you have 8 consecutive
		 * bytes to store the data.
		 */
		for (i=0;i<8;i++)
			*(temp1+i) = *(temp2+i);
		return;
default_ts:
	seconds = get_time_of_day();
	temp1 = (char *) (timestamp);
        temp2 = (char *) &(seconds);
	/*
         * This is assuming that you have 8 consecutive
         * bytes to store the data.
         */
        for (i=0;i<8;i++)
		*(temp1+i) = *(temp2+i);
        return;
}     /* ts_get */

/*===========================================================================
FUNCTION   ts_get_lohi

DESCRIPTION
  Extracts timestamp from system and places into lo and hi parameters

DEPENDENCIES
  None

RETURN VALUE


SIDE EFFECTS
  None

===========================================================================*/
void ts_get_lohi(uint32 *ts_lo, uint32 *ts_hi)
{
	char buf[8];

	ts_get(buf);
	*ts_lo = *(uint32 *)&buf[0];
	*ts_hi = *(uint32 *)&buf[4];

	return;
}

