/*
  this file contians functions implementation for IR sensors driver
    Autohor : Hamid Mustafa

*/
#include"config/pin_config.h"
#include "ir_sensors.h"

static signed char last_error = 0;

void IRSensors_Init(void){
    //set IR senors pins as Input 
    //IR_TRIS |= (1<<IR_SENSOR1) |(1<<RI_SENSOR2)| (1<<IR_SENSOR3)|(1<<IR_SENSOR4)|(1<<IR_SENSOR5);
    IR_TRIS |= IR_MASK; // Set lower 5 bits of TRISB as input for IR sensors
}

signed char IRSensors_Read(void){
   //reed IR_sensors port 
   //the sensor is active low (0 when on line, 1 when off line)

    unsigned char IR_state = (~IR_PORT) & IR_MASK;  

    // then claculate the error based on the pattern of active sensors
    switch(IR_state){
        case 0b00100: last_error = 0;  return 0;   // Center
        
        case 0b00110: last_error = 1;  return 1;   // Slightly Right
        case 0b00010: last_error = 2;  return 2;   // Right
        case 0b00011: last_error = 3;  return 3;   // Far Right
        case 0b00001: last_error = 4;  return 4;   // Edge Right
        
        case 0b01100: last_error = -1; return -1;  // Slightly Left
        case 0b01000: last_error = -2; return -2;  // Left
        case 0b11000: last_error = -3; return -3;  // Far Left
        case 0b10000: last_error = -4; return -4;  // Edge Left

        case 0b00000: // Lost line (All sensors see White)
            if (last_error > 0) return 5;  
            if (last_error < 0) return -5; 
            return 0;

        default: return last_error; 
    }
}


/*note :IR sensor is actiive low  
the function IRSensors_Read returns a signed char representing the error from the line position based on the pattern of active sensors.
the error values are defined as follows:
-1: Slightly left (two middle sensors active)
-2: Left (only left middle sensor active)
-3: Far left (two left sensors active)
-4: Edge left (only left edge sensor active)
0: Centered on line (only middle sensor active)
1: Slightly right (two middle sensors active)
2: Right (only right middle sensor active)
3: Far right (two right sensors active)
4: Edge right (only right edge sensor active)
5: Lost line to the right (all sensors see white, but last error was positive)
-5: Lost line to the left (all sensors see white, but last error was negative)
*/

