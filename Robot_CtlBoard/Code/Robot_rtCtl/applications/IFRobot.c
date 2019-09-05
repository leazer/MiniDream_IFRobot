#include <main.h>

#include <board.h>
#include "single_pwm_motor.h"
#include "motor.h"
#include "ab_phase_encoder.h"
#include "encoder.h"
#include "pos_pid_controller.h"
#include "wheel.h"
#include "chassis.h"
#include "kinematics.h"
#define DBG_SECTION_NAME  "IFRobot"
#define DBG_LEVEL         DBG_LOG
#include <rtdbg.h>



#define MOTOR_PWM				"pwm8"
#define MOTOR1_CH				3
#define MOTOR2_CH				4
#define MOTOR3_CH				1
#define MOTOR4_CH				2
#define MOTOR1_A				GET_PIN(C, 1)
#define MOTOR1_B				GET_PIN(C, 0)
#define MOTOR2_A				GET_PIN(D, 10)
#define MOTOR2_B				GET_PIN(D, 11)
#define MOTOR3_A				GET_PIN(C, 2)
#define MOTOR3_B				GET_PIN(C, 3)
#define MOTOR4_A				GET_PIN(D, 9)
#define MOTOR4_B				GET_PIN(D, 8)

#define ENCODER1_A				GET_PIN(E, 5)
#define ENCODER1_B				GET_PIN(E, 6)
#define ENCODER2_A				GET_PIN(D, 12)
#define ENCODER2_B				GET_PIN(D, 13)
#define ENCODER3_A				GET_PIN(A, 0)
#define ENCODER3_B				GET_PIN(A, 1)
#define ENCODER4_A				GET_PIN(B, 14)
#define ENCODER4_B				GET_PIN(B, 15)
#define ENCODER_PULSE_REVOL		0x000B
#define ENCODER_SAMPLE_TIME	    10

#define PID_SAMPLE_TIME             50
#define PID_PARAM_KP                6.6
#define PID_PARAM_KI                6.5
#define PID_PARAM_KD                7.6

#define WHEEL_RAUIUS            22.5f
#define GEAR_RATIO              20
#define TRACK                   17.0f
#define WHEELBASE               19.0f
// Car Thread
#define THREAD_PRIORITY             10
#define THREAD_STACK_SIZE          512
#define THREAD_TIMESLICE             5
// CAR
chassis_t IFRobot_chas;

static rt_thread_t tid_car = RT_NULL;

void IFRobot_chassis_thread(void *param)
{
    // TODO

    struct velocity target_velocity;

    target_velocity.linear_x = 0.00f;
    target_velocity.linear_y = 00;
    target_velocity.angular_z = 0;
    chassis_set_velocity(IFRobot_chas, target_velocity);

    // Open loop control
//    controller_disable(IFRobot_chas->c_wheels[0]->w_controller);
//    controller_disable(IFRobot_chas->c_wheels[1]->w_controller);
//    controller_disable(IFRobot_chas->c_wheels[2]->w_controller);
//    controller_disable(IFRobot_chas->c_wheels[3]->w_controller);

    while (1)
    {
		led1_toggle();
        rt_thread_mdelay(50);
        chassis_update(IFRobot_chas);
    }
}



void IFRobot_chassis_init(void *parameter){
	wheel_t* c_wheels = (wheel_t*) rt_malloc(sizeof(wheel_t) * 4);
    if (c_wheels == RT_NULL)
    {
        LOG_D("Failed to malloc memory for wheels");
    }
	single_pwm_motor_t motor1 = single_pwm_motor_create(MOTOR_PWM, MOTOR1_CH, MOTOR1_A, MOTOR1_B);	
	single_pwm_motor_t motor2 = single_pwm_motor_create(MOTOR_PWM, MOTOR2_CH, MOTOR2_A, MOTOR2_B);
	single_pwm_motor_t motor3 = single_pwm_motor_create(MOTOR_PWM, MOTOR3_CH, MOTOR3_A, MOTOR3_B);
	single_pwm_motor_t motor4 = single_pwm_motor_create(MOTOR_PWM, MOTOR4_CH, MOTOR4_A, MOTOR4_B);
	
	ab_phase_encoder_t encoder1 = ab_phase_encoder_create(ENCODER1_A,ENCODER1_B, ENCODER_PULSE_REVOL);
	ab_phase_encoder_t encoder2 = ab_phase_encoder_create(ENCODER2_A,ENCODER2_B, ENCODER_PULSE_REVOL);
	ab_phase_encoder_t encoder3 = ab_phase_encoder_create(ENCODER3_A,ENCODER3_B, ENCODER_PULSE_REVOL);
	ab_phase_encoder_t encoder4 = ab_phase_encoder_create(ENCODER4_A,ENCODER4_B, ENCODER_PULSE_REVOL);

	pos_pid_controller_t pid_motor1 = pos_pid_controller_create(PID_PARAM_KP,PID_PARAM_KI,PID_PARAM_KD);
	pos_pid_controller_t pid_motor2 = pos_pid_controller_create(PID_PARAM_KP,PID_PARAM_KI,PID_PARAM_KD);
	pos_pid_controller_t pid_motor3 = pos_pid_controller_create(PID_PARAM_KP,PID_PARAM_KI,PID_PARAM_KD);
	pos_pid_controller_t pid_motor4 = pos_pid_controller_create(PID_PARAM_KP,PID_PARAM_KI,PID_PARAM_KD);
	
	c_wheels[0] = wheel_create((motor_t)motor1,(encoder_t)encoder1,(controller_t)pid_motor1,WHEEL_RAUIUS,GEAR_RATIO);
    c_wheels[1] = wheel_create((motor_t)motor2,(encoder_t)encoder2,(controller_t)pid_motor2,WHEEL_RAUIUS,GEAR_RATIO);
	c_wheels[2] = wheel_create((motor_t)motor3,(encoder_t)encoder3,(controller_t)pid_motor3,WHEEL_RAUIUS,GEAR_RATIO);
	c_wheels[3] = wheel_create((motor_t)motor4,(encoder_t)encoder4,(controller_t)pid_motor4,WHEEL_RAUIUS,GEAR_RATIO);
	
	
	kinematics_t c_kinematics = kinematics_create(MECANUM, TRACK, WHEELBASE, WHEEL_RAUIUS);
	
	IFRobot_chas = chassis_create(c_wheels, c_kinematics);
	
	chassis_enable(IFRobot_chas);
	
	tid_car = rt_thread_create("tcar",IFRobot_chassis_thread,RT_NULL,THREAD_STACK_SIZE,THREAD_PRIORITY, THREAD_TIMESLICE);
	
	if (tid_car != RT_NULL)
    {
        rt_thread_startup(tid_car);
    }
}
//INIT_COMPONENT_EXPORT(IFRobot_chassis_init);

