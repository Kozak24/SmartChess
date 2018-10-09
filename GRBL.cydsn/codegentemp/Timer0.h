/*******************************************************************************
* File Name: Timer0.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the Timer0
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

#if !defined(CY_TCPWM_Timer0_H)
#define CY_TCPWM_Timer0_H


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
} Timer0_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Timer0_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Timer0_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Timer0_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Timer0_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define Timer0_QUAD_ENCODING_MODES            (0lu)
#define Timer0_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define Timer0_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Timer0_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Timer0_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Timer0_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Timer0_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Timer0_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Timer0_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Timer0_TC_RUN_MODE                    (0lu)
#define Timer0_TC_COUNTER_MODE                (0lu)
#define Timer0_TC_COMP_CAP_MODE               (0lu)
#define Timer0_TC_PRESCALER                   (3lu)

/* Signal modes */
#define Timer0_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Timer0_TC_COUNT_SIGNAL_MODE           (3lu)
#define Timer0_TC_START_SIGNAL_MODE           (0lu)
#define Timer0_TC_STOP_SIGNAL_MODE            (0lu)
#define Timer0_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Timer0_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Timer0_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Timer0_TC_START_SIGNAL_PRESENT        (0lu)
#define Timer0_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Timer0_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Timer0_TC_INTERRUPT_MASK              (2lu)

/* PWM Mode */
/* Parameters */
#define Timer0_PWM_KILL_EVENT                 (0lu)
#define Timer0_PWM_STOP_EVENT                 (0lu)
#define Timer0_PWM_MODE                       (4lu)
#define Timer0_PWM_OUT_N_INVERT               (0lu)
#define Timer0_PWM_OUT_INVERT                 (0lu)
#define Timer0_PWM_ALIGN                      (0lu)
#define Timer0_PWM_RUN_MODE                   (0lu)
#define Timer0_PWM_DEAD_TIME_CYCLE            (0lu)
#define Timer0_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Timer0_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Timer0_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Timer0_PWM_START_SIGNAL_MODE          (0lu)
#define Timer0_PWM_STOP_SIGNAL_MODE           (0lu)
#define Timer0_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Timer0_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Timer0_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Timer0_PWM_START_SIGNAL_PRESENT       (0lu)
#define Timer0_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Timer0_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Timer0_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Timer0_TC_PERIOD_VALUE                (255lu)
#define Timer0_TC_COMPARE_VALUE               (255lu)
#define Timer0_TC_COMPARE_BUF_VALUE           (255lu)
#define Timer0_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Timer0_PWM_PERIOD_VALUE               (65535lu)
#define Timer0_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Timer0_PWM_PERIOD_SWAP                (0lu)
#define Timer0_PWM_COMPARE_VALUE              (65535lu)
#define Timer0_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Timer0_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Timer0__LEFT 0
#define Timer0__RIGHT 1
#define Timer0__CENTER 2
#define Timer0__ASYMMETRIC 3

#define Timer0__X1 0
#define Timer0__X2 1
#define Timer0__X4 2

#define Timer0__PWM 4
#define Timer0__PWM_DT 5
#define Timer0__PWM_PR 6

#define Timer0__INVERSE 1
#define Timer0__DIRECT 0

#define Timer0__CAPTURE 2
#define Timer0__COMPARE 0

#define Timer0__TRIG_LEVEL 3
#define Timer0__TRIG_RISING 0
#define Timer0__TRIG_FALLING 1
#define Timer0__TRIG_BOTH 2

#define Timer0__INTR_MASK_TC 1
#define Timer0__INTR_MASK_CC_MATCH 2
#define Timer0__INTR_MASK_NONE 0
#define Timer0__INTR_MASK_TC_CC 3

#define Timer0__UNCONFIG 8
#define Timer0__TIMER 1
#define Timer0__QUAD 3
#define Timer0__PWM_SEL 7

#define Timer0__COUNT_UP 0
#define Timer0__COUNT_DOWN 1
#define Timer0__COUNT_UPDOWN0 2
#define Timer0__COUNT_UPDOWN1 3


/* Prescaler */
#define Timer0_PRESCALE_DIVBY1                ((uint32)(0u << Timer0_PRESCALER_SHIFT))
#define Timer0_PRESCALE_DIVBY2                ((uint32)(1u << Timer0_PRESCALER_SHIFT))
#define Timer0_PRESCALE_DIVBY4                ((uint32)(2u << Timer0_PRESCALER_SHIFT))
#define Timer0_PRESCALE_DIVBY8                ((uint32)(3u << Timer0_PRESCALER_SHIFT))
#define Timer0_PRESCALE_DIVBY16               ((uint32)(4u << Timer0_PRESCALER_SHIFT))
#define Timer0_PRESCALE_DIVBY32               ((uint32)(5u << Timer0_PRESCALER_SHIFT))
#define Timer0_PRESCALE_DIVBY64               ((uint32)(6u << Timer0_PRESCALER_SHIFT))
#define Timer0_PRESCALE_DIVBY128              ((uint32)(7u << Timer0_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Timer0_MODE_TIMER_COMPARE             ((uint32)(Timer0__COMPARE         <<  \
                                                                  Timer0_MODE_SHIFT))
#define Timer0_MODE_TIMER_CAPTURE             ((uint32)(Timer0__CAPTURE         <<  \
                                                                  Timer0_MODE_SHIFT))
#define Timer0_MODE_QUAD                      ((uint32)(Timer0__QUAD            <<  \
                                                                  Timer0_MODE_SHIFT))
#define Timer0_MODE_PWM                       ((uint32)(Timer0__PWM             <<  \
                                                                  Timer0_MODE_SHIFT))
#define Timer0_MODE_PWM_DT                    ((uint32)(Timer0__PWM_DT          <<  \
                                                                  Timer0_MODE_SHIFT))
#define Timer0_MODE_PWM_PR                    ((uint32)(Timer0__PWM_PR          <<  \
                                                                  Timer0_MODE_SHIFT))

/* Quad Modes */
#define Timer0_MODE_X1                        ((uint32)(Timer0__X1              <<  \
                                                                  Timer0_QUAD_MODE_SHIFT))
#define Timer0_MODE_X2                        ((uint32)(Timer0__X2              <<  \
                                                                  Timer0_QUAD_MODE_SHIFT))
#define Timer0_MODE_X4                        ((uint32)(Timer0__X4              <<  \
                                                                  Timer0_QUAD_MODE_SHIFT))

/* Counter modes */
#define Timer0_COUNT_UP                       ((uint32)(Timer0__COUNT_UP        <<  \
                                                                  Timer0_UPDOWN_SHIFT))
#define Timer0_COUNT_DOWN                     ((uint32)(Timer0__COUNT_DOWN      <<  \
                                                                  Timer0_UPDOWN_SHIFT))
#define Timer0_COUNT_UPDOWN0                  ((uint32)(Timer0__COUNT_UPDOWN0   <<  \
                                                                  Timer0_UPDOWN_SHIFT))
#define Timer0_COUNT_UPDOWN1                  ((uint32)(Timer0__COUNT_UPDOWN1   <<  \
                                                                  Timer0_UPDOWN_SHIFT))

/* PWM output invert */
#define Timer0_INVERT_LINE                    ((uint32)(Timer0__INVERSE         <<  \
                                                                  Timer0_INV_OUT_SHIFT))
#define Timer0_INVERT_LINE_N                  ((uint32)(Timer0__INVERSE         <<  \
                                                                  Timer0_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Timer0_TRIG_RISING                    ((uint32)Timer0__TRIG_RISING)
#define Timer0_TRIG_FALLING                   ((uint32)Timer0__TRIG_FALLING)
#define Timer0_TRIG_BOTH                      ((uint32)Timer0__TRIG_BOTH)
#define Timer0_TRIG_LEVEL                     ((uint32)Timer0__TRIG_LEVEL)

/* Interrupt mask */
#define Timer0_INTR_MASK_TC                   ((uint32)Timer0__INTR_MASK_TC)
#define Timer0_INTR_MASK_CC_MATCH             ((uint32)Timer0__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Timer0_CC_MATCH_SET                   (0x00u)
#define Timer0_CC_MATCH_CLEAR                 (0x01u)
#define Timer0_CC_MATCH_INVERT                (0x02u)
#define Timer0_CC_MATCH_NO_CHANGE             (0x03u)
#define Timer0_OVERLOW_SET                    (0x00u)
#define Timer0_OVERLOW_CLEAR                  (0x04u)
#define Timer0_OVERLOW_INVERT                 (0x08u)
#define Timer0_OVERLOW_NO_CHANGE              (0x0Cu)
#define Timer0_UNDERFLOW_SET                  (0x00u)
#define Timer0_UNDERFLOW_CLEAR                (0x10u)
#define Timer0_UNDERFLOW_INVERT               (0x20u)
#define Timer0_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Timer0_PWM_MODE_LEFT                  (Timer0_CC_MATCH_CLEAR        |   \
                                                         Timer0_OVERLOW_SET           |   \
                                                         Timer0_UNDERFLOW_NO_CHANGE)
#define Timer0_PWM_MODE_RIGHT                 (Timer0_CC_MATCH_SET          |   \
                                                         Timer0_OVERLOW_NO_CHANGE     |   \
                                                         Timer0_UNDERFLOW_CLEAR)
#define Timer0_PWM_MODE_ASYM                  (Timer0_CC_MATCH_INVERT       |   \
                                                         Timer0_OVERLOW_SET           |   \
                                                         Timer0_UNDERFLOW_CLEAR)

#if (Timer0_CY_TCPWM_V2)
    #if(Timer0_CY_TCPWM_4000)
        #define Timer0_PWM_MODE_CENTER                (Timer0_CC_MATCH_INVERT       |   \
                                                                 Timer0_OVERLOW_NO_CHANGE     |   \
                                                                 Timer0_UNDERFLOW_CLEAR)
    #else
        #define Timer0_PWM_MODE_CENTER                (Timer0_CC_MATCH_INVERT       |   \
                                                                 Timer0_OVERLOW_SET           |   \
                                                                 Timer0_UNDERFLOW_CLEAR)
    #endif /* (Timer0_CY_TCPWM_4000) */
#else
    #define Timer0_PWM_MODE_CENTER                (Timer0_CC_MATCH_INVERT       |   \
                                                             Timer0_OVERLOW_NO_CHANGE     |   \
                                                             Timer0_UNDERFLOW_CLEAR)
#endif /* (Timer0_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Timer0_CMD_CAPTURE                    (0u)
#define Timer0_CMD_RELOAD                     (8u)
#define Timer0_CMD_STOP                       (16u)
#define Timer0_CMD_START                      (24u)

/* Status */
#define Timer0_STATUS_DOWN                    (1u)
#define Timer0_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Timer0_Init(void);
void   Timer0_Enable(void);
void   Timer0_Start(void);
void   Timer0_Stop(void);

void   Timer0_SetMode(uint32 mode);
void   Timer0_SetCounterMode(uint32 counterMode);
void   Timer0_SetPWMMode(uint32 modeMask);
void   Timer0_SetQDMode(uint32 qdMode);

void   Timer0_SetPrescaler(uint32 prescaler);
void   Timer0_TriggerCommand(uint32 mask, uint32 command);
void   Timer0_SetOneShot(uint32 oneShotEnable);
uint32 Timer0_ReadStatus(void);

void   Timer0_SetPWMSyncKill(uint32 syncKillEnable);
void   Timer0_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Timer0_SetPWMDeadTime(uint32 deadTime);
void   Timer0_SetPWMInvert(uint32 mask);

void   Timer0_SetInterruptMode(uint32 interruptMask);
uint32 Timer0_GetInterruptSourceMasked(void);
uint32 Timer0_GetInterruptSource(void);
void   Timer0_ClearInterrupt(uint32 interruptMask);
void   Timer0_SetInterrupt(uint32 interruptMask);

void   Timer0_WriteCounter(uint32 count);
uint32 Timer0_ReadCounter(void);

uint32 Timer0_ReadCapture(void);
uint32 Timer0_ReadCaptureBuf(void);

void   Timer0_WritePeriod(uint32 period);
uint32 Timer0_ReadPeriod(void);
void   Timer0_WritePeriodBuf(uint32 periodBuf);
uint32 Timer0_ReadPeriodBuf(void);

void   Timer0_WriteCompare(uint32 compare);
uint32 Timer0_ReadCompare(void);
void   Timer0_WriteCompareBuf(uint32 compareBuf);
uint32 Timer0_ReadCompareBuf(void);

void   Timer0_SetPeriodSwap(uint32 swapEnable);
void   Timer0_SetCompareSwap(uint32 swapEnable);

void   Timer0_SetCaptureMode(uint32 triggerMode);
void   Timer0_SetReloadMode(uint32 triggerMode);
void   Timer0_SetStartMode(uint32 triggerMode);
void   Timer0_SetStopMode(uint32 triggerMode);
void   Timer0_SetCountMode(uint32 triggerMode);

void   Timer0_SaveConfig(void);
void   Timer0_RestoreConfig(void);
void   Timer0_Sleep(void);
void   Timer0_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Timer0_BLOCK_CONTROL_REG              (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Timer0_BLOCK_CONTROL_PTR              ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Timer0_COMMAND_REG                    (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Timer0_COMMAND_PTR                    ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Timer0_INTRRUPT_CAUSE_REG             (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Timer0_INTRRUPT_CAUSE_PTR             ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Timer0_CONTROL_REG                    (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__CTRL )
#define Timer0_CONTROL_PTR                    ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__CTRL )
#define Timer0_STATUS_REG                     (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__STATUS )
#define Timer0_STATUS_PTR                     ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__STATUS )
#define Timer0_COUNTER_REG                    (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__COUNTER )
#define Timer0_COUNTER_PTR                    ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__COUNTER )
#define Timer0_COMP_CAP_REG                   (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__CC )
#define Timer0_COMP_CAP_PTR                   ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__CC )
#define Timer0_COMP_CAP_BUF_REG               (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__CC_BUFF )
#define Timer0_COMP_CAP_BUF_PTR               ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__CC_BUFF )
#define Timer0_PERIOD_REG                     (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__PERIOD )
#define Timer0_PERIOD_PTR                     ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__PERIOD )
#define Timer0_PERIOD_BUF_REG                 (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Timer0_PERIOD_BUF_PTR                 ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Timer0_TRIG_CONTROL0_REG              (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Timer0_TRIG_CONTROL0_PTR              ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Timer0_TRIG_CONTROL1_REG              (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Timer0_TRIG_CONTROL1_PTR              ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Timer0_TRIG_CONTROL2_REG              (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Timer0_TRIG_CONTROL2_PTR              ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Timer0_INTERRUPT_REQ_REG              (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__INTR )
#define Timer0_INTERRUPT_REQ_PTR              ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__INTR )
#define Timer0_INTERRUPT_SET_REG              (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__INTR_SET )
#define Timer0_INTERRUPT_SET_PTR              ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__INTR_SET )
#define Timer0_INTERRUPT_MASK_REG             (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__INTR_MASK )
#define Timer0_INTERRUPT_MASK_PTR             ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__INTR_MASK )
#define Timer0_INTERRUPT_MASKED_REG           (*(reg32 *) Timer0_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Timer0_INTERRUPT_MASKED_PTR           ( (reg32 *) Timer0_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Timer0_MASK                           ((uint32)Timer0_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Timer0_RELOAD_CC_SHIFT                (0u)
#define Timer0_RELOAD_PERIOD_SHIFT            (1u)
#define Timer0_PWM_SYNC_KILL_SHIFT            (2u)
#define Timer0_PWM_STOP_KILL_SHIFT            (3u)
#define Timer0_PRESCALER_SHIFT                (8u)
#define Timer0_UPDOWN_SHIFT                   (16u)
#define Timer0_ONESHOT_SHIFT                  (18u)
#define Timer0_QUAD_MODE_SHIFT                (20u)
#define Timer0_INV_OUT_SHIFT                  (20u)
#define Timer0_INV_COMPL_OUT_SHIFT            (21u)
#define Timer0_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Timer0_RELOAD_CC_MASK                 ((uint32)(Timer0_1BIT_MASK        <<  \
                                                                            Timer0_RELOAD_CC_SHIFT))
#define Timer0_RELOAD_PERIOD_MASK             ((uint32)(Timer0_1BIT_MASK        <<  \
                                                                            Timer0_RELOAD_PERIOD_SHIFT))
#define Timer0_PWM_SYNC_KILL_MASK             ((uint32)(Timer0_1BIT_MASK        <<  \
                                                                            Timer0_PWM_SYNC_KILL_SHIFT))
#define Timer0_PWM_STOP_KILL_MASK             ((uint32)(Timer0_1BIT_MASK        <<  \
                                                                            Timer0_PWM_STOP_KILL_SHIFT))
#define Timer0_PRESCALER_MASK                 ((uint32)(Timer0_8BIT_MASK        <<  \
                                                                            Timer0_PRESCALER_SHIFT))
#define Timer0_UPDOWN_MASK                    ((uint32)(Timer0_2BIT_MASK        <<  \
                                                                            Timer0_UPDOWN_SHIFT))
#define Timer0_ONESHOT_MASK                   ((uint32)(Timer0_1BIT_MASK        <<  \
                                                                            Timer0_ONESHOT_SHIFT))
#define Timer0_QUAD_MODE_MASK                 ((uint32)(Timer0_3BIT_MASK        <<  \
                                                                            Timer0_QUAD_MODE_SHIFT))
#define Timer0_INV_OUT_MASK                   ((uint32)(Timer0_2BIT_MASK        <<  \
                                                                            Timer0_INV_OUT_SHIFT))
#define Timer0_MODE_MASK                      ((uint32)(Timer0_3BIT_MASK        <<  \
                                                                            Timer0_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Timer0_CAPTURE_SHIFT                  (0u)
#define Timer0_COUNT_SHIFT                    (2u)
#define Timer0_RELOAD_SHIFT                   (4u)
#define Timer0_STOP_SHIFT                     (6u)
#define Timer0_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Timer0_CAPTURE_MASK                   ((uint32)(Timer0_2BIT_MASK        <<  \
                                                                  Timer0_CAPTURE_SHIFT))
#define Timer0_COUNT_MASK                     ((uint32)(Timer0_2BIT_MASK        <<  \
                                                                  Timer0_COUNT_SHIFT))
#define Timer0_RELOAD_MASK                    ((uint32)(Timer0_2BIT_MASK        <<  \
                                                                  Timer0_RELOAD_SHIFT))
#define Timer0_STOP_MASK                      ((uint32)(Timer0_2BIT_MASK        <<  \
                                                                  Timer0_STOP_SHIFT))
#define Timer0_START_MASK                     ((uint32)(Timer0_2BIT_MASK        <<  \
                                                                  Timer0_START_SHIFT))

/* MASK */
#define Timer0_1BIT_MASK                      ((uint32)0x01u)
#define Timer0_2BIT_MASK                      ((uint32)0x03u)
#define Timer0_3BIT_MASK                      ((uint32)0x07u)
#define Timer0_6BIT_MASK                      ((uint32)0x3Fu)
#define Timer0_8BIT_MASK                      ((uint32)0xFFu)
#define Timer0_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Timer0_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Timer0_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Timer0_QUAD_ENCODING_MODES     << Timer0_QUAD_MODE_SHIFT))       |\
         ((uint32)(Timer0_CONFIG                  << Timer0_MODE_SHIFT)))

#define Timer0_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Timer0_PWM_STOP_EVENT          << Timer0_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Timer0_PWM_OUT_INVERT          << Timer0_INV_OUT_SHIFT))         |\
         ((uint32)(Timer0_PWM_OUT_N_INVERT        << Timer0_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Timer0_PWM_MODE                << Timer0_MODE_SHIFT)))

#define Timer0_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Timer0_PWM_RUN_MODE         << Timer0_ONESHOT_SHIFT))
            
#define Timer0_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Timer0_PWM_ALIGN            << Timer0_UPDOWN_SHIFT))

#define Timer0_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Timer0_PWM_KILL_EVENT      << Timer0_PWM_SYNC_KILL_SHIFT))

#define Timer0_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Timer0_PWM_DEAD_TIME_CYCLE  << Timer0_PRESCALER_SHIFT))

#define Timer0_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Timer0_PWM_PRESCALER        << Timer0_PRESCALER_SHIFT))

#define Timer0_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Timer0_TC_PRESCALER            << Timer0_PRESCALER_SHIFT))       |\
         ((uint32)(Timer0_TC_COUNTER_MODE         << Timer0_UPDOWN_SHIFT))          |\
         ((uint32)(Timer0_TC_RUN_MODE             << Timer0_ONESHOT_SHIFT))         |\
         ((uint32)(Timer0_TC_COMP_CAP_MODE        << Timer0_MODE_SHIFT)))
        
#define Timer0_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Timer0_QUAD_PHIA_SIGNAL_MODE   << Timer0_COUNT_SHIFT))           |\
         ((uint32)(Timer0_QUAD_INDEX_SIGNAL_MODE  << Timer0_RELOAD_SHIFT))          |\
         ((uint32)(Timer0_QUAD_STOP_SIGNAL_MODE   << Timer0_STOP_SHIFT))            |\
         ((uint32)(Timer0_QUAD_PHIB_SIGNAL_MODE   << Timer0_START_SHIFT)))

#define Timer0_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Timer0_PWM_SWITCH_SIGNAL_MODE  << Timer0_CAPTURE_SHIFT))         |\
         ((uint32)(Timer0_PWM_COUNT_SIGNAL_MODE   << Timer0_COUNT_SHIFT))           |\
         ((uint32)(Timer0_PWM_RELOAD_SIGNAL_MODE  << Timer0_RELOAD_SHIFT))          |\
         ((uint32)(Timer0_PWM_STOP_SIGNAL_MODE    << Timer0_STOP_SHIFT))            |\
         ((uint32)(Timer0_PWM_START_SIGNAL_MODE   << Timer0_START_SHIFT)))

#define Timer0_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Timer0_TC_CAPTURE_SIGNAL_MODE  << Timer0_CAPTURE_SHIFT))         |\
         ((uint32)(Timer0_TC_COUNT_SIGNAL_MODE    << Timer0_COUNT_SHIFT))           |\
         ((uint32)(Timer0_TC_RELOAD_SIGNAL_MODE   << Timer0_RELOAD_SHIFT))          |\
         ((uint32)(Timer0_TC_STOP_SIGNAL_MODE     << Timer0_STOP_SHIFT))            |\
         ((uint32)(Timer0_TC_START_SIGNAL_MODE    << Timer0_START_SHIFT)))
        
#define Timer0_TIMER_UPDOWN_CNT_USED                                                          \
                ((Timer0__COUNT_UPDOWN0 == Timer0_TC_COUNTER_MODE)                  ||\
                 (Timer0__COUNT_UPDOWN1 == Timer0_TC_COUNTER_MODE))

#define Timer0_PWM_UPDOWN_CNT_USED                                                            \
                ((Timer0__CENTER == Timer0_PWM_ALIGN)                               ||\
                 (Timer0__ASYMMETRIC == Timer0_PWM_ALIGN))               
        
#define Timer0_PWM_PR_INIT_VALUE              (1u)
#define Timer0_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Timer0_H */

/* [] END OF FILE */
