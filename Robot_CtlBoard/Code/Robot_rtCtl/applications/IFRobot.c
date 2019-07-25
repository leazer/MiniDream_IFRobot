#include "single_pwm_motor.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
#include "wheel.h"
#include "chassis.h"
#include "kinematics.h"
#define DBG_SECTION_NAME  "IFRobot"
#define DBG_LEVEL         DBG_LOG
#include <rtdbg.h>

#define WHEEL_RAUIUS            22.5f
#define GEAR_RATIO              20
#define TRACK                   17.0f
#define WHEELBASE               19.0f
#define MOTOR_PWM				"pwm8"


single_pwm_motor_t left_front_motor;
single_pwm_motor_t right_front_motor;
single_pwm_motor_t left_back_motor;
single_pwm_motor_t right_back_motor;

int IFRobot_chassis_create(void){
	left_front_motor = single_pwm_motor_create(MOTOR_PWM,1, 32, 33);
	right_front_motor = single_pwm_motor_create(MOTOR_PWM,2,56, 57);
	left_back_motor = single_pwm_motor_create(MOTOR_PWM,3, 34, 35);
	right_back_motor = single_pwm_motor_create(MOTOR_PWM,4, 58, 59);
	
	motor_enable(&left_front_motor->mot);
	motor_enable(&right_front_motor->mot);
	motor_enable(&left_back_motor->mot);
	motor_enable(&right_back_motor->mot);
    return RT_EOK;
}
int IFRobot_chassis_test(rt_int16_t speed1,rt_int16_t speed2,rt_int16_t speed3,rt_int16_t speed4){
	motor_run(&right_back_motor->mot,speed1);
	motor_run(&right_front_motor->mot,speed2);
	motor_run(&left_back_motor->mot,speed3);
	motor_run(&right_back_motor->mot,speed4);
    return RT_EOK;
}

