/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.0.1
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

static void (*PB3_InterruptHandler)(void);
static void (*PB2_InterruptHandler)(void);
static void (*PA6_InterruptHandler)(void);
static void (*PB4_InterruptHandler)(void);
static void (*PB5_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{
  /* DIR Registers Initialization */
    PORTA.DIR = 0x0;
    PORTB.DIR = 0x34;
    PORTC.DIR = 0x0;

  /* OUT Registers Initialization */
    PORTA.OUT = 0x0;
    PORTB.OUT = 0x14;
    PORTC.OUT = 0x0;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x0;
    PORTA.PIN1CTRL = 0x0;
    PORTA.PIN2CTRL = 0x0;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x0;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x0;
    PORTB.PIN0CTRL = 0x0;
    PORTB.PIN1CTRL = 0x0;
    PORTB.PIN2CTRL = 0x0;
    PORTB.PIN3CTRL = 0x0;
    PORTB.PIN4CTRL = 0x0;
    PORTB.PIN5CTRL = 0x8;
    PORTB.PIN6CTRL = 0x0;
    PORTB.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x0;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;

  /* PORTMUX Initialization */
    PORTMUX.CTRLA = 0x0;
    PORTMUX.CTRLB = 0x0;
    PORTMUX.CTRLC = 0x0;
    PORTMUX.CTRLD = 0x0;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    PB3_SetInterruptHandler(PB3_DefaultInterruptHandler);
    PB2_SetInterruptHandler(PB2_DefaultInterruptHandler);
    PA6_SetInterruptHandler(PA6_DefaultInterruptHandler);
    PB4_SetInterruptHandler(PB4_DefaultInterruptHandler);
    PB5_SetInterruptHandler(PB5_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for PB3 at application runtime
*/
void PB3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PB3_InterruptHandler = interruptHandler;
}

void PB3_DefaultInterruptHandler(void)
{
    // add your PB3 interrupt custom code
    // or set custom function using PB3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PB2 at application runtime
*/
void PB2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PB2_InterruptHandler = interruptHandler;
}

void PB2_DefaultInterruptHandler(void)
{
    // add your PB2 interrupt custom code
    // or set custom function using PB2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PA6 at application runtime
*/
void PA6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PA6_InterruptHandler = interruptHandler;
}

void PA6_DefaultInterruptHandler(void)
{
    // add your PA6 interrupt custom code
    // or set custom function using PA6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PB4 at application runtime
*/
void PB4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PB4_InterruptHandler = interruptHandler;
}

void PB4_DefaultInterruptHandler(void)
{
    // add your PB4 interrupt custom code
    // or set custom function using PB4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PB5 at application runtime
*/
void PB5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PB5_InterruptHandler = interruptHandler;
}

void PB5_DefaultInterruptHandler(void)
{
    // add your PB5 interrupt custom code
    // or set custom function using PB5_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT6_bm)
    {
       PA6_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTB_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTB.INTFLAGS & PORT_INT3_bm)
    {
       PB3_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT2_bm)
    {
       PB2_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT4_bm)
    {
       PB4_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT5_bm)
    {
       PB5_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTB.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

/**
 End of File
*/