/*
  this file contains the implementation of the DisplayManager module, 
  which is responsible for updating the LCD display with real-time information about the robot's status,
   such as line following error, speed, and obstacle distance. 
   The DisplayManager_Init function initializes the LCD and prints static labels, 
   while the DisplayManager_Refresh function updates the dynamic values and visual indicators based on data from the LineFollower and ObstacleManager modules.
  The refresh function is designed to be called every 200ms by the Scheduler,
   balancing the need for up-to-date information with the performance constraints of the LCD.
*/


#include "display_mgr.h"
#include "line_follower.h"
#include "obstacle_mgr.h"

// We use MikroC's built-in conversions
#include <built_in.h>

void DisplayManager_Init(void) {
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    
    // Print static labels once to save CPU time during Refresh
    Lcd_Out(1, 1, "E:0");     // Error label
    Lcd_Out(1, 8, "S:150");   // Speed label
    Lcd_Out(2, 1, "DIST:---"); // Distance label
}

void DisplayManager_Refresh(void) {
    char txt[7]; // Buffer for conversion strings
    signed char err = LineFollower_GetLastKnownError();
    uint8_t dist = ObstacleManager_GetDistance();
    
    // 1. Update Error Value (Position 1, 3)
    IntToStr(err, txt);
    Lcd_Out(1, 3, Ltrim(txt)); 
    Lcd_Out(1, 6, " "); // Eraser for shifting digits

    // 2. Update Distance (Position 2, 6)
    ByteToStr(dist, txt);
    Lcd_Out(2, 6, Ltrim(txt));
    Lcd_Out(2, 9, "cm "); // Unit and eraser

    // 3. Update Visual Direction (Position 2, 11)
    if (err > 1)       Lcd_Out(2, 11, "[RGHT]");
    else if (err < -1) Lcd_Out(2, 11, "[LEFT]");
    else               Lcd_Out(2, 11, "[CENT]");
    
    // 4. Handle Obstacle Warning Overlay
    if (ObstacleManager_IsBlocked()) {
        Lcd_Out(1, 14, "!!!"); // Small visual alarm
    } else {
        Lcd_Out(1, 14, "   "); // Clear alarm
    }
}
/*
the logic for display is as follows:
- The LCD is initialized with static labels for error (E:), speed (S:), and distance (DIST:).
- The DisplayManager_Refresh function updates the error value, distance, and a visual direction indicator 
based on the last known error from the LineFollower module and the distance from the ObstacleManager module.
- If the error is greater than 1, it shows "[RGHT]", if less than -1, it shows "[LEFT]", and if between -1 and 1, it shows "[CENT]".
- Additionally, if the ObstacleManager indicates that the path is blocked, it displays "!!!" as a visual warning on the LCD.
*/