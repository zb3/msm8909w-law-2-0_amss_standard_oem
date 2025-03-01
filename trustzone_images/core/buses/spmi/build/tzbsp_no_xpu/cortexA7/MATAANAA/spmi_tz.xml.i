<!--
 * @brief: Configuration file for the SPMI driver
 * 
 * Copyright (c) 2013 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime:$
 * $Header:$
 * $Change:$
-->
<driver name="NULL">
    <device id="DALDEVICEID_SPMI_DEVICE">
<!-- System props -->
<props name="pmic_arb_base_addr" type=DALPROP_ATTR_TYPE_UINT32>
    0x02000000
</props>
<props name="useDebugChan" type=DALPROP_ATTR_TYPE_UINT32>
    1
</props>
        <!-- User configurable props -->
        <props name="owner" type=DALPROP_ATTR_TYPE_UINT32>
            1
        </props>
        <props name="useDebugChan" type=DALPROP_ATTR_TYPE_UINT32>
    	   1
	</props>
    </device>
</driver>
