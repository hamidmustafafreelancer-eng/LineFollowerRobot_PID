#include "line_follower.h"
#include "ir_sensor.h"
#include "motor.h"
#include "pid.h"

// Global PID instance for the line follower
static pid_t robot_pid;

void LineFollower_Init() {
    // Initialize PID with specific gains (Scaled by 100)
    // Example: Kp=1.8 (180), Ki=0.01 (1), Kd=2.5 (250)
    PID_Init(&robot_pid, 180, 1, 250);
}

signed char LineFollower_ReadLineError() {
    // Wrapper for the Driver function we built
    return IRSensors_Read();
}

void LineFollower_RequestCorrection() {
    signed char error;
    int16_t correction;
    int16_t l_speed, r_speed;

    // 1. Get the current position (The "Brain" perceives)
    error = LineFollower_ReadLineError();

    // 2. Get the PID correction (The "Logic" calculates)
    correction = PID_Update(&robot_pid, (int16_t)error);

    // 3. Apply the Differential Steering Logic
    l_speed = BASE_SPEED + correction;
    r_speed = BASE_SPEED - correction;

    // 4. Safety Clamping (Don't exceed PWM limits)
    if (l_speed > MAX_SPEED) l_speed = MAX_SPEED;
    if (l_speed < 0)         l_speed = 0;
    
    if (r_speed > MAX_SPEED) r_speed = MAX_SPEED;
    if (r_speed < 0)         r_speed = 0;

    // 5. Output to Hardware (The "Feet" move)
    Motor_SetDirection(1, 1); // Always forward during line follow
    Motor_SetSpeed((unsigned char)l_speed, (unsigned char)r_speed);
}
