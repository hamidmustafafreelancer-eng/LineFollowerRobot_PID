/* 
 * File:   PID.h
 * Author: mahmoud
 *
 * Created on April 30, 2026, 1:31 PM
 */

#ifndef PID_H
#define	PID_H

#include "stdint.h"

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        double Kp;
        double Ki;
        double Kd;
        double output_clamp_pos;
        double output_clamp_neg;
        double low_pass_cutoff_freq;
        double integral_sum;
        double derivative_state;
        double output;
        double clamped_output;
    } pid_t;

    /**
     * @brief Initialize PID object
     * @param pid - pointer to PID object
     */
    void pid_init(pid_t *pid);
    
    /**
     * @brief Iterates one cycle and returns PID output
     * @param pid - pointer to PID object
     * @param error - error in the system
     * @return PID output
     */
    double pid_update(pid_t *pid, double error);
    

#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

