// <editor-fold defaultstate="collapsed" desc="File Header">
/***********************************************************************************************************************
 *
 * Filename:   lightSensor.c
 *
 * Global Designator: LS_
 *
 * Contents: Data Visualizer Demo using the Light Sensor on the Atmel I/O1 board connected to an ATtiny3217 Xplained Pro
 * 
 ***********************************************************************************************************************
 * © 2022 Microchip Technology Inc. and its subsidiaries.  You may use this software and any derivatives exclusively
 * with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS
 * SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE,
 * COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF
 * THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON
 * ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID
 * DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 * 
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS. 
 ***********************************************************************************************************************
 *
 * $Log$ Karl Davlin <karl.davlin@microchip.com> Created December 5, 2022, 10:17 AM
 *
 * Last Update:
 *
 * 
 **********************************************************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Include Files">
/* ****************************************************************************************************************** */
/* INCLUDE FILES */

#include "lightSensor.h"
#include "mcc_generated_files/system/system.h"
#include <string.h>

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Macro Definitions">
/* ****************************************************************************************************************** */
/* MACRO DEFINITIONS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Type Definitions">
/* ****************************************************************************************************************** */
/* TYPE DEFINITIONS */

typedef enum
{
    eIDLE,      // Not converting and no data is ready
    eREADING,   // Waiting for the ADC to complete to read the data
    eDONE       // ADC is done and the data is ready to be read
}eState_t;      // Light Sensor State Machine states

typedef struct
{
    uint16_t result;        // ADC result
    eState_t state;         // State machine
    bool     bDataReady;    // Flag indicating data is ready to be read
}lsVars_t;                  // module variables

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Local Function Prototypes">
/* ****************************************************************************************************************** */
/* FUNCTION PROTOTYPES */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Constant Definitions">
/* ****************************************************************************************************************** */
/* CONSTANTS */

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="File Variables - Static">
/* ****************************************************************************************************************** */
/* FILE VARIABLE DEFINITIONS */

static lsVars_t ls; // Local module variables

// </editor-fold>

/* ****************************************************************************************************************** */
/* FUNCTION DEFINITIONS */

// <editor-fold defaultstate="collapsed" desc="void LS_init( void )">
/***********************************************************************************************************************
 *
 * Function Name: LS_init
 *
 * Purpose: Initializes this module.  Must be called once before any other function in this module is called.
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: Enables the ADC
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void LS_init( void )
{
    (void)memset(&ls, 0, sizeof(ls));   // Clear the module variables, the state will be idle
    ADC0_Enable();              
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void LS_timeSlice( void )">
/***********************************************************************************************************************
 *
 * Function Name: LS_timeSlice
 *
 * Purpose: Must be called ever time through the main loop
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: Uses the ADC
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void LS_timeSlice( void )
{
    switch(ls.state)
    {
        case eIDLE: 
        {
            break;
        }
        case eREADING: 
        {
            if (ADC0_IsConversionDone())
            {
                ls.bDataReady = true;
                ls.result = ADC0_GetConversionResult()/64;
                ls.state = eDONE;
            }
            break;
        }
        case eDONE: 
        {
            break;
        }
        default: 
        {
            break;
        }
    }
    DataStreamer.LS_state = (uint16_t)ls.state; // This is the debug part of this, get the state to stream to the PC
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="bool LS_isIdle( void )">
/***********************************************************************************************************************
 *
 * Function Name: LS_isIdle
 *
 * Purpose: returns true is the state is idle
 *
 * Arguments: None
 *
 * Returns: bool - true = idle
 *
 * Side Effects: None
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
bool LS_isIdle( void )
{
    bool bRetVal = false;
    if (eIDLE == ls.state)
    {
        bRetVal = true;
    }
    return(bRetVal);
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="void LS_startSample( void )">
/***********************************************************************************************************************
 *
 * Function Name: LS_startSample
 *
 * Purpose: Starts the state machine by starting the ADC
 *
 * Arguments: None
 *
 * Returns: None
 *
 * Side Effects: ADC starts conversion
 *
 * Reentrant Code: No
 *
 **********************************************************************************************************************/
void LS_startSample( void )
{
   ADC0_StartConversion(ADC_MUXPOS_AIN6_gc);
   ls.state = eREADING;
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="bool LS_isDone( void )">
/***********************************************************************************************************************
 *
 * Function Name: LS_isDone
 *
 * Purpose: returns ture is the result is ready to be read
 *
 * Arguments: None
 *
 * Returns: bool - true = done
 *
 * Side Effects: None
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
bool LS_isDone( void )
{
    bool bRetVal = false;
    if (eDONE == ls.state)
    {
        bRetVal = true;
    }
    return(bRetVal);
}
/* ****************************************************************************************************************** */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="uint16_t LS_getValue( void )">
/***********************************************************************************************************************
 *
 * Function Name: LS_getValue
 *
 * Purpose: Returns the ADC result
 *
 * Arguments: None
 *
 * Returns: uint16_t = ADC result (10-bits of real data)
 *
 * Side Effects: None
 *
 * Reentrant Code: Yes
 *
 **********************************************************************************************************************/
uint16_t LS_getValue( void )
{
    ls.state = eIDLE;
    return(ls.result);
}
/* ****************************************************************************************************************** */
// </editor-fold>

/* ****************************************************************************************************************** */
/* Local Functions */

/* ****************************************************************************************************************** */
/* Event Handlers */

/* ****************************************************************************************************************** */
/* Unit Test Code */
