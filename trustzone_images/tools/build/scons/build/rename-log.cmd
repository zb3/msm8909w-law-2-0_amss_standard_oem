@echo off
rem ==========================================================================
rem
rem  CBSP Buils system
rem
rem  General Description
rem     build rename log file.
rem
rem Copyright (c) 2009-2009 by QUALCOMM, Incorporated.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem
rem --------------------------------------------------------------------------
rem
rem $Header: //components/rel/tz.bf/2.5.c10/trustzone_images/tools/build/scons/build/rename-log.cmd#1 $
rem $DateTime: 2016/06/17 14:31:11 $
rem $Author: pwbldsvc $
rem $Change: 10727476 $
rem                      EDIT HISTORY FOR FILE
rem
rem  This section contains comments describing changes made to the module.
rem  Notice that changes are listed in reverse chronological order.
rem
rem when       who     what, where, why
rem --------   ---     ---------------------------------------------------------
rem
rem ==========================================================================

setlocal enableDelayedExpansion

if not exist "build-log.txt" goto :eof
set i=1
:next
if /I %i% LEQ 999 set ii=%i%
if /I %i% LEQ 99 set ii=0%i%
if /I %i% LEQ 9 set ii=00%i%
if not exist "build-log-!ii!.txt" (
ren "build-log.txt" "build-log-!ii!.txt"
goto :eof
)
set /a i+=1
if /i %i% LSS 999 goto next
)
