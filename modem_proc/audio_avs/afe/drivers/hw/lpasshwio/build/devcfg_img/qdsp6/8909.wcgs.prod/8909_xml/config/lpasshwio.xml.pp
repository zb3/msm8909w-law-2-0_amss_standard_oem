# 1 "/local/mnt/workspace/CRMBuilds/MPSS.JO.2.0.c1.4-00005-8909_GENS_PACK-1_20170119_051958/b/modem_proc/audio_avs/afe/drivers/hw/lpasshwio/devcfg/config/lpasshwio.xml"
# 1 "/local/mnt/workspace/CRMBuilds/MPSS.JO.2.0.c1.4-00005-8909_GENS_PACK-1_20170119_051958/b/modem_proc/audio_avs/afe/drivers/hw/lpasshwio/devcfg/config/lpasshwio.xml" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 136 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/MPSS.JO.2.0.c1.4-00005-8909_GENS_PACK-1_20170119_051958/b/modem_proc/audio_avs/afe/drivers/hw/lpasshwio/devcfg/config/lpasshwio.xml" 2
<!--
  Copyright (c) 2012 Qualcomm Technologies Incorporated.
           All Rights Reserved.

   DESCRIPTION: LPASS HWIO driver.
   $Header: $
 -->

<!-- NULL Driver does not require Dal Driver Interface APIs, since none of AVS HWD drivers uses DAL Device framework -->
<driver name="NULL">
   <!-- AUDIOIF -->
   <device id="AUDIOIF">
      <props name="AudioIfPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>audioif_prop</props>
   </device>
   <!-- AVTimer -->
   <device id="AVTIMER">
      <props name="AvtimerPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>avtimer_prop</props>
   </device>
   <!-- DMLite -->
   <device id="DMLITE">
      <props name="DmlitePropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>dmlite_prop</props>
   </device>
   <!-- Resampler -->
   <device id="RESAMPLER">
      <props name="ResamplerPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>resampler_prop</props>
   </device>
   <!-- VFR -->
   <device id="VFR">
      <props name="VfrPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>vfr_prop</props>
   </device>
   <device id="AFERiva">
      <props name="AFERivaPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>afe_riva_prop</props>
   </device>
   <device id="AFESlimbus">
      <props name="AFESlimbusPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>afe_slimbus_prop</props>
   </device>
   <!-- MIDI -->
   <device id="MIDI">
      <props name="MidiPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>midi_prop</props>
   </device>
   <device id="LPASS">
      <props name="LpassPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>lpass_prop</props>
   </device>
   <!--SPDIFTX -->
   <device id="SPDIFTX">
      <props name="SpdifTxPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>spdiftx_prop</props>
   </device>
   <!--HDMIRX -->
   <device id="HDMIRX">
      <props name="HdmiInputPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>hdmi_input_prop</props>
   </device>
   <!--MMPM -->
   <device id="AFEMMPM">
      <props name="MmpmPropStructPtr" type=DALPROP_ATTR_TYPE_STRUCT_PTR>mmpm_prop</props>
   </device>
</driver>
