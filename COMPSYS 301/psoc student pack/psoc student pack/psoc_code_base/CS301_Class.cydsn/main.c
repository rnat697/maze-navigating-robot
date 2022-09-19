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

#define rotaSpeed 15 
#define rota180 500 //turns
#define rota90Left 250

#define moveSlow 50
#define travelDist 326 // how

CY_ISR_PROTO(isr_eoc_Interrupt_test);
CY_ISR_PROTO(isr_motor_interrupt_speed);

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
    if (value >= 2211) // why      5v/4095 gives interval ,voltage we want *interval = adc value/ .       4095 from (2^12-1)   2.194v //old was 2457
    {
        LED_Write(1);   
    
    }
    
    else{
        LED_Write(0);

    }
    /* `#END` */
}
void motorGoStraight(){
    ////PWM_1_WriteCompare(150); // left wheel near power switch is stronker than right wheel //150 //250 
    //M1_IN2_Write(0);
    PWM_1_WriteCompare(200);//202
    PWM_2_WriteCompare(50); //52
}
void motorGoBackwards(){
    
    //M1_IN2_Write(0);
    PWM_1_WriteCompare(55); //55
    PWM_2_WriteCompare(201); //201
}
void motorStop(){
    PWM_1_WriteCompare(128); // left wheel near power switch is stronker than right wheel
    PWM_2_WriteCompare(125);
}

void motorTurnLeft(){
    // TO DO
    
    PWM_1_WriteCompare(rotaSpeed); //55
    PWM_2_WriteCompare(125); //201
    CyDelay(rota90Left);
    
    
    
    //255
}

void motorTurnRight(){
    // TO DO
   
}

// NEED TO INCREASE/DECREASE SPEED TOO
// AND IMPLEMENT LIGHT SENSOR THINGS
volatile static int8 count;
CY_ISR(isr_motor_interrupt_speed)
{
    #ifdef isr_motor_INTERRUPT_INTERRUPT_CALLBACK
        isr_motor_Interrupt_InterruptCallback();
    #endif /* isr_motor_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START isr_motor_Interrupt` */
      /*int16 currCountMotor2 = QuadDec_M2_GetCounter();
      int16 currCountMotor1 = QuadDec_M1_GetCounter();  
      
     speedMotor1 = (currCountMotor1 - prevcountMotor1) / 0.2;
     speedMotor2 = (currCountMotor2 - prevcountMotor2) / 0.2;
    
      prevcountMotor1 = currCountMotor1;
      prevcountMotor2 = currCountMotor2;*/
    
    /* `#END` */
}
void motorCount(){
    int16 beginningCountMotor1 = 0;
    int16 beginningCountMotor2 = 0;
    int16 endCountMotor2 = QuadDec_M2_GetCounter();
    int16 endCountMotor1 = QuadDec_M1_GetCounter();
    char motor1String[10000]; 
    sprintf(motor1String,"Motor 1 - start count: %d, end count: %d \n", beginningCountMotor1, endCountMotor1);
    char motor2String[10000];
    sprintf(motor2String,"Motor 2 - start count: %d, end count: %d \n", beginningCountMotor2 , endCountMotor2);
    
    usbPutString(motor1String);
    usbPutString(motor2String);

}

void motorRun(){
    
    
    
    PWM_1_Start();
    PWM_2_Start();


    motorStop();
    CyDelay(2000); // so we have time to set the robot up
    motorGoStraight();
    CyDelay(2000);
    motorStop();
    
    //motorGoBackwards();

    
    //CyDelay(2000);
 
    //motorStop();
    //motorCount();//checks count per second.

}



int main()
{
    

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;
    count  = 0;
    
   
    Timer_TS_Start();
    Timer_Motor_Start();
    QuadDec_M1_Start();
    QuadDec_M2_Start(); //init the quadencoder,
    isr_motor_StartEx(isr_motor_interrupt_speed);
    isr_eoc_StartEx(isr_eoc_Interrupt_test);
    
    
    ADC_Start();
    ADC_StartConvert();
    
    PWM_1_Start();
    PWM_2_Start();
    
    LED_Write(0);
    //VDAC8_1_Start();
   
    //motorRun();
     
    ///////IF NOT USINNG MOTOR RUN DO PWM START STUFF
    // SO write compare is a measure of speed
    // And Cy delay delays the running of the motor and duration that it travels
    //look at motor RUn config above for more info.
    motorStop();
    CyDelay(2000); // to prep
    while(QuadDec_M1_GetCounter()<travelDist){
    //where counter is value we want it to stop at.
        motorGoStraight();
    
    
    }

    
    //motorStop();
   // CyDelay(2000); // so we have time to set the robot up
    //motorTurnLeft();
    motorStop();
    //motorCount();//checks count per second.
     
    
    

    

    
// ------USB SETUP ----------------    
#ifdef USE_USB    
    USBUART_Start(0,USBUART_5V_OPERATION);
#endif        
        
    RF_BT_SELECT_Write(0);
    motorCount();//checks count per second.

    //usbPutString(displaystring);
    while(1)
    {
        /* Place your application code here. */
        /*handle_usb();
        if (flag_KB_string == 1)
        {
            usbPutString(line);
            flag_KB_string = 0;
        }  */
        
         // if counts >=120
        //stop motor.
        
        
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
