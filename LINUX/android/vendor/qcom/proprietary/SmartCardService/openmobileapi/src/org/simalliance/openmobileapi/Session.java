/*
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc. 
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 * Not a Contribution.
 * Apache license notifications and license are retained
 * for attribution purposes only.
 */
/*
 * Copyright (C) 2011, The Android Open Source Project
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
/*
 * Contributed by: Giesecke & Devrient GmbH.
 */

package org.simalliance.openmobileapi;

import java.io.IOException;
import java.util.MissingResourceException;
import java.util.NoSuchElementException;

import org.simalliance.openmobileapi.service.ISmartcardServiceChannel;
import org.simalliance.openmobileapi.service.ISmartcardServiceSession;
import org.simalliance.openmobileapi.service.SmartcardError;

import android.os.RemoteException;
import android.util.Log;

/**
 * Instances of this class represent a connection session to one of the Secure
 * Elements available on the device. These objects can be used to get a
 * communication channel with an Applet in the Secure Element.
 * This channel can be the basic channel or a logical channel.
 *
 * @see <a href="http://simalliance.org">SIMalliance Open Mobile API  v3.0</a>
 */
public class Session {

    private final Object mLock = new Object();
    private final SEService mService;
    private final Reader mReader;
    private final ISmartcardServiceSession mSession;
    public static final String _TAG = "SmartcardService - Session";
    public int mHandle;

    Session(SEService service, ISmartcardServiceSession session, Reader reader) {
        mService = service;
        mReader = reader;
        mSession = session;
    }

    /**
     *specific eSE over TZ session constructor
     */
    Session(SEService service, ISmartcardServiceSession session, Reader reader, int sessionHandle) {
        mService = service;
        mReader = reader;
        mSession = session;
        mHandle = sessionHandle;
    }
    /**
     * Get the reader that provides this session.
     *
     * @return The Reader object.
     */
    public Reader getReader() {
        return mReader;
    }

    /**
     * Get the Answer to Reset of this Secure Element. <br>
     * The returned byte array can be null if the ATR for this Secure Element is
     * not available.
     *
     * @return the ATR as a byte array or null.
     */
    public byte[] getATR() {
        if (mService == null || !mService.isConnected()) {
            throw new IllegalStateException("service not connected to system");
        }
        if( mSession == null ){
            throw new IllegalStateException("service session is null");
        }
        try {
            return mSession.getAtr();
        } catch (RemoteException e) {
            throw new IllegalStateException(e.getMessage());
        }
    }

    /**
     * Close the connection with the Secure Element. This will close any
     * channels opened by this application with this Secure Element.
     */
    public void close() {
        if (mService == null || !mService.isConnected()) {
            throw new IllegalStateException("service not connected to system");
        }
        if( mSession != null ){
            synchronized (mLock) {
                try {
                    SmartcardError error = new SmartcardError();
                    mSession.close(error);
                    if (error.isSet()) {
                        error.throwException();
                    }
                } catch (Exception e) {
                    Log.e(_TAG, "Error closing session", e);
                }
            }
        }
    }

    /**
     * Tells if this session is closed.
     *
     * @return <code>true</code> if the session is closed, false otherwise.
     */
    public boolean isClosed() {
        try {
            return mSession == null || mSession.isClosed();
        } catch (RemoteException e) {
            throw new IllegalStateException(e.getMessage());
        }
    }

    /**
     * Close any channel opened on this session.
     * @throws IOException
     */
    public void closeChannels() {

        if (mService == null || !mService.isConnected()) {
            throw new IllegalStateException("service not connected to system");
        }

        if( mSession != null ){
            synchronized (mLock) {
                try {
                    SmartcardError error = new SmartcardError();
                    mSession.closeChannels(error);
                    if (error.isSet()) {
                        error.throwException();
                    }
                } catch (Exception e) {
                    Log.e(_TAG, "Error closing channels", e);
                }
            }
        }
    }

    /**
     * returns the handle corresponding to this session.
     * @throws Exception
     *
     * @returns the handle as an int
     */
    public int getHandle() {
        int handle = 0;
        try {
            handle = mSession.getHandle();
        } catch (Exception e){
            Log.e(_TAG, "unable to get the session handle :" + e.getMessage());
        }
        return handle;
    }

    /**
     * set the handle corresponding to this session.
     */
    public void setHandle(int handle) {
        mHandle = handle;
    }

    /**
     * Get an access to the basic channel, as defined in the ISO/IEC 7816-4 specification (the
     * one that has number 0). The obtained object is an instance of the Channel class.
     * If the AID is null, it means no Applet is to be selected on this channel and the default
     * Applet is used. If the AID is defined then the corresponding Applet is selected.
     * Once this channel has been opened by a device application, it is considered as "locked"
     * by this device application, and other calls to this method will return null, until the channel
     * is closed. Some Secure Elements (like the UICC) might always keep the basic channel
     * locked (i.e. return null to applications), to prevent access to the basic channel, while
     * some other might return a channel object implementing some kind of filtering on the
     * commands, restricting the set of accepted command to a smaller set.
     * It is recommended for the UICC to reject the opening of the basic channel to a specific
     * applet, by always answering null to such a request.
     * For other Secure Elements, the recommendation is to accept opening the basic channel
     * on the default applet until another applet is selected on the basic channel. As there is no
     * other way than a reset to select again the default applet, the implementation of the
     * transport API should guarantee that the openBasicChannel(null) command will return
     * null until a reset occurs.
     * With previous release (V2.05) it was not possible to set P2 value, this value was always
     * set to '00'.Except for specific needs it is recommended to keep P2 to '00'. It is
     * recommended that the device allows all values for P2, however only the following values
     * are mandatory: '00', '04', '08', '0C'(as defined in [2])
     * The implementation of the underlying SELECT command within this method shall be
     * based on ISO 7816-4 with following options:
     * <ul>
     * <li>CLA = '00'</li>
     * <li>INS = 'A4'</li>
     * <li>P1 = '04' (Select by DF name/application identifier)</li>
     * </ul>
     *
     * The select response data can be retrieved with byte[] getSelectResponse().
     * The API shall handle received status word as follow. If the status word indicates that the
     * Secure Element was able to open a channel (e.g. status word '90 00' or status words
     * referencing a warning in ISO-7816-4: '62 XX' or '63 XX') the API shall keep the
     * channel opened and the next getSelectResponse() shall return the received status
     * word.
     * Other received status codes indicating that the Secure Element was able not to open a
     * channel shall be considered as an error and the corresponding channel shall not be
     * opened.
     * The function without P2 as parameter is provided for backwards compatibility and will
     * fall back to a select command with P2='00'.
     *
     * @param aid the AID of the Applet to be selected on this channel, as a
     *            byte array, or null if no Applet is to be selected.
     * @param p2 the P2 parameter of the SELECT APDU executed on this channel.
     * @throws IOException if there is a communication problem to the reader or
     *             the Secure Element.
     * @throws IllegalStateException if the Secure Element session is used after
     *             being closed.
     * @throws IllegalArgumentException if the aid's length is not within 5 to
     *             16 (inclusive).
     * @throws SecurityException if the calling application cannot be granted
     *             access to this AID or the default Applet on this
     *             session.
     * @throws NoSuchElementException if the AID on the Secure Element is not available or cannot be
     *             selected.
     * @throws UnsupportedOperationException if the given P2 parameter is not
     *             supported by the device
     * @return an instance of Channel if available or null.
     */
    public Channel openBasicChannel(byte[] aid, byte p2) throws IOException,
            IllegalStateException, IllegalArgumentException, SecurityException,
            NoSuchElementException, UnsupportedOperationException {

        if (mService == null || !mService.isConnected()) {
            throw new IllegalStateException("service not connected to system");
        }
        if( mSession == null ){
            throw new IllegalStateException("service session is null");
        }
        if (getReader() == null) {
            throw new IllegalStateException("reader must not be null");
        }

        synchronized (mLock) {
            try {
                SmartcardError error = new SmartcardError();
                ISmartcardServiceChannel channel = mSession.openBasicChannel(
                        aid,
                        p2,
                        mReader.getSEService().getCallback(),
                        error);
                if (error.isSet()) {
                    error.throwException();
                }
                if (channel == null) {
                    return null;
                }
                return new Channel(mService, this, channel);
            } catch (RemoteException e) {
                throw new IllegalStateException(e.getMessage());
            }
        }
    }

    /**
     * This method is provided to ease the development of mobile application and for compliancy
     * with existing applications.
     * This method is equivalent to openBasicChannel(aid, P2=0x00)
     *
     * @param aid the AID of the Applet to be selected on this channel, as a
     *            byte array, or null if no Applet is to be selected.
     * @throws IOException if there is a communication problem to the reader or
     *             the Secure Element.
     * @throws IllegalStateException if the Secure Element session is used after
     *             being closed.
     * @throws IllegalArgumentException if the aid's length is not within 5 to
     *             16 (inclusive).
     * @throws SecurityException if the calling application cannot be granted
     *             access to this AID or the default Applet on this
     *             session.
     * @throws NoSuchElementException if the AID on the Secure Element is not available or cannot be
     *             selected.
     * @throws UnsupportedOperationException if the given P2 parameter is not
     *             supported by the device
     * @return an instance of Channel if available or null.
     */
    public Channel openBasicChannel(byte[] aid) throws IOException,
            IllegalStateException, IllegalArgumentException, SecurityException,
            NoSuchElementException, UnsupportedOperationException {
        return openBasicChannel(aid, (byte) 0x00);
    }

    /**
     * Open a logical channel with the Secure Element, selecting the Applet represented by
     * the given AID. If the AID is null, which means no Applet is to be selected on this
     * channel, the default Applet is used. It's up to the Secure Element to choose which
     * logical channel will be used.
     * With previous release (V2.05) it was not possible to set P2 value, this value was always
     * set to '00'.Except for specific needs it is recommended to keep P2 to '00'. It is
     * recommended that the device allows all values for P2, however only the following values
     * are mandatory: '00', '04', '08', '0C'(as defined in [2])
     * The implementation of the underlying SELECT command within this method shall be
     * based on ISO 7816-4 with following options:
     *
     * <ul>
     * <li>CLA = '01' to '03', '40 to 4F'</li>
     * <li>INS = 'A4'</li>
     * <li>P1 = '04' (Select by DF name/application identifier)</li>
     * </ul>
     *
     * The select response data can be retrieved with byte[] getSelectResponse().
     * The API shall handle received status word as follow. If the status word indicates that the
     * Secure Element was able to open a channel (e.g. status word '90 00' or status words
     * referencing a warning in ISO-7816-4: '62 XX' or '63 XX') the API shall keep the
     * channel opened and the next getSelectResponse() shall return the received status
     * word.
     * Other received status codes indicating that the Secure Element was able not to open a
     * channel shall be considered as an error and the corresponding channel shall not be
     * opened.
     * In case of UICC it is recommended for the API to reject the opening of the logical
     * channel without a specific AID, by always answering null to such a request.
     * The function without P2 as parameter is provided for backwards compatibility and will
     * fall back to a select command with P2=00.
     *
     * @param aid the AID of the Applet to be selected on this channel, as a
     *            byte array.
     * @param p2 the P2 parameter of the SELECT APDU executed on this channel.
     * @throws IOException if there is a communication problem to the reader or
     *             the Secure Element.
     * @throws IllegalStateException if the Secure Element is used after being
     *             closed.
     * @throws IllegalArgumentException if the aid's length is not within 5 to
     *             16 (inclusive).
     * @throws SecurityException if the calling application cannot be granted
     *             access to this AID or the default Applet on this
     *             session.
     * @throws NoSuchElementException if the AID on the Secure Element is not
     *             available or cannot be selected or a logical channel is already
     *             open to a non-multiselectable Applet.
     * @throws UnsupportedOperationException if the given P2 parameter is not
     *             supported by the device.
     * @return an instance of Channel. Null if the Secure Element is unable to
     *         provide a new logical channel.
     */
    public Channel openLogicalChannel(byte[] aid, byte p2) throws IOException,
            IllegalStateException, IllegalArgumentException, SecurityException,
            NoSuchElementException, UnsupportedOperationException {

        if (mService == null || !mService.isConnected()) {
            throw new IllegalStateException("service not connected to system");
        }
        if( mSession == null ){
            throw new IllegalStateException("service session is null");
        }
        if (getReader() == null) {
            throw new IllegalStateException("reader must not be null");
        }
        synchronized (mLock) {
            try {
                SmartcardError error = new SmartcardError();
                ISmartcardServiceChannel channel = mSession.openLogicalChannel(
                        aid,
                        p2,
                        mReader.getSEService().getCallback(),
                        error);
                if (error.isSet()) {
                    error.throwException();
                }
                if (channel == null) {
                    return null;
                }
                return new Channel(mService, this, channel);
            } catch (RemoteException e) {
                throw new IllegalStateException(e.getMessage());
            }
        }
    }

    /**
     * This method is provided to ease the development of mobile application and for compliancy
     * with existing applications.
     * This method is equivalent to openLogicalChannel(aid, P2=0x00)
     *
     * @param aid the AID of the Applet to be selected on this channel, as a
     *            byte array.
     * @throws IOException if there is a communication problem to the reader or
     *             the Secure Element.
     * @throws IllegalStateException if the Secure Element is used after being
     *             closed.
     * @throws IllegalArgumentException if the aid's length is not within 5 to
     *             16 (inclusive).
     * @throws SecurityException if the calling application cannot be granted
     *             access to this AID or the default Applet on this
     *             session.
     * @throws NoSuchElementException if the AID on the Secure Element is not
     *             available or cannot be selected or a logical channel is already
     *             open to a non-multiselectable Applet.
     * @throws UnsupportedOperationException if the given P2 parameter is not
     *             supported by the device.
     * @return an instance of Channel. Null if the Secure Element is unable to
     *         provide a new logical channel.
     */
    public Channel openLogicalChannel(byte[] aid) throws IOException,
            IllegalStateException, IllegalArgumentException, SecurityException,
            NoSuchElementException, UnsupportedOperationException {
        return openLogicalChannel(aid, (byte) 0x00);
    }
}
