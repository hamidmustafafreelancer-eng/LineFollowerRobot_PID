#ifndef PID_H
#define PID_H

#include <stdint.h>

// SCALE 100 means a gain of 1.0 is represented as 100
#define PID_SCALE   100

// Output limits for PIC16 PWM (0-255)
#define PID_MAX     255
#define PID_MIN    -255

typedef struct {
    // Tuning Gains (Scaled by 100)
    int16_t kp;
    int16_t ki;
    int16_t kd;

    // State Variables
    int32_t integral_sum;
    int16_t last_error;
    
    // Output Storage
    int16_t output;
} pid_t;

// UML: + SetTunings() / Init
void PID_Init(pid_t *pid, int16_t p, int16_t i, int16_t d);

// UML: + Compute() / Update
int16_t PID_Update(pid_t *pid, int16_t error);

// UML: + Reset()
void PID_Reset(pid_t *pid);

#endif // PID_H
