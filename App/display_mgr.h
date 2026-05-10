/*
this module handles the display logic for the robot's LCD screen.
 It provides functions to refresh the display with relevant information and show a boot screen on startup.
 Author : Hamid Mustafa
*/

#ifndef DISPLAY_MGR_H
#define DISPLAY_MGR_H

// Called once in System_Setup
void DisplayManager_Init(void);


// Formats and prints data to the LCD (Speed, Error, Obstacles)
/// Called every 200ms by the Scheduler
void DisplayManager_Refresh(void);

#endif
