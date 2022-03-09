#include "grip.h"
#include "pid.h"
#include "bsp_can.h"
#include "tim.h"
#include "motor_pid.h"
extern moto_info_t motor_info[MOTOR_MAX_NUM];
pid_struct_t motor_pid[7];
				

void rotor_pid_task(float target_speed)	//在此处设定所需要的速度
{
	for(int i=0;i<7;i++)
	{
			motor_info[i].set_voltage = pid_calc(&motor_pid[i], target_speed, motor_info[i].rotor_speed);
	}
			/* send motor control message through can bus*/
	set_motor_voltage(0, 
										motor_info[0].set_voltage, 
										motor_info[1].set_voltage, 
										motor_info[2].set_voltage, 
										motor_info[3].set_voltage);
	set_motor_voltage(1, 
									motor_info[4].set_voltage, 
									motor_info[5].set_voltage, 
									motor_info[6].set_voltage, 
									0);
}