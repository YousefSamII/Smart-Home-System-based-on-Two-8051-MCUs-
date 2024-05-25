 /******************************************************************************
 *
 * Module: Servomotor
 *
 * File Name: motor.c
 *
 * Description: Source file for the Servo motor driver
 *
 * Author: Mahmoud Magdy
 *
 *******************************************************************************/

#include "servomotor.h"
#include "../../MCAL/TIMER0/timer0.h"
#include <REG52.h>

/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/
  
unsigned int ON_Period, OFF_Period, DutyCycle;

sbit servoMotor_PIN = SERVOMOTOR_PIN_ID;







 /*
 * Description :
 * Function to rotate the servo motor with specific degree 
 */
void servoMotor_rotate(float duty_cycle)
{
	float period = 65535 - PWM_PERIOD;
	ON_Period = ((period/100.0) * duty_cycle);
	OFF_Period = (period - ON_Period);	
	ON_Period = 65535 - ON_Period;	
	OFF_Period = 65535 - OFF_Period;
}


/*
 * Description :
 * Function to rotate servo motor with 0 degree  
 */

void servoMotor_rotate_0 (void)
{
	servoMotor_rotate(SERVOMOTOR_ROTATE_0);
}


/*
 * Description :
 * Function to rotate servo motor with 90 degree  
 */
void servoMotor_rotate_90 (void)
{
	servoMotor_rotate(SERVOMOTOR_ROTATE_90);
}


/*
 * Description :
 * Function to rotate servo motor with 180 degree  
 */
void servoMotor_rotate_180 (void)
{
	servoMotor_rotate(SERVOMOTOR_ROTATE_180);
}
