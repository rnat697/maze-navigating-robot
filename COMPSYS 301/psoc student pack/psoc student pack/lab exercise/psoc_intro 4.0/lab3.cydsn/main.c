
/* ========================================
 * Laboratory Exercise 3
 *
 * Program timer to flash LED at 1Hz, use interrupts
 *
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Univ of Auckland.
 *
 * ========================================
*/
#include <project.h>
CY_ISR_PROTO(MyISR);
int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    Timer_1_Start();
//    isr_TC_Start();
    isr_TC_StartEx(MyISR);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LED_Write(1);
    for(;;)
    {
        /* Place your application code here. */

        
    }
}

CY_ISR(MyISR){
    if(LED_Read()){
        LED_Write(0);
        
    }else{
        LED_Write(1);
    }
    
}
/* [] END OF FILE */
