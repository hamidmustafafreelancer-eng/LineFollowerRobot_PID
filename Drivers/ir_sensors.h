/*
this file defines All finctions /ApIs for IR sensors driver
it includes the following functions :
1- void IRSensors_Init(void) : to initialize the IR sensor pins
2- unsigned char IRSensors_Read(void) : to read the state of all IR sensors and return a byte where each bit represents a sensor state (1 for active, 0 for inactive)
3-conevert the byte to a more usable format for line following control algorithms


  Autohor : Hamid Mustafa 
*/

#ifndef IR_SENSORS_H
#define IR_SENSORS_H

void IRSensors_Init(void);// Initialize IR sensor pins


signed char IRSensors_Read(void); // Read the state of all IR sensors




#endif 