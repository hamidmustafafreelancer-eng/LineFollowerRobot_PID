/* 
 * File: pin_config.h
 * Purpose: Hardware abstraction for PIC16F877A Line Robot
 */

#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#if defined(__XC8) || defined(__XC8__)
    #include <xc.h>
#endif

// IR Sensors (PORTB - Consecutive) 
#define IR_TRIS         TRISB
#define IR_PORT         PORTB

#if defined(__XC8) || defined(__XC8__)
    #define IR_SENSOR_1     PORTBbits.RB0
    #define IR_SENSOR_2     PORTBbits.RB1
    #define IR_SENSOR_3     PORTBbits.RB2
    #define IR_SENSOR_4     PORTBbits.RB3
    #define IR_SENSOR_5     PORTBbits.RB4

    #define IR_MASK         0x1F   // 00011111
#else
    #define IR_SENSOR_1     RB0_bit
    #define IR_SENSOR_2     RB1_bit
    #define IR_SENSOR_3     RB2_bit
    #define IR_SENSOR_4     RB3_bit
    #define IR_SENSOR_5     RB4_bit

    #define IR_MASK         0x1F   // 00011111
#endif

// Motors Direction (PORTC)
#define MOTOR_DIR_TRIS  TRISC

#if defined(__XC8) || defined(__XC8__)
    #define L_IN1_TRIS TRISC3_bit
    #define L_IN2_TRIS TRISC4_bit
    #define R_IN3_TRIS TRISC5_bit
    #define R_IN4_TRIS TRISC6_bit
    
    #define L_IN1           PORTCbits.RC3
    #define L_IN2           PORTCbits.RC4

    #define R_IN3           PORTCbits.RC5
    #define R_IN4           PORTCbits.RC6

    //define L_PWM ,define R_PWM          RC2, RC1
    // Left = RC2 (CCP1), Right = RC1 (CCP2)
    #define L_PWM           PORTCbits.RC2   // CCP1
    #define R_PWM           PORTCbits.RC1   // CCP2
#else
    #define L_IN1           RC3_bit
    #define L_IN2           RC4_bit

    #define R_IN3           RC5_bit
    #define R_IN4           RC6_bit

    //define L_PWM ,define R_PWM          RC2_bit, RC1_bit
    #define L_PWM           RC2_bit
    #define R_PWM           RC1_bit
    // Motors PWM (PORTC) - Handled by MikroC PWM Library
    // Left = RC2 (CCP1), Right = RC1 (CCP2)
    #define L_PWM           RC2_bit   // CCP1
    #define R_PWM           RC1_bit   // CCP2
#endif

// Ultrasonic (PORTB)
#if defined(__XC8) || defined(__XC8__)
    #define TRIG_PIN        PORTBbits.RB5
    #define ECHO_PIN        PORTBbits.RB6
    // TRIS for Ultrasonic
    #define TRIG_TRIS       TRISBbits.TRISB5
    #define ECHO_TRIS       TRISBbits.TRISB6
#else
    #define TRIG_PIN        RB5_bit
    #define ECHO_PIN        RB6_bit
    // TRIS for Ultrasonic
    #define TRIG_TRIS       TRISB5_bit
    #define ECHO_TRIS       TRISB6_bit
#endif

// Buzzer (PORTC)
#if defined(__XC8) || defined(__XC8__)
    #define BUZZER_PIN      PORTCbits.RC0
    #define BUZZER_TRIS     TRISCbits.TRISC0
#else
    #define BUZZER_PIN      RC0_bit
    #define BUZZER_TRIS     TRISC0_bit
#endif

// LCD Pinout (Standard MikroC Lcd Connection)
#if defined(__XC8) || defined(__XC8__)
    #define LCD_RS      PORTDbits.RD0;
    #define LCD_EN      PORTDbits.RD1;
    #define LCD_D4      PORTDbits.RD4;
    #define LCD_D5      PORTDbits.RD5;
    #define LCD_D6      PORTDbits.RD6;
    #define LCD_D7      PORTDbits.RD7;
    // LCD TRIS
    #define LCD_RS_Direction  TRISDbits.TRISD0
    #define LCD_EN_Direction  TRISDbits.TRISD1
    #define LCD_D4_Direction  TRISDbits.TRISD4
    #define LCD_D5_Direction  TRISDbits.TRISD5
    #define LCD_D6_Direction  TRISDbits.TRISD6
    #define LCD_D7_Direction  TRISDbits.TRISD7
#else
    sbit LCD_RS at RD0_bit;
    sbit LCD_EN at RD1_bit;
    sbit LCD_D4 at RD4_bit;
    sbit LCD_D5 at RD5_bit;
    sbit LCD_D6 at RD6_bit;
    sbit LCD_D7 at RD7_bit;
    // LCD TRIS
    sbit LCD_RS_Direction at TRISD0_bit;
    sbit LCD_EN_Direction at TRISD1_bit;
    sbit LCD_D4_Direction at TRISD4_bit;
    sbit LCD_D5_Direction at TRISD5_bit;
    sbit LCD_D6_Direction at TRISD6_bit;
    sbit LCD_D7_Direction at TRISD7_bit;
#endif

#endif
