#include "compiler_config.h" // Must be first

#include "scheduler.h"

volatile uint8_t task_20ms_count = 0;
volatile uint8_t task_200ms_count = 0;

/*
    Timer0 Interrupt:
    Creates a 4ms system heartbeat.

    IMPORTANT:
    ISR only handles timing.
    Heavy logic must stay in main loop.
*/
void interrupt() {

    static uint8_t count_20 = 0;
    static uint8_t count_200 = 0;

    if(TMR0IF_bit) {

        TMR0IF_bit = 0;
        TMR0 = 6;

        count_20++;
        count_200++;

        // 20ms task
        if(count_20 >= 5) {

            if(task_20ms_count < 255)
                task_20ms_count++;

            count_20 = 0;
        }

        // 200ms task
        if(count_200 >= 50) {

            if(task_200ms_count < 255)
                task_200ms_count++;

            count_200 = 0;
        }
    }
}

void Scheduler_Init(void) {

    // Timer0:
    // Internal Clock (Fosc/4)
    // Prescaler = 1:32
    OPTION_REG = 0x84;

    // 4ms preload
    TMR0 = 6;

    // Clear pending interrupt
    TMR0IF_bit = 0;

    // Enable Timer0 interrupt
    TMR0IE_bit = 1;

    // Enable global interrupts
    GIE_bit = 1;
}