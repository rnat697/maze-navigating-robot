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
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
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


#define rota180 500 //turns
#define rota90Left 250

#define moveSlow 50
#define travelDist 326 // how
#define Q1CHANNEL 3
#define Q2CHANNEL 5 
#define Q3CHANNEL 0
#define Q4CHANNEL 1
#define Q5CHANNEL 2
#define Q6CHANNEL 4

CY_ISR_PROTO(isr_eoc_Interrupt_test);
CY_ISR_PROTO(isr_motor_interrupt_speed);
CY_ISR_PROTO(isr_TS_interrupt_sample);
int convertSensorBinary();
int convertBackBinary();

void motorGoStraight(){
    ////PWM_1_WriteCompare(150); // left wheel near power switch is stronker than right wheel //150 //250 
    //M1_IN2_Write(0);
    PWM_1_WriteCompare(160);//200 //180 //160
    PWM_2_WriteCompare(93); //52 //72 //93
}
void motorSetSpeed(int x){
    ////PWM_1_WriteCompare(150); // left wheel near power switch is stronker than right wheel //150 //250 
    //M1_IN2_Write(0);
    
    //fastest speed
    PWM_1_WriteCompare(200+x);//200 //180 //160
    PWM_2_WriteCompare(52-x); //52 //72 //93
}
void motorGoBackwards(){
    
    //M1_IN2_Write(0);
    PWM_1_WriteCompare(55); //55
    PWM_2_WriteCompare(201); //201
}
void motorStop(){
    PWM_1_WriteCompare(127); 
    PWM_2_WriteCompare(127);
}

void motorTurnLeft(uint8 x){
    // TO DO
    
    PWM_1_WriteCompare(127); //55
    PWM_2_WriteCompare(x); //201
    
    
    
    //255
}

void motorTurnRight(int x){
    // TO DO
    
    PWM_1_WriteCompare(x);//200
    PWM_2_WriteCompare(127); //50

}


void motorCircle(uint8 x){
    // TO DO
    //positive value turns left
    //negative value turns right
    PWM_1_WriteCompare(127+x); //147
    PWM_2_WriteCompare(127+x); //
    
    
    
    //255
}
int changeMotor=0;
int checkLight =0;
int lightState=0;
volatile int lightDetectedFront[3] = {0,0,0};
volatile int lightDetectedBack[3] = {0,0,0};
volatile int counteoc = 0;
volatile int processSensors = 0;
volatile int middle =0;
CY_ISR(isr_eoc_Interrupt_test)
{
    #ifdef isr_test_INTERRUPT_INTERRUPT_CALLBACK
        isr_TS_Interrupt_InterruptCallback();
    #endif /* isr_eoc_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START isr_eoc_Interrupt` */
    int16 valueQ3 =  ADC_GetResult16(Q3CHANNEL);
    int16 valueQ4 =  ADC_GetResult16(Q4CHANNEL);
    int16 valueQ5 =  ADC_GetResult16(Q5CHANNEL);
    
    int16 valueQ1 =  ADC_GetResult16(Q1CHANNEL);
    int16 valueQ2 =  ADC_GetResult16(Q2CHANNEL);
    int16 valueQ6 =  ADC_GetResult16(Q6CHANNEL);
    
    // get value from ADC then convert to DAC to send to external LEDs
    if (counteoc < 10) {
        //2211
        if (valueQ3 >= 2211) {
        //set flag for white light detected
        lightDetectedFront[0] = 1;
        }
        if (valueQ4 >= 2211) {
        //set flag for white light detected
        lightDetectedFront[1] = 1;
        }
    
        if (valueQ5 >= 2211) {
        //set flag for white light detected
        lightDetectedFront[2] = 1;
        }
        
        if (valueQ1 >= 2211) {
        //set flag for white light detected
            lightDetectedBack[1] = 1;
        }
        
        if (valueQ2 >= 2211) {
        //set flag for white light detected
            lightDetectedBack[2] = 1;
        }
                
                
        if (valueQ6 >= 2211) {
        //set flag for white light detected
            lightDetectedBack[0] = 1;
        }
        
        counteoc++;
    } else {
        processSensors = 1;   
       
    }
    /* `#END` */
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

void motorRun(int x){
    
    
    
    //PWM_1_Start();
    //PWM_2_Start();


    //motorStop();
    //CyDelay(time); // so we have time to set the robot up
    motorSetSpeed(x);
    //CyDelay(time);
    motorStop();
    
    //motorGoBackwards();

    
    //CyDelay(2000);
 
    //motorStop();
    //motorCount();//checks count per second.

    
}
CY_ISR(isr_TS_Interrupt_sample)
{
    #ifdef isr_TS_INTERRUPT_INTERRUPT_CALLBACK
        isr_TS_Interrupt_InterruptCallback();
    #endif /* isr_TS_INTERRUPT_INTERRUPT_CALLBACK */ 
        ADC_StartConvert();
    /*  Place your Interrupt code here. */
    /* `#START isr_TS_Interrupt` */

    /* `#END` */
}


int main()
{
    

// --------------------------------    
// ----- INITIALIZATIONS ----------
    CYGlobalIntEnable;
    count  = 0;
    
    ADC_Start();
    Timer_TS_Start();
    Timer_Motor_Start();
    QuadDec_M1_Start();
    QuadDec_M2_Start(); //init the quadencoder,
    //isr_motor_StartEx(isr_motor_interrupt_speed);
    
    isr_TS_StartEx(isr_TS_Interrupt_sample);
    isr_eoc_StartEx(isr_eoc_Interrupt_test);
    
    
    //ADC_StartConvert();
    
    PWM_1_Start();
    PWM_2_Start();
    LED_Write(0);
    motorStop();
    USBUART_Start(0,USBUART_5V_OPERATION)   ; 
    ////////////////////////////////
    
    // Speed//
    //int speed = -33;
    //int time = 2000;
   // motorRun(speed,time);

    /////////////////////////////////////////////
    int lastState=0;
    //usbPutString(displaystring);
     //87cm motor 1 945, motor2 -958. 2seconds.
    //10.8 counts per cm for distance.
   //for speed,43.5cm/s 
    
//    
// ----------      //distance ---------
 int travelDis = 1740;//10.8 * travelDis
  while(QuadDec_M1_GetCounter()<travelDis){
        if (processSensors == 1) {
    
            int operation = convertSensorBinary();
            
    
            switch(operation){
                case 3:// 0 1 1 // Q3 under black
                    motorTurnLeft(50);//decrease go fast used to be 50 by 6
                    LED_Write(1);
                    break;    
                    
                case 6:// 1 1 0 // Q5 under black  
                    motorTurnRight(200);//increase 200 by 6
                    LED_Write(1);
                    break;
                    
                case 5:// 101 // Q4 under black
                    motorSetSpeed(-7); //-40 is original
                    LED_Write(0);
                    break;
            }
            
             processSensors = 0;
            //reset counter

            counteoc = 0;
            //reset flags for lightsensors because it checks every 10 iterations, adds delay/
            lightDetectedFront[0] = 0;
            lightDetectedFront[1] = 0;
            lightDetectedFront[2] = 0;
            lightDetectedBack[0] = 0;
            lightDetectedBack[1] = 0;
            lightDetectedBack[2] = 0;
          
            
    
        }
    }
    motorStop();
    motorCount();
    
    /// ---------End here----------
    
    
    
    
    
    
    
   ///////////////////////////////////////// LINE TRACKING////////
    
//    while(1)
//    {
//        /* Place your application code here. */
//       
//        if (processSensors == 1) {
//                   
//            int operation = convertSensorBinary();
//            int backOps = convertBackBinary();
//
//            switch(operation){
//            //where 1 is on white, 0 is on black.
//                
//                case 7: // 111 // all under white\\
//                    
//                
//              
//                        if(backOps == 7){
//                            
//                             motorCircle(40);
//                            
//                        }
//                        
//                    
//                        else if(backOps == 5){
//                            motorGoStraight();
//                        }   
//                        break;
//                    
//                case 3:// 0 1 1 // Q3 under black
//                    motorTurnLeft(50);//decrease go fast used to be 50 by 6
//                    LED_Write(1);
//                    break;    
//                    
//                case 6:// 1 1 0 // Q5 under black  
//                    motorTurnRight(200);//increase 200 by 6
//                    LED_Write(1);
//                    break;
//                    
//                case 5:// 101 // Q4 under black
//                    motorGoStraight();
//                    LED_Write(0);
//                    break;
//                case 1: // 001 --> left intersection
//                    //lastState=1;
//                    motorStop();
//                    CyDelay(50);
//                    motorTurnLeft(44);
//                    CyDelay(350);
//                    break;
//                case 4: // 100 --> right intersection
//                   // lastState=2;
//                    motorStop();
//                    CyDelay(50);
//                    motorTurnRight(206);
//                    CyDelay(350);
//                    break;
//                    
//                
//                
//                
//                    
//                case 0: // 000 // ALL UNDER black
//                      
//                    motorStop();
//                    break;    
//
//               
//                
//               
//            
//            }
//            
//        
//
//       
//            //reset variable.
//            processSensors = 0;
//            //reset counter
//
//             counteoc = 0;
//            //reset flags for lightsensors because it checks every 10 iterations, adds delay/
//            lightDetectedFront[0] = 0;
//            lightDetectedFront[1] = 0;
//            lightDetectedFront[2] = 0;
//            lightDetectedBack[0] = 0;
//            lightDetectedBack[1] = 0;
//            lightDetectedBack[2] = 0;
//          
//        }
//        
//    }   
    
//////////////////////////////////////
}

  

int convertBackBinary(){

    int value1=0;
    int Q1 = lightDetectedBack[1] ;
    int Q2 = lightDetectedBack[2];
    int Q6 =lightDetectedBack[0];
    value1 =  value1 + lightDetectedBack[1] *2;
    value1 = value1 +  lightDetectedBack[2] *4;
    value1 = value1 + lightDetectedBack[0] *1;

    return value1;

}

int convertSensorBinary()
{
   int value=0;
  int Q3 = lightDetectedFront[0];
  int Q4 = lightDetectedFront[1];
   int Q5 = lightDetectedFront[2];
  value=value + lightDetectedFront[0]*4;
  value=value + lightDetectedFront[1]*2;
  value=value + lightDetectedFront[2]*1;
    return value;
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
    uint8 c = 0; 
    

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
