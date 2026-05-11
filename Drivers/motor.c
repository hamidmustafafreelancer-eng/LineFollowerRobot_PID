/*
this file contains functions implementation for motor driver
Autohor : Hamid Mustafa 
*/

#include "config/pin_config.h"
#include "config/compiler_config.h"
#include "motor.h"

void Motor_Init(void){
    #ifdef __XC8
        PR2 = 124;
        T2CON = 0x05;
        CCP1CON = 0x0C;
        CCP2CON = 0x0C;
        TRISC1 = 0; // Standard XC8 syntax
        TRISC2 = 0;
    #else
        // Use the simplified driver-init we agreed on
        PWM1_Init(4000);
        PWM2_Init(4000);
        PWM1_Start();
        PWM2_Start();
    #endif

    // Direction pins initialization
    L_IN1_Dir = 0; L_IN2_Dir = 0;
    R_IN3_Dir = 0; R_IN4_Dir = 0;
    
    Motor_Stop();
}

void Motor_SetSpeed(short int leftDuty, short int rightDuty){
    // Optimization: PWM_Set_Duty expects 0-255. 
    // If you pass 'short int', ensure it's not negative before sending.
    if(leftDuty < 0) leftDuty = 0;
    if(rightDuty < 0) rightDuty = 0;
    
    PWM1_Set_Duty((uint8_t)leftDuty);
    PWM2_Set_Duty((uint8_t)rightDuty);
}



void Motor_Stop(void){
    #ifdef __XC8
    L_IN1 = 0; L_IN2 = 0;// Set direction pins to 0 to stop the motor

    #else
    // Stop left motor
    L_IN1 = 0; L_IN2 = 0;// Set direction pins to 0 to stop the motor
    PWM1_Set_Duty(0); // Set duty cycle to 0 to stop PWM signal
    // Stop right motor
    R_IN3 = 0;R_IN4 = 0;// Set direction pins to 0 to stop the motor
    PWM2_Set_Duty(0); // Set duty cycle to 0 to stop PWM signal  
    #endif
   
   
    
}

/* logic for movement control :
we use the base speed this make robot move forward at default speed
to move backward we set the speed to negative value
leftspeed= base speed + turn adjustment
rightspeed= base speed - turn adjustment
turn adjustment is a value that we can calculate based on the error from line following sensors or any other control algorithm
*/  

