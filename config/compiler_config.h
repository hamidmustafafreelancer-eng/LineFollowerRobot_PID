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


        // --- 1. PWM MACRO MAPPING (MikroC -> XC8) ---
        // MikroC: PWM1_Set_Duty(val)
        // XC8: Manual register write
        #define PWM1_Set_Duty(duty) CCPR1L = duty
        #define PWM2_Set_Duty(duty) CCPR2L = duty
        
        // --- 2. LCD MACRO MAPPING (MikroC -> XC8) ---
        // MikroC: Lcd_Out(row, col, text)
        // XC8: Maps to our custom manual driver in display_mgr.c
        #define Lcd_Out(r, c, txt)  LCD_Goto(r, c); LCD_Print(txt)
        #define Lcd_Cmd(cmd)        LCD_Send_Cmd(cmd)
        #define Lcd_Chr(r, c, ch)   LCD_Goto(r, c); LCD_PrintChar(ch)

        // --- 3. DELAY MAPPING ---
        #define Delay_ms(ms)        __delay_ms(ms)
        #define Delay_us(us)        __delay_us(us)

        // --- 4. ISR MAPPING ---
        #define INTERRUPT_FUNC      void __interrupt() isr(void)
        #define TMR0IF_bit          INTCONbits.TMR0IF
        #define TMR0IE_bit          INTCONbits.TMR0IE
        #define GIE_bit             INTCONbits.GIE

    #else
        #define COMPILER_MIKROC
        // MikroC already has these built-in; no macros needed.
        #define INTERRUPT_FUNC      void interrupt()
        // MikroC Aliases
        #define TMR0_IF     TMR0IF_bit
        #define G_INT_E     GIE_bit
    #endif



#endif
