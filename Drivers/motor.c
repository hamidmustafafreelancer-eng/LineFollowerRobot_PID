/*
this file contains functions implementation for motor driver
Autohor : Hamid Mustafa 
*/
#include"config/pin_config.h"
#include"motor.h"


void Motor_Init(void){
    // Set motor direction pins as output
    MOTOR_DIR_TRIS &= ~(1 << L_IN1) & ~(1 << L_IN2) & ~(1 << R_IN3) & ~(1 << R_IN4);
    // Set PWM pins as output
    MOTOR_PWM_TRIS &= ~(1 << L_PWM) & ~(1 << R_PWM);
    // Initialize PWM modules (assuming MikroC PWM library is used)
    PWM1_Init(5000); // Initialize PWM1 for left motor at 5kHz
    PWM2_Init(5000); // Initialize PWM2 for right motor at 5kHz
    PWM1_Start();
    PWM2_Start();
    // Stop motors initially
    Motor_Stop();
}

void Motor_SetDirection(unsigned char leftDir, unsigned char rightDir) {
    // Left Motor Logic
    if (leftDir == 1) { L_IN1 = 1; L_IN2 = 0;} // Forward 
    else {L_IN1 = 0; L_IN2 = 1;} //Backward
    
    // Right Motor Logic
    if (rightDir == 1) {R_IN3 = 1; R_IN4 = 0; } // Forward
    else {R_IN3 = 0; R_IN4 = 1;} // Backward
    
}


void Motor_SetSpeed(short int   leftSpeed, short int rightSpeed){
    // left motor speed control
    PWM1_Set_Duty(leftDuty);
    //right motor speed control
    PWM2_Set_Duty(rightDuty);
}



void Motor_Stop(void){
    // Stop left motor
    L_IN1 = 0; L_IN2 = 0;// Set direction pins to 0 to stop the motor
    PWM1_Set_Duty(0); // Set duty cycle to 0 to stop PWM signal
    // Stop right motor
    R_IN3 = 0;R_IN4 = 0;// Set direction pins to 0 to stop the motor
    PWM2_Set_Duty(0); // Set duty cycle to 0 to stop PWM signal
}

/* logic for movement control :
we use the base speed this make robot move forward at default speed
to move backward we set the speed to negative value
leftspeed= base speed + turn adjustment
rightspeed= base speed - turn adjustment
turn adjustment is a value that we can calculate based on the error from line following sensors or any other control algorithm
*/  

//note motor speed is controlled by PWM duty cycle (0-100%)
//we need to use 10 bit resolution for PWM (0-1023) in MikroC, so we will convert percentage to 0-1023 range
//convert percentage to 0-1023 range by multiplying by 10.23 (1023/100)