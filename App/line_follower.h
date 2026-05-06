/*
this file defines All finctions /ApIs for line follower application
This module handles the logic of staying on the path.
Author : Hamid Mustafa

*/

#ifndef LINE_FOLLOW_APP_H
#define LINE_FOLLOW_APP_H

#include "pid.h"

// Configuration Constants
#define BASE_SPEED    150   // Cruising speed (0-255)
#define MAX_SPEED     230   // Safety cap
#define MIN_SPEED     30    // Minimum to keep motors turning

// Function Prototypes from UML
void LineFollower_Init();
void LineFollower_RequestCorrection();

// Helper logic
signed char LineFollower_ReadLineError();

#endif
