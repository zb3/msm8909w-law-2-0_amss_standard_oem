/*
 * Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 * Not a Contribution.
 * Apache license notifications and license are retained
 * for attribution purposes only.
 */

/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.qualcomm.qti.gsma.services.nfc;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class StartGsmaService extends BroadcastReceiver {
    public final static String _TAG = "StartGsmaService";

    @Override
    public void onReceive(Context context, Intent intent) {
        final boolean bootCompleted = intent.getAction().equals("android.intent.action.BOOT_COMPLETED");

        if( bootCompleted ){
            Log.d(_TAG, "Starting GSMA service after boot completed");
            Intent serviceIntent = new Intent(context, com.qualcomm.qti.gsma.services.nfc.GsmaService.class );
            context.startService(serviceIntent);
        }
    }
};
