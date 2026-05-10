#ifndef BUZZER_H
#define BUZZER_H

/**
 * @brief Initializes the Buzzer pin as an output.
 */
void Buzzer_Init(void);

/**
 * @brief Turns the buzzer ON (Static).
 */
void Buzzer_On(void);

/**
 * @brief Turns the buzzer OFF.
 */
void Buzzer_Off(void);

/**
 * @brief Toggles the buzzer state. 
 * Useful for creating "beeping" sounds in the scheduler.
 */
void Buzzer_Toggle(void);

#endif
