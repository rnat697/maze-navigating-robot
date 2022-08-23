/*******************************************************************************
* File Name: rED.h  
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

#if !defined(CY_PINS_rED_H) /* Pins rED_H */
#define CY_PINS_rED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "rED_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 rED__PORT == 15 && ((rED__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    rED_Write(uint8 value);
void    rED_SetDriveMode(uint8 mode);
uint8   rED_ReadDataReg(void);
uint8   rED_Read(void);
void    rED_SetInterruptMode(uint16 position, uint16 mode);
uint8   rED_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the rED_SetDriveMode() function.
     *  @{
     */
        #define rED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define rED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define rED_DM_RES_UP          PIN_DM_RES_UP
        #define rED_DM_RES_DWN         PIN_DM_RES_DWN
        #define rED_DM_OD_LO           PIN_DM_OD_LO
        #define rED_DM_OD_HI           PIN_DM_OD_HI
        #define rED_DM_STRONG          PIN_DM_STRONG
        #define rED_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define rED_MASK               rED__MASK
#define rED_SHIFT              rED__SHIFT
#define rED_WIDTH              1u

/* Interrupt constants */
#if defined(rED__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in rED_SetInterruptMode() function.
     *  @{
     */
        #define rED_INTR_NONE      (uint16)(0x0000u)
        #define rED_INTR_RISING    (uint16)(0x0001u)
        #define rED_INTR_FALLING   (uint16)(0x0002u)
        #define rED_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define rED_INTR_MASK      (0x01u) 
#endif /* (rED__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define rED_PS                     (* (reg8 *) rED__PS)
/* Data Register */
#define rED_DR                     (* (reg8 *) rED__DR)
/* Port Number */
#define rED_PRT_NUM                (* (reg8 *) rED__PRT) 
/* Connect to Analog Globals */                                                  
#define rED_AG                     (* (reg8 *) rED__AG)                       
/* Analog MUX bux enable */
#define rED_AMUX                   (* (reg8 *) rED__AMUX) 
/* Bidirectional Enable */                                                        
#define rED_BIE                    (* (reg8 *) rED__BIE)
/* Bit-mask for Aliased Register Access */
#define rED_BIT_MASK               (* (reg8 *) rED__BIT_MASK)
/* Bypass Enable */
#define rED_BYP                    (* (reg8 *) rED__BYP)
/* Port wide control signals */                                                   
#define rED_CTL                    (* (reg8 *) rED__CTL)
/* Drive Modes */
#define rED_DM0                    (* (reg8 *) rED__DM0) 
#define rED_DM1                    (* (reg8 *) rED__DM1)
#define rED_DM2                    (* (reg8 *) rED__DM2) 
/* Input Buffer Disable Override */
#define rED_INP_DIS                (* (reg8 *) rED__INP_DIS)
/* LCD Common or Segment Drive */
#define rED_LCD_COM_SEG            (* (reg8 *) rED__LCD_COM_SEG)
/* Enable Segment LCD */
#define rED_LCD_EN                 (* (reg8 *) rED__LCD_EN)
/* Slew Rate Control */
#define rED_SLW                    (* (reg8 *) rED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define rED_PRTDSI__CAPS_SEL       (* (reg8 *) rED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define rED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) rED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define rED_PRTDSI__OE_SEL0        (* (reg8 *) rED__PRTDSI__OE_SEL0) 
#define rED_PRTDSI__OE_SEL1        (* (reg8 *) rED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define rED_PRTDSI__OUT_SEL0       (* (reg8 *) rED__PRTDSI__OUT_SEL0) 
#define rED_PRTDSI__OUT_SEL1       (* (reg8 *) rED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define rED_PRTDSI__SYNC_OUT       (* (reg8 *) rED__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(rED__SIO_CFG)
    #define rED_SIO_HYST_EN        (* (reg8 *) rED__SIO_HYST_EN)
    #define rED_SIO_REG_HIFREQ     (* (reg8 *) rED__SIO_REG_HIFREQ)
    #define rED_SIO_CFG            (* (reg8 *) rED__SIO_CFG)
    #define rED_SIO_DIFF           (* (reg8 *) rED__SIO_DIFF)
#endif /* (rED__SIO_CFG) */

/* Interrupt Registers */
#if defined(rED__INTSTAT)
    #define rED_INTSTAT            (* (reg8 *) rED__INTSTAT)
    #define rED_SNAP               (* (reg8 *) rED__SNAP)
    
	#define rED_0_INTTYPE_REG 		(* (reg8 *) rED__0__INTTYPE)
#endif /* (rED__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_rED_H */


/* [] END OF FILE */
