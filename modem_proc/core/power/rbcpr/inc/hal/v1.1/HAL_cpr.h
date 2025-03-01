#ifndef HAL_CPR_H
#define HAL_CPR_H
/*============================================================================
@file HalCpr.h

Hardware Abstraction Layer for RBCPR HW.

Copyright � 2013, 2015 QUALCOMM Technologies, Incorporated.
All Rights Reserved.
QUALCOMM Confidential and Proprietary.

$Header: //components/rel/core.mpss/3.5.c12.3/power/rbcpr/inc/hal/v1.1/HAL_cpr.h#1 $
=============================================================================*/
#include "com_dtypes.h"
#include "DALStdDef.h"
#include "DALSysTypes.h"
#include "cpr_tgt_stub.h"
#include "ULog.h"
#include "cpr.h"


/**
 * Types of interrupts that can be generated by the HW. They MUST be listed in
 * the same order as the HW bitmask used to enable these interrupts.
 */
typedef enum
{
  HAL_CPR_INTERRUPT_DONE,
  HAL_CPR_INTERRUPT_MIN,
  HAL_CPR_INTERRUPT_DOWN,
  HAL_CPR_INTERRUPT_MID,
  HAL_CPR_INTERRUPT_UP,
  HAL_CPR_INTERRUPT_MAX,
  HAL_CPR_INTERRUPT_COUNT,
  HAL_CPR_INTERRUPT_INVALID = 0x7fffFFFF
} HalCprInterruptEnumType;


typedef struct
{
  // Number of CPR sensors on the subsystem
  uint16                    numSensors;

  // Interrupts we're interested in receiving
  HalCprInterruptEnumType   interrupts[HAL_CPR_INTERRUPT_COUNT];

} HalCprConfigType;


/**
 * Oscillator configuration
 */
typedef struct
{
  //uint32 gcnt;
  uint32 target;

} HalCprOscillatorCfgType;


/**
 * Voltage mode dependent configuration
 */
typedef struct
{
  uint32 modeEnum; 

  // Quotient value per PMIC Vdd step (value that corresponds to each
  // 12.5mV step. Voltage step size may vary based on target.
  uint16   stepQuotient;

  //RBCPR_STEP_QUOT.IDLE_CLOCKS controls the number of idle cycles between
  //states of the CPR controller state machine.  The number needs to be
  //set per SoC to account for different SoC timing closure condition.
  uint8    idleClocks;

  // New May 2014 feature.  Modes will have a floor calculated from the ceiling
  // and open loop fuses + this correction factor. 
  int32    floorCalc_correction; 
  uint32   initialFloorVoltage;
  uint32   initialCeilingVoltage;

  // On some products the functional ceiling the voltage is being changed.  
  // For the purpose of correctly calculating the intended open loop voltages the original 
  // ceiling voltage used in factory fuse programming calculations needs to be recorded and used.
  uint32   factoryOpenLoopCeilingCalculationVoltage; 
  
  HalCprOscillatorCfgType oscCfg[CPR_OSCILLATOR_COUNT];

} HalCprVmodeCfgType;


/**
 * One-time configuration values needed at initialization.
 */
typedef struct
{
  //pointer to text documenting what the target configuration being used is. 
  char* configVersionText;

  // We'll only need 2 words for the sensor mask since the HW only supports 64
  // sensors (one bit per sensor).
  uint32 sensorMask[2];
  uint32 sensorBypass[2];

  // Bit mask for which RO's should be disabled.
  // 0x1 for RO0, 0x2 for RO1, 0x4 for RO2, etc
  uint32 speedpushed_ROs;

  // Bitmask of sensors that are on the CPU (Q6) block. We'll bypass these
  // sensors when clkrgm decides to use the LDO to power the Q6 (instead of
  // using the MSS rail).
  uint32 sensorsOnCpuBlock[2];

  // RegisterName__BitField values where RegisterName is the register name
  // used in the SWI, BitField is the bit field name within that register.
  uint8  CTL__DN_THRESHOLD;
  uint8  CTL__UP_THRESHOLD;
  uint8  SW_VLEVEL__SW_VLEVEL;
  uint8  TIMER_ADJUST__CONSECUTIVE_DN;

} HalCprStaticCfgType;


/**
 * Target and voltage dependent configuration.
 */
typedef struct
{
  HalCprStaticCfgType staticCfg;

  // NULL if no supported mode, non NULL points to an available vmode.
  HalCprVmodeCfgType* halVmodeCfgPtrs[CPR_MAX_VMODE_COUNT];

} HalCprTargetConfigType;


/**
 * <!-- HalCprInit -->
 *
 * @brief Initialalize CPR masks, bypass, thresholds, mode, limit, timer,
 * and enable the up interrupt.
 *
 * @param tgtCfg : Pointer to the target specifc configuration info.
 * @param ulogHandle : The ULog handle used to log VDD_MSS CPR activities.
 */
void HalCprInit( HalCprTargetConfigType * tgtCfg,
                 ULogHandle               ulogHandle,
                 ULogHandle               ulogStaticHandle);

/**
 * <!-- HalCprUnclampMemAndIO -->
 *
 * @brief Unclamp the MSS memories and IO. Needed on some chips.
 *
 * Unclamp ALL so that there are no concurency risks with other code running.
 */
void HalCprUnclampMemAndIO( void );


/**
 * <!-- HalCprSetErrStepThresholds -->
 * 
 * @brief Set threshold for allowing the HW to trigger voltage-correction interrupts.
 * 
 * @param dnThresh : Number of error steps (PMIC voltage steps) by which the
 *                   voltage can drop before an interrupt is raised.
 * @param upThresh : Number of error steps (PMIC voltage steps) by which the
 *                   voltage must be increased.
 */
void HalCprSetErrStepThresholds( uint32 dnThresh,
                                 uint32 upThresh );


/**
 * <!-- HalCprConfigInterrupts -->
 *
 * @brief Enable/disable CPR interrupts.
 * 
 * @param enable : If TRUE, will enable all interrupts selected in
 * HalCprConfiguration.interrupts; will disabled all interrupts if FALSE.
 */
void HalCprConfigInterrupts( boolean enable, boolean enableUp, boolean enableDown );


/**
 * <!-- HalCprEnable -->
 *
 * @brief Enable/disable the auto-loop timer HW used for starting CPR measurements.
 * 
 * @param enable : TRUE to enable; FALSE otherwise.
 */
void HalCprEnable( boolean enable );


/**
 * <!-- HalCprEnableInterrupt -->
 *
 * @brief Enable/disable the specified interrupt.
 * 
 * @param interrupt : Interrupt to change
 * @param enable : TRUE to enable; FALSE otherwise.
 */
void HalCprEnableInterrupt( HalCprInterruptEnumType interrupt,
                            boolean                 enable );

/**
 * <!-- HalCprClearAllInterrupts -->
 *
 * @brief Clear the interrupt status of all interrupts.
 */
void HalCprClearAllInterrupts( void );


/**
 * <!-- HalCprEnableDownRecommendation -->
 *
 * @brief Enables/disable the down recommendation from the HW. Disables 
 * the Down interrupt and also enable the auto nack for any down
 * recommendations.
 * 
 * @param enable : Enabled if TRUE; FALSE otherwise
 */
void HalCprEnableDownRecommendation( boolean enable );

/**
 * <!-- HalCprEnableUpRecommendation -->
 *
 * @brief Enables/disable the up recommendation from the HW. Disables 
 * the up interrupt.
 * 
 * @param enable : Enabled if TRUE; FALSE otherwise
 */
void HalCprEnableUpRecommendation( boolean enable );


/**
 * <!-- HalCprStartNextMeasurement -->
 *
 * @brief Provide feedback to HW on whether the recommendation was accepted/rejected
 * and allow the next measurement to start.
 * 
 * @param recomAccepted : TRUE if accepted; FALSE otherwise.
 */
void HalCprStartNextMeasurement( boolean recomAccepted );


/**
 * <!-- HalCprSetupVoltageMode -->
 *
 * @brief Setup the CPR oscillators to operate the specified voltage mode.
 * 
 * @param newMode : voltage mode to switch to.
 * @param refClkRate : Reference clock rate in kHz
 * @param delay : Number of millisecs to delay the next measurement
 */
void HalCprSetupVoltageMode( uint32   newMode,
                             uint32   refClkRate,
                             uint32   delay );


/**
 * <!-- HalCprBypassCpuBlock -->
 *
 * @brief Bypass the sensors on the CPU block. This is necessary when the Q6 is
 * being powered at different voltage than VDD MSS.
 * 
 * @param bypass : TRUE to bypass the CPU sensors; FALSE to no bypass.
 */
void HalCprBypassCpuBlock( boolean bypass );


/**
 * <!-- HalCprIsBusy -->
 *
 * @brief Checks if the HW has completed the measurement.
 * 
 * @return boolean : TRUE if completed; FALSE otherwise.
 */
boolean HalCprIsBusy( void );


/**
 * <!-- HalCprGetOffsetRecommendation -->
 *
 * @brief Gets the offset recommendation of the HW. 
 * HalCprIsBusy() must be called before calling this API to verify the HW has
 * indeed completed measuring before we attempt to read the result.
 * 
 * @return error steps (PMIC voltage steps)
 */
int32 HalCprGetOffsetRecommendation( void );


/**
 * <!-- HalCprLogInterruptStatus -->
 *
 * @brief Log which interrupts are enabled and the interrupt status.
 */
void HalCprLogInterruptStatus( void );


#endif // HAL_CPR_H

