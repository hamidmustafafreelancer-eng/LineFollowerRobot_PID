/*
 this file define this file defines All finctions /ApIs for ultrasonic sensor driver
it includes the following functions :
1- ultrasonic_init() : to initialize the ultrasonic sensor pins
2- ultrasonic_get_distance_cm() : to get the distance measured by the ultrasonic sensor in cm

Authors : Hamid Mustafa

*/
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

void ultrasonic_init();

unsigned int ultrasonic_get_distance_cm();


#endif