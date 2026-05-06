/*
this module manages the ultrasonic sensor to detect obstacles and determine the robot's state (SAFE, WARNING, CRITICAL) based on distance readings.
 It provides functions to initialize the sensor, update readings, check if the path is blocked, and get the current distance for display purposes.

 This module acts as a "High-Priority Supervisor."
Author : Hamid Mustafa

*/

#ifndef OBSTACLE_MGR_H
#define OBSTACLE_MGR_H

#include <stdint.h>

// Initialize Ultrasonic parameters
void ObstacleManager_Init(void);

// Reads distance and determines if robot is in 'SAFE', 'WARNING', or 'CRITICAL' state
void ObstacleManager_Update(void);

// Returns 1 if path is blocked (Critical distance reached)
uint8_t ObstacleManager_IsBlocked(void);

// Returns current distance in CM for the Display Manager
uint16_t ObstacleManager_GetDistance(void);

#endif
