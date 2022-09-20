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

void motorGoStraight(){
    ////PWM_1_WriteCompare(150); // left wheel near power switch is stronker than right wheel //150 //250 
    //M1_IN2_Write(0);
    PWM_1_WriteCompare(180);//200
    PWM_2_WriteCompare(72); //50
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
            middle = 1;
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
    ///////IF NOT USINNG MOTOR RUN DO PWM START STUFF
    // SO write compare is a measure of speed
    // And Cy delay delays the running of the motor and duration that it travels
    //look at motor RUn config above for more info.
    motorStop();
    CyDelay(2000); // to prep PARTY PART!! WHOOP WHOOP
   /* while(QuadDec_M1_GetCounter()<travelDist){
    //where counter is value we want it to stop at.
        motorGoStraight();
    
    
    }*/

    
    //motorStop();
   // CyDelay(2000); // so we have time to set the robot up
    //motorTurnLeft();
    //motorStop();
    //motorCount();//checks count per second.
     
    
    

    

    
// ------USB SETUP ----------------    
//#ifdef USE_USB    
//    USBUART_Start(0,USBUART_5V_OPERATION);
//#endif        
//        
//    RF_BT_SELECT_Write(0);
//    motorCount();//checks count per second.
    int onLine=0; // tracks if line is between three sensors
    //usbPutString(displaystring);
    while(1)
    {
        /* Place your application code here. */
        
        //if Q3 SENSES BLACK LIGHT BUT Q4 DOES NOT SENSE THE BLACK LIGHT MOVE TOWARDS THE RIGHT TO REALIGN CENTER
    // IF Q3 AND Q4 SENSES TURN 90 DEGREES LEFT - intersection
    // IF Q5 BUT NOT Q4 SENSES BLACK LIGHT MOVE TOWARDS THE LEFT TO REALIGN CENTER
    // IF Q5 AND Q4 TURN 90 DEGREES RIGHT - intersection
       
        if (processSensors == 1) {
            
            //make decision
            
            //checks intersection
            //int leftIntersection= (lightDetectedFront[0] == 1 && lightDetectedFront[1]==1);
            //int rightIntersection=  (lightDetectedFront[2] == 1 && lightDetectedFront[1]==1);
            
           //check intersectin
            ///mazeIntersection(leftIntersection,rightIntersection);
        
            int operation = convertSensorBinary();
            
            if (onLine){
              motorGoStraight();
              LED_Write(0);
            }
            

            
            
            switch(operation){
            //where 1 is on white, 0 is on black.
                
                case 7: // 111 // all under white\\
                    
                    if (onLine==1){
                    
                    motorGoStraight();
                    break;
                    }
                    
                    else{
                    motorStop();
                    break;
                    }
                    
                case 3:// 0 1 1 // Q3 under black
                    onLine=0;
                    motorTurnLeft(50);
                    LED_Write(1);
                    break;    
                    
                case 6:// 1 1 0 // Q5 under black
                    onLine=0;
                    motorTurnRight(200);
                    LED_Write(1);
                    break;
                    
                case 5:// 101 // Q4 under black
                    onLine=1;
                    motorGoStraight();
                    LED_Write(0);
                    break;
                    
                
                
                
                    
                case 0: // 000 // ALL UNDER black
                      
                    motorStop();
                    break;    

               
                
               
            
            }
            
            
            
            
//            if(leftIntersection){
//                motorTurnLeft(55);
//            
//            
//                CyDelay(250);
//            }
//            
//            if(rightIntersection){
//                motorTurnRight(55);
//                
//                CyDelay(250);//small rotation need small time
//            
//            }
            
//            //Slight turns
//            if(lightDetectedFront[0] == 1 && lightDetectedFront[1]==0){
//                motorTurnRight(140);
//                CyDelay(20);//small rotation need small time
//            }
//            
//            if(lightDetectedFront[2] == 0 && lightDetectedFront[1]==1){
//                motorTurnLeft(140);
//                CyDelay(20);//small rotation need small time
//            }

       
            //reset variable.
            processSensors = 0;
            //reset counter

             counteoc = 0;
            //reset flags for lightsensors because it checks every 10 iterations, adds delay/
            lightDetectedFront[0] = 0;
            lightDetectedFront[1] = 0;
            lightDetectedFront[2] = 0;
          
        }
        
    }   
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
