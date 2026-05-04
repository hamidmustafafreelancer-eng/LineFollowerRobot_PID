#include "pid.h"

void PID_Init(pid_t *pid, int16_t p, int16_t i, int16_t d) {
    pid->kp = p;
    pid->ki = i;
    pid->kd = d;
    PID_Reset(pid);
}

void PID_Reset(pid_t *pid) {
    pid->integral_sum = 0;
    pid->derivative_state = 0;
    pid->output = 0;
}

int16_t PID_Update(pid_t *pid, int16_t error) {
    int32_t p_term, i_term, d_term;
    int32_t total_out;
    int16_t clamped_out;

    // 1. Proportional Term
    p_term = (int32_t)error * pid->kp;

    // 2. Integral Term with Anti-Windup Logic
    // We only add to the integral if the output isn't already saturated
    // This prevents the "spinning circle" effect after a sharp turn
    if (!((pid->output >= PID_MAX && error > 0) || 
          (pid->output <= PID_MIN && error < 0))) {
        pid->integral_sum += error;
    }
    i_term = pid->integral_sum * pid->ki;

    // 3. Derivative Term (Change in Error)
    // Note: We multiply by KD first to maintain precision before scaling
    d_term = (((int32_t)error * pid->kd) - pid->derivative_state) / PID_LP_FILTER_TIME_CONSTANT;
    pid->derivative_state += d_term;

    // 4. Combine and Scale back down
    total_out = (p_term + i_term + d_term) / PID_SCALE;

    // 5. Hard Clamping to PWM Limits
    if (total_out > PID_MAX)  clamped_out = PID_MAX;
    else if (total_out < PID_MIN) clamped_out = PID_MIN;
    else clamped_out = (int16_t)total_out;

    pid->output = clamped_out; // Store for the next Anti-Windup check
    return clamped_out;
}
