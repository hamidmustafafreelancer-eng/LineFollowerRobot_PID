/* 
 * File: pin_config.h
 * Purpose: Hardware abstraction for PIC16F877A Line Robot
 */

#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// IR Sensors (PORTA)
#define IR_TRIS         TRISA
#define IR_PORT         PORTA
// Note: We use RA0, RA1, RA2, RA3, RA5

// Motors Direction (PORTB)
#define MOTOR_DIR_TRIS  TRISB
#define L_IN1           RB0_bit
#define L_IN2           RB1_bit
#define R_IN3           RB2_bit
#define R_IN4           RB3_bit

// Motors PWM (PORTC) - Handled by MikroC PWM Library
// Left = RC2 (CCP1), Right = RC1 (CCP2)

// Ultrasonic (PORTB)
#define TRIG_PIN        RB4_bit
#define ECHO_PIN        RB5_bit
#define TRIG_TRIS       TRISB4_bit
#define ECHO_TRIS       TRISB5_bit

// Buzzer (PORTC)
#define BUZZER_PIN      RC0_bit
#define BUZZER_TRIS     TRISC0_bit

// LCD Pinout (Standard MikroC Lcd Connection)
sbit LCD_RS at RD0_bit;
sbit LCD_EN at RD1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD0_bit;
sbit LCD_EN_Direction at TRISD1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

#endif
