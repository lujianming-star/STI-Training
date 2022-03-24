#include "myqueue.h"
void queue_init()
{
	myQueue01Handle = xQueueCreate(10, sizeof(float));

	
  speedLFQueueHandle = xQueueCreate(10, sizeof(float));
	speedLBQueueHandle = xQueueCreate(10, sizeof(float));
	speedRFQueueHandle = xQueueCreate(10, sizeof(float));
	speedRBQueueHandle = xQueueCreate(10, sizeof(float));
	yawQueueHandle = xQueueCreate(10, sizeof(float));	//控制电机速度	

  xposPIRQueueHandle = xQueueCreate(10, sizeof(float));
	yposPIRQueueHandle = xQueueCreate(10, sizeof(float));
	yawPIRQueueHandle = xQueueCreate(10, sizeof(float));			//由红外传感器获得的坐标
  xposIMUQueueHandle = xQueueCreate(10, sizeof(float));
	yposIMUQueueHandle = xQueueCreate(10, sizeof(float)); 
	yawIMUQueueHandle = xQueueCreate(10, sizeof(float));			//由陀螺仪获得的坐标
  xposRefQueueHandle = xQueueCreate(10, sizeof(float));
	yposRefQueueHandle = xQueueCreate(10, sizeof(float)); 
	yawRefQueueHandle = xQueueCreate(10, sizeof(float));			//修正后的坐标

  G6020AngleQueueHandle = xQueueCreate(10, sizeof(float));			//云台角度
  G6020AnleRefQueueHandle = xQueueCreate(10, sizeof(float));		//云台修正角度
  ArmAttitudeQueueHandle = xQueueCreate(10, sizeof(float));		//机械臂角度控制
  ArmhandstateQueueHandle = xQueueCreate(10, sizeof(float));		//机械臂状态
  
	RasperryDataQueueHandle = xQueueCreate(10, sizeof(float));
	RasperryitemQueueHandle = xQueueCreate(10, sizeof(float));
	RasperrycircleQueueHandle = xQueueCreate(10, sizeof(float));
	RasperrylineQueueHandle = xQueueCreate(10, sizeof(float));	//树莓派物料，圆圈，横线数据
	
}