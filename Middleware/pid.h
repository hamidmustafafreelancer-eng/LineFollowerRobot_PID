/* 
 * File:   PID.h
 * Author: mahmoud
 *
 * Created on April 30, 2026, 1:31 PM
 */

#ifndef PID_H
#define	PID_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define SCALE   100

#define KP      100    // Scaled by 100
#define KI      5       // Scaled by 100
#define KD      100    // Scaled by 100

#define OUTPUT_CLAMP_POSITIVE   1024
#define OUTPUT_CLAMP_NEGATIVE   -1024
#define LOW_PASS_TIME_CONST     10

    typedef struct {
        int16_t integral_sum;
        int16_t derivative_state;
        int16_t output;
        int16_t clamped_output;
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
    void PID_Update(pid_t *pid, int16_t error);
    

#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

