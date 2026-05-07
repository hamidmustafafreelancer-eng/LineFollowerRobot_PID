#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

/*
    Scheduler:
    A simple timing system that decides WHEN tasks should run.

    Fast tasks:
    - PID control
    - Obstacle detection

    Slow tasks:
    - LCD updates

    This prevents slow LCD operations from affecting robot movement.
*/

// Counters are used instead of simple ON/OFF flags.
// This helps the scheduler remember if a task became ready multiple times.
extern volatile uint8_t task_20ms_count;
extern volatile uint8_t task_200ms_count;

/*
    Configure Timer0:
    - Clock = Fosc/4
    - Prescaler = 1:32
    - Base Tick = 4ms
*/
void Scheduler_Init(void);

#endif // SCHEDULER_H