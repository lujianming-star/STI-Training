#ifndef _MYQUEUE_H
#define _MYQUEUE_H
#include "stdint.h"
#include "FreeRTOS.h"
#include "queue.h"
QueueHandle_t	myQueue01Handle;

QueueHandle_t speedLFQueueHandle, speedLBQueueHandle, speedRFQueueHandle, speedRBQueueHandle, yawQueueHandle;	//���Ƶ���ٶ�	

QueueHandle_t xposPIRQueueHandle, yposPIRQueueHandle, yawPIRQueueHandle;			//�ɺ��⴫������õ�����
QueueHandle_t xposIMUQueueHandle, yposIMUQueueHandle, yawIMUQueueHandle;			//�������ǻ�õ�����
QueueHandle_t xposRefQueueHandle, yposRefQueueHandle, yawRefQueueHandle;			//�����������

QueueHandle_t G6020AngleQueueHandle;			//��̨�Ƕ�
QueueHandle_t G6020AnleRefQueueHandle;		//��̨�����Ƕ�
QueueHandle_t ArmAttitudeQueueHandle;		//��е�۽Ƕȿ���
QueueHandle_t ArmhandstateQueueHandle;		//��е��״̬
QueueHandle_t RasperryDataQueueHandle, RasperryitemQueueHandle, RasperrycircleQueueHandle, RasperrylineQueueHandle;	//��ݮ�����ϣ�ԲȦ����������
void queue_init();
#endif