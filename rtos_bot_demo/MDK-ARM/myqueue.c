#include "myqueue.h"
void queue_init()
{
	myQueue01Handle = xQueueCreate(10, sizeof(float));

	
  speedLFQueueHandle = xQueueCreate(10, sizeof(float));
	speedLBQueueHandle = xQueueCreate(10, sizeof(float));
	speedRFQueueHandle = xQueueCreate(10, sizeof(float));
	speedRBQueueHandle = xQueueCreate(10, sizeof(float));
	yawQueueHandle = xQueueCreate(10, sizeof(float));	//���Ƶ���ٶ�	

  xposPIRQueueHandle = xQueueCreate(10, sizeof(float));
	yposPIRQueueHandle = xQueueCreate(10, sizeof(float));
	yawPIRQueueHandle = xQueueCreate(10, sizeof(float));			//�ɺ��⴫������õ�����
  xposIMUQueueHandle = xQueueCreate(10, sizeof(float));
	yposIMUQueueHandle = xQueueCreate(10, sizeof(float)); 
	yawIMUQueueHandle = xQueueCreate(10, sizeof(float));			//�������ǻ�õ�����
  xposRefQueueHandle = xQueueCreate(10, sizeof(float));
	yposRefQueueHandle = xQueueCreate(10, sizeof(float)); 
	yawRefQueueHandle = xQueueCreate(10, sizeof(float));			//�����������

  G6020AngleQueueHandle = xQueueCreate(10, sizeof(float));			//��̨�Ƕ�
  G6020AnleRefQueueHandle = xQueueCreate(10, sizeof(float));		//��̨�����Ƕ�
  ArmAttitudeQueueHandle = xQueueCreate(10, sizeof(float));		//��е�۽Ƕȿ���
  ArmhandstateQueueHandle = xQueueCreate(10, sizeof(float));		//��е��״̬
  
	RasperryDataQueueHandle = xQueueCreate(10, sizeof(float));
	RasperryitemQueueHandle = xQueueCreate(10, sizeof(float));
	RasperrycircleQueueHandle = xQueueCreate(10, sizeof(float));
	RasperrylineQueueHandle = xQueueCreate(10, sizeof(float));	//��ݮ�����ϣ�ԲȦ����������
	
}