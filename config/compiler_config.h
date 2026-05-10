#ifndef COMPILER_CONFIG_H
#define COMPILER_CONFIG_H

/**
 * @file compiler_config.h
 * @brief Bridges the gap between MikroC and MPLAB XC8 syntax.
 */

// 1. Detect Compiler and Include standard headers
#if defined(__XC8) || defined(__XC8__)
    #include <xc.h>
    #include <stdio.h>
    #define COMPILER_XC8
    #define _XTAL_FREQ 8000000 // Required for XC8 delays
#else
    #define COMPILER_MIKROC
#endif

// 2. Map Delay Functions
#ifdef COMPILER_XC8
    #define DELAY_MS(ms) __delay_ms(ms)
    #define DELAY_US(us) __delay_us(us)
#else
    #define DELAY_MS(ms) VDelay_ms(ms)
    #define DELAY_US(us) Delay_us(us)
#endif

// 3. Map ISR Keyword
#ifdef COMPILER_XC8
    #define INTERRUPT_FUNC void __interrupt() isr(void)
#else
    #define INTERRUPT_FUNC void interrupt()
#endif

// 4. Common Atomic Bit Mapping (Example for TMR0)
// In MikroC, TMR0IF_bit is built-in. In XC8, it is INTCONbits.TMR0IF.
#ifdef COMPILER_XC8
    #define TIMER0_IF  INTCONbits.TMR0IF
    #define TIMER0_IE  INTCONbits.TMR0IE
    #define G_INT_E    INTCONbits.GIE
#else
    #define TIMER0_IF  TMR0IF_bit
    #define TIMER0_IE  TMR0IE_bit
    #define G_INT_E    GIE_bit
#endif

#endif
