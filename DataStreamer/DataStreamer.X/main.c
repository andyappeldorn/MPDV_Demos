 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"
#include "lightSensor.h"

int main(void)                  // Main application
{
    uint16_t lightSensorValue;  // Contains the most recent light sensor results
    
    SYSTEM_Initialize();        // Initialize - pins, adc, data streamer (all things configured by MCC)
    LS_init();                  // Initializes the light sensor module
    while(1)                    // Main Loop
    {
        LS_timeSlice();         // Called to give the light sensor a time-slice to process.
        if (LS_isIdle())        // If the light sensor is idle, then we want to start sampling
        {
            LS_startSample();   // Start sampling (starts the state machine)
        }
        else                    // Not idle, so check if the conversion is complete
        {
            if (LS_isDone())    // Is the light sensor state done?
            {
                lightSensorValue = LS_getValue();               // Get the value
                DataStreamer.lightSensor = lightSensorValue;    // Set the light sensor debug value
            }
        }
        DBGIO_Toggle();     // Toggles the DBGIO bit    (nice indication of transmission timing)
        LED_Toggle();       // Toggles the LED 
        WriteFrame();       // Send the frame to the PC
    }    
}
