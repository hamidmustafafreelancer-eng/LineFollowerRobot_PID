/*
this module handles the display logic for the robot's LCD screen.
 It provides functions to refresh the display with relevant information and show a boot screen on startup.

 Author : Hamid Mustafa
*/

#ifndef DISPLAY_MGR_H
#define DISPLAY_MGR_H

// Formats and prints data to the LCD (Speed, Error, Obstacles)
// Note: This is slow, so it should be called less frequently
void DisplayManager_Refresh(void);

// Briefly shows a splash screen on boot
void DisplayManager_ShowBootScreen(void);

#endif
