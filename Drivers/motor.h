/*
this file defines All finctions /ApIs for motor driver 
it includes the following functions :
1- void Motor_Init(void) : to initialize the motor pins and PWM modules
2- void Motor_SetSpeed(unsigned char leftSpeed, unsigned char rightSpeed) : to set the speed of both motors using PWM duty cycle
3- void Motor_SetDirection(unsigned char leftDir, unsigned char rightDir) : to set the direction of both motors (forward, backward, stop)

Autohor : Hamid Mustafa 
*/

#ifndef MOTOR_H
#define MOTOR_H


// Function prototypes for motor control    

void Motor_Init(void);// Initialize motor pins and PWM modules

void Motor_SetSpeed(unsigned char leftSpeed, unsigned char rightSpeed);// Set motor speed (0-100% duty cycle)

void Motor_SetDirection(unsigned char leftDir, unsigned char rightDir);// Set motor direction

void Motor_Stop(void);// Stop both motors


#endif
