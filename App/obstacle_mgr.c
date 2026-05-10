#include "obstacle_mgr.h"
#include "ultrasonic.h"
#include "buzzer.h"
#include "motor.h"

// Private state variables (Global to this file to save stack space)
static uint8_t distance_cm = 250; // Default to a safe distance
static uint8_t is_blocked = 0;

void ObstacleManager_Init(void) {
    Ultrasonic_Init();
    Buzzer_Init();
    is_blocked = 0;
}

/**
 * Logic:
 * 100cm > Distance > 30cm -> ALERT (Buzzer)
 * Distance < 30cm -> STOP
 */
 
void ObstacleManager_Update(void) {
    distance_cm = Ultrasonic_GetDistance_cm();
    
    // 1. Determine Safety State
    if (distance_cm < 30) {
        is_blocked = 1;
    } else {
        is_blocked = 0;
    }

    // 2. Determine Alert State (Fixes the "Stuck Buzzer" bug)
    // Buzzer should ONLY be on if in warning zone, and OFF otherwise.
    if (distance_cm >= 30 && distance_cm < 100) {
        Buzzer_On();
    } else {
        Buzzer_Off();
    }
    //motor stop will be handled in the scheduler based on the is_blocked flag,
    // so we don't stop the motor here to avoid conflicts with other modules that might want to control the motor.

}



bool ObstacleManager_IsBlocked(void){
    return is_blocked;
}

uint8_t ObstacleManager_IsCritical(void){
    return (distance_cm < 30) ? 1 : 0;
} // Returns 1 if < 30cm
