/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId HMITaskHandle;				//串口屏任务，优先级1
osThreadId ComTaskHandle;				//与树莓派通讯任务，优先级3
osThreadId TopTaskHandle;				//顶层任务,优先级4
osThreadId ActionTaskHandle;		//动作执行任务，优先级5
osThreadId MearmTaskHandle;			//机械臂舵机任务，优先级6
osThreadId MotcorTaskHandle;		
osThreadId PirTaskHandle;				//红外传感器任务，优先级7
osThreadId MotorTaskHandle;			//底盘任务，优先级7
osMessageQId speedLFQueueHandle, speedLBQueueHandle, speedRFQueueHandle, speedRBQueueHandle, yawQueueHandle;	//控制电机速度	

osMessageQId xposPIRQueueHandle, yposPIRQueueHandle, yawPIRQueueHandle;			//由红外传感器获得的坐标
osMessageQId xposIMUQueueHandle, yposIMUQueueHandle, yawIMUQueueHandle;			//由陀螺仪获得的坐标
osMessageQId xposRefQueueHandle, yposRefQueueHandle, yawRefQueueHandle;			//修正后的坐标

osMessageQId G6020AngleQueueHandle;			//云台角度
osMessageQId G6020AnleRefQueueHandle;		//云台修正角度
osMessageQId ArmAttitudeQueueHandle;		//机械臂角度控制
osMessageQId ArmhandstateQueueHandle;		//机械臂状态
osMessageQId RasperryDataQueueHandle, RasperryitemQueueHandle, RasperrycircleQueueHandle, RasperrylineQueueHandle;	//树莓派物料，圆圈，横线数据


/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void HMI_Task(void const * argument);
void Com_Task(void const * argument);
void Top_Task(void const * argument);
void Action_Task(void const * argument);
void Mearm_Task(void const * argument);
void Motcor_Task(void const * argument);
void Pir_Task(void const * argument);
void Motor_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of speedLFQueue */
  osMessageQDef(speedLFQueue, 1, uint16_t);
  speedLFQueueHandle = osMessageCreate(osMessageQ(speedLFQueue), NULL);

  /* definition and creation of speedLBQueue */
  osMessageQDef(speedLBQueue, 1, uint16_t);
  speedLBQueueHandle = osMessageCreate(osMessageQ(speedLBQueue), NULL);

  /* definition and creation of speedRFQueue */
  osMessageQDef(speedRFQueue, 1, uint16_t);
  speedRFQueueHandle = osMessageCreate(osMessageQ(speedRFQueue), NULL);

  /* definition and creation of speedRBQueue */
  osMessageQDef(speedRBQueue, 1, uint16_t);
  speedRBQueueHandle = osMessageCreate(osMessageQ(speedRBQueue), NULL);

  /* definition and creation of yawQueue */
  osMessageQDef(yawQueue, 1, uint16_t);
  yawQueueHandle = osMessageCreate(osMessageQ(yawQueue), NULL);

  /* definition and creation of xposPIRQueue */
  osMessageQDef(xposPIRQueue, 1, uint16_t);
  xposPIRQueueHandle = osMessageCreate(osMessageQ(xposPIRQueue), NULL);

  /* definition and creation of xposIMUQueue */
  osMessageQDef(xposIMUQueue, 1, uint16_t);
  xposIMUQueueHandle = osMessageCreate(osMessageQ(xposIMUQueue), NULL);

  /* definition and creation of xposRefQueue */
  osMessageQDef(xposRefQueue, 1, uint16_t);
  xposRefQueueHandle = osMessageCreate(osMessageQ(xposRefQueue), NULL);

  /* definition and creation of yposPIRQueue */
  osMessageQDef(yposPIRQueue, 1, uint16_t);
  yposPIRQueueHandle = osMessageCreate(osMessageQ(yposPIRQueue), NULL);

  /* definition and creation of yposIMUQueue */
  osMessageQDef(yposIMUQueue, 1, uint16_t);
  yposIMUQueueHandle = osMessageCreate(osMessageQ(yposIMUQueue), NULL);

  /* definition and creation of yposRefQueue */
  osMessageQDef(yposRefQueue, 1, uint16_t);
  yposRefQueueHandle = osMessageCreate(osMessageQ(yposRefQueue), NULL);

  /* definition and creation of yawPIRQueue */
  osMessageQDef(yawPIRQueue, 1, uint16_t);
  yawPIRQueueHandle = osMessageCreate(osMessageQ(yawPIRQueue), NULL);

  /* definition and creation of yawIMUQueue */
  osMessageQDef(yawIMUQueue, 1, uint16_t);
  yawIMUQueueHandle = osMessageCreate(osMessageQ(yawIMUQueue), NULL);

  /* definition and creation of yawRefQueue */
  osMessageQDef(yawRefQueue, 1, uint16_t);
  yawRefQueueHandle = osMessageCreate(osMessageQ(yawRefQueue), NULL);

  /* definition and creation of G6020AngleQueue */
  osMessageQDef(G6020AngleQueue, 1, uint16_t);
  G6020AngleQueueHandle = osMessageCreate(osMessageQ(G6020AngleQueue), NULL);

  /* definition and creation of G6020AnleRefQueue */
  osMessageQDef(G6020AnleRefQueue, 1, uint16_t);
  G6020AnleRefQueueHandle = osMessageCreate(osMessageQ(G6020AnleRefQueue), NULL);

  /* definition and creation of ArmAttitudeQueue */
  osMessageQDef(ArmAttitudeQueue, 1, uint16_t);
  ArmAttitudeQueueHandle = osMessageCreate(osMessageQ(ArmAttitudeQueue), NULL);

  /* definition and creation of ArmhandstateQueue */
  osMessageQDef(ArmhandstateQueue, 1, uint16_t);
  ArmhandstateQueueHandle = osMessageCreate(osMessageQ(ArmhandstateQueue), NULL);

  /* definition and creation of RasperryDataQueue */
  osMessageQDef(RasperryDataQueue, 1, uint16_t);
  RasperryDataQueueHandle = osMessageCreate(osMessageQ(RasperryDataQueue), NULL);

  /* definition and creation of RasperryitemQueue */
  osMessageQDef(RasperryitemQueue, 1, uint16_t);
  RasperryitemQueueHandle = osMessageCreate(osMessageQ(RasperryitemQueue), NULL);

  /* definition and creation of RasperrycircleQueue */
  osMessageQDef(RasperrycircleQueue, 1, uint16_t);
  RasperrycircleQueueHandle = osMessageCreate(osMessageQ(RasperrycircleQueue), NULL);

  /* definition and creation of RasperrylineQueue */
  osMessageQDef(RasperrylineQueue, 1, uint16_t);
  RasperrylineQueueHandle = osMessageCreate(osMessageQ(RasperrylineQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of HMITask */
  osThreadDef(HMITask, HMI_Task, osPriorityIdle, 0, 128);
  HMITaskHandle = osThreadCreate(osThread(HMITask), NULL);

  /* definition and creation of ComTask */
  osThreadDef(ComTask, Com_Task, osPriorityLow, 0, 128);
  ComTaskHandle = osThreadCreate(osThread(ComTask), NULL);

  /* definition and creation of TopTask */
  osThreadDef(TopTask, Top_Task, osPriorityBelowNormal, 0, 128);
  TopTaskHandle = osThreadCreate(osThread(TopTask), NULL);

  /* definition and creation of ActionTask */
  osThreadDef(ActionTask, Action_Task, osPriorityNormal, 0, 128);
  ActionTaskHandle = osThreadCreate(osThread(ActionTask), NULL);

  /* definition and creation of MearmTask */
  osThreadDef(MearmTask, Mearm_Task, osPriorityAboveNormal, 0, 128);
  MearmTaskHandle = osThreadCreate(osThread(MearmTask), NULL);

  /* definition and creation of MotcorTask */
  osThreadDef(MotcorTask, Motcor_Task, osPriorityAboveNormal, 0, 128);
  MotcorTaskHandle = osThreadCreate(osThread(MotcorTask), NULL);

  /* definition and creation of PirTask */
  osThreadDef(PirTask, Pir_Task, osPriorityHigh, 0, 128);
  PirTaskHandle = osThreadCreate(osThread(PirTask), NULL);

  /* definition and creation of MotorTask */
  osThreadDef(MotorTask, Motor_Task, osPriorityHigh, 0, 128);
  MotorTaskHandle = osThreadCreate(osThread(MotorTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_HMI_Task */
/**
  * @brief  Function implementing the HMITask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_HMI_Task */
void HMI_Task(void const * argument)
{
    
    
    
    
    
    
    
    
    

  /* USER CODE BEGIN HMI_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END HMI_Task */
}

/* USER CODE BEGIN Header_Com_Task */
/**
* @brief Function implementing the ComTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Com_Task */
void Com_Task(void const * argument)
{
  /* USER CODE BEGIN Com_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Com_Task */
}

/* USER CODE BEGIN Header_Top_Task */
/**
* @brief Function implementing the TopTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Top_Task */
void Top_Task(void const * argument)
{
  /* USER CODE BEGIN Top_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Top_Task */
}

/* USER CODE BEGIN Header_Action_Task */
/**
* @brief Function implementing the ActionTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Action_Task */
void Action_Task(void const * argument)
{
  /* USER CODE BEGIN Action_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Action_Task */
}

/* USER CODE BEGIN Header_Mearm_Task */
/**
* @brief Function implementing the MearmTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Mearm_Task */
void Mearm_Task(void const * argument)
{
  /* USER CODE BEGIN Mearm_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Mearm_Task */
}

/* USER CODE BEGIN Header_Motcor_Task */
/**
* @brief Function implementing the MotcorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Motcor_Task */
void Motcor_Task(void const * argument)
{
  /* USER CODE BEGIN Motcor_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Motcor_Task */
}

/* USER CODE BEGIN Header_Pir_Task */
/**
* @brief Function implementing the PirTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Pir_Task */
void Pir_Task(void const * argument)
{
  /* USER CODE BEGIN Pir_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Pir_Task */
}

/* USER CODE BEGIN Header_Motor_Task */
/**
* @brief Function implementing the MotorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Motor_Task */
void Motor_Task(void const * argument)
{
  /* USER CODE BEGIN Motor_Task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Motor_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
