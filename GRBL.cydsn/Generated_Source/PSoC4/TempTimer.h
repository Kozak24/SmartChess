/*******************************************************************************
* File Name: TempTimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the TempTimer
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_TempTimer_H)
#define CY_TCPWM_TempTimer_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} TempTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  TempTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define TempTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define TempTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define TempTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define TempTimer_QUAD_ENCODING_MODES            (0lu)
#define TempTimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define TempTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define TempTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define TempTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define TempTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define TempTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define TempTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define TempTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define TempTimer_TC_RUN_MODE                    (0lu)
#define TempTimer_TC_COUNTER_MODE                (0lu)
#define TempTimer_TC_COMP_CAP_MODE               (2lu)
#define TempTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define TempTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define TempTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define TempTimer_TC_START_SIGNAL_MODE           (0lu)
#define TempTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define TempTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define TempTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define TempTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define TempTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define TempTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define TempTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TempTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define TempTimer_PWM_KILL_EVENT                 (0lu)
#define TempTimer_PWM_STOP_EVENT                 (0lu)
#define TempTimer_PWM_MODE                       (4lu)
#define TempTimer_PWM_OUT_N_INVERT               (0lu)
#define TempTimer_PWM_OUT_INVERT                 (0lu)
#define TempTimer_PWM_ALIGN                      (0lu)
#define TempTimer_PWM_RUN_MODE                   (0lu)
#define TempTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define TempTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define TempTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define TempTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define TempTimer_PWM_START_SIGNAL_MODE          (0lu)
#define TempTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define TempTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define TempTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define TempTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define TempTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define TempTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define TempTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TempTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define TempTimer_TC_PERIOD_VALUE                (1000lu)
#define TempTimer_TC_COMPARE_VALUE               (65535lu)
#define TempTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define TempTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define TempTimer_PWM_PERIOD_VALUE               (65535lu)
#define TempTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define TempTimer_PWM_PERIOD_SWAP                (0lu)
#define TempTimer_PWM_COMPARE_VALUE              (65535lu)
#define TempTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define TempTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define TempTimer__LEFT 0
#define TempTimer__RIGHT 1
#define TempTimer__CENTER 2
#define TempTimer__ASYMMETRIC 3

#define TempTimer__X1 0
#define TempTimer__X2 1
#define TempTimer__X4 2

#define TempTimer__PWM 4
#define TempTimer__PWM_DT 5
#define TempTimer__PWM_PR 6

#define TempTimer__INVERSE 1
#define TempTimer__DIRECT 0

#define TempTimer__CAPTURE 2
#define TempTimer__COMPARE 0

#define TempTimer__TRIG_LEVEL 3
#define TempTimer__TRIG_RISING 0
#define TempTimer__TRIG_FALLING 1
#define TempTimer__TRIG_BOTH 2

#define TempTimer__INTR_MASK_TC 1
#define TempTimer__INTR_MASK_CC_MATCH 2
#define TempTimer__INTR_MASK_NONE 0
#define TempTimer__INTR_MASK_TC_CC 3

#define TempTimer__UNCONFIG 8
#define TempTimer__TIMER 1
#define TempTimer__QUAD 3
#define TempTimer__PWM_SEL 7

#define TempTimer__COUNT_UP 0
#define TempTimer__COUNT_DOWN 1
#define TempTimer__COUNT_UPDOWN0 2
#define TempTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define TempTimer_PRESCALE_DIVBY1                ((uint32)(0u << TempTimer_PRESCALER_SHIFT))
#define TempTimer_PRESCALE_DIVBY2                ((uint32)(1u << TempTimer_PRESCALER_SHIFT))
#define TempTimer_PRESCALE_DIVBY4                ((uint32)(2u << TempTimer_PRESCALER_SHIFT))
#define TempTimer_PRESCALE_DIVBY8                ((uint32)(3u << TempTimer_PRESCALER_SHIFT))
#define TempTimer_PRESCALE_DIVBY16               ((uint32)(4u << TempTimer_PRESCALER_SHIFT))
#define TempTimer_PRESCALE_DIVBY32               ((uint32)(5u << TempTimer_PRESCALER_SHIFT))
#define TempTimer_PRESCALE_DIVBY64               ((uint32)(6u << TempTimer_PRESCALER_SHIFT))
#define TempTimer_PRESCALE_DIVBY128              ((uint32)(7u << TempTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define TempTimer_MODE_TIMER_COMPARE             ((uint32)(TempTimer__COMPARE         <<  \
                                                                  TempTimer_MODE_SHIFT))
#define TempTimer_MODE_TIMER_CAPTURE             ((uint32)(TempTimer__CAPTURE         <<  \
                                                                  TempTimer_MODE_SHIFT))
#define TempTimer_MODE_QUAD                      ((uint32)(TempTimer__QUAD            <<  \
                                                                  TempTimer_MODE_SHIFT))
#define TempTimer_MODE_PWM                       ((uint32)(TempTimer__PWM             <<  \
                                                                  TempTimer_MODE_SHIFT))
#define TempTimer_MODE_PWM_DT                    ((uint32)(TempTimer__PWM_DT          <<  \
                                                                  TempTimer_MODE_SHIFT))
#define TempTimer_MODE_PWM_PR                    ((uint32)(TempTimer__PWM_PR          <<  \
                                                                  TempTimer_MODE_SHIFT))

/* Quad Modes */
#define TempTimer_MODE_X1                        ((uint32)(TempTimer__X1              <<  \
                                                                  TempTimer_QUAD_MODE_SHIFT))
#define TempTimer_MODE_X2                        ((uint32)(TempTimer__X2              <<  \
                                                                  TempTimer_QUAD_MODE_SHIFT))
#define TempTimer_MODE_X4                        ((uint32)(TempTimer__X4              <<  \
                                                                  TempTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define TempTimer_COUNT_UP                       ((uint32)(TempTimer__COUNT_UP        <<  \
                                                                  TempTimer_UPDOWN_SHIFT))
#define TempTimer_COUNT_DOWN                     ((uint32)(TempTimer__COUNT_DOWN      <<  \
                                                                  TempTimer_UPDOWN_SHIFT))
#define TempTimer_COUNT_UPDOWN0                  ((uint32)(TempTimer__COUNT_UPDOWN0   <<  \
                                                                  TempTimer_UPDOWN_SHIFT))
#define TempTimer_COUNT_UPDOWN1                  ((uint32)(TempTimer__COUNT_UPDOWN1   <<  \
                                                                  TempTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define TempTimer_INVERT_LINE                    ((uint32)(TempTimer__INVERSE         <<  \
                                                                  TempTimer_INV_OUT_SHIFT))
#define TempTimer_INVERT_LINE_N                  ((uint32)(TempTimer__INVERSE         <<  \
                                                                  TempTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define TempTimer_TRIG_RISING                    ((uint32)TempTimer__TRIG_RISING)
#define TempTimer_TRIG_FALLING                   ((uint32)TempTimer__TRIG_FALLING)
#define TempTimer_TRIG_BOTH                      ((uint32)TempTimer__TRIG_BOTH)
#define TempTimer_TRIG_LEVEL                     ((uint32)TempTimer__TRIG_LEVEL)

/* Interrupt mask */
#define TempTimer_INTR_MASK_TC                   ((uint32)TempTimer__INTR_MASK_TC)
#define TempTimer_INTR_MASK_CC_MATCH             ((uint32)TempTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define TempTimer_CC_MATCH_SET                   (0x00u)
#define TempTimer_CC_MATCH_CLEAR                 (0x01u)
#define TempTimer_CC_MATCH_INVERT                (0x02u)
#define TempTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define TempTimer_OVERLOW_SET                    (0x00u)
#define TempTimer_OVERLOW_CLEAR                  (0x04u)
#define TempTimer_OVERLOW_INVERT                 (0x08u)
#define TempTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define TempTimer_UNDERFLOW_SET                  (0x00u)
#define TempTimer_UNDERFLOW_CLEAR                (0x10u)
#define TempTimer_UNDERFLOW_INVERT               (0x20u)
#define TempTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define TempTimer_PWM_MODE_LEFT                  (TempTimer_CC_MATCH_CLEAR        |   \
                                                         TempTimer_OVERLOW_SET           |   \
                                                         TempTimer_UNDERFLOW_NO_CHANGE)
#define TempTimer_PWM_MODE_RIGHT                 (TempTimer_CC_MATCH_SET          |   \
                                                         TempTimer_OVERLOW_NO_CHANGE     |   \
                                                         TempTimer_UNDERFLOW_CLEAR)
#define TempTimer_PWM_MODE_ASYM                  (TempTimer_CC_MATCH_INVERT       |   \
                                                         TempTimer_OVERLOW_SET           |   \
                                                         TempTimer_UNDERFLOW_CLEAR)

#if (TempTimer_CY_TCPWM_V2)
    #if(TempTimer_CY_TCPWM_4000)
        #define TempTimer_PWM_MODE_CENTER                (TempTimer_CC_MATCH_INVERT       |   \
                                                                 TempTimer_OVERLOW_NO_CHANGE     |   \
                                                                 TempTimer_UNDERFLOW_CLEAR)
    #else
        #define TempTimer_PWM_MODE_CENTER                (TempTimer_CC_MATCH_INVERT       |   \
                                                                 TempTimer_OVERLOW_SET           |   \
                                                                 TempTimer_UNDERFLOW_CLEAR)
    #endif /* (TempTimer_CY_TCPWM_4000) */
#else
    #define TempTimer_PWM_MODE_CENTER                (TempTimer_CC_MATCH_INVERT       |   \
                                                             TempTimer_OVERLOW_NO_CHANGE     |   \
                                                             TempTimer_UNDERFLOW_CLEAR)
#endif /* (TempTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define TempTimer_CMD_CAPTURE                    (0u)
#define TempTimer_CMD_RELOAD                     (8u)
#define TempTimer_CMD_STOP                       (16u)
#define TempTimer_CMD_START                      (24u)

/* Status */
#define TempTimer_STATUS_DOWN                    (1u)
#define TempTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   TempTimer_Init(void);
void   TempTimer_Enable(void);
void   TempTimer_Start(void);
void   TempTimer_Stop(void);

void   TempTimer_SetMode(uint32 mode);
void   TempTimer_SetCounterMode(uint32 counterMode);
void   TempTimer_SetPWMMode(uint32 modeMask);
void   TempTimer_SetQDMode(uint32 qdMode);

void   TempTimer_SetPrescaler(uint32 prescaler);
void   TempTimer_TriggerCommand(uint32 mask, uint32 command);
void   TempTimer_SetOneShot(uint32 oneShotEnable);
uint32 TempTimer_ReadStatus(void);

void   TempTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   TempTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   TempTimer_SetPWMDeadTime(uint32 deadTime);
void   TempTimer_SetPWMInvert(uint32 mask);

void   TempTimer_SetInterruptMode(uint32 interruptMask);
uint32 TempTimer_GetInterruptSourceMasked(void);
uint32 TempTimer_GetInterruptSource(void);
void   TempTimer_ClearInterrupt(uint32 interruptMask);
void   TempTimer_SetInterrupt(uint32 interruptMask);

void   TempTimer_WriteCounter(uint32 count);
uint32 TempTimer_ReadCounter(void);

uint32 TempTimer_ReadCapture(void);
uint32 TempTimer_ReadCaptureBuf(void);

void   TempTimer_WritePeriod(uint32 period);
uint32 TempTimer_ReadPeriod(void);
void   TempTimer_WritePeriodBuf(uint32 periodBuf);
uint32 TempTimer_ReadPeriodBuf(void);

void   TempTimer_WriteCompare(uint32 compare);
uint32 TempTimer_ReadCompare(void);
void   TempTimer_WriteCompareBuf(uint32 compareBuf);
uint32 TempTimer_ReadCompareBuf(void);

void   TempTimer_SetPeriodSwap(uint32 swapEnable);
void   TempTimer_SetCompareSwap(uint32 swapEnable);

void   TempTimer_SetCaptureMode(uint32 triggerMode);
void   TempTimer_SetReloadMode(uint32 triggerMode);
void   TempTimer_SetStartMode(uint32 triggerMode);
void   TempTimer_SetStopMode(uint32 triggerMode);
void   TempTimer_SetCountMode(uint32 triggerMode);

void   TempTimer_SaveConfig(void);
void   TempTimer_RestoreConfig(void);
void   TempTimer_Sleep(void);
void   TempTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define TempTimer_BLOCK_CONTROL_REG              (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TempTimer_BLOCK_CONTROL_PTR              ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TempTimer_COMMAND_REG                    (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TempTimer_COMMAND_PTR                    ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TempTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TempTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TempTimer_CONTROL_REG                    (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__CTRL )
#define TempTimer_CONTROL_PTR                    ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__CTRL )
#define TempTimer_STATUS_REG                     (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__STATUS )
#define TempTimer_STATUS_PTR                     ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__STATUS )
#define TempTimer_COUNTER_REG                    (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__COUNTER )
#define TempTimer_COUNTER_PTR                    ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__COUNTER )
#define TempTimer_COMP_CAP_REG                   (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__CC )
#define TempTimer_COMP_CAP_PTR                   ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__CC )
#define TempTimer_COMP_CAP_BUF_REG               (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define TempTimer_COMP_CAP_BUF_PTR               ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define TempTimer_PERIOD_REG                     (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__PERIOD )
#define TempTimer_PERIOD_PTR                     ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__PERIOD )
#define TempTimer_PERIOD_BUF_REG                 (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TempTimer_PERIOD_BUF_PTR                 ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TempTimer_TRIG_CONTROL0_REG              (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TempTimer_TRIG_CONTROL0_PTR              ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TempTimer_TRIG_CONTROL1_REG              (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TempTimer_TRIG_CONTROL1_PTR              ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TempTimer_TRIG_CONTROL2_REG              (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TempTimer_TRIG_CONTROL2_PTR              ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TempTimer_INTERRUPT_REQ_REG              (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__INTR )
#define TempTimer_INTERRUPT_REQ_PTR              ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__INTR )
#define TempTimer_INTERRUPT_SET_REG              (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define TempTimer_INTERRUPT_SET_PTR              ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define TempTimer_INTERRUPT_MASK_REG             (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define TempTimer_INTERRUPT_MASK_PTR             ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define TempTimer_INTERRUPT_MASKED_REG           (*(reg32 *) TempTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define TempTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) TempTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define TempTimer_MASK                           ((uint32)TempTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define TempTimer_RELOAD_CC_SHIFT                (0u)
#define TempTimer_RELOAD_PERIOD_SHIFT            (1u)
#define TempTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define TempTimer_PWM_STOP_KILL_SHIFT            (3u)
#define TempTimer_PRESCALER_SHIFT                (8u)
#define TempTimer_UPDOWN_SHIFT                   (16u)
#define TempTimer_ONESHOT_SHIFT                  (18u)
#define TempTimer_QUAD_MODE_SHIFT                (20u)
#define TempTimer_INV_OUT_SHIFT                  (20u)
#define TempTimer_INV_COMPL_OUT_SHIFT            (21u)
#define TempTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define TempTimer_RELOAD_CC_MASK                 ((uint32)(TempTimer_1BIT_MASK        <<  \
                                                                            TempTimer_RELOAD_CC_SHIFT))
#define TempTimer_RELOAD_PERIOD_MASK             ((uint32)(TempTimer_1BIT_MASK        <<  \
                                                                            TempTimer_RELOAD_PERIOD_SHIFT))
#define TempTimer_PWM_SYNC_KILL_MASK             ((uint32)(TempTimer_1BIT_MASK        <<  \
                                                                            TempTimer_PWM_SYNC_KILL_SHIFT))
#define TempTimer_PWM_STOP_KILL_MASK             ((uint32)(TempTimer_1BIT_MASK        <<  \
                                                                            TempTimer_PWM_STOP_KILL_SHIFT))
#define TempTimer_PRESCALER_MASK                 ((uint32)(TempTimer_8BIT_MASK        <<  \
                                                                            TempTimer_PRESCALER_SHIFT))
#define TempTimer_UPDOWN_MASK                    ((uint32)(TempTimer_2BIT_MASK        <<  \
                                                                            TempTimer_UPDOWN_SHIFT))
#define TempTimer_ONESHOT_MASK                   ((uint32)(TempTimer_1BIT_MASK        <<  \
                                                                            TempTimer_ONESHOT_SHIFT))
#define TempTimer_QUAD_MODE_MASK                 ((uint32)(TempTimer_3BIT_MASK        <<  \
                                                                            TempTimer_QUAD_MODE_SHIFT))
#define TempTimer_INV_OUT_MASK                   ((uint32)(TempTimer_2BIT_MASK        <<  \
                                                                            TempTimer_INV_OUT_SHIFT))
#define TempTimer_MODE_MASK                      ((uint32)(TempTimer_3BIT_MASK        <<  \
                                                                            TempTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define TempTimer_CAPTURE_SHIFT                  (0u)
#define TempTimer_COUNT_SHIFT                    (2u)
#define TempTimer_RELOAD_SHIFT                   (4u)
#define TempTimer_STOP_SHIFT                     (6u)
#define TempTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define TempTimer_CAPTURE_MASK                   ((uint32)(TempTimer_2BIT_MASK        <<  \
                                                                  TempTimer_CAPTURE_SHIFT))
#define TempTimer_COUNT_MASK                     ((uint32)(TempTimer_2BIT_MASK        <<  \
                                                                  TempTimer_COUNT_SHIFT))
#define TempTimer_RELOAD_MASK                    ((uint32)(TempTimer_2BIT_MASK        <<  \
                                                                  TempTimer_RELOAD_SHIFT))
#define TempTimer_STOP_MASK                      ((uint32)(TempTimer_2BIT_MASK        <<  \
                                                                  TempTimer_STOP_SHIFT))
#define TempTimer_START_MASK                     ((uint32)(TempTimer_2BIT_MASK        <<  \
                                                                  TempTimer_START_SHIFT))

/* MASK */
#define TempTimer_1BIT_MASK                      ((uint32)0x01u)
#define TempTimer_2BIT_MASK                      ((uint32)0x03u)
#define TempTimer_3BIT_MASK                      ((uint32)0x07u)
#define TempTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define TempTimer_8BIT_MASK                      ((uint32)0xFFu)
#define TempTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define TempTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define TempTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(TempTimer_QUAD_ENCODING_MODES     << TempTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(TempTimer_CONFIG                  << TempTimer_MODE_SHIFT)))

#define TempTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(TempTimer_PWM_STOP_EVENT          << TempTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(TempTimer_PWM_OUT_INVERT          << TempTimer_INV_OUT_SHIFT))         |\
         ((uint32)(TempTimer_PWM_OUT_N_INVERT        << TempTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(TempTimer_PWM_MODE                << TempTimer_MODE_SHIFT)))

#define TempTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(TempTimer_PWM_RUN_MODE         << TempTimer_ONESHOT_SHIFT))
            
#define TempTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(TempTimer_PWM_ALIGN            << TempTimer_UPDOWN_SHIFT))

#define TempTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(TempTimer_PWM_KILL_EVENT      << TempTimer_PWM_SYNC_KILL_SHIFT))

#define TempTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(TempTimer_PWM_DEAD_TIME_CYCLE  << TempTimer_PRESCALER_SHIFT))

#define TempTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(TempTimer_PWM_PRESCALER        << TempTimer_PRESCALER_SHIFT))

#define TempTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(TempTimer_TC_PRESCALER            << TempTimer_PRESCALER_SHIFT))       |\
         ((uint32)(TempTimer_TC_COUNTER_MODE         << TempTimer_UPDOWN_SHIFT))          |\
         ((uint32)(TempTimer_TC_RUN_MODE             << TempTimer_ONESHOT_SHIFT))         |\
         ((uint32)(TempTimer_TC_COMP_CAP_MODE        << TempTimer_MODE_SHIFT)))
        
#define TempTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(TempTimer_QUAD_PHIA_SIGNAL_MODE   << TempTimer_COUNT_SHIFT))           |\
         ((uint32)(TempTimer_QUAD_INDEX_SIGNAL_MODE  << TempTimer_RELOAD_SHIFT))          |\
         ((uint32)(TempTimer_QUAD_STOP_SIGNAL_MODE   << TempTimer_STOP_SHIFT))            |\
         ((uint32)(TempTimer_QUAD_PHIB_SIGNAL_MODE   << TempTimer_START_SHIFT)))

#define TempTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(TempTimer_PWM_SWITCH_SIGNAL_MODE  << TempTimer_CAPTURE_SHIFT))         |\
         ((uint32)(TempTimer_PWM_COUNT_SIGNAL_MODE   << TempTimer_COUNT_SHIFT))           |\
         ((uint32)(TempTimer_PWM_RELOAD_SIGNAL_MODE  << TempTimer_RELOAD_SHIFT))          |\
         ((uint32)(TempTimer_PWM_STOP_SIGNAL_MODE    << TempTimer_STOP_SHIFT))            |\
         ((uint32)(TempTimer_PWM_START_SIGNAL_MODE   << TempTimer_START_SHIFT)))

#define TempTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(TempTimer_TC_CAPTURE_SIGNAL_MODE  << TempTimer_CAPTURE_SHIFT))         |\
         ((uint32)(TempTimer_TC_COUNT_SIGNAL_MODE    << TempTimer_COUNT_SHIFT))           |\
         ((uint32)(TempTimer_TC_RELOAD_SIGNAL_MODE   << TempTimer_RELOAD_SHIFT))          |\
         ((uint32)(TempTimer_TC_STOP_SIGNAL_MODE     << TempTimer_STOP_SHIFT))            |\
         ((uint32)(TempTimer_TC_START_SIGNAL_MODE    << TempTimer_START_SHIFT)))
        
#define TempTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((TempTimer__COUNT_UPDOWN0 == TempTimer_TC_COUNTER_MODE)                  ||\
                 (TempTimer__COUNT_UPDOWN1 == TempTimer_TC_COUNTER_MODE))

#define TempTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((TempTimer__CENTER == TempTimer_PWM_ALIGN)                               ||\
                 (TempTimer__ASYMMETRIC == TempTimer_PWM_ALIGN))               
        
#define TempTimer_PWM_PR_INIT_VALUE              (1u)
#define TempTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_TempTimer_H */

/* [] END OF FILE */
