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

#define KP      10.0
#define KI      0.005
#define KD      10.0

#define OUTPUT_CLAMP_POSITIVE   1024.0
#define OUTPUT_CLAMP_NEGATIVE   -1024.0
#define LOW_PASS_CUTOFF_FREQ    0.1

    typedef struct {
        double integral_sum;
        double derivative_state;
        double output;
        double clamped_output;
    } pid_t;

    /**
     * @brief Initialize PID object
     * @param pid - pointer to PID object
     */
    void PID_Init(pid_t *pid);
    
    /**
     * @brief Iterates one cycle and returns PID output
     * @param pid - pointer to PID object
     * @param error - error in the system
     * @return PID output
     */
    double PID_Update(pid_t *pid, double error);
    

#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

