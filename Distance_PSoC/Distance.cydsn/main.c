/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */
#include "project.h"
#include "servo.h"
#include <stdio.h>

// Define constants for LCD display and ultrasonic sensor parameters
#define LCD_CLEAR "                "
#define SOUND_SPEED 340
#define CLOCK_FREQ 12000000
#define LAMBDA 1
#define INTERVAL 100

// Define constants for servo and control
#define SERVO_ID 7
#define KM 1
#define CENTER 400
#define V_SAT 500

// Initialize variables for timeout flag, timer period, and
// servo velocity
int timeout = 0;
uint16 period = 0;
short v = 0;

// Function to trigger the ultrasonic sensor
void trigger()
{
    Tx_Write(1);
    CyDelayUs(100);
    Tx_Write(0);
}

// Function to start counting time
void startcount()
{
    Timer_Start();
    Timer_WriteCounter(period - 1);
}

// Function to end counting time and return elapsed time
uint32 endcount()
{
    uint32 cnt = Timer_ReadCounter();
    Timer_Stop();
    return period - 1 - cnt;
}

// Function to calculate distance in millimeters from elapsed time
long long calculate_millimeter(uint32 cnt)
{
    return ((long long)cnt) * SOUND_SPEED * 1000 * LAMBDA / CLOCK_FREQ / 2;
}

// Interrupt Service Routine for timeout event
CY_ISR(InterruptHandler)
{
    Timer_STATUS; // Read Status register to clear TC bit
    timeout = 1;  // Set timeout flag
    Timer_Stop(); // Stop the Timer
}

int main(void)
{
    // Enable interrupts
    CyGlobalIntEnable; /* Enable global interrupts. */
    TimeoutISR_StartEx(InterruptHandler);

    // variables for distance and velocity measured.
    // variables and strings for LCD display.
    // note: variable velocity is different from the servo velocity variable named v.
    uint32 cnt = 0;
    char distance_str[64], velocity_str[64];
    int distance_int, distance_frac, velocity_int, velocity_frac;
    long long distance = 0, lastdistance = 0, velocity = 0;

    // variable and buffer for USBUART communication.
    uint8 buffer[64];
    int flag_getconfig, flag_cdcready;

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    // initialize all hardware module.
    LCD_Start();
    Clock_Start();
    UART_Start();
    period = Timer_ReadPeriod();
    SetServoLimit(SERVO_ID, 0, 0);

    USBUART_Start(0, USBUART_3V_OPERATION);
    flag_getconfig = USBUART_GetConfiguration();
    USBUART_CDC_Init();

    while (1)
    {
        // Clear timeout flag and LCD screen.
        timeout = 0;
        LCD_Position(0, 0);
        LCD_PrintString(LCD_CLEAR);
        LCD_Position(1, 0);
        LCD_PrintString(LCD_CLEAR);

        // Check if USB configuration is received.
        // This code is different from code example of USBUART.
        // It can prevent the program from being blocked here.
        if (!flag_getconfig)
        {
            flag_getconfig = USBUART_GetConfiguration();
        }

        // Trigger the ultrasonic sensor
        trigger();

        // Wait for Rx to go high or timeout. 
        // Due to the polling-based distance measurement approach, 
        // I've implemented a timeout interrupt to prevent the program 
        // from getting stuck
        while (Rx_Read() == 0 && timeout == 0)
            ;

        // Start counting time
        startcount();

        // Wait for Rx to go low or timeout
        while (Rx_Read() != 0 && timeout == 0)
            ;

        // End counting time and get elapsed time
        cnt = endcount();

        if (timeout == 0)
        {
            // Clear LCD
            LCD_Position(0, 0);
            LCD_PrintString(LCD_CLEAR);
            LCD_Position(0, 0);

            // Update distance and velocity
            lastdistance = distance;
            distance = calculate_millimeter(cnt);
            velocity = (lastdistance - distance) * 1000 / INTERVAL;

            // Calculate and display distance and velocity
            // Note: cannot use %f on PSoC for some reason.
            distance_int = distance / 10;
            distance_frac = (distance % 10);
            velocity_int = velocity / 10;
            velocity_frac = velocity % 10;
            if (velocity_frac < 0)
                velocity_frac = -velocity_frac;
            sprintf(distance_str, "%d.%d cm", distance_int, distance_frac);
            sprintf(velocity_str, "%d.%d cm/s", velocity_int, velocity_frac);
            LCD_Position(0, 0);
            LCD_PrintString("d:");
            LCD_PrintString(distance_str);
            LCD_Position(1, 0);
            LCD_PrintString("v:");
            LCD_PrintString(velocity_str);

            // Turn on LED if distance is less than 100 mm
            if (distance < 100)
            {
                LED_Write(1);
            }
            else
            {
                LED_Write(0);
            }

            // Send data to computer via USBUART
            // Similarly, this method by using cdcready flag can prevent 
            // the program from being blocked.
            sprintf(buffer, "%d %d\n", (int)distance, (int)velocity);
            flag_cdcready = USBUART_CDCIsReady();
            if (flag_cdcready && flag_getconfig)
            {
                USBUART_PutString(buffer);
            }

            // Control the servo to perform harmonic oscillation, 
            // by making acceleration proportional to distance.
            v += KM * (distance - CENTER);
            if (v > V_SAT)
                v = V_SAT;
            else if (v < -V_SAT)
                v = -V_SAT;

            SetServoVelocity(SERVO_ID, v);
        }

        // Delay for specified interval
        CyDelay(INTERVAL);
    }
}
/* [] END OF FILE */
