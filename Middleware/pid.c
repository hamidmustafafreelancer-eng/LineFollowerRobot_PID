#include <stdint.h>
#include "pid.h"

static int16_t PID_Derivative(pid_t* pid, int16_t error);
static int16_t PID_Integral(pid_t* pid, int16_t error);
static int16_t PID_Clamped_Output(pid_t *pid);

void PID_Init(pid_t *pid)
{
    pid->derivative_state = 0;
    pid->integral_sum = 0;
    pid->output = 0;
    pid->clamped_output = 0;
}

void PID_Update(pid_t* pid, int16_t error)
{
    // Calculate D component
    int16_t D = PID_Derivative(pid, error * KD);
    
    // Calculate I component
    int16_t I = PID_Integral(pid, error * KI);
    
    // Calculate P component
    int16_t P = error * KP;
    
    // Calculate PID output
    pid->output = (int16_t)(((int32_t)P + (int32_t)I + (int32_t)D) / SCALE);
    
    pid->clamped_output = PID_Clamped_Output(pid);
}

/**
 * @brief Calculates derivative term with low-pass filter
 * @param pid - Pointer to PID object
 * @param error - System error
 * @return Derivative term
 */
int16_t PID_Derivative(pid_t *pid, int16_t error)
{
    // Combined equation for Derivative & Low-pass filter
    int16_t D = ((error - pid->derivative_state) / LOW_PASS_TIME_CONST);
    
    // Update derivative state
    pid->derivative_state += D;

    return D;
}

/**
 * @brief Calculates integral term
 * @param pid - Pointer to PID object
 * @param error - System error
 * @return Integral term
 */
int16_t PID_Integral(pid_t *pid, int16_t error)
{
    // is system output saturated
    uint8_t saturated = (pid->output != pid->clamped_output);
    
    // are error & output in the same direction
    uint8_t same_direction = (((int32_t)(pid->output) * (int32_t)error) > 0);
    
    if (!(saturated && same_direction))
    {
        pid->integral_sum += error;
    }
    
    return pid->integral_sum;
}

/**
 * @brief Returns clamped value of PID output
 * @param pid - Pointer to PID object
 * @return Clamped value of PID output
 */
int16_t PID_Clamped_Output(pid_t *pid)
{
    if (pid->output > OUTPUT_CLAMP_POSITIVE)
        return OUTPUT_CLAMP_POSITIVE;
    
    if (pid->output < OUTPUT_CLAMP_NEGATIVE)
        return OUTPUT_CLAMP_NEGATIVE;
    
    return pid->output;
}
