#include "stdint.h"
#include "PID.h"

static double PID_Derivative(pid_t* pid, double error);
static double PID_Integral(pid_t* pid, double error);
static double PID_Clamped_Output(pid_t *pid);

void PID_Init(pid_t *pid)
{
    pid->derivative_state = 0;
    pid->integral_sum = 0;
    pid->output = 0;
    pid->clamped_output = 0;
}

double PID_Update(pid_t* pid, double error)
{
    // Calculate D component
    double D = PID_Derivative(pid, error) * KD;
    
    // Calculate I component
    double I = PID_Integral(pid, error) * KI;
    
    // Calculate P component
    double P = error * KP;
    
    // Calculate PID output
    pid->output = P + I + D;
    
    pid->clamped_output = PID_Clamped_Output(pid);
    
    // return clamped output
    return pid->clamped_output;
}

/**
 * @brief Calculates derivative term with low-pass filter
 * @param pid - Pointer to PID object
 * @param error - System error
 * @return Derivative term
 */
double PID_Derivative(pid_t *pid, double error)
{
    // Combined equation for Derivative & Low-pass filter
    double D = (error - pid->derivative_state) * LOW_PASS_CUTOFF_FREQ;
    
    // Update derivative sum
    pid->derivative_state += D;

    return D;
}

/**
 * @brief Calculates integral term
 * @param pid - Pointer to PID object
 * @param error - System error
 * @return Integral term
 */
double PID_Integral(pid_t *pid, double error)
{
    // is system output saturated
    uint8_t saturated = (pid->output != pid->clamped_output);
    
    // are error & output in the same direction
    uint8_t same_direction = ((pid->output * error) > 0);
    
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
double PID_Clamped_Output(pid_t *pid)
{
    if (pid->output > OUTPUT_CLAMP_POSITIVE)
        return OUTPUT_CLAMP_POSITIVE;
    
    if (pid->output < OUTPUT_CLAMP_NEGATIVE)
        return OUTPUT_CLAMP_NEGATIVE;
    
    return pid->output;
}
