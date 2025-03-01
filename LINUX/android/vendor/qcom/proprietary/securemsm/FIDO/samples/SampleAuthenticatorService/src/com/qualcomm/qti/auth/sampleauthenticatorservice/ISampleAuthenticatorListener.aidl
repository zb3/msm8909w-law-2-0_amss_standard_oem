/*
 * Copyright (c) 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */

package com.qualcomm.qti.auth.sampleauthenticatorservice;

oneway interface ISampleAuthenticatorListener {
  void onUserVerificationResult(in byte[] nonce, int result, String authenticatorName, long userId, long userEntityId, in byte[] encapsulatedResult);
  void onCancel(in byte[] nonce);
  void onEnrollmentStatus(long userId, boolean status);
}
