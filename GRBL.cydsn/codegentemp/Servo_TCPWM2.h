/*******************************************************************************
* File Name: Servo_TCPWM2.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the Servo_TCPWM2
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

#if !defined(CY_TCPWM_Servo_TCPWM2_H)
#define CY_TCPWM_Servo_TCPWM2_H


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
} Servo_TCPWM2_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Servo_TCPWM2_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Servo_TCPWM2_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Servo_TCPWM2_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Servo_TCPWM2_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define Servo_TCPWM2_QUAD_ENCODING_MODES            (0lu)
#define Servo_TCPWM2_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define Servo_TCPWM2_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Servo_TCPWM2_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Servo_TCPWM2_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Servo_TCPWM2_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Servo_TCPWM2_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Servo_TCPWM2_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Servo_TCPWM2_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Servo_TCPWM2_TC_RUN_MODE                    (0lu)
#define Servo_TCPWM2_TC_COUNTER_MODE                (0lu)
#define Servo_TCPWM2_TC_COMP_CAP_MODE               (2lu)
#define Servo_TCPWM2_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Servo_TCPWM2_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Servo_TCPWM2_TC_COUNT_SIGNAL_MODE           (3lu)
#define Servo_TCPWM2_TC_START_SIGNAL_MODE           (0lu)
#define Servo_TCPWM2_TC_STOP_SIGNAL_MODE            (0lu)
#define Servo_TCPWM2_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Servo_TCPWM2_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Servo_TCPWM2_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Servo_TCPWM2_TC_START_SIGNAL_PRESENT        (0lu)
#define Servo_TCPWM2_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Servo_TCPWM2_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Servo_TCPWM2_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define Servo_TCPWM2_PWM_KILL_EVENT                 (0lu)
#define Servo_TCPWM2_PWM_STOP_EVENT                 (0lu)
#define Servo_TCPWM2_PWM_MODE                       (4lu)
#define Servo_TCPWM2_PWM_OUT_N_INVERT               (0lu)
#define Servo_TCPWM2_PWM_OUT_INVERT                 (0lu)
#define Servo_TCPWM2_PWM_ALIGN                      (0lu)
#define Servo_TCPWM2_PWM_RUN_MODE                   (0lu)
#define Servo_TCPWM2_PWM_DEAD_TIME_CYCLE            (0lu)
#define Servo_TCPWM2_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Servo_TCPWM2_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Servo_TCPWM2_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Servo_TCPWM2_PWM_START_SIGNAL_MODE          (0lu)
#define Servo_TCPWM2_PWM_STOP_SIGNAL_MODE           (0lu)
#define Servo_TCPWM2_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Servo_TCPWM2_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Servo_TCPWM2_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Servo_TCPWM2_PWM_START_SIGNAL_PRESENT       (0lu)
#define Servo_TCPWM2_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Servo_TCPWM2_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Servo_TCPWM2_PWM_INTERRUPT_MASK             (0lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Servo_TCPWM2_TC_PERIOD_VALUE                (65535lu)
#define Servo_TCPWM2_TC_COMPARE_VALUE               (65535lu)
#define Servo_TCPWM2_TC_COMPARE_BUF_VALUE           (65535lu)
#define Servo_TCPWM2_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Servo_TCPWM2_PWM_PERIOD_VALUE               (39lu)
#define Servo_TCPWM2_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Servo_TCPWM2_PWM_PERIOD_SWAP                (0lu)
#define Servo_TCPWM2_PWM_COMPARE_VALUE              (1lu)
#define Servo_TCPWM2_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Servo_TCPWM2_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Servo_TCPWM2__LEFT 0
#define Servo_TCPWM2__RIGHT 1
#define Servo_TCPWM2__CENTER 2
#define Servo_TCPWM2__ASYMMETRIC 3

#define Servo_TCPWM2__X1 0
#define Servo_TCPWM2__X2 1
#define Servo_TCPWM2__X4 2

#define Servo_TCPWM2__PWM 4
#define Servo_TCPWM2__PWM_DT 5
#define Servo_TCPWM2__PWM_PR 6

#define Servo_TCPWM2__INVERSE 1
#define Servo_TCPWM2__DIRECT 0

#define Servo_TCPWM2__CAPTURE 2
#define Servo_TCPWM2__COMPARE 0

#define Servo_TCPWM2__TRIG_LEVEL 3
#define Servo_TCPWM2__TRIG_RISING 0
#define Servo_TCPWM2__TRIG_FALLING 1
#define Servo_TCPWM2__TRIG_BOTH 2

#define Servo_TCPWM2__INTR_MASK_TC 1
#define Servo_TCPWM2__INTR_MASK_CC_MATCH 2
#define Servo_TCPWM2__INTR_MASK_NONE 0
#define Servo_TCPWM2__INTR_MASK_TC_CC 3

#define Servo_TCPWM2__UNCONFIG 8
#define Servo_TCPWM2__TIMER 1
#define Servo_TCPWM2__QUAD 3
#define Servo_TCPWM2__PWM_SEL 7

#define Servo_TCPWM2__COUNT_UP 0
#define Servo_TCPWM2__COUNT_DOWN 1
#define Servo_TCPWM2__COUNT_UPDOWN0 2
#define Servo_TCPWM2__COUNT_UPDOWN1 3


/* Prescaler */
#define Servo_TCPWM2_PRESCALE_DIVBY1                ((uint32)(0u << Servo_TCPWM2_PRESCALER_SHIFT))
#define Servo_TCPWM2_PRESCALE_DIVBY2                ((uint32)(1u << Servo_TCPWM2_PRESCALER_SHIFT))
#define Servo_TCPWM2_PRESCALE_DIVBY4                ((uint32)(2u << Servo_TCPWM2_PRESCALER_SHIFT))
#define Servo_TCPWM2_PRESCALE_DIVBY8                ((uint32)(3u << Servo_TCPWM2_PRESCALER_SHIFT))
#define Servo_TCPWM2_PRESCALE_DIVBY16               ((uint32)(4u << Servo_TCPWM2_PRESCALER_SHIFT))
#define Servo_TCPWM2_PRESCALE_DIVBY32               ((uint32)(5u << Servo_TCPWM2_PRESCALER_SHIFT))
#define Servo_TCPWM2_PRESCALE_DIVBY64               ((uint32)(6u << Servo_TCPWM2_PRESCALER_SHIFT))
#define Servo_TCPWM2_PRESCALE_DIVBY128              ((uint32)(7u << Servo_TCPWM2_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Servo_TCPWM2_MODE_TIMER_COMPARE             ((uint32)(Servo_TCPWM2__COMPARE         <<  \
                                                                  Servo_TCPWM2_MODE_SHIFT))
#define Servo_TCPWM2_MODE_TIMER_CAPTURE             ((uint32)(Servo_TCPWM2__CAPTURE         <<  \
                                                                  Servo_TCPWM2_MODE_SHIFT))
#define Servo_TCPWM2_MODE_QUAD                      ((uint32)(Servo_TCPWM2__QUAD            <<  \
                                                                  Servo_TCPWM2_MODE_SHIFT))
#define Servo_TCPWM2_MODE_PWM                       ((uint32)(Servo_TCPWM2__PWM             <<  \
                                                                  Servo_TCPWM2_MODE_SHIFT))
#define Servo_TCPWM2_MODE_PWM_DT                    ((uint32)(Servo_TCPWM2__PWM_DT          <<  \
                                                                  Servo_TCPWM2_MODE_SHIFT))
#define Servo_TCPWM2_MODE_PWM_PR                    ((uint32)(Servo_TCPWM2__PWM_PR          <<  \
                                                                  Servo_TCPWM2_MODE_SHIFT))

/* Quad Modes */
#define Servo_TCPWM2_MODE_X1                        ((uint32)(Servo_TCPWM2__X1              <<  \
                                                                  Servo_TCPWM2_QUAD_MODE_SHIFT))
#define Servo_TCPWM2_MODE_X2                        ((uint32)(Servo_TCPWM2__X2              <<  \
                                                                  Servo_TCPWM2_QUAD_MODE_SHIFT))
#define Servo_TCPWM2_MODE_X4                        ((uint32)(Servo_TCPWM2__X4              <<  \
                                                                  Servo_TCPWM2_QUAD_MODE_SHIFT))

/* Counter modes */
#define Servo_TCPWM2_COUNT_UP                       ((uint32)(Servo_TCPWM2__COUNT_UP        <<  \
                                                                  Servo_TCPWM2_UPDOWN_SHIFT))
#define Servo_TCPWM2_COUNT_DOWN                     ((uint32)(Servo_TCPWM2__COUNT_DOWN      <<  \
                                                                  Servo_TCPWM2_UPDOWN_SHIFT))
#define Servo_TCPWM2_COUNT_UPDOWN0                  ((uint32)(Servo_TCPWM2__COUNT_UPDOWN0   <<  \
                                                                  Servo_TCPWM2_UPDOWN_SHIFT))
#define Servo_TCPWM2_COUNT_UPDOWN1                  ((uint32)(Servo_TCPWM2__COUNT_UPDOWN1   <<  \
                                                                  Servo_TCPWM2_UPDOWN_SHIFT))

/* PWM output invert */
#define Servo_TCPWM2_INVERT_LINE                    ((uint32)(Servo_TCPWM2__INVERSE         <<  \
                                                                  Servo_TCPWM2_INV_OUT_SHIFT))
#define Servo_TCPWM2_INVERT_LINE_N                  ((uint32)(Servo_TCPWM2__INVERSE         <<  \
                                                                  Servo_TCPWM2_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Servo_TCPWM2_TRIG_RISING                    ((uint32)Servo_TCPWM2__TRIG_RISING)
#define Servo_TCPWM2_TRIG_FALLING                   ((uint32)Servo_TCPWM2__TRIG_FALLING)
#define Servo_TCPWM2_TRIG_BOTH                      ((uint32)Servo_TCPWM2__TRIG_BOTH)
#define Servo_TCPWM2_TRIG_LEVEL                     ((uint32)Servo_TCPWM2__TRIG_LEVEL)

/* Interrupt mask */
#define Servo_TCPWM2_INTR_MASK_TC                   ((uint32)Servo_TCPWM2__INTR_MASK_TC)
#define Servo_TCPWM2_INTR_MASK_CC_MATCH             ((uint32)Servo_TCPWM2__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Servo_TCPWM2_CC_MATCH_SET                   (0x00u)
#define Servo_TCPWM2_CC_MATCH_CLEAR                 (0x01u)
#define Servo_TCPWM2_CC_MATCH_INVERT                (0x02u)
#define Servo_TCPWM2_CC_MATCH_NO_CHANGE             (0x03u)
#define Servo_TCPWM2_OVERLOW_SET                    (0x00u)
#define Servo_TCPWM2_OVERLOW_CLEAR                  (0x04u)
#define Servo_TCPWM2_OVERLOW_INVERT                 (0x08u)
#define Servo_TCPWM2_OVERLOW_NO_CHANGE              (0x0Cu)
#define Servo_TCPWM2_UNDERFLOW_SET                  (0x00u)
#define Servo_TCPWM2_UNDERFLOW_CLEAR                (0x10u)
#define Servo_TCPWM2_UNDERFLOW_INVERT               (0x20u)
#define Servo_TCPWM2_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Servo_TCPWM2_PWM_MODE_LEFT                  (Servo_TCPWM2_CC_MATCH_CLEAR        |   \
                                                         Servo_TCPWM2_OVERLOW_SET           |   \
                                                         Servo_TCPWM2_UNDERFLOW_NO_CHANGE)
#define Servo_TCPWM2_PWM_MODE_RIGHT                 (Servo_TCPWM2_CC_MATCH_SET          |   \
                                                         Servo_TCPWM2_OVERLOW_NO_CHANGE     |   \
                                                         Servo_TCPWM2_UNDERFLOW_CLEAR)
#define Servo_TCPWM2_PWM_MODE_ASYM                  (Servo_TCPWM2_CC_MATCH_INVERT       |   \
                                                         Servo_TCPWM2_OVERLOW_SET           |   \
                                                         Servo_TCPWM2_UNDERFLOW_CLEAR)

#if (Servo_TCPWM2_CY_TCPWM_V2)
    #if(Servo_TCPWM2_CY_TCPWM_4000)
        #define Servo_TCPWM2_PWM_MODE_CENTER                (Servo_TCPWM2_CC_MATCH_INVERT       |   \
                                                                 Servo_TCPWM2_OVERLOW_NO_CHANGE     |   \
                                                                 Servo_TCPWM2_UNDERFLOW_CLEAR)
    #else
        #define Servo_TCPWM2_PWM_MODE_CENTER                (Servo_TCPWM2_CC_MATCH_INVERT       |   \
                                                                 Servo_TCPWM2_OVERLOW_SET           |   \
                                                                 Servo_TCPWM2_UNDERFLOW_CLEAR)
    #endif /* (Servo_TCPWM2_CY_TCPWM_4000) */
#else
    #define Servo_TCPWM2_PWM_MODE_CENTER                (Servo_TCPWM2_CC_MATCH_INVERT       |   \
                                                             Servo_TCPWM2_OVERLOW_NO_CHANGE     |   \
                                                             Servo_TCPWM2_UNDERFLOW_CLEAR)
#endif /* (Servo_TCPWM2_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Servo_TCPWM2_CMD_CAPTURE                    (0u)
#define Servo_TCPWM2_CMD_RELOAD                     (8u)
#define Servo_TCPWM2_CMD_STOP                       (16u)
#define Servo_TCPWM2_CMD_START                      (24u)

/* Status */
#define Servo_TCPWM2_STATUS_DOWN                    (1u)
#define Servo_TCPWM2_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Servo_TCPWM2_Init(void);
void   Servo_TCPWM2_Enable(void);
void   Servo_TCPWM2_Start(void);
void   Servo_TCPWM2_Stop(void);

void   Servo_TCPWM2_SetMode(uint32 mode);
void   Servo_TCPWM2_SetCounterMode(uint32 counterMode);
void   Servo_TCPWM2_SetPWMMode(uint32 modeMask);
void   Servo_TCPWM2_SetQDMode(uint32 qdMode);

void   Servo_TCPWM2_SetPrescaler(uint32 prescaler);
void   Servo_TCPWM2_TriggerCommand(uint32 mask, uint32 command);
void   Servo_TCPWM2_SetOneShot(uint32 oneShotEnable);
uint32 Servo_TCPWM2_ReadStatus(void);

void   Servo_TCPWM2_SetPWMSyncKill(uint32 syncKillEnable);
void   Servo_TCPWM2_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Servo_TCPWM2_SetPWMDeadTime(uint32 deadTime);
void   Servo_TCPWM2_SetPWMInvert(uint32 mask);

void   Servo_TCPWM2_SetInterruptMode(uint32 interruptMask);
uint32 Servo_TCPWM2_GetInterruptSourceMasked(void);
uint32 Servo_TCPWM2_GetInterruptSource(void);
void   Servo_TCPWM2_ClearInterrupt(uint32 interruptMask);
void   Servo_TCPWM2_SetInterrupt(uint32 interruptMask);

void   Servo_TCPWM2_WriteCounter(uint32 count);
uint32 Servo_TCPWM2_ReadCounter(void);

uint32 Servo_TCPWM2_ReadCapture(void);
uint32 Servo_TCPWM2_ReadCaptureBuf(void);

void   Servo_TCPWM2_WritePeriod(uint32 period);
uint32 Servo_TCPWM2_ReadPeriod(void);
void   Servo_TCPWM2_WritePeriodBuf(uint32 periodBuf);
uint32 Servo_TCPWM2_ReadPeriodBuf(void);

void   Servo_TCPWM2_WriteCompare(uint32 compare);
uint32 Servo_TCPWM2_ReadCompare(void);
void   Servo_TCPWM2_WriteCompareBuf(uint32 compareBuf);
uint32 Servo_TCPWM2_ReadCompareBuf(void);

void   Servo_TCPWM2_SetPeriodSwap(uint32 swapEnable);
void   Servo_TCPWM2_SetCompareSwap(uint32 swapEnable);

void   Servo_TCPWM2_SetCaptureMode(uint32 triggerMode);
void   Servo_TCPWM2_SetReloadMode(uint32 triggerMode);
void   Servo_TCPWM2_SetStartMode(uint32 triggerMode);
void   Servo_TCPWM2_SetStopMode(uint32 triggerMode);
void   Servo_TCPWM2_SetCountMode(uint32 triggerMode);

void   Servo_TCPWM2_SaveConfig(void);
void   Servo_TCPWM2_RestoreConfig(void);
void   Servo_TCPWM2_Sleep(void);
void   Servo_TCPWM2_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Servo_TCPWM2_BLOCK_CONTROL_REG              (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Servo_TCPWM2_BLOCK_CONTROL_PTR              ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Servo_TCPWM2_COMMAND_REG                    (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Servo_TCPWM2_COMMAND_PTR                    ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Servo_TCPWM2_INTRRUPT_CAUSE_REG             (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Servo_TCPWM2_INTRRUPT_CAUSE_PTR             ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Servo_TCPWM2_CONTROL_REG                    (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__CTRL )
#define Servo_TCPWM2_CONTROL_PTR                    ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__CTRL )
#define Servo_TCPWM2_STATUS_REG                     (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__STATUS )
#define Servo_TCPWM2_STATUS_PTR                     ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__STATUS )
#define Servo_TCPWM2_COUNTER_REG                    (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__COUNTER )
#define Servo_TCPWM2_COUNTER_PTR                    ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__COUNTER )
#define Servo_TCPWM2_COMP_CAP_REG                   (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__CC )
#define Servo_TCPWM2_COMP_CAP_PTR                   ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__CC )
#define Servo_TCPWM2_COMP_CAP_BUF_REG               (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__CC_BUFF )
#define Servo_TCPWM2_COMP_CAP_BUF_PTR               ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__CC_BUFF )
#define Servo_TCPWM2_PERIOD_REG                     (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__PERIOD )
#define Servo_TCPWM2_PERIOD_PTR                     ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__PERIOD )
#define Servo_TCPWM2_PERIOD_BUF_REG                 (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Servo_TCPWM2_PERIOD_BUF_PTR                 ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Servo_TCPWM2_TRIG_CONTROL0_REG              (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Servo_TCPWM2_TRIG_CONTROL0_PTR              ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Servo_TCPWM2_TRIG_CONTROL1_REG              (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Servo_TCPWM2_TRIG_CONTROL1_PTR              ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Servo_TCPWM2_TRIG_CONTROL2_REG              (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Servo_TCPWM2_TRIG_CONTROL2_PTR              ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Servo_TCPWM2_INTERRUPT_REQ_REG              (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__INTR )
#define Servo_TCPWM2_INTERRUPT_REQ_PTR              ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__INTR )
#define Servo_TCPWM2_INTERRUPT_SET_REG              (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__INTR_SET )
#define Servo_TCPWM2_INTERRUPT_SET_PTR              ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__INTR_SET )
#define Servo_TCPWM2_INTERRUPT_MASK_REG             (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__INTR_MASK )
#define Servo_TCPWM2_INTERRUPT_MASK_PTR             ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__INTR_MASK )
#define Servo_TCPWM2_INTERRUPT_MASKED_REG           (*(reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Servo_TCPWM2_INTERRUPT_MASKED_PTR           ( (reg32 *) Servo_TCPWM2_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Servo_TCPWM2_MASK                           ((uint32)Servo_TCPWM2_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Servo_TCPWM2_RELOAD_CC_SHIFT                (0u)
#define Servo_TCPWM2_RELOAD_PERIOD_SHIFT            (1u)
#define Servo_TCPWM2_PWM_SYNC_KILL_SHIFT            (2u)
#define Servo_TCPWM2_PWM_STOP_KILL_SHIFT            (3u)
#define Servo_TCPWM2_PRESCALER_SHIFT                (8u)
#define Servo_TCPWM2_UPDOWN_SHIFT                   (16u)
#define Servo_TCPWM2_ONESHOT_SHIFT                  (18u)
#define Servo_TCPWM2_QUAD_MODE_SHIFT                (20u)
#define Servo_TCPWM2_INV_OUT_SHIFT                  (20u)
#define Servo_TCPWM2_INV_COMPL_OUT_SHIFT            (21u)
#define Servo_TCPWM2_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Servo_TCPWM2_RELOAD_CC_MASK                 ((uint32)(Servo_TCPWM2_1BIT_MASK        <<  \
                                                                            Servo_TCPWM2_RELOAD_CC_SHIFT))
#define Servo_TCPWM2_RELOAD_PERIOD_MASK             ((uint32)(Servo_TCPWM2_1BIT_MASK        <<  \
                                                                            Servo_TCPWM2_RELOAD_PERIOD_SHIFT))
#define Servo_TCPWM2_PWM_SYNC_KILL_MASK             ((uint32)(Servo_TCPWM2_1BIT_MASK        <<  \
                                                                            Servo_TCPWM2_PWM_SYNC_KILL_SHIFT))
#define Servo_TCPWM2_PWM_STOP_KILL_MASK             ((uint32)(Servo_TCPWM2_1BIT_MASK        <<  \
                                                                            Servo_TCPWM2_PWM_STOP_KILL_SHIFT))
#define Servo_TCPWM2_PRESCALER_MASK                 ((uint32)(Servo_TCPWM2_8BIT_MASK        <<  \
                                                                            Servo_TCPWM2_PRESCALER_SHIFT))
#define Servo_TCPWM2_UPDOWN_MASK                    ((uint32)(Servo_TCPWM2_2BIT_MASK        <<  \
                                                                            Servo_TCPWM2_UPDOWN_SHIFT))
#define Servo_TCPWM2_ONESHOT_MASK                   ((uint32)(Servo_TCPWM2_1BIT_MASK        <<  \
                                                                            Servo_TCPWM2_ONESHOT_SHIFT))
#define Servo_TCPWM2_QUAD_MODE_MASK                 ((uint32)(Servo_TCPWM2_3BIT_MASK        <<  \
                                                                            Servo_TCPWM2_QUAD_MODE_SHIFT))
#define Servo_TCPWM2_INV_OUT_MASK                   ((uint32)(Servo_TCPWM2_2BIT_MASK        <<  \
                                                                            Servo_TCPWM2_INV_OUT_SHIFT))
#define Servo_TCPWM2_MODE_MASK                      ((uint32)(Servo_TCPWM2_3BIT_MASK        <<  \
                                                                            Servo_TCPWM2_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Servo_TCPWM2_CAPTURE_SHIFT                  (0u)
#define Servo_TCPWM2_COUNT_SHIFT                    (2u)
#define Servo_TCPWM2_RELOAD_SHIFT                   (4u)
#define Servo_TCPWM2_STOP_SHIFT                     (6u)
#define Servo_TCPWM2_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Servo_TCPWM2_CAPTURE_MASK                   ((uint32)(Servo_TCPWM2_2BIT_MASK        <<  \
                                                                  Servo_TCPWM2_CAPTURE_SHIFT))
#define Servo_TCPWM2_COUNT_MASK                     ((uint32)(Servo_TCPWM2_2BIT_MASK        <<  \
                                                                  Servo_TCPWM2_COUNT_SHIFT))
#define Servo_TCPWM2_RELOAD_MASK                    ((uint32)(Servo_TCPWM2_2BIT_MASK        <<  \
                                                                  Servo_TCPWM2_RELOAD_SHIFT))
#define Servo_TCPWM2_STOP_MASK                      ((uint32)(Servo_TCPWM2_2BIT_MASK        <<  \
                                                                  Servo_TCPWM2_STOP_SHIFT))
#define Servo_TCPWM2_START_MASK                     ((uint32)(Servo_TCPWM2_2BIT_MASK        <<  \
                                                                  Servo_TCPWM2_START_SHIFT))

/* MASK */
#define Servo_TCPWM2_1BIT_MASK                      ((uint32)0x01u)
#define Servo_TCPWM2_2BIT_MASK                      ((uint32)0x03u)
#define Servo_TCPWM2_3BIT_MASK                      ((uint32)0x07u)
#define Servo_TCPWM2_6BIT_MASK                      ((uint32)0x3Fu)
#define Servo_TCPWM2_8BIT_MASK                      ((uint32)0xFFu)
#define Servo_TCPWM2_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Servo_TCPWM2_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Servo_TCPWM2_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Servo_TCPWM2_QUAD_ENCODING_MODES     << Servo_TCPWM2_QUAD_MODE_SHIFT))       |\
         ((uint32)(Servo_TCPWM2_CONFIG                  << Servo_TCPWM2_MODE_SHIFT)))

#define Servo_TCPWM2_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Servo_TCPWM2_PWM_STOP_EVENT          << Servo_TCPWM2_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Servo_TCPWM2_PWM_OUT_INVERT          << Servo_TCPWM2_INV_OUT_SHIFT))         |\
         ((uint32)(Servo_TCPWM2_PWM_OUT_N_INVERT        << Servo_TCPWM2_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Servo_TCPWM2_PWM_MODE                << Servo_TCPWM2_MODE_SHIFT)))

#define Servo_TCPWM2_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Servo_TCPWM2_PWM_RUN_MODE         << Servo_TCPWM2_ONESHOT_SHIFT))
            
#define Servo_TCPWM2_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Servo_TCPWM2_PWM_ALIGN            << Servo_TCPWM2_UPDOWN_SHIFT))

#define Servo_TCPWM2_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Servo_TCPWM2_PWM_KILL_EVENT      << Servo_TCPWM2_PWM_SYNC_KILL_SHIFT))

#define Servo_TCPWM2_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Servo_TCPWM2_PWM_DEAD_TIME_CYCLE  << Servo_TCPWM2_PRESCALER_SHIFT))

#define Servo_TCPWM2_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Servo_TCPWM2_PWM_PRESCALER        << Servo_TCPWM2_PRESCALER_SHIFT))

#define Servo_TCPWM2_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Servo_TCPWM2_TC_PRESCALER            << Servo_TCPWM2_PRESCALER_SHIFT))       |\
         ((uint32)(Servo_TCPWM2_TC_COUNTER_MODE         << Servo_TCPWM2_UPDOWN_SHIFT))          |\
         ((uint32)(Servo_TCPWM2_TC_RUN_MODE             << Servo_TCPWM2_ONESHOT_SHIFT))         |\
         ((uint32)(Servo_TCPWM2_TC_COMP_CAP_MODE        << Servo_TCPWM2_MODE_SHIFT)))
        
#define Servo_TCPWM2_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Servo_TCPWM2_QUAD_PHIA_SIGNAL_MODE   << Servo_TCPWM2_COUNT_SHIFT))           |\
         ((uint32)(Servo_TCPWM2_QUAD_INDEX_SIGNAL_MODE  << Servo_TCPWM2_RELOAD_SHIFT))          |\
         ((uint32)(Servo_TCPWM2_QUAD_STOP_SIGNAL_MODE   << Servo_TCPWM2_STOP_SHIFT))            |\
         ((uint32)(Servo_TCPWM2_QUAD_PHIB_SIGNAL_MODE   << Servo_TCPWM2_START_SHIFT)))

#define Servo_TCPWM2_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Servo_TCPWM2_PWM_SWITCH_SIGNAL_MODE  << Servo_TCPWM2_CAPTURE_SHIFT))         |\
         ((uint32)(Servo_TCPWM2_PWM_COUNT_SIGNAL_MODE   << Servo_TCPWM2_COUNT_SHIFT))           |\
         ((uint32)(Servo_TCPWM2_PWM_RELOAD_SIGNAL_MODE  << Servo_TCPWM2_RELOAD_SHIFT))          |\
         ((uint32)(Servo_TCPWM2_PWM_STOP_SIGNAL_MODE    << Servo_TCPWM2_STOP_SHIFT))            |\
         ((uint32)(Servo_TCPWM2_PWM_START_SIGNAL_MODE   << Servo_TCPWM2_START_SHIFT)))

#define Servo_TCPWM2_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Servo_TCPWM2_TC_CAPTURE_SIGNAL_MODE  << Servo_TCPWM2_CAPTURE_SHIFT))         |\
         ((uint32)(Servo_TCPWM2_TC_COUNT_SIGNAL_MODE    << Servo_TCPWM2_COUNT_SHIFT))           |\
         ((uint32)(Servo_TCPWM2_TC_RELOAD_SIGNAL_MODE   << Servo_TCPWM2_RELOAD_SHIFT))          |\
         ((uint32)(Servo_TCPWM2_TC_STOP_SIGNAL_MODE     << Servo_TCPWM2_STOP_SHIFT))            |\
         ((uint32)(Servo_TCPWM2_TC_START_SIGNAL_MODE    << Servo_TCPWM2_START_SHIFT)))
        
#define Servo_TCPWM2_TIMER_UPDOWN_CNT_USED                                                          \
                ((Servo_TCPWM2__COUNT_UPDOWN0 == Servo_TCPWM2_TC_COUNTER_MODE)                  ||\
                 (Servo_TCPWM2__COUNT_UPDOWN1 == Servo_TCPWM2_TC_COUNTER_MODE))

#define Servo_TCPWM2_PWM_UPDOWN_CNT_USED                                                            \
                ((Servo_TCPWM2__CENTER == Servo_TCPWM2_PWM_ALIGN)                               ||\
                 (Servo_TCPWM2__ASYMMETRIC == Servo_TCPWM2_PWM_ALIGN))               
        
#define Servo_TCPWM2_PWM_PR_INIT_VALUE              (1u)
#define Servo_TCPWM2_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Servo_TCPWM2_H */

/* [] END OF FILE */
