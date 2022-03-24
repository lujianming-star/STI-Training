#ifndef _MYQUEUE_H
#define _MYQUEUE_H
#include "stdint.h"
#include "FreeRTOS.h"
#include "queue.h"
QueueHandle_t	myQueue01Handle;

QueueHandle_t speedLFQueueHandle, speedLBQueueHandle, speedRFQueueHandle, speedRBQueueHandle, yawQueueHandle;	//控制电机速度	

QueueHandle_t xposPIRQueueHandle, yposPIRQueueHandle, yawPIRQueueHandle;			//由红外传感器获得的坐标
QueueHandle_t xposIMUQueueHandle, yposIMUQueueHandle, yawIMUQueueHandle;			//由陀螺仪获得的坐标
QueueHandle_t xposRefQueueHandle, yposRefQueueHandle, yawRefQueueHandle;			//修正后的坐标

QueueHandle_t G6020AngleQueueHandle;			//云台角度
QueueHandle_t G6020AnleRefQueueHandle;		//云台修正角度
QueueHandle_t ArmAttitudeQueueHandle;		//机械臂角度控制
QueueHandle_t ArmhandstateQueueHandle;		//机械臂状态
QueueHandle_t RasperryDataQueueHandle, RasperryitemQueueHandle, RasperrycircleQueueHandle, RasperrylineQueueHandle;	//树莓派物料，圆圈，横线数据
void queue_init();
#endif