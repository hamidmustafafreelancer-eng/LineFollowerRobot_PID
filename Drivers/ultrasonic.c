/*
 This file contains the implementation of the ultrasonic sensor driver functions.
 Authors : Hamid Mustafa
*/

#include "ultrasonic.h"
#include "pin_config.h"

void ultrasonic_init() {
    // Set TRIG_PIN as output and ECHO_PIN as input
    TRIG_TRIS = 0; // Output
    ECHO_TRIS = 1; // Input
    // Ensure TRIG_PIN is low
    TRIG_PIN = 0;
}

unsigned int ultrasonic_get_distance_cm() {
    // Implementation for getting distance in cm

    TRIG_PIN = 1; // Set TRIG_PIN high
    Delay_us(10); // Wait for 10 microseconds
    TRIG_PIN = 0; // Set TRIG_PIN low

    
    // Wait for ECHO_PIN to go high
    TMR1H = 0; TMR1L = 0; // Reset timer
    WHILE (ECHO_PIN == 0); // Wait for the echo to start


    T1CON.TMR1ON = 1; // Start Timer
    // Wait for ECHO_PIN to go low
    WHILE (ECHO_PIN == 1); // Wait for the echo to end
    T1CON.TMR1ON = 0; // Stop Timer
    

    // Calculate distance
    unsigned int time_taken =(TMR1H << 8) | TMR1L;
    unsigned int ditance_cm = (time_taken * 34300) / (2 * 1000000); // Convert to cm
    return ditance_cm;

}


/*
note : ultrasonic work by sending a short pulse (10 msec)  on trigger pin 
       then it waits for the echo pin to go high, and measures the time it stays high 
       then it calculate the distance by using the formula : distance = (time * speed of sound) / 2
       where speed of sound is approximately 34300 cm/s at room temperature
*/