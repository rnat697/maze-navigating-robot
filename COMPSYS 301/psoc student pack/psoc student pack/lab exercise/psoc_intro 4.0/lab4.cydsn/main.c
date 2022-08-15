
/* ========================================
 * Laboratory Exercise 4
 *
 * Program a UART to receive the string from a RF receiver.
 * The RF receiver : 57.6k b/s, 8b, no parity, no flow control, one start and one stop bit
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
#include <stdio.h>
#include <ADC_SAR_1.h>
#include "VDAC8_1.h"

//* ========================================
#define TOGGLE_LED LED_Write(~LED_Read())
#define PACKETSIZE 32
#define RXSTRINGSIZE 255

#define FALSE 0
#define TRUE 1

#define BUF_SIZE 64 // USBUART fixed buffer size
#define CHAR_NULL '0'
#define CHAR_BACKSP 0x08
#define CHAR_DEL 0x7F
#define CHAR_ENTER 0x0D
#define LOW_DIGIT '0'
#define HIGH_DIGIT '9'

#define SOP 0xaa
//* ========================================
uint8 flag_rx = 0;
uint8 flag_packet = 0;
uint8 outputC;
uint8 flag_KB_string = 0;
//* ========================================
char rf_string[RXSTRINGSIZE];
char displaystring[BUF_SIZE] = "UART Lab Exercise 4\n";
char line[BUF_SIZE], entry[BUF_SIZE];
uint8 usbBuffer[BUF_SIZE];
//* ========================================
typedef struct data_main {
	int8            rssi;	
    uint8           index;			// index number of packet. incremented number
	uint16			robot_xpos;	 	// 
	uint16			robot_ypos;		//
    uint16         robot_orientation;
	uint16			g0_xpos;		//
	uint16			g0_ypos;		//
	uint16			g0_speed;		//
	uint16		g0_direction;	//
	uint16			g1_xpos;		//
	uint16			g1_ypos;		//
	uint16			g1_speed;		//
    uint16		g1_direction;	//
    uint16			g2_xpos;		//
    uint16			g2_ypos;		//
    uint16			g2_speed;		//
    uint16		g2_direction;	//
} vtype1;

struct data_main system_state;
//* ========================================



//* ========================================
void usbPutString(char *s);
void usbPutChar(char c);
void handle_rx_binary();
void handle_rx_ascii();
void handle_usb();
//* ========================================
CY_ISR_PROTO(isr_1_Interrupt_custom);
int main()
{
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    Timer_1_Start();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ADC_SAR_1_Start();
    isr_1_StartEx(isr_1_Interrupt_custom);
    ADC_SAR_1_StartConvert();
    //ADC_SAR_1_IRQ_StartEx(isr_1_Interrupt_custom);
    //ADC_SAR_1_IRQ_Enable();
    VDAC8_1_Start();
    for(;;)
    {
        
        
        /* Place your application code here. */
        
  
}
    }
uint16_t count = 0;
uint8_t test = 0;
CY_ISR(isr_1_Interrupt_custom)
{
    #ifdef isr_1_INTERRUPT_INTERRUPT_CALLBACK
        isr_1_Interrupt_InterruptCallback();
    #endif /* isr_1_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START isr_1_Interrupt` */
            
        LED_Write(~LED_Read());
        uint8 result = ADC_SAR_1_GetResult8();
        VDAC8_1_SetValue(result);
        
        
        isr_1_ClearPending();
    /* `#END` */
}
