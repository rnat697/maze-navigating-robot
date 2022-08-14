/*******************************************************************************
* File Name: Rx_mirror.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Rx_mirror_ALIASES_H) /* Pins Rx_mirror_ALIASES_H */
#define CY_PINS_Rx_mirror_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Rx_mirror_0			(Rx_mirror__0__PC)
#define Rx_mirror_0_INTR	((uint16)((uint16)0x0001u << Rx_mirror__0__SHIFT))

#define Rx_mirror_INTR_ALL	 ((uint16)(Rx_mirror_0_INTR))

#endif /* End Pins Rx_mirror_ALIASES_H */


/* [] END OF FILE */
