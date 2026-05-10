/*this module manages the ultrasonic sensor to detect obstacles and determine the robot's state (SAFE, WARNING, CRITICAL) based on distance readings.
    It provides functions to initialize the sensor, update readings, check if the path is blocked, and get the current distance for display purposes.

    This module acts as a "High-Priority Supervisor."
    Author : Hamid Mustafa
*/

#ifndef OBSTACLE_MGR_H
#define OBSTACLE_MGR_H

#include <stdint.h>




// UML Definitions
void ObstacleManager_Init(void);
void ObstacleManager_Update(void); // To be called in the loop

// APIs for the Scheduler
uint8_t ObstacleManager_IsCritical(void); // Returns 1 if < 30cm
void ObstacleManager_HandleAlerts(void);  // Handles Buzzer logic

bool ObstacleManager_IsBlocked(void); // Returns 1 if < 30cm, used for motor control

#endif

