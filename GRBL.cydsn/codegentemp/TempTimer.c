/*******************************************************************************
* File Name: TempTimer.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the TempTimer
*  component
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

#include "TempTimer.h"

uint8 TempTimer_initVar = 0u;


/*******************************************************************************
* Function Name: TempTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default TempTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (TempTimer__QUAD == TempTimer_CONFIG)
        TempTimer_CONTROL_REG = TempTimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TempTimer_TRIG_CONTROL1_REG  = TempTimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        TempTimer_SetInterruptMode(TempTimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        TempTimer_SetCounterMode(TempTimer_COUNT_DOWN);
        TempTimer_WritePeriod(TempTimer_QUAD_PERIOD_INIT_VALUE);
        TempTimer_WriteCounter(TempTimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (TempTimer__QUAD == TempTimer_CONFIG) */

    #if (TempTimer__TIMER == TempTimer_CONFIG)
        TempTimer_CONTROL_REG = TempTimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TempTimer_TRIG_CONTROL1_REG  = TempTimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TempTimer_SetInterruptMode(TempTimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        TempTimer_WritePeriod(TempTimer_TC_PERIOD_VALUE );

        #if (TempTimer__COMPARE == TempTimer_TC_COMP_CAP_MODE)
            TempTimer_WriteCompare(TempTimer_TC_COMPARE_VALUE);

            #if (1u == TempTimer_TC_COMPARE_SWAP)
                TempTimer_SetCompareSwap(1u);
                TempTimer_WriteCompareBuf(TempTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == TempTimer_TC_COMPARE_SWAP) */
        #endif  /* (TempTimer__COMPARE == TempTimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (TempTimer_CY_TCPWM_V2 && TempTimer_TIMER_UPDOWN_CNT_USED && !TempTimer_CY_TCPWM_4000)
            TempTimer_WriteCounter(1u);
        #elif(TempTimer__COUNT_DOWN == TempTimer_TC_COUNTER_MODE)
            TempTimer_WriteCounter(TempTimer_TC_PERIOD_VALUE);
        #else
            TempTimer_WriteCounter(0u);
        #endif /* (TempTimer_CY_TCPWM_V2 && TempTimer_TIMER_UPDOWN_CNT_USED && !TempTimer_CY_TCPWM_4000) */
    #endif  /* (TempTimer__TIMER == TempTimer_CONFIG) */

    #if (TempTimer__PWM_SEL == TempTimer_CONFIG)
        TempTimer_CONTROL_REG = TempTimer_CTRL_PWM_BASE_CONFIG;

        #if (TempTimer__PWM_PR == TempTimer_PWM_MODE)
            TempTimer_CONTROL_REG |= TempTimer_CTRL_PWM_RUN_MODE;
            TempTimer_WriteCounter(TempTimer_PWM_PR_INIT_VALUE);
        #else
            TempTimer_CONTROL_REG |= TempTimer_CTRL_PWM_ALIGN | TempTimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (TempTimer_CY_TCPWM_V2 && TempTimer_PWM_UPDOWN_CNT_USED && !TempTimer_CY_TCPWM_4000)
                TempTimer_WriteCounter(1u);
            #elif (TempTimer__RIGHT == TempTimer_PWM_ALIGN)
                TempTimer_WriteCounter(TempTimer_PWM_PERIOD_VALUE);
            #else 
                TempTimer_WriteCounter(0u);
            #endif  /* (TempTimer_CY_TCPWM_V2 && TempTimer_PWM_UPDOWN_CNT_USED && !TempTimer_CY_TCPWM_4000) */
        #endif  /* (TempTimer__PWM_PR == TempTimer_PWM_MODE) */

        #if (TempTimer__PWM_DT == TempTimer_PWM_MODE)
            TempTimer_CONTROL_REG |= TempTimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (TempTimer__PWM_DT == TempTimer_PWM_MODE) */

        #if (TempTimer__PWM == TempTimer_PWM_MODE)
            TempTimer_CONTROL_REG |= TempTimer_CTRL_PWM_PRESCALER;
        #endif  /* (TempTimer__PWM == TempTimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        TempTimer_TRIG_CONTROL1_REG  = TempTimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TempTimer_SetInterruptMode(TempTimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (TempTimer__PWM_PR == TempTimer_PWM_MODE)
            TempTimer_TRIG_CONTROL2_REG =
                    (TempTimer_CC_MATCH_NO_CHANGE    |
                    TempTimer_OVERLOW_NO_CHANGE      |
                    TempTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (TempTimer__LEFT == TempTimer_PWM_ALIGN)
                TempTimer_TRIG_CONTROL2_REG = TempTimer_PWM_MODE_LEFT;
            #endif  /* ( TempTimer_PWM_LEFT == TempTimer_PWM_ALIGN) */

            #if (TempTimer__RIGHT == TempTimer_PWM_ALIGN)
                TempTimer_TRIG_CONTROL2_REG = TempTimer_PWM_MODE_RIGHT;
            #endif  /* ( TempTimer_PWM_RIGHT == TempTimer_PWM_ALIGN) */

            #if (TempTimer__CENTER == TempTimer_PWM_ALIGN)
                TempTimer_TRIG_CONTROL2_REG = TempTimer_PWM_MODE_CENTER;
            #endif  /* ( TempTimer_PWM_CENTER == TempTimer_PWM_ALIGN) */

            #if (TempTimer__ASYMMETRIC == TempTimer_PWM_ALIGN)
                TempTimer_TRIG_CONTROL2_REG = TempTimer_PWM_MODE_ASYM;
            #endif  /* (TempTimer__ASYMMETRIC == TempTimer_PWM_ALIGN) */
        #endif  /* (TempTimer__PWM_PR == TempTimer_PWM_MODE) */

        /* Set other values from customizer */
        TempTimer_WritePeriod(TempTimer_PWM_PERIOD_VALUE );
        TempTimer_WriteCompare(TempTimer_PWM_COMPARE_VALUE);

        #if (1u == TempTimer_PWM_COMPARE_SWAP)
            TempTimer_SetCompareSwap(1u);
            TempTimer_WriteCompareBuf(TempTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == TempTimer_PWM_COMPARE_SWAP) */

        #if (1u == TempTimer_PWM_PERIOD_SWAP)
            TempTimer_SetPeriodSwap(1u);
            TempTimer_WritePeriodBuf(TempTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == TempTimer_PWM_PERIOD_SWAP) */
    #endif  /* (TempTimer__PWM_SEL == TempTimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: TempTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the TempTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    TempTimer_BLOCK_CONTROL_REG |= TempTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (TempTimer__PWM_SEL == TempTimer_CONFIG)
        #if (0u == TempTimer_PWM_START_SIGNAL_PRESENT)
            TempTimer_TriggerCommand(TempTimer_MASK, TempTimer_CMD_START);
        #endif /* (0u == TempTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (TempTimer__PWM_SEL == TempTimer_CONFIG) */

    #if (TempTimer__TIMER == TempTimer_CONFIG)
        #if (0u == TempTimer_TC_START_SIGNAL_PRESENT)
            TempTimer_TriggerCommand(TempTimer_MASK, TempTimer_CMD_START);
        #endif /* (0u == TempTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (TempTimer__TIMER == TempTimer_CONFIG) */
    
    #if (TempTimer__QUAD == TempTimer_CONFIG)
        #if (0u != TempTimer_QUAD_AUTO_START)
            TempTimer_TriggerCommand(TempTimer_MASK, TempTimer_CMD_RELOAD);
        #endif /* (0u != TempTimer_QUAD_AUTO_START) */
    #endif  /* (TempTimer__QUAD == TempTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: TempTimer_Start
********************************************************************************
*
* Summary:
*  Initializes the TempTimer with default customizer
*  values when called the first time and enables the TempTimer.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TempTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time TempTimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the TempTimer_Start() routine.
*
*******************************************************************************/
void TempTimer_Start(void)
{
    if (0u == TempTimer_initVar)
    {
        TempTimer_Init();
        TempTimer_initVar = 1u;
    }

    TempTimer_Enable();
}


/*******************************************************************************
* Function Name: TempTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the TempTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_BLOCK_CONTROL_REG &= (uint32)~TempTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the TempTimer. This function is used when
*  configured as a generic TempTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the TempTimer to operate in
*   Values:
*   - TempTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - TempTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - TempTimer_MODE_QUAD - Quadrature decoder
*         - TempTimer_MODE_PWM - PWM
*         - TempTimer_MODE_PWM_DT - PWM with dead time
*         - TempTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_MODE_MASK;
    TempTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - TempTimer_MODE_X1 - Counts on phi 1 rising
*         - TempTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - TempTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_QUAD_MODE_MASK;
    TempTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - TempTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - TempTimer_PRESCALE_DIVBY2    - Divide by 2
*         - TempTimer_PRESCALE_DIVBY4    - Divide by 4
*         - TempTimer_PRESCALE_DIVBY8    - Divide by 8
*         - TempTimer_PRESCALE_DIVBY16   - Divide by 16
*         - TempTimer_PRESCALE_DIVBY32   - Divide by 32
*         - TempTimer_PRESCALE_DIVBY64   - Divide by 64
*         - TempTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_PRESCALER_MASK;
    TempTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the TempTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  TempTimer operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_ONESHOT_MASK;
    TempTimer_CONTROL_REG |= ((uint32)((oneShotEnable & TempTimer_1BIT_MASK) <<
                                                               TempTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetPWMMode(uint32 modeMask)
{
    TempTimer_TRIG_CONTROL2_REG = (modeMask & TempTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: TempTimer_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_PWM_SYNC_KILL_MASK;
    TempTimer_CONTROL_REG |= ((uint32)((syncKillEnable & TempTimer_1BIT_MASK)  <<
                                               TempTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_PWM_STOP_KILL_MASK;
    TempTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & TempTimer_1BIT_MASK)  <<
                                                         TempTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_PRESCALER_MASK;
    TempTimer_CONTROL_REG |= ((uint32)((deadTime & TempTimer_8BIT_MASK) <<
                                                          TempTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - TempTimer_INVERT_LINE   - Inverts the line output
*         - TempTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_INV_OUT_MASK;
    TempTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: TempTimer_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_WriteCounter(uint32 count)
{
    TempTimer_COUNTER_REG = (count & TempTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TempTimer_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 TempTimer_ReadCounter(void)
{
    return (TempTimer_COUNTER_REG & TempTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TempTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - TempTimer_COUNT_UP       - Counts up
*     - TempTimer_COUNT_DOWN     - Counts down
*     - TempTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - TempTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_UPDOWN_MASK;
    TempTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_WritePeriod(uint32 period)
{
    TempTimer_PERIOD_REG = (period & TempTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TempTimer_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 TempTimer_ReadPeriod(void)
{
    return (TempTimer_PERIOD_REG & TempTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TempTimer_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_RELOAD_CC_MASK;
    TempTimer_CONTROL_REG |= (swapEnable & TempTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_WritePeriodBuf(uint32 periodBuf)
{
    TempTimer_PERIOD_BUF_REG = (periodBuf & TempTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TempTimer_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 TempTimer_ReadPeriodBuf(void)
{
    return (TempTimer_PERIOD_BUF_REG & TempTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TempTimer_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_CONTROL_REG &= (uint32)~TempTimer_RELOAD_PERIOD_MASK;
    TempTimer_CONTROL_REG |= ((uint32)((swapEnable & TempTimer_1BIT_MASK) <<
                                                            TempTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void TempTimer_WriteCompare(uint32 compare)
{
    #if (TempTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TempTimer_CY_TCPWM_4000) */

    #if (TempTimer_CY_TCPWM_4000)
        currentMode = ((TempTimer_CONTROL_REG & TempTimer_UPDOWN_MASK) >> TempTimer_UPDOWN_SHIFT);

        if (((uint32)TempTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)TempTimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (TempTimer_CY_TCPWM_4000) */
    
    TempTimer_COMP_CAP_REG = (compare & TempTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TempTimer_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 TempTimer_ReadCompare(void)
{
    #if (TempTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TempTimer_CY_TCPWM_4000) */

    #if (TempTimer_CY_TCPWM_4000)
        currentMode = ((TempTimer_CONTROL_REG & TempTimer_UPDOWN_MASK) >> TempTimer_UPDOWN_SHIFT);
        
        regVal = TempTimer_COMP_CAP_REG;
        
        if (((uint32)TempTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TempTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TempTimer_16BIT_MASK);
    #else
        return (TempTimer_COMP_CAP_REG & TempTimer_16BIT_MASK);
    #endif /* (TempTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TempTimer_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void TempTimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (TempTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TempTimer_CY_TCPWM_4000) */

    #if (TempTimer_CY_TCPWM_4000)
        currentMode = ((TempTimer_CONTROL_REG & TempTimer_UPDOWN_MASK) >> TempTimer_UPDOWN_SHIFT);

        if (((uint32)TempTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)TempTimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (TempTimer_CY_TCPWM_4000) */
    
    TempTimer_COMP_CAP_BUF_REG = (compareBuf & TempTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TempTimer_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 TempTimer_ReadCompareBuf(void)
{
    #if (TempTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TempTimer_CY_TCPWM_4000) */

    #if (TempTimer_CY_TCPWM_4000)
        currentMode = ((TempTimer_CONTROL_REG & TempTimer_UPDOWN_MASK) >> TempTimer_UPDOWN_SHIFT);

        regVal = TempTimer_COMP_CAP_BUF_REG;
        
        if (((uint32)TempTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TempTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TempTimer_16BIT_MASK);
    #else
        return (TempTimer_COMP_CAP_BUF_REG & TempTimer_16BIT_MASK);
    #endif /* (TempTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TempTimer_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 TempTimer_ReadCapture(void)
{
    return (TempTimer_COMP_CAP_REG & TempTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TempTimer_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 TempTimer_ReadCaptureBuf(void)
{
    return (TempTimer_COMP_CAP_BUF_REG & TempTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TempTimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TempTimer_TRIG_LEVEL     - Level
*     - TempTimer_TRIG_RISING    - Rising edge
*     - TempTimer_TRIG_FALLING   - Falling edge
*     - TempTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_TRIG_CONTROL1_REG &= (uint32)~TempTimer_CAPTURE_MASK;
    TempTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TempTimer_TRIG_LEVEL     - Level
*     - TempTimer_TRIG_RISING    - Rising edge
*     - TempTimer_TRIG_FALLING   - Falling edge
*     - TempTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_TRIG_CONTROL1_REG &= (uint32)~TempTimer_RELOAD_MASK;
    TempTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TempTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TempTimer_TRIG_LEVEL     - Level
*     - TempTimer_TRIG_RISING    - Rising edge
*     - TempTimer_TRIG_FALLING   - Falling edge
*     - TempTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_TRIG_CONTROL1_REG &= (uint32)~TempTimer_START_MASK;
    TempTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TempTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TempTimer_TRIG_LEVEL     - Level
*     - TempTimer_TRIG_RISING    - Rising edge
*     - TempTimer_TRIG_FALLING   - Falling edge
*     - TempTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_TRIG_CONTROL1_REG &= (uint32)~TempTimer_STOP_MASK;
    TempTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TempTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TempTimer_TRIG_LEVEL     - Level
*     - TempTimer_TRIG_RISING    - Rising edge
*     - TempTimer_TRIG_FALLING   - Falling edge
*     - TempTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_TRIG_CONTROL1_REG &= (uint32)~TempTimer_COUNT_MASK;
    TempTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TempTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - TempTimer_CMD_CAPTURE    - Trigger Capture/Switch command
*     - TempTimer_CMD_RELOAD     - Trigger Reload/Index command
*     - TempTimer_CMD_STOP       - Trigger Stop/Kill command
*     - TempTimer_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TempTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TempTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the TempTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - TempTimer_STATUS_DOWN    - Set if counting down
*     - TempTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 TempTimer_ReadStatus(void)
{
    return ((TempTimer_STATUS_REG >> TempTimer_RUNNING_STATUS_SHIFT) |
            (TempTimer_STATUS_REG & TempTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: TempTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - TempTimer_INTR_MASK_TC       - Terminal count mask
*     - TempTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetInterruptMode(uint32 interruptMask)
{
    TempTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: TempTimer_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - TempTimer_INTR_MASK_TC       - Terminal count mask
*     - TempTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TempTimer_GetInterruptSourceMasked(void)
{
    return (TempTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: TempTimer_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - TempTimer_INTR_MASK_TC       - Terminal count mask
*     - TempTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TempTimer_GetInterruptSource(void)
{
    return (TempTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: TempTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - TempTimer_INTR_MASK_TC       - Terminal count mask
*     - TempTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_ClearInterrupt(uint32 interruptMask)
{
    TempTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: TempTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - TempTimer_INTR_MASK_TC       - Terminal count mask
*     - TempTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TempTimer_SetInterrupt(uint32 interruptMask)
{
    TempTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
