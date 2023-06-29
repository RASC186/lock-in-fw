/*******************************************************************************
* File Name: SOC_PWM.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the SOC_PWM
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SOC_PWM.h"

/** Indicates whether or not the SOC_PWM has been initialized. 
*  The variable is initialized to 0 and set to 1 the first time 
*  SOC_PWM_Start() is called. This allows the Component to 
*  restart without reinitialization after the first call to 
*  the SOC_PWM_Start() routine.
*/
uint8_t SOC_PWM_initVar = 0U;

/** The instance-specific configuration structure. This should be used in the 
*  associated SOC_PWM_Init() function.
*/ 
cy_stc_tcpwm_pwm_config_t const SOC_PWM_config =
{
    .pwmMode = 4UL,
    .clockPrescaler = 0UL,
    .pwmAlignment = 0UL,
    .deadTimeClocks = 0UL,
    .runMode = 0UL,
    .period0 = 4999UL,
    .period1 = 32768UL,
    .enablePeriodSwap = false,
    .compare0 = 2500UL,
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
* Function Name: SOC_PWM_Start
****************************************************************************//**
*
*  Calls the SOC_PWM_Init() when called the first time and enables 
*  the SOC_PWM. For subsequent calls the configuration is left 
*  unchanged and the component is just enabled.
*
* \globalvars
*  \ref SOC_PWM_initVar
*
*******************************************************************************/
void SOC_PWM_Start(void)
{
    if (0U == SOC_PWM_initVar)
    {
        (void) Cy_TCPWM_PWM_Init(SOC_PWM_HW, SOC_PWM_CNT_NUM, &SOC_PWM_config);

        SOC_PWM_initVar = 1U;
    }

    Cy_TCPWM_Enable_Multiple(SOC_PWM_HW, SOC_PWM_CNT_MASK);
    
    #if (SOC_PWM_INPUT_DISABLED == 7UL)
        Cy_TCPWM_TriggerStart(SOC_PWM_HW, SOC_PWM_CNT_MASK);
    #endif /* (SOC_PWM_INPUT_DISABLED == 7UL) */    
}


/* [] END OF FILE */
