/*******************************************************************************
* File Name: BLE_Call.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the BLE_Call
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

#if !defined(CY_TCPWM_BLE_Call_H)
#define CY_TCPWM_BLE_Call_H


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
} BLE_Call_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  BLE_Call_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define BLE_Call_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define BLE_Call_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define BLE_Call_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define BLE_Call_QUAD_ENCODING_MODES            (0lu)
#define BLE_Call_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define BLE_Call_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define BLE_Call_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define BLE_Call_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define BLE_Call_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define BLE_Call_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define BLE_Call_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define BLE_Call_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define BLE_Call_TC_RUN_MODE                    (0lu)
#define BLE_Call_TC_COUNTER_MODE                (0lu)
#define BLE_Call_TC_COMP_CAP_MODE               (2lu)
#define BLE_Call_TC_PRESCALER                   (0lu)

/* Signal modes */
#define BLE_Call_TC_RELOAD_SIGNAL_MODE          (0lu)
#define BLE_Call_TC_COUNT_SIGNAL_MODE           (3lu)
#define BLE_Call_TC_START_SIGNAL_MODE           (0lu)
#define BLE_Call_TC_STOP_SIGNAL_MODE            (0lu)
#define BLE_Call_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define BLE_Call_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define BLE_Call_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define BLE_Call_TC_START_SIGNAL_PRESENT        (0lu)
#define BLE_Call_TC_STOP_SIGNAL_PRESENT         (0lu)
#define BLE_Call_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define BLE_Call_TC_INTERRUPT_MASK              (0lu)

/* PWM Mode */
/* Parameters */
#define BLE_Call_PWM_KILL_EVENT                 (0lu)
#define BLE_Call_PWM_STOP_EVENT                 (0lu)
#define BLE_Call_PWM_MODE                       (4lu)
#define BLE_Call_PWM_OUT_N_INVERT               (0lu)
#define BLE_Call_PWM_OUT_INVERT                 (0lu)
#define BLE_Call_PWM_ALIGN                      (0lu)
#define BLE_Call_PWM_RUN_MODE                   (0lu)
#define BLE_Call_PWM_DEAD_TIME_CYCLE            (0lu)
#define BLE_Call_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define BLE_Call_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define BLE_Call_PWM_COUNT_SIGNAL_MODE          (3lu)
#define BLE_Call_PWM_START_SIGNAL_MODE          (0lu)
#define BLE_Call_PWM_STOP_SIGNAL_MODE           (0lu)
#define BLE_Call_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define BLE_Call_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define BLE_Call_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define BLE_Call_PWM_START_SIGNAL_PRESENT       (0lu)
#define BLE_Call_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define BLE_Call_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define BLE_Call_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define BLE_Call_TC_PERIOD_VALUE                (120lu)
#define BLE_Call_TC_COMPARE_VALUE               (65535lu)
#define BLE_Call_TC_COMPARE_BUF_VALUE           (65535lu)
#define BLE_Call_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define BLE_Call_PWM_PERIOD_VALUE               (65535lu)
#define BLE_Call_PWM_PERIOD_BUF_VALUE           (65535lu)
#define BLE_Call_PWM_PERIOD_SWAP                (0lu)
#define BLE_Call_PWM_COMPARE_VALUE              (65535lu)
#define BLE_Call_PWM_COMPARE_BUF_VALUE          (65535lu)
#define BLE_Call_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define BLE_Call__LEFT 0
#define BLE_Call__RIGHT 1
#define BLE_Call__CENTER 2
#define BLE_Call__ASYMMETRIC 3

#define BLE_Call__X1 0
#define BLE_Call__X2 1
#define BLE_Call__X4 2

#define BLE_Call__PWM 4
#define BLE_Call__PWM_DT 5
#define BLE_Call__PWM_PR 6

#define BLE_Call__INVERSE 1
#define BLE_Call__DIRECT 0

#define BLE_Call__CAPTURE 2
#define BLE_Call__COMPARE 0

#define BLE_Call__TRIG_LEVEL 3
#define BLE_Call__TRIG_RISING 0
#define BLE_Call__TRIG_FALLING 1
#define BLE_Call__TRIG_BOTH 2

#define BLE_Call__INTR_MASK_TC 1
#define BLE_Call__INTR_MASK_CC_MATCH 2
#define BLE_Call__INTR_MASK_NONE 0
#define BLE_Call__INTR_MASK_TC_CC 3

#define BLE_Call__UNCONFIG 8
#define BLE_Call__TIMER 1
#define BLE_Call__QUAD 3
#define BLE_Call__PWM_SEL 7

#define BLE_Call__COUNT_UP 0
#define BLE_Call__COUNT_DOWN 1
#define BLE_Call__COUNT_UPDOWN0 2
#define BLE_Call__COUNT_UPDOWN1 3


/* Prescaler */
#define BLE_Call_PRESCALE_DIVBY1                ((uint32)(0u << BLE_Call_PRESCALER_SHIFT))
#define BLE_Call_PRESCALE_DIVBY2                ((uint32)(1u << BLE_Call_PRESCALER_SHIFT))
#define BLE_Call_PRESCALE_DIVBY4                ((uint32)(2u << BLE_Call_PRESCALER_SHIFT))
#define BLE_Call_PRESCALE_DIVBY8                ((uint32)(3u << BLE_Call_PRESCALER_SHIFT))
#define BLE_Call_PRESCALE_DIVBY16               ((uint32)(4u << BLE_Call_PRESCALER_SHIFT))
#define BLE_Call_PRESCALE_DIVBY32               ((uint32)(5u << BLE_Call_PRESCALER_SHIFT))
#define BLE_Call_PRESCALE_DIVBY64               ((uint32)(6u << BLE_Call_PRESCALER_SHIFT))
#define BLE_Call_PRESCALE_DIVBY128              ((uint32)(7u << BLE_Call_PRESCALER_SHIFT))

/* TCPWM set modes */
#define BLE_Call_MODE_TIMER_COMPARE             ((uint32)(BLE_Call__COMPARE         <<  \
                                                                  BLE_Call_MODE_SHIFT))
#define BLE_Call_MODE_TIMER_CAPTURE             ((uint32)(BLE_Call__CAPTURE         <<  \
                                                                  BLE_Call_MODE_SHIFT))
#define BLE_Call_MODE_QUAD                      ((uint32)(BLE_Call__QUAD            <<  \
                                                                  BLE_Call_MODE_SHIFT))
#define BLE_Call_MODE_PWM                       ((uint32)(BLE_Call__PWM             <<  \
                                                                  BLE_Call_MODE_SHIFT))
#define BLE_Call_MODE_PWM_DT                    ((uint32)(BLE_Call__PWM_DT          <<  \
                                                                  BLE_Call_MODE_SHIFT))
#define BLE_Call_MODE_PWM_PR                    ((uint32)(BLE_Call__PWM_PR          <<  \
                                                                  BLE_Call_MODE_SHIFT))

/* Quad Modes */
#define BLE_Call_MODE_X1                        ((uint32)(BLE_Call__X1              <<  \
                                                                  BLE_Call_QUAD_MODE_SHIFT))
#define BLE_Call_MODE_X2                        ((uint32)(BLE_Call__X2              <<  \
                                                                  BLE_Call_QUAD_MODE_SHIFT))
#define BLE_Call_MODE_X4                        ((uint32)(BLE_Call__X4              <<  \
                                                                  BLE_Call_QUAD_MODE_SHIFT))

/* Counter modes */
#define BLE_Call_COUNT_UP                       ((uint32)(BLE_Call__COUNT_UP        <<  \
                                                                  BLE_Call_UPDOWN_SHIFT))
#define BLE_Call_COUNT_DOWN                     ((uint32)(BLE_Call__COUNT_DOWN      <<  \
                                                                  BLE_Call_UPDOWN_SHIFT))
#define BLE_Call_COUNT_UPDOWN0                  ((uint32)(BLE_Call__COUNT_UPDOWN0   <<  \
                                                                  BLE_Call_UPDOWN_SHIFT))
#define BLE_Call_COUNT_UPDOWN1                  ((uint32)(BLE_Call__COUNT_UPDOWN1   <<  \
                                                                  BLE_Call_UPDOWN_SHIFT))

/* PWM output invert */
#define BLE_Call_INVERT_LINE                    ((uint32)(BLE_Call__INVERSE         <<  \
                                                                  BLE_Call_INV_OUT_SHIFT))
#define BLE_Call_INVERT_LINE_N                  ((uint32)(BLE_Call__INVERSE         <<  \
                                                                  BLE_Call_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define BLE_Call_TRIG_RISING                    ((uint32)BLE_Call__TRIG_RISING)
#define BLE_Call_TRIG_FALLING                   ((uint32)BLE_Call__TRIG_FALLING)
#define BLE_Call_TRIG_BOTH                      ((uint32)BLE_Call__TRIG_BOTH)
#define BLE_Call_TRIG_LEVEL                     ((uint32)BLE_Call__TRIG_LEVEL)

/* Interrupt mask */
#define BLE_Call_INTR_MASK_TC                   ((uint32)BLE_Call__INTR_MASK_TC)
#define BLE_Call_INTR_MASK_CC_MATCH             ((uint32)BLE_Call__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define BLE_Call_CC_MATCH_SET                   (0x00u)
#define BLE_Call_CC_MATCH_CLEAR                 (0x01u)
#define BLE_Call_CC_MATCH_INVERT                (0x02u)
#define BLE_Call_CC_MATCH_NO_CHANGE             (0x03u)
#define BLE_Call_OVERLOW_SET                    (0x00u)
#define BLE_Call_OVERLOW_CLEAR                  (0x04u)
#define BLE_Call_OVERLOW_INVERT                 (0x08u)
#define BLE_Call_OVERLOW_NO_CHANGE              (0x0Cu)
#define BLE_Call_UNDERFLOW_SET                  (0x00u)
#define BLE_Call_UNDERFLOW_CLEAR                (0x10u)
#define BLE_Call_UNDERFLOW_INVERT               (0x20u)
#define BLE_Call_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define BLE_Call_PWM_MODE_LEFT                  (BLE_Call_CC_MATCH_CLEAR        |   \
                                                         BLE_Call_OVERLOW_SET           |   \
                                                         BLE_Call_UNDERFLOW_NO_CHANGE)
#define BLE_Call_PWM_MODE_RIGHT                 (BLE_Call_CC_MATCH_SET          |   \
                                                         BLE_Call_OVERLOW_NO_CHANGE     |   \
                                                         BLE_Call_UNDERFLOW_CLEAR)
#define BLE_Call_PWM_MODE_ASYM                  (BLE_Call_CC_MATCH_INVERT       |   \
                                                         BLE_Call_OVERLOW_SET           |   \
                                                         BLE_Call_UNDERFLOW_CLEAR)

#if (BLE_Call_CY_TCPWM_V2)
    #if(BLE_Call_CY_TCPWM_4000)
        #define BLE_Call_PWM_MODE_CENTER                (BLE_Call_CC_MATCH_INVERT       |   \
                                                                 BLE_Call_OVERLOW_NO_CHANGE     |   \
                                                                 BLE_Call_UNDERFLOW_CLEAR)
    #else
        #define BLE_Call_PWM_MODE_CENTER                (BLE_Call_CC_MATCH_INVERT       |   \
                                                                 BLE_Call_OVERLOW_SET           |   \
                                                                 BLE_Call_UNDERFLOW_CLEAR)
    #endif /* (BLE_Call_CY_TCPWM_4000) */
#else
    #define BLE_Call_PWM_MODE_CENTER                (BLE_Call_CC_MATCH_INVERT       |   \
                                                             BLE_Call_OVERLOW_NO_CHANGE     |   \
                                                             BLE_Call_UNDERFLOW_CLEAR)
#endif /* (BLE_Call_CY_TCPWM_NEW) */

/* Command operations without condition */
#define BLE_Call_CMD_CAPTURE                    (0u)
#define BLE_Call_CMD_RELOAD                     (8u)
#define BLE_Call_CMD_STOP                       (16u)
#define BLE_Call_CMD_START                      (24u)

/* Status */
#define BLE_Call_STATUS_DOWN                    (1u)
#define BLE_Call_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   BLE_Call_Init(void);
void   BLE_Call_Enable(void);
void   BLE_Call_Start(void);
void   BLE_Call_Stop(void);

void   BLE_Call_SetMode(uint32 mode);
void   BLE_Call_SetCounterMode(uint32 counterMode);
void   BLE_Call_SetPWMMode(uint32 modeMask);
void   BLE_Call_SetQDMode(uint32 qdMode);

void   BLE_Call_SetPrescaler(uint32 prescaler);
void   BLE_Call_TriggerCommand(uint32 mask, uint32 command);
void   BLE_Call_SetOneShot(uint32 oneShotEnable);
uint32 BLE_Call_ReadStatus(void);

void   BLE_Call_SetPWMSyncKill(uint32 syncKillEnable);
void   BLE_Call_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   BLE_Call_SetPWMDeadTime(uint32 deadTime);
void   BLE_Call_SetPWMInvert(uint32 mask);

void   BLE_Call_SetInterruptMode(uint32 interruptMask);
uint32 BLE_Call_GetInterruptSourceMasked(void);
uint32 BLE_Call_GetInterruptSource(void);
void   BLE_Call_ClearInterrupt(uint32 interruptMask);
void   BLE_Call_SetInterrupt(uint32 interruptMask);

void   BLE_Call_WriteCounter(uint32 count);
uint32 BLE_Call_ReadCounter(void);

uint32 BLE_Call_ReadCapture(void);
uint32 BLE_Call_ReadCaptureBuf(void);

void   BLE_Call_WritePeriod(uint32 period);
uint32 BLE_Call_ReadPeriod(void);
void   BLE_Call_WritePeriodBuf(uint32 periodBuf);
uint32 BLE_Call_ReadPeriodBuf(void);

void   BLE_Call_WriteCompare(uint32 compare);
uint32 BLE_Call_ReadCompare(void);
void   BLE_Call_WriteCompareBuf(uint32 compareBuf);
uint32 BLE_Call_ReadCompareBuf(void);

void   BLE_Call_SetPeriodSwap(uint32 swapEnable);
void   BLE_Call_SetCompareSwap(uint32 swapEnable);

void   BLE_Call_SetCaptureMode(uint32 triggerMode);
void   BLE_Call_SetReloadMode(uint32 triggerMode);
void   BLE_Call_SetStartMode(uint32 triggerMode);
void   BLE_Call_SetStopMode(uint32 triggerMode);
void   BLE_Call_SetCountMode(uint32 triggerMode);

void   BLE_Call_SaveConfig(void);
void   BLE_Call_RestoreConfig(void);
void   BLE_Call_Sleep(void);
void   BLE_Call_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define BLE_Call_BLOCK_CONTROL_REG              (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define BLE_Call_BLOCK_CONTROL_PTR              ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define BLE_Call_COMMAND_REG                    (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define BLE_Call_COMMAND_PTR                    ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define BLE_Call_INTRRUPT_CAUSE_REG             (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define BLE_Call_INTRRUPT_CAUSE_PTR             ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define BLE_Call_CONTROL_REG                    (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__CTRL )
#define BLE_Call_CONTROL_PTR                    ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__CTRL )
#define BLE_Call_STATUS_REG                     (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__STATUS )
#define BLE_Call_STATUS_PTR                     ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__STATUS )
#define BLE_Call_COUNTER_REG                    (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__COUNTER )
#define BLE_Call_COUNTER_PTR                    ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__COUNTER )
#define BLE_Call_COMP_CAP_REG                   (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__CC )
#define BLE_Call_COMP_CAP_PTR                   ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__CC )
#define BLE_Call_COMP_CAP_BUF_REG               (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__CC_BUFF )
#define BLE_Call_COMP_CAP_BUF_PTR               ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__CC_BUFF )
#define BLE_Call_PERIOD_REG                     (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__PERIOD )
#define BLE_Call_PERIOD_PTR                     ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__PERIOD )
#define BLE_Call_PERIOD_BUF_REG                 (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define BLE_Call_PERIOD_BUF_PTR                 ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define BLE_Call_TRIG_CONTROL0_REG              (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define BLE_Call_TRIG_CONTROL0_PTR              ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define BLE_Call_TRIG_CONTROL1_REG              (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define BLE_Call_TRIG_CONTROL1_PTR              ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define BLE_Call_TRIG_CONTROL2_REG              (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define BLE_Call_TRIG_CONTROL2_PTR              ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define BLE_Call_INTERRUPT_REQ_REG              (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__INTR )
#define BLE_Call_INTERRUPT_REQ_PTR              ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__INTR )
#define BLE_Call_INTERRUPT_SET_REG              (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__INTR_SET )
#define BLE_Call_INTERRUPT_SET_PTR              ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__INTR_SET )
#define BLE_Call_INTERRUPT_MASK_REG             (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__INTR_MASK )
#define BLE_Call_INTERRUPT_MASK_PTR             ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__INTR_MASK )
#define BLE_Call_INTERRUPT_MASKED_REG           (*(reg32 *) BLE_Call_cy_m0s8_tcpwm_1__INTR_MASKED )
#define BLE_Call_INTERRUPT_MASKED_PTR           ( (reg32 *) BLE_Call_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define BLE_Call_MASK                           ((uint32)BLE_Call_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define BLE_Call_RELOAD_CC_SHIFT                (0u)
#define BLE_Call_RELOAD_PERIOD_SHIFT            (1u)
#define BLE_Call_PWM_SYNC_KILL_SHIFT            (2u)
#define BLE_Call_PWM_STOP_KILL_SHIFT            (3u)
#define BLE_Call_PRESCALER_SHIFT                (8u)
#define BLE_Call_UPDOWN_SHIFT                   (16u)
#define BLE_Call_ONESHOT_SHIFT                  (18u)
#define BLE_Call_QUAD_MODE_SHIFT                (20u)
#define BLE_Call_INV_OUT_SHIFT                  (20u)
#define BLE_Call_INV_COMPL_OUT_SHIFT            (21u)
#define BLE_Call_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define BLE_Call_RELOAD_CC_MASK                 ((uint32)(BLE_Call_1BIT_MASK        <<  \
                                                                            BLE_Call_RELOAD_CC_SHIFT))
#define BLE_Call_RELOAD_PERIOD_MASK             ((uint32)(BLE_Call_1BIT_MASK        <<  \
                                                                            BLE_Call_RELOAD_PERIOD_SHIFT))
#define BLE_Call_PWM_SYNC_KILL_MASK             ((uint32)(BLE_Call_1BIT_MASK        <<  \
                                                                            BLE_Call_PWM_SYNC_KILL_SHIFT))
#define BLE_Call_PWM_STOP_KILL_MASK             ((uint32)(BLE_Call_1BIT_MASK        <<  \
                                                                            BLE_Call_PWM_STOP_KILL_SHIFT))
#define BLE_Call_PRESCALER_MASK                 ((uint32)(BLE_Call_8BIT_MASK        <<  \
                                                                            BLE_Call_PRESCALER_SHIFT))
#define BLE_Call_UPDOWN_MASK                    ((uint32)(BLE_Call_2BIT_MASK        <<  \
                                                                            BLE_Call_UPDOWN_SHIFT))
#define BLE_Call_ONESHOT_MASK                   ((uint32)(BLE_Call_1BIT_MASK        <<  \
                                                                            BLE_Call_ONESHOT_SHIFT))
#define BLE_Call_QUAD_MODE_MASK                 ((uint32)(BLE_Call_3BIT_MASK        <<  \
                                                                            BLE_Call_QUAD_MODE_SHIFT))
#define BLE_Call_INV_OUT_MASK                   ((uint32)(BLE_Call_2BIT_MASK        <<  \
                                                                            BLE_Call_INV_OUT_SHIFT))
#define BLE_Call_MODE_MASK                      ((uint32)(BLE_Call_3BIT_MASK        <<  \
                                                                            BLE_Call_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define BLE_Call_CAPTURE_SHIFT                  (0u)
#define BLE_Call_COUNT_SHIFT                    (2u)
#define BLE_Call_RELOAD_SHIFT                   (4u)
#define BLE_Call_STOP_SHIFT                     (6u)
#define BLE_Call_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define BLE_Call_CAPTURE_MASK                   ((uint32)(BLE_Call_2BIT_MASK        <<  \
                                                                  BLE_Call_CAPTURE_SHIFT))
#define BLE_Call_COUNT_MASK                     ((uint32)(BLE_Call_2BIT_MASK        <<  \
                                                                  BLE_Call_COUNT_SHIFT))
#define BLE_Call_RELOAD_MASK                    ((uint32)(BLE_Call_2BIT_MASK        <<  \
                                                                  BLE_Call_RELOAD_SHIFT))
#define BLE_Call_STOP_MASK                      ((uint32)(BLE_Call_2BIT_MASK        <<  \
                                                                  BLE_Call_STOP_SHIFT))
#define BLE_Call_START_MASK                     ((uint32)(BLE_Call_2BIT_MASK        <<  \
                                                                  BLE_Call_START_SHIFT))

/* MASK */
#define BLE_Call_1BIT_MASK                      ((uint32)0x01u)
#define BLE_Call_2BIT_MASK                      ((uint32)0x03u)
#define BLE_Call_3BIT_MASK                      ((uint32)0x07u)
#define BLE_Call_6BIT_MASK                      ((uint32)0x3Fu)
#define BLE_Call_8BIT_MASK                      ((uint32)0xFFu)
#define BLE_Call_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define BLE_Call_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define BLE_Call_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(BLE_Call_QUAD_ENCODING_MODES     << BLE_Call_QUAD_MODE_SHIFT))       |\
         ((uint32)(BLE_Call_CONFIG                  << BLE_Call_MODE_SHIFT)))

#define BLE_Call_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(BLE_Call_PWM_STOP_EVENT          << BLE_Call_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(BLE_Call_PWM_OUT_INVERT          << BLE_Call_INV_OUT_SHIFT))         |\
         ((uint32)(BLE_Call_PWM_OUT_N_INVERT        << BLE_Call_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(BLE_Call_PWM_MODE                << BLE_Call_MODE_SHIFT)))

#define BLE_Call_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(BLE_Call_PWM_RUN_MODE         << BLE_Call_ONESHOT_SHIFT))
            
#define BLE_Call_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(BLE_Call_PWM_ALIGN            << BLE_Call_UPDOWN_SHIFT))

#define BLE_Call_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(BLE_Call_PWM_KILL_EVENT      << BLE_Call_PWM_SYNC_KILL_SHIFT))

#define BLE_Call_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(BLE_Call_PWM_DEAD_TIME_CYCLE  << BLE_Call_PRESCALER_SHIFT))

#define BLE_Call_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(BLE_Call_PWM_PRESCALER        << BLE_Call_PRESCALER_SHIFT))

#define BLE_Call_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(BLE_Call_TC_PRESCALER            << BLE_Call_PRESCALER_SHIFT))       |\
         ((uint32)(BLE_Call_TC_COUNTER_MODE         << BLE_Call_UPDOWN_SHIFT))          |\
         ((uint32)(BLE_Call_TC_RUN_MODE             << BLE_Call_ONESHOT_SHIFT))         |\
         ((uint32)(BLE_Call_TC_COMP_CAP_MODE        << BLE_Call_MODE_SHIFT)))
        
#define BLE_Call_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(BLE_Call_QUAD_PHIA_SIGNAL_MODE   << BLE_Call_COUNT_SHIFT))           |\
         ((uint32)(BLE_Call_QUAD_INDEX_SIGNAL_MODE  << BLE_Call_RELOAD_SHIFT))          |\
         ((uint32)(BLE_Call_QUAD_STOP_SIGNAL_MODE   << BLE_Call_STOP_SHIFT))            |\
         ((uint32)(BLE_Call_QUAD_PHIB_SIGNAL_MODE   << BLE_Call_START_SHIFT)))

#define BLE_Call_PWM_SIGNALS_MODES                                                              \
        (((uint32)(BLE_Call_PWM_SWITCH_SIGNAL_MODE  << BLE_Call_CAPTURE_SHIFT))         |\
         ((uint32)(BLE_Call_PWM_COUNT_SIGNAL_MODE   << BLE_Call_COUNT_SHIFT))           |\
         ((uint32)(BLE_Call_PWM_RELOAD_SIGNAL_MODE  << BLE_Call_RELOAD_SHIFT))          |\
         ((uint32)(BLE_Call_PWM_STOP_SIGNAL_MODE    << BLE_Call_STOP_SHIFT))            |\
         ((uint32)(BLE_Call_PWM_START_SIGNAL_MODE   << BLE_Call_START_SHIFT)))

#define BLE_Call_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(BLE_Call_TC_CAPTURE_SIGNAL_MODE  << BLE_Call_CAPTURE_SHIFT))         |\
         ((uint32)(BLE_Call_TC_COUNT_SIGNAL_MODE    << BLE_Call_COUNT_SHIFT))           |\
         ((uint32)(BLE_Call_TC_RELOAD_SIGNAL_MODE   << BLE_Call_RELOAD_SHIFT))          |\
         ((uint32)(BLE_Call_TC_STOP_SIGNAL_MODE     << BLE_Call_STOP_SHIFT))            |\
         ((uint32)(BLE_Call_TC_START_SIGNAL_MODE    << BLE_Call_START_SHIFT)))
        
#define BLE_Call_TIMER_UPDOWN_CNT_USED                                                          \
                ((BLE_Call__COUNT_UPDOWN0 == BLE_Call_TC_COUNTER_MODE)                  ||\
                 (BLE_Call__COUNT_UPDOWN1 == BLE_Call_TC_COUNTER_MODE))

#define BLE_Call_PWM_UPDOWN_CNT_USED                                                            \
                ((BLE_Call__CENTER == BLE_Call_PWM_ALIGN)                               ||\
                 (BLE_Call__ASYMMETRIC == BLE_Call_PWM_ALIGN))               
        
#define BLE_Call_PWM_PR_INIT_VALUE              (1u)
#define BLE_Call_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_BLE_Call_H */

/* [] END OF FILE */
