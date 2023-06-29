/*******************************************************************************
* File Name: L740_PWM.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the L740_PWM
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "L740_PWM.h"

/** Indicates whether or not the L740_PWM has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  L740_PWM_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the L740_PWM_Start() routine.
*/
uint8_t L740_PWM_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated L740_PWM_Init() function.
*/ 
cy_stc_tcpwm_pwm_config_t const L740_PWM_config =
{
    .pwmMode = 4UL,
    .clockPrescaler = 0UL,
    .pwmAlignment = 0UL,
    .deadTimeClocks = 0UL,
    .runMode = 0UL,
    .period0 = 39999UL,
    .period1 = 32768UL,
    .enablePeriodSwap = false,
    .compare0 = 20000UL,
    .compare1 = 16384UL,
    .enableCompareSwap = false,
    .interruptSources = 0UL,
    .invertPWMOut = 0UL,
    .invertPWMOutN = 0UL,
    .killMode = 2UL,
    .swapInputMode = 3UL,
    .swapInput = CY_TCPWM_INPUT_CREATOR,
    .reloadInputMode = 3UL,
    .reloadInput = CY_TCPWM_INPUT_CREATOR,
    .startInputMode = 3UL,
    .startInput = CY_TCPWM_INPUT_CREATOR,
    .killInputMode = 3UL,
    .killInput = CY_TCPWM_INPUT_CREATOR,
    .countInputMode = 3UL,
    .countInput = CY_TCPWM_INPUT_CREATOR,
};


/*******************************************************************************
* Function Name: L740_PWM_Start
****************************************************************************//**
*
*  Calls the L740_PWM_Init() when called the first time and enables 
*  the L740_PWM. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref L740_PWM_initVar
*
*******************************************************************************/
void L740_PWM_Start(void)
{
    if (0U == L740_PWM_initVar)
    {
        (void) Cy_TCPWM_PWM_Init(L740_PWM_HW, L740_PWM_CNT_NUM, &L740_PWM_config);

        L740_PWM_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(L740_PWM_HW, L740_PWM_CNT_MASK);
    
    #if (L740_PWM_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(L740_PWM_HW, L740_PWM_CNT_MASK);
    #endif /* (L740_PWM_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
