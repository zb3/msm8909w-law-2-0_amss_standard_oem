#line 1 "/local/mnt/workspace/CRMBuilds/BOOT.BF.3.1.2.c3-00012-M8909WAAAANAZB-1_20161208_043404/b/boot_images/core/buses/uart/config/uart_sbl_8909.xml"
<!-- ================================================================================================== -->
<!-- GPIO configs.                                                                                      -->
<!--                                                                                                    -->
<!-- Source:  IP Catalog                                                                                -->
<!-- ================================================================================================== -->
<!--

     BLSP_UART1_TX_DATA     DAL_GPIO_CFG(  4, 2, DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP,   DAL_GPIO_2MA )
     BLSP_UART1_RX_DATA     DAL_GPIO_CFG(  5, 2, DAL_GPIO_INPUT,  DAL_GPIO_PULL_DOWN, DAL_GPIO_2MA )
     BLSP_UART1_CTS_N       DAL_GPIO_CFG(  6, 2, DAL_GPIO_INPUT,  DAL_GPIO_PULL_DOWN, DAL_GPIO_2MA )
     BLSP_UART1_RFR_N       DAL_GPIO_CFG(  7, 2, DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP,   DAL_GPIO_2MA )

     BLSP_UART2_TX_DATA     DAL_GPIO_CFG(  20, 3, DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP,   DAL_GPIO_2MA )
     BLSP_UART2_RX_DATA     DAL_GPIO_CFG(  21, 3, DAL_GPIO_INPUT,  DAL_GPIO_PULL_DOWN, DAL_GPIO_2MA )


======================================================================================================= -->

<driver name="NULL">

  <global_def>
    <string name="UART_PHY_DEVICE_1"     type=DALPROP_DATA_TYPE_STRING> /core/buses/uart/1  </string>
    <string name="UART_PHY_DEVICE_2"     type=DALPROP_DATA_TYPE_STRING> /core/buses/uart/2  </string>
  </global_def>

  <!-- =================================================================== -->
  <!-- TARGET SPECIFIC UART PROPERTIES                                  -->
  <!-- =================================================================== -->
  <device id="/core/buses/uart">
      <props name="UartMainPortPhy"  type=DALPROP_ATTR_TYPE_STRING_PTR>  UART_PHY_DEVICE_1 </props>
  </device>

  <!-- =================================================================== -->
  <!-- UART1                                                            -->
  <!-- =================================================================== -->

  <device id="/core/buses/uart/1">
    <props name="GpioRxData"     type=DALPROP_ATTR_TYPE_UINT32>         0x20008052           </props>
    <props name="GpioTxData"     type=DALPROP_ATTR_TYPE_UINT32>         0x2001C042           </props>
    <props name="GpioRfrN"       type=DALPROP_ATTR_TYPE_UINT32>         0x2001C072           </props>
    <props name="GpioCtsN"       type=DALPROP_ATTR_TYPE_UINT32>         0x20008062           </props>
    <props name="UartBase"       type=DALPROP_ATTR_TYPE_UINT32>         0x78af000            </props>
    <props name="IsLoopback"     type=DALPROP_ATTR_TYPE_UINT32>         0                    </props>
    <props name="BitRate"        type=DALPROP_ATTR_TYPE_UINT32>         115200               </props>
    <props name="ClockIdIndex"   type=DALPROP_ATTR_TYPE_UINT32>         1                    </props>
  </device>

  <!-- =================================================================== -->
  <!-- UART2                                                            -->
  <!-- =================================================================== -->

  <device id="/core/buses/uart/2">
    <props name="GpioRxData"     type=DALPROP_ATTR_TYPE_UINT32>         0x20008153           </props>
    <props name="GpioTxData"     type=DALPROP_ATTR_TYPE_UINT32>         0x2001C143           </props>
	<!-- On 8936 CDP, only TX and RX is routed out.
    <props name="GpioRfrN"       type=DALPROP_ATTR_TYPE_UINT32>         0x2001c072           </props>
    <props name="GpioCtsN"       type=DALPROP_ATTR_TYPE_UINT32>         0x20008062           </props>
    -->
    <props name="UartBase"       type=DALPROP_ATTR_TYPE_UINT32>         0x78b0000            </props>
    <props name="IsLoopback"     type=DALPROP_ATTR_TYPE_UINT32>         0                    </props>
    <props name="BitRate"        type=DALPROP_ATTR_TYPE_UINT32>         115200               </props>
    <props name="ClockIdIndex"   type=DALPROP_ATTR_TYPE_UINT32>         2                    </props>
  </device>


</driver>
