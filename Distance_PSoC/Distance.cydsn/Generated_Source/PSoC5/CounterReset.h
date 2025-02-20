/*******************************************************************************
* File Name: CounterReset.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CounterReset_H) /* Pins CounterReset_H */
#define CY_PINS_CounterReset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CounterReset_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CounterReset__PORT == 15 && ((CounterReset__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CounterReset_Write(uint8 value);
void    CounterReset_SetDriveMode(uint8 mode);
uint8   CounterReset_ReadDataReg(void);
uint8   CounterReset_Read(void);
void    CounterReset_SetInterruptMode(uint16 position, uint16 mode);
uint8   CounterReset_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CounterReset_SetDriveMode() function.
     *  @{
     */
        #define CounterReset_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CounterReset_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CounterReset_DM_RES_UP          PIN_DM_RES_UP
        #define CounterReset_DM_RES_DWN         PIN_DM_RES_DWN
        #define CounterReset_DM_OD_LO           PIN_DM_OD_LO
        #define CounterReset_DM_OD_HI           PIN_DM_OD_HI
        #define CounterReset_DM_STRONG          PIN_DM_STRONG
        #define CounterReset_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CounterReset_MASK               CounterReset__MASK
#define CounterReset_SHIFT              CounterReset__SHIFT
#define CounterReset_WIDTH              1u

/* Interrupt constants */
#if defined(CounterReset__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CounterReset_SetInterruptMode() function.
     *  @{
     */
        #define CounterReset_INTR_NONE      (uint16)(0x0000u)
        #define CounterReset_INTR_RISING    (uint16)(0x0001u)
        #define CounterReset_INTR_FALLING   (uint16)(0x0002u)
        #define CounterReset_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CounterReset_INTR_MASK      (0x01u) 
#endif /* (CounterReset__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CounterReset_PS                     (* (reg8 *) CounterReset__PS)
/* Data Register */
#define CounterReset_DR                     (* (reg8 *) CounterReset__DR)
/* Port Number */
#define CounterReset_PRT_NUM                (* (reg8 *) CounterReset__PRT) 
/* Connect to Analog Globals */                                                  
#define CounterReset_AG                     (* (reg8 *) CounterReset__AG)                       
/* Analog MUX bux enable */
#define CounterReset_AMUX                   (* (reg8 *) CounterReset__AMUX) 
/* Bidirectional Enable */                                                        
#define CounterReset_BIE                    (* (reg8 *) CounterReset__BIE)
/* Bit-mask for Aliased Register Access */
#define CounterReset_BIT_MASK               (* (reg8 *) CounterReset__BIT_MASK)
/* Bypass Enable */
#define CounterReset_BYP                    (* (reg8 *) CounterReset__BYP)
/* Port wide control signals */                                                   
#define CounterReset_CTL                    (* (reg8 *) CounterReset__CTL)
/* Drive Modes */
#define CounterReset_DM0                    (* (reg8 *) CounterReset__DM0) 
#define CounterReset_DM1                    (* (reg8 *) CounterReset__DM1)
#define CounterReset_DM2                    (* (reg8 *) CounterReset__DM2) 
/* Input Buffer Disable Override */
#define CounterReset_INP_DIS                (* (reg8 *) CounterReset__INP_DIS)
/* LCD Common or Segment Drive */
#define CounterReset_LCD_COM_SEG            (* (reg8 *) CounterReset__LCD_COM_SEG)
/* Enable Segment LCD */
#define CounterReset_LCD_EN                 (* (reg8 *) CounterReset__LCD_EN)
/* Slew Rate Control */
#define CounterReset_SLW                    (* (reg8 *) CounterReset__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CounterReset_PRTDSI__CAPS_SEL       (* (reg8 *) CounterReset__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CounterReset_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CounterReset__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CounterReset_PRTDSI__OE_SEL0        (* (reg8 *) CounterReset__PRTDSI__OE_SEL0) 
#define CounterReset_PRTDSI__OE_SEL1        (* (reg8 *) CounterReset__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CounterReset_PRTDSI__OUT_SEL0       (* (reg8 *) CounterReset__PRTDSI__OUT_SEL0) 
#define CounterReset_PRTDSI__OUT_SEL1       (* (reg8 *) CounterReset__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CounterReset_PRTDSI__SYNC_OUT       (* (reg8 *) CounterReset__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CounterReset__SIO_CFG)
    #define CounterReset_SIO_HYST_EN        (* (reg8 *) CounterReset__SIO_HYST_EN)
    #define CounterReset_SIO_REG_HIFREQ     (* (reg8 *) CounterReset__SIO_REG_HIFREQ)
    #define CounterReset_SIO_CFG            (* (reg8 *) CounterReset__SIO_CFG)
    #define CounterReset_SIO_DIFF           (* (reg8 *) CounterReset__SIO_DIFF)
#endif /* (CounterReset__SIO_CFG) */

/* Interrupt Registers */
#if defined(CounterReset__INTSTAT)
    #define CounterReset_INTSTAT            (* (reg8 *) CounterReset__INTSTAT)
    #define CounterReset_SNAP               (* (reg8 *) CounterReset__SNAP)
    
	#define CounterReset_0_INTTYPE_REG 		(* (reg8 *) CounterReset__0__INTTYPE)
#endif /* (CounterReset__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CounterReset_H */


/* [] END OF FILE */
