#ifndef QPA4361_TYPEDEF_AG_H
#define QPA4361_TYPEDEF_AG_H


#include "comdef.h"

/*----------------------------------------------------------------------------*/
/*!
  It defines the QPA4361 pa_port enum.
*/
typedef enum 
{
  QPA4361_CDMA_BAND0_PORT_PA_BC0, 
  QPA4361_CDMA_BAND10_PORT_PA_BC10, 
  QPA4361_CDMA_BAND1_PORT_PA_BC1, 
  QPA4361_CDMA_BAND6_PORT_PA_BC6, 
  QPA4361_CDMA_BAND15_PORT_PA_BC15, 
  QPA4361_WCDMA_BAND5_PORT_PA_B5__W, 
  QPA4361_WCDMA_BAND6_PORT_PA_B5__W, 
  QPA4361_WCDMA_BAND19_PORT_PA_B5__W, 
  QPA4361_WCDMA_BAND8_PORT_PA_B8__W, 
  QPA4361_WCDMA_BAND3_PORT_PA_B3__W, 
  QPA4361_WCDMA_BAND9_PORT_PA_B3__W, 
  QPA4361_WCDMA_BAND4_PORT_PA_B4__W, 
  QPA4361_WCDMA_BAND10_PORT_PA_B4__W, 
  QPA4361_WCDMA_BAND2_PORT_PA_B2_B25__W, 
  QPA4361_WCDMA_BAND25_PORT_PA_B2_B25__W, 
  QPA4361_WCDMA_BAND1_PORT_PA_B1__W, 
  QPA4361_LTE_BAND12_PORT_PA_B12_17, 
  QPA4361_LTE_BAND17_PORT_PA_B12_17, 
  QPA4361_LTE_BAND13_PORT_PA_13, 
  QPA4361_LTE_BAND14_PORT_PA_13, 
  QPA4361_LTE_BAND28_PORT_PA_B28A, 
  QPA4361_LTE_BAND28_B_PORT_PA_B28B, 
  QPA4361_LTE_BAND20_PORT_PA_B20, 
  QPA4361_LTE_BAND27_PORT_PA_B27, 
  QPA4361_LTE_BAND5_PORT_PA_B5_26, 
  QPA4361_LTE_BAND18_PORT_PA_B5_26, 
  QPA4361_LTE_BAND19_PORT_PA_B5_26, 
  QPA4361_LTE_BAND26_PORT_PA_B5_26, 
  QPA4361_LTE_BAND8_PORT_PA_B8, 
  QPA4361_LTE_BAND3_PORT_PA_B3, 
  QPA4361_LTE_BAND9_PORT_PA_B3, 
  QPA4361_LTE_BAND4_PORT_PA_B4, 
  QPA4361_LTE_BAND2_PORT_PA_B2_B25, 
  QPA4361_LTE_BAND25_PORT_PA_B2_B25, 
  QPA4361_LTE_BAND1_PORT_PA_B1, 
  QPA4361_LTE_BAND34_PORT_PA_B34, 
  QPA4361_LTE_BAND39_PORT_PA_B39, 
  QPA4361_LTE_BAND30_PORT_PA_B30, 
  QPA4361_LTE_BAND40_PORT_PA_B40, 
  QPA4361_LTE_BAND41_PORT_PA_B41, 
  QPA4361_LTE_BAND38_PORT_PA_B38, 
  QPA4361_LTE_BAND7_PORT_PA_B7, 
  QPA4361_TDSCDMA_BAND34_PORT_PA_B34__TDS, 
  QPA4361_TDSCDMA_BAND39_PORT_PA_B39__TDS, 
  QPA4361_PORT_NUM, 
  QPA4361_PORT_INVALID, 
} qpa4361_pa_port_data_type;

#include "qpa4361_gsm_port_typedef_ag.h"

#endif