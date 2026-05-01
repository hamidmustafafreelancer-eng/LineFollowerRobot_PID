#include "stdint.h"
#include "PID.h"

static double pid_derivative(pid_t* pid, double error);
static double pid_integral(pid_t* pid, double error);
static double pid_clamped_output(pid_t *pid);

void pid_init(pid_t *pid)
{
    pid->derivative_state = 0;
    pid->integral_sum = 0;
    pid->output = 0;
}

double pid_update(pid_t* pid, double error)
{
    // Three components
    double P, I, D;
    
    // Calculate P component
    P = error * pid->Kp;
    
    // Calculate I component
    I = pid_integral(pid, error) * pid->Ki;
    
    // Calculate D component
    D = pid_derivative(pid, error) * pid->Kd;
    
    // Calculate PID output
    pid->output = P + I + D;
    
    pid->clamped_output = pid_clamped_output(pid);
    
    // return clamped output
    return pid->clamped_output;
}

/**
 * @brief Calculates derivative term with low-pass filter
 * @param pid - Pointer to PID object
 * @param error - System error
 * @return Derivative term
 */
double pid_derivative(pid_t *pid, double error)
{
    // Derivative term
    double D;
    
    // Combined equation for Derivative & Low-pass filter
    D = (error - pid->derivative_state) * pid->low_pass_cutoff_freq;
    
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
double pid_integral(pid_t *pid, double error)
{
    double unclamped = pid->output;
    double clamped = pid->clamped_output;
    
    uint8_t saturated = (unclamped != clamped);
    
    // are error & output in the same direction
    uint8_t same_direction = ((pid->output * error) > 0);
    
    uint8_t hold_integral = (saturated && same_direction);
    
    if (!hold_integral)
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
double pid_clamped_output(pid_t *pid)
{
    if (pid->output > pid->output_clamp_pos)
        return pid->output_clamp_pos;
    
    if (pid->output < pid->output_clamp_neg)
        return pid->output_clamp_neg;
    
    return pid->output;
}