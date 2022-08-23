/*******************************************************************************
* File Name: blue.h  
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

#if !defined(CY_PINS_blue_H) /* Pins blue_H */
#define CY_PINS_blue_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "blue_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 blue__PORT == 15 && ((blue__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    blue_Write(uint8 value);
void    blue_SetDriveMode(uint8 mode);
uint8   blue_ReadDataReg(void);
uint8   blue_Read(void);
void    blue_SetInterruptMode(uint16 position, uint16 mode);
uint8   blue_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the blue_SetDriveMode() function.
     *  @{
     */
        #define blue_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define blue_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define blue_DM_RES_UP          PIN_DM_RES_UP
        #define blue_DM_RES_DWN         PIN_DM_RES_DWN
        #define blue_DM_OD_LO           PIN_DM_OD_LO
        #define blue_DM_OD_HI           PIN_DM_OD_HI
        #define blue_DM_STRONG          PIN_DM_STRONG
        #define blue_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define blue_MASK               blue__MASK
#define blue_SHIFT              blue__SHIFT
#define blue_WIDTH              1u

/* Interrupt constants */
#if defined(blue__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in blue_SetInterruptMode() function.
     *  @{
     */
        #define blue_INTR_NONE      (uint16)(0x0000u)
        #define blue_INTR_RISING    (uint16)(0x0001u)
        #define blue_INTR_FALLING   (uint16)(0x0002u)
        #define blue_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define blue_INTR_MASK      (0x01u) 
#endif /* (blue__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define blue_PS                     (* (reg8 *) blue__PS)
/* Data Register */
#define blue_DR                     (* (reg8 *) blue__DR)
/* Port Number */
#define blue_PRT_NUM                (* (reg8 *) blue__PRT) 
/* Connect to Analog Globals */                                                  
#define blue_AG                     (* (reg8 *) blue__AG)                       
/* Analog MUX bux enable */
#define blue_AMUX                   (* (reg8 *) blue__AMUX) 
/* Bidirectional Enable */                                                        
#define blue_BIE                    (* (reg8 *) blue__BIE)
/* Bit-mask for Aliased Register Access */
#define blue_BIT_MASK               (* (reg8 *) blue__BIT_MASK)
/* Bypass Enable */
#define blue_BYP                    (* (reg8 *) blue__BYP)
/* Port wide control signals */                                                   
#define blue_CTL                    (* (reg8 *) blue__CTL)
/* Drive Modes */
#define blue_DM0                    (* (reg8 *) blue__DM0) 
#define blue_DM1                    (* (reg8 *) blue__DM1)
#define blue_DM2                    (* (reg8 *) blue__DM2) 
/* Input Buffer Disable Override */
#define blue_INP_DIS                (* (reg8 *) blue__INP_DIS)
/* LCD Common or Segment Drive */
#define blue_LCD_COM_SEG            (* (reg8 *) blue__LCD_COM_SEG)
/* Enable Segment LCD */
#define blue_LCD_EN                 (* (reg8 *) blue__LCD_EN)
/* Slew Rate Control */
#define blue_SLW                    (* (reg8 *) blue__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define blue_PRTDSI__CAPS_SEL       (* (reg8 *) blue__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define blue_PRTDSI__DBL_SYNC_IN    (* (reg8 *) blue__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define blue_PRTDSI__OE_SEL0        (* (reg8 *) blue__PRTDSI__OE_SEL0) 
#define blue_PRTDSI__OE_SEL1        (* (reg8 *) blue__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define blue_PRTDSI__OUT_SEL0       (* (reg8 *) blue__PRTDSI__OUT_SEL0) 
#define blue_PRTDSI__OUT_SEL1       (* (reg8 *) blue__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define blue_PRTDSI__SYNC_OUT       (* (reg8 *) blue__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(blue__SIO_CFG)
    #define blue_SIO_HYST_EN        (* (reg8 *) blue__SIO_HYST_EN)
    #define blue_SIO_REG_HIFREQ     (* (reg8 *) blue__SIO_REG_HIFREQ)
    #define blue_SIO_CFG            (* (reg8 *) blue__SIO_CFG)
    #define blue_SIO_DIFF           (* (reg8 *) blue__SIO_DIFF)
#endif /* (blue__SIO_CFG) */

/* Interrupt Registers */
#if defined(blue__INTSTAT)
    #define blue_INTSTAT            (* (reg8 *) blue__INTSTAT)
    #define blue_SNAP               (* (reg8 *) blue__SNAP)
    
	#define blue_0_INTTYPE_REG 		(* (reg8 *) blue__0__INTTYPE)
#endif /* (blue__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_blue_H */


/* [] END OF FILE */
