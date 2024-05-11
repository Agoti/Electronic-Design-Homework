/*******************************************************************************
* File Name: TimeoutISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_TimeoutISR_H)
#define CY_ISR_TimeoutISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TimeoutISR_Start(void);
void TimeoutISR_StartEx(cyisraddress address);
void TimeoutISR_Stop(void);

CY_ISR_PROTO(TimeoutISR_Interrupt);

void TimeoutISR_SetVector(cyisraddress address);
cyisraddress TimeoutISR_GetVector(void);

void TimeoutISR_SetPriority(uint8 priority);
uint8 TimeoutISR_GetPriority(void);

void TimeoutISR_Enable(void);
uint8 TimeoutISR_GetState(void);
void TimeoutISR_Disable(void);

void TimeoutISR_SetPending(void);
void TimeoutISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TimeoutISR ISR. */
#define TimeoutISR_INTC_VECTOR            ((reg32 *) TimeoutISR__INTC_VECT)

/* Address of the TimeoutISR ISR priority. */
#define TimeoutISR_INTC_PRIOR             ((reg8 *) TimeoutISR__INTC_PRIOR_REG)

/* Priority of the TimeoutISR interrupt. */
#define TimeoutISR_INTC_PRIOR_NUMBER      TimeoutISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TimeoutISR interrupt. */
#define TimeoutISR_INTC_SET_EN            ((reg32 *) TimeoutISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TimeoutISR interrupt. */
#define TimeoutISR_INTC_CLR_EN            ((reg32 *) TimeoutISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TimeoutISR interrupt state to pending. */
#define TimeoutISR_INTC_SET_PD            ((reg32 *) TimeoutISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TimeoutISR interrupt. */
#define TimeoutISR_INTC_CLR_PD            ((reg32 *) TimeoutISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_TimeoutISR_H */


/* [] END OF FILE */
