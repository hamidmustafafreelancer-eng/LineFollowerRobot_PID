#include "buzzer.h"
#include "config/pin_config.h"

void Buzzer_Init(void) {
    BUZZER_TRIS = 0; // Set RC0 as Output
    BUZZER_PIN = 0;  // Ensure it starts OFF
}

void Buzzer_On(void) {
    BUZZER_PIN = 1;
}

void Buzzer_Off(void) {
    BUZZER_PIN = 0;
}

void Buzzer_Toggle(void) {
    BUZZER_PIN = ~BUZZER_PIN;
}
