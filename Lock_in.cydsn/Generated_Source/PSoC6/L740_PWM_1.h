/*******************************************************************************
* File Name: L740_PWM_1.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the L740_PWM_1
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(L740_PWM_1_CY_TCPWM_PWM_PDL_H)
#define L740_PWM_1_CY_TCPWM_PWM_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_pwm.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  L740_PWM_1_initVar;
extern cy_stc_tcpwm_pwm_config_t const L740_PWM_1_config;
/** @} group_globals */


/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void L740_PWM_1_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t L740_PWM_1_Init(cy_stc_tcpwm_pwm_config_t const *config);
__STATIC_INLINE void L740_PWM_1_DeInit(void);
__STATIC_INLINE void L740_PWM_1_Enable(void);
__STATIC_INLINE void L740_PWM_1_Disable(void);
__STATIC_INLINE uint32_t L740_PWM_1_GetStatus(void);
__STATIC_INLINE void L740_PWM_1_SetCompare0(uint32_t compare0);
__STATIC_INLINE uint32_t L740_PWM_1_GetCompare0(void);
__STATIC_INLINE void L740_PWM_1_SetCompare1(uint32_t compare1);
__STATIC_INLINE uint32_t L740_PWM_1_GetCompare1(void);
__STATIC_INLINE void L740_PWM_1_EnableCompareSwap(bool enable);
__STATIC_INLINE void L740_PWM_1_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t L740_PWM_1_GetCounter(void);
__STATIC_INLINE void L740_PWM_1_SetPeriod0(uint32_t period0);
__STATIC_INLINE uint32_t L740_PWM_1_GetPeriod0(void);
__STATIC_INLINE void L740_PWM_1_SetPeriod1(uint32_t period1);
__STATIC_INLINE uint32_t L740_PWM_1_GetPeriod1(void);
__STATIC_INLINE void L740_PWM_1_EnablePeriodSwap(bool enable);
__STATIC_INLINE void L740_PWM_1_TriggerStart(void);
__STATIC_INLINE void L740_PWM_1_TriggerReload(void);
__STATIC_INLINE void L740_PWM_1_TriggerKill(void);
__STATIC_INLINE void L740_PWM_1_TriggerSwap(void);
__STATIC_INLINE uint32_t L740_PWM_1_GetInterruptStatus(void);
__STATIC_INLINE void L740_PWM_1_ClearInterrupt(uint32_t source);
__STATIC_INLINE void L740_PWM_1_SetInterrupt(uint32_t source);
__STATIC_INLINE void L740_PWM_1_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t L740_PWM_1_GetInterruptMask(void);
__STATIC_INLINE uint32_t L740_PWM_1_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define L740_PWM_1_HW                 (L740_PWM_1_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define L740_PWM_1_CNT_HW             (L740_PWM_1_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define L740_PWM_1_CNT_NUM            (L740_PWM_1_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define L740_PWM_1_CNT_MASK           (1UL << L740_PWM_1_CNT_NUM)
/** @} group_macros */

#define L740_PWM_1_INPUT_MODE_MASK    (0x3U)
#define L740_PWM_1_INPUT_DISABLED     (7U)


/*******************************************************************************
* Function Name: L740_PWM_1_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t L740_PWM_1_Init(cy_stc_tcpwm_pwm_config_t const *config)
{
    return(Cy_TCPWM_PWM_Init(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: L740_PWM_1_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_DeInit(void)                   
{
    Cy_TCPWM_PWM_DeInit(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, &L740_PWM_1_config);
}

/*******************************************************************************
* Function Name: L740_PWM_1_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(L740_PWM_1_HW, L740_PWM_1_CNT_MASK);
}


/*******************************************************************************
* Function Name: L740_PWM_1_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(L740_PWM_1_HW, L740_PWM_1_CNT_MASK);
}


/*******************************************************************************
* Function Name: L740_PWM_1_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t L740_PWM_1_GetStatus(void)                
{
    return(Cy_TCPWM_PWM_GetStatus(L740_PWM_1_HW, L740_PWM_1_CNT_NUM));
}


/*******************************************************************************
* Function Name: L740_PWM_1_SetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_SetCompare0(uint32_t compare0)      
{
    Cy_TCPWM_PWM_SetCompare0(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, compare0);
}


/*******************************************************************************
* Function Name: L740_PWM_1_GetCompare0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t L740_PWM_1_GetCompare0(void)              
{
    return(Cy_TCPWM_PWM_GetCompare0(L740_PWM_1_HW, L740_PWM_1_CNT_NUM));
}


/*******************************************************************************
* Function Name: L740_PWM_1_SetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_SetCompare1(uint32_t compare1)      
{
    Cy_TCPWM_PWM_SetCompare1(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, compare1);
}


/*******************************************************************************
* Function Name: L740_PWM_1_GetCompare1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCompare1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t L740_PWM_1_GetCompare1(void)              
{
    return(Cy_TCPWM_PWM_GetCompare1(L740_PWM_1_HW, L740_PWM_1_CNT_NUM));
}


/*******************************************************************************
* Function Name: L740_PWM_1_EnableCompareSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnableCompareSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_EnableCompareSwap(bool enable)  
{
    Cy_TCPWM_PWM_EnableCompareSwap(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: L740_PWM_1_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_SetCounter(uint32_t count)          
{
    Cy_TCPWM_PWM_SetCounter(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: L740_PWM_1_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t L740_PWM_1_GetCounter(void)               
{
    return(Cy_TCPWM_PWM_GetCounter(L740_PWM_1_HW, L740_PWM_1_CNT_NUM));
}


/*******************************************************************************
* Function Name: L740_PWM_1_SetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_SetPeriod0(uint32_t period0)          
{
    Cy_TCPWM_PWM_SetPeriod0(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, period0);
}


/*******************************************************************************
* Function Name: L740_PWM_1_GetPeriod0
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod0() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t L740_PWM_1_GetPeriod0(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod0(L740_PWM_1_HW, L740_PWM_1_CNT_NUM));
}


/*******************************************************************************
* Function Name: L740_PWM_1_SetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_SetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_SetPeriod1(uint32_t period1)
{
    Cy_TCPWM_PWM_SetPeriod1(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, period1);
}


/*******************************************************************************
* Function Name: L740_PWM_1_GetPeriod1
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_GetPeriod1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t L740_PWM_1_GetPeriod1(void)                
{
    return(Cy_TCPWM_PWM_GetPeriod1(L740_PWM_1_HW, L740_PWM_1_CNT_NUM));
}


/*******************************************************************************
* Function Name: L740_PWM_1_EnablePeriodSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_PWM_EnablePeriodSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_EnablePeriodSwap(bool enable)
{
    Cy_TCPWM_PWM_EnablePeriodSwap(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, enable);
}


/*******************************************************************************
* Function Name: L740_PWM_1_TriggerStart
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_TriggerStart(void)             
{
    Cy_TCPWM_TriggerStart(L740_PWM_1_HW, L740_PWM_1_CNT_MASK);
}


/*******************************************************************************
* Function Name: L740_PWM_1_TriggerReload
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_TriggerReload(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(L740_PWM_1_HW, L740_PWM_1_CNT_MASK);
}


/*******************************************************************************
* Function Name: L740_PWM_1_TriggerKill
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_TriggerKill(void)
{
    Cy_TCPWM_TriggerStopOrKill(L740_PWM_1_HW, L740_PWM_1_CNT_MASK);
}


/*******************************************************************************
* Function Name: L740_PWM_1_TriggerSwap
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerCaptureOrSwap() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_TriggerSwap(void)     
{
    Cy_TCPWM_TriggerCaptureOrSwap(L740_PWM_1_HW, L740_PWM_1_CNT_MASK);
}


/*******************************************************************************
* Function Name: L740_PWM_1_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t L740_PWM_1_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(L740_PWM_1_HW, L740_PWM_1_CNT_NUM));
}


/*******************************************************************************
* Function Name: L740_PWM_1_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: L740_PWM_1_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: L740_PWM_1_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void L740_PWM_1_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(L740_PWM_1_HW, L740_PWM_1_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: L740_PWM_1_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t L740_PWM_1_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(L740_PWM_1_HW, L740_PWM_1_CNT_NUM));
}


/*******************************************************************************
* Function Name: L740_PWM_1_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t L740_PWM_1_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(L740_PWM_1_HW, L740_PWM_1_CNT_NUM));
}

#endif /* L740_PWM_1_CY_TCPWM_PWM_PDL_H */


/* [] END OF FILE */
