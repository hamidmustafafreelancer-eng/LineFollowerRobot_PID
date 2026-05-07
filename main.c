/*
    main.c
    ----------------------------------------------------------------------------
    Main application entry point for the Industrial Line Follower Robot.

    System Architecture:
    - Cooperative Scheduler
    - Interrupt-driven timing using Timer0
    - Layered firmware structure (Drivers + Application Layer)

    Design Goals:
    - Fast and stable PID control
    - Non-blocking execution
    - Safety-first obstacle handling
    - Separation between control logic and UI updates

    Execution Model:
    1. Perception  -> Read sensors
    2. Decision    -> Evaluate robot state
    3. Action      -> Control motors / alerts
    4. Telemetry   -> Refresh LCD at low priority

    Target MCU:
    PIC16F877A @ 8MHz

    Author:
    Hamid Mustafa
    
*/

#include "config/pin_config.h"

#include "scheduler.h"

#include "motor.h"
#include "buzzer.h"

#include "line_follower.h"
#include "obstacle_mgr.h"
#include "display_mgr.h"


/*
    System_Setup()
    ----------------------------------------------------------------------------
    Initializes the complete firmware stack.

    Initialization Order:
    1. MCU digital configuration
    2. Clear output ports
    3. Initialize hardware drivers
    4. Initialize application modules
    5. Start scheduler heartbeat LAST

    NOTE:
    Interrupts begin firing after Scheduler_Init().
*/
static void System_Setup(void) {

    
    // 1. Configure MCU Pins

    // Configure PORTA and PORTE as digital I/O
    // Required for IR sensors and general GPIO usage
    ADCON1 = 0x06;


    // 2. Clear All Ports

    // Prevent undefined startup states
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;

    // 3. Initialize Hardware Drivers
    

    // Each driver configures its own TRIS registers internally
    Motor_Init();
    Buzzer_Init();


    // 4. Initialize Application Modules

    LineFollower_Init();

    // Ultrasonic module must implement timeout protection
    // to avoid blocking if sensor fails
    ObstacleManager_Init();

    DisplayManager_Init();

    // 5. Start System Scheduler LAST

    // Starts Timer0 heartbeat and enables interrupts
    Scheduler_Init();
}


/*
    
    main()
    
    Main control loop.

    Scheduler Strategy:
    - High Priority Tasks  -> 20ms
    - Low Priority Tasks   -> 200ms

    Using task counters instead of simple flags prevents missed
    task execution if the CPU becomes temporarily busy.
    
*/
void main() {

    System_Setup();

    while(1) {

        // HIGH PRIORITY TASKS (20ms)
    
        if(task_20ms_count) {

            // Consume one scheduled event
            task_20ms_count--;

            // STEP 1: Perception
            

            // Update obstacle detection state
            ObstacleManager_Update();
            
            // STEP 2: Alerts
            
            // Handle buzzer warnings
            ObstacleManager_HandleAlerts();

            // STEP 3: Decision + Action

            // Safety has highest priority
            if(ObstacleManager_IsBlocked()) {

                // Immediate stop if obstacle detected
                Motor_Stop();
            }
            else {
                // Normal line following behavior
                // Internally performs:
                // IR Read -> PID Compute -> Motor Update
                LineFollower_RequestCorrection();
            }
        }


        
        // LOW PRIORITY TASKS (200ms)
        if(task_200ms_count) {

            // Consume one scheduled event
            task_200ms_count--;


            // UI / Telemetry
            // LCD updates are intentionally slow priority
            // to avoid affecting PID timing
            DisplayManager_Refresh();
        }


        //----------------------------------------------------------------------
        // IDLE LOOP
        //----------------------------------------------------------------------
        // CPU remains free here until next scheduled task
        // Future improvement:
        // Low-power sleep mode could be added here
    }
}