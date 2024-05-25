 /******************************************************************************
 *
 * Module: Timer 0
 *
 * File Name: timer.c
 *
 * Description: Source file for the timer 0 with pwm
 *
 * Author: Mahmoud Magdy
 *
 *******************************************************************************/
 
 #include "REG52.h"
 #include "timer0.h"
 
sbit servoMotor_PIN = PWM_TIMER0_PIN_ID;
 
 
 /*******************************************************************************
 *                               ISR                                           *
 *******************************************************************************/
 

 
 
 /* Timer0 interrupt service routine (ISR) */
void Timer0_ISR() interrupt 1	
{
	servoMotor_PIN = !servoMotor_PIN;
	if(servoMotor_PIN)
	{
		TH0 = (ON_Period >> 8);
		TL0 = ON_Period;
	}	
	else
	{
		TH0 = (OFF_Period >> 8);
		TL0 = OFF_Period;
	}	
			
}




/*******************************************************************************
 *                      Functions Definitions                                  *
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
void Timer0_init()
{
	TMOD = (TMOD & 0xF0) | 0x01;		/* Timer0 mode1 */
	TH0 = (PWM_PERIOD >> 8);/* 20ms timer value */
	TL0 = PWM_PERIOD;
	TR0 = 1;		/* Start timer0 */
	EA  = 1;		/* Enable global interrupt */
  	ET0 = 1;         	/* Enable timer0 interrupt */
}