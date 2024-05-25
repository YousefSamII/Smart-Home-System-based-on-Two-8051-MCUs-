 /******************************************************************************
 *
 * Module: Servomotor
 *
 * File Name: servomotor.h
 *
 * Description: Header file for the Servo motor driver
 *
 * Author: Mahmoud Magdy
 *
 *******************************************************************************/
 
#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "MCAL/TIMER0/timer0.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
 
#define SERVOMOTOR_ROTATE_0 		2
#define SERVOMOTOR_ROTATE_90		6
#define SERVOMOTOR_ROTATE_180		10.6

#define SERVOMOTOR_PIN_ID				PWM_TIMER0_PIN_ID







/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
 
 /*
 * Description :
 * Function to rotate the servo motor with specific degree 
 */
void servoMotor_rotate(float duty_cycle);


 /*
 * Description :
 * Function to rotate servo motor with 0 degree  
 */
 void servoMotor_rotate_0 (void);


/*
 * Description :
 * Function to rotate servo motor with 90 degree  
 */
 void servoMotor_rotate_90 (void);
 
 
 /*
 * Description :
 * Function to rotate servo motor with 180 degree  
 */
 void servoMotor_rotate_180 (void);
 


#endif 