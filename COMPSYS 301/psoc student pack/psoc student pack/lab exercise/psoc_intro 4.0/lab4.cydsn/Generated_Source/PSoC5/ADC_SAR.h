/*******************************************************************************
* File Name: ADC_SAR.h  
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

#if !defined(CY_PINS_ADC_SAR_H) /* Pins ADC_SAR_H */
#define CY_PINS_ADC_SAR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ADC_SAR_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ADC_SAR__PORT == 15 && ((ADC_SAR__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ADC_SAR_Write(uint8 value);
void    ADC_SAR_SetDriveMode(uint8 mode);
uint8   ADC_SAR_ReadDataReg(void);
uint8   ADC_SAR_Read(void);
void    ADC_SAR_SetInterruptMode(uint16 position, uint16 mode);
uint8   ADC_SAR_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ADC_SAR_SetDriveMode() function.
     *  @{
     */
        #define ADC_SAR_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ADC_SAR_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ADC_SAR_DM_RES_UP          PIN_DM_RES_UP
        #define ADC_SAR_DM_RES_DWN         PIN_DM_RES_DWN
        #define ADC_SAR_DM_OD_LO           PIN_DM_OD_LO
        #define ADC_SAR_DM_OD_HI           PIN_DM_OD_HI
        #define ADC_SAR_DM_STRONG          PIN_DM_STRONG
        #define ADC_SAR_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ADC_SAR_MASK               ADC_SAR__MASK
#define ADC_SAR_SHIFT              ADC_SAR__SHIFT
#define ADC_SAR_WIDTH              1u

/* Interrupt constants */
#if defined(ADC_SAR__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ADC_SAR_SetInterruptMode() function.
     *  @{
     */
        #define ADC_SAR_INTR_NONE      (uint16)(0x0000u)
        #define ADC_SAR_INTR_RISING    (uint16)(0x0001u)
        #define ADC_SAR_INTR_FALLING   (uint16)(0x0002u)
        #define ADC_SAR_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ADC_SAR_INTR_MASK      (0x01u) 
#endif /* (ADC_SAR__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ADC_SAR_PS                     (* (reg8 *) ADC_SAR__PS)
/* Data Register */
#define ADC_SAR_DR                     (* (reg8 *) ADC_SAR__DR)
/* Port Number */
#define ADC_SAR_PRT_NUM                (* (reg8 *) ADC_SAR__PRT) 
/* Connect to Analog Globals */                                                  
#define ADC_SAR_AG                     (* (reg8 *) ADC_SAR__AG)                       
/* Analog MUX bux enable */
#define ADC_SAR_AMUX                   (* (reg8 *) ADC_SAR__AMUX) 
/* Bidirectional Enable */                                                        
#define ADC_SAR_BIE                    (* (reg8 *) ADC_SAR__BIE)
/* Bit-mask for Aliased Register Access */
#define ADC_SAR_BIT_MASK               (* (reg8 *) ADC_SAR__BIT_MASK)
/* Bypass Enable */
#define ADC_SAR_BYP                    (* (reg8 *) ADC_SAR__BYP)
/* Port wide control signals */                                                   
#define ADC_SAR_CTL                    (* (reg8 *) ADC_SAR__CTL)
/* Drive Modes */
#define ADC_SAR_DM0                    (* (reg8 *) ADC_SAR__DM0) 
#define ADC_SAR_DM1                    (* (reg8 *) ADC_SAR__DM1)
#define ADC_SAR_DM2                    (* (reg8 *) ADC_SAR__DM2) 
/* Input Buffer Disable Override */
#define ADC_SAR_INP_DIS                (* (reg8 *) ADC_SAR__INP_DIS)
/* LCD Common or Segment Drive */
#define ADC_SAR_LCD_COM_SEG            (* (reg8 *) ADC_SAR__LCD_COM_SEG)
/* Enable Segment LCD */
#define ADC_SAR_LCD_EN                 (* (reg8 *) ADC_SAR__LCD_EN)
/* Slew Rate Control */
#define ADC_SAR_SLW                    (* (reg8 *) ADC_SAR__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ADC_SAR_PRTDSI__CAPS_SEL       (* (reg8 *) ADC_SAR__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ADC_SAR_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ADC_SAR__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ADC_SAR_PRTDSI__OE_SEL0        (* (reg8 *) ADC_SAR__PRTDSI__OE_SEL0) 
#define ADC_SAR_PRTDSI__OE_SEL1        (* (reg8 *) ADC_SAR__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ADC_SAR_PRTDSI__OUT_SEL0       (* (reg8 *) ADC_SAR__PRTDSI__OUT_SEL0) 
#define ADC_SAR_PRTDSI__OUT_SEL1       (* (reg8 *) ADC_SAR__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ADC_SAR_PRTDSI__SYNC_OUT       (* (reg8 *) ADC_SAR__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ADC_SAR__SIO_CFG)
    #define ADC_SAR_SIO_HYST_EN        (* (reg8 *) ADC_SAR__SIO_HYST_EN)
    #define ADC_SAR_SIO_REG_HIFREQ     (* (reg8 *) ADC_SAR__SIO_REG_HIFREQ)
    #define ADC_SAR_SIO_CFG            (* (reg8 *) ADC_SAR__SIO_CFG)
    #define ADC_SAR_SIO_DIFF           (* (reg8 *) ADC_SAR__SIO_DIFF)
#endif /* (ADC_SAR__SIO_CFG) */

/* Interrupt Registers */
#if defined(ADC_SAR__INTSTAT)
    #define ADC_SAR_INTSTAT            (* (reg8 *) ADC_SAR__INTSTAT)
    #define ADC_SAR_SNAP               (* (reg8 *) ADC_SAR__SNAP)
    
	#define ADC_SAR_0_INTTYPE_REG 		(* (reg8 *) ADC_SAR__0__INTTYPE)
#endif /* (ADC_SAR__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ADC_SAR_H */


/* [] END OF FILE */
