/* 
 * File: pin_config.h
 * Purpose: Hardware abstraction for PIC16F877A Line Robot
 */

#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// IR Sensors (PORTB - Consecutive) 
#define IR_TRIS         TRISB
#define IR_PORT         PORTB

#define IR_SENSOR_1     RB0_bit
#define IR_SENSOR_2     RB1_bit
#define IR_SENSOR_3     RB2_bit
#define IR_SENSOR_4     RB3_bit
#define IR_SENSOR_5     RB4_bit

#define IR_MASK         0x1F   // 00011111

// Motors Direction (PORTC)
#define MOTOR_DIR_TRIS  TRISC

#define L_IN1           RC3_bit
#define L_IN2           RC4_bit

#define R_IN3           RC5_bit
#define R_IN4           RC6_bit

//definre L_PWM ,define R_PWM          RC2_bit, RC1_bit
#define L_PWM           RC2_bit
#define R_PWM           RC1_bit
// Motors PWM (PORTC) - Handled by MikroC PWM Library
// Left = RC2 (CCP1), Right = RC1 (CCP2)
#define L_PWM           RC2_bit   // CCP1
#define R_PWM           RC1_bit   // CCP2
// Ultrasonic (PORTB)
#define TRIG_PIN        RB5_bit
#define ECHO_PIN        RB6_bit
// TRIS for Ultrasonic
#define TRIG_TRIS       TRISB5_bit
#define ECHO_TRIS       TRISB6_bit

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
// LCD TRIS
sbit LCD_RS_Direction at TRISD0_bit;
sbit LCD_EN_Direction at TRISD1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

#endif
