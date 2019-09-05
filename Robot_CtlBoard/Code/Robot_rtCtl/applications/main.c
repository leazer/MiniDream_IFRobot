/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */
 
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "IFRobot.h"
#define DBG_SECTION_NAME  "main"
#define DBG_LEVEL         DBG_LOG
#include <rtdbg.h>
/* defined the LED0 pin: PB1 */
#define LED0_PIN    GET_PIN(B, 9)
#define LED1_PIN    GET_PIN(B, 8)

void led1_toggle(void){
	static int8_t status = 1;
	if(status == 1){
		rt_pin_write(LED1_PIN, PIN_HIGH);
	}
	else{
		rt_pin_write(LED1_PIN, PIN_LOW);
	}
	status =~status;
}
	
int main(void)
{
    int count = 1;
	IFRobot_chassis_init();
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(100);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(100);
		//LOG_D("log debug test");                                        
    }

    return RT_EOK;
}









