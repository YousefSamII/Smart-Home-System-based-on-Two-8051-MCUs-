 /******************************************************************************
 *
 * Module: Timer 0
 *
 * File Name: timer.h
 *
 * Description: Header file for the timer 0 with pwm
 *
 * Author: Mahmoud Magdy
 *
 *******************************************************************************/
 #ifndef _TIMER0_H_
 #define _TIMER0_H_
 
 /*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
extern unsigned int ON_Period, OFF_Period, DutyCycle;
	

/* Define value to be loaded in timer for PWM period of 20 milli second */
#define PWM_PERIOD							0xB39E		/* 45982 */
#define SERVOMOTOR_PIN_ID				P2^0



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
 
  /*
 * Description :
 * Initialize Timer0 with the following: 
 * 1- Timer0 model.
 * 2- 20ms timer value.
 * 3- Start Timer0. 
 * 4- Enable Global Interrupt.
 * 5- Enable Timer0 Interrupt.
 */
void Timer0_init();

 
 
 
 #endif