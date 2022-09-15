/* ========================================
 * Fully working code: 
 * PWM      : 
 * Encoder  : 
 * ADC      :
 * USB      : port displays speed and position.
 * CMD: "PW xx"
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Univ of Auckland.
 *
 * ========================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <project.h>
//* ========================================
#include "defines.h"
#include "vars.h"
#include "isr_eoc.h"
//* ========================================
void usbPutString(char *s);
void usbPutChar(char c);
void handle_usb();
//* ========================================

CY_ISR_PROTO(isr_eoc_Interrupt_test);

CY_ISR(isr_eoc_Interrupt_test)
{
    #ifdef isr_test_INTERRUPT_INTERRUPT_CALLBACK
        isr_TS_Interrupt_InterruptCallback();
    #endif /* isr_eoc_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START isr_eoc_Interrupt` */
    int8 channel = 0; // connect filter output to pin 0.5 for channel 0 
    uint16 value =  ADC_GetResult16(channel);
    // get value from ADC then convert to DAC to send to external LEDs
    if (value >= 2457) // why      4095 /5v,4095 = x / voltage we want .       4095 from (2^12-1)   2.194v
    {
        LED_Write(1);
    
        blue_Write(1); //red
        rED_Write(0); //blue -.-
    
    }
    
    else{
        LED_Write(0);
        blue_Write(0);
        rED_Write(1);
    }
    /* `#END` */
}
void motorGoStraight(){
    PWM_1_WriteCompare(150); // left wheel near power switch is stronker than right wheel
    PWM_2_WriteCompare(162); // increase the PWM by 12 for it to be able to go straight
}

int main()
{
    

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;
    Timer_TS_Start();
    Timer_Motor_Start();
    isr_motor_Start();
    isr_eoc_StartEx(isr_eoc_Interrupt_test);
    ADC_Start();
    ADC_StartConvert();
    
    LED_Write(0);
    //VDAC8_1_Start();
    
    // Motor PWM
    
    PWM_1_Start();
    PWM_2_Start();
    motorGoStraight();
    
    
// ------USB SETUP ----------------    
#ifdef USE_USB    
    //USBUART_Start(0,USBUART_5V_OPERATION);
#endif        
        
    RF_BT_SELECT_Write(0);

    //usbPutString(displaystring);
    for(;;)
    {
        /* Place your application code here. */
        /*handle_usb();
        if (flag_KB_string == 1)
        {
            usbPutString(line);
            flag_KB_string = 0;
        }   */    
    }   
}
//* ========================================
void usbPutString(char *s)
{
// !! Assumes that *s is a string with allocated space >=64 chars     
//  Since USB implementation retricts data packets to 64 chars, this function truncates the
//  length to 62 char (63rd char is a '!')

#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    s[63]='\0';
    s[62]='!';
    USBUART_PutData((uint8*)s,strlen(s));
#endif
}
//* ========================================
void usbPutChar(char c)
{
#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    USBUART_PutChar(c);
#endif    
}
//* ========================================
void handle_usb()
{
    // handles input at terminal, echos it back to the terminal
    // turn echo OFF, key emulation: only CR
    // entered string is made available in 'line' and 'flag_KB_string' is set
    
    static uint8 usbStarted = FALSE;
    static uint16 usbBufCount = 0;
    uint8 c; 
    

    if (!usbStarted)
    {
        if (USBUART_GetConfiguration())
        {
            USBUART_CDC_Init();
            usbStarted = TRUE;
        }
    }
    else
    {
        if (USBUART_DataIsReady() != 0)
        {  
            c = USBUART_GetChar();

            if ((c == 13) || (c == 10))
            {
//                if (usbBufCount > 0)
                {
                    entry[usbBufCount]= '\0';
                    strcpy(line,entry);
                    usbBufCount = 0;
                    flag_KB_string = 1;
                }
            }
            else 
            {
                if (((c == CHAR_BACKSP) || (c == CHAR_DEL) ) && (usbBufCount > 0) )
                    usbBufCount--;
                else
                {
                    if (usbBufCount > (BUF_SIZE-2) ) // one less else strtok triggers a crash
                    {
                       USBUART_PutChar('!');        
                    }
                    else
                        entry[usbBufCount++] = c;  
                }  
            }
        }
    }    
}


/* [] END OF FILE */
