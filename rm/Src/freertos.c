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
#include "caculate.h"
#include "grip.h"		
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
float servoAngle[4] = {90, 0, 0, 0};
/* USER CODE END Variables */
osThreadId ServoTaskHandle;
osThreadId TopTaskHandle;
osThreadId caCcommuHandle;
osMessageQId myQueue01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void Servo_Task(void const * argument);
void Top_Task(void const * argument);
void can_Commu(void const * argument);

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
  /* definition and creation of myQueue01 */
  osMessageQDef(myQueue01, 16, uint8_t);
  myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of ServoTask */
  osThreadDef(ServoTask, Servo_Task, osPriorityAboveNormal, 0, 128);
  ServoTaskHandle = osThreadCreate(osThread(ServoTask), NULL);

  /* definition and creation of TopTask */
  osThreadDef(TopTask, Top_Task, osPriorityNormal, 0, 128);
  TopTaskHandle = osThreadCreate(osThread(TopTask), NULL);

  /* definition and creation of caCcommu */
  osThreadDef(caCcommu, can_Commu, osPriorityIdle, 0, 128);
  caCcommuHandle = osThreadCreate(osThread(caCcommu), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Servo_Task */
/**
  * @brief  Function implementing the ServoTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_Servo_Task */
void Servo_Task(void const * argument)
{
    
    
    
    

  /* USER CODE BEGIN Servo_Task */
	MecArmAttiSturcture  rx;				//接收结构体变量要在接收函数里定义
	
  /* Infinite loop */
  for(;;)
  {
//			if(xQueueReceive(myQueue01Handle, &rx, 1000))
//			{
//				printf("successfully receive : %d \n", rx.pointX);
//				if(attitudeGetAngle(rx, servoAngle) != 1)
//				{
//					vTaskDelay(5);
//					servo1(servoAngle[0]);
//					vTaskDelay(5);
//					servo2(servoAngle[1]);
//					vTaskDelay(5);
//					servo3(servoAngle[2]);
//					vTaskDelay(5);
//					for(int i = 0; i < 3; i++)
//					{
//						printf(" angle = %f \n ",servoAngle[i]);
//						osDelay(50);
//					}
//				}
//				rm_servo(-15,v);
//				vTaskDelay(1500);
//				rm_servo(350,v);
//				vTaskDelay(1500);
			}
    //osDelay(1000);
  }
  /* USER CODE END Servo_Task */


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
	MecArmAttiSturcture  tx;		//接收的结构体变量和发送的变量
	tx.pointX = 0.14;
	tx.pointY = 0.095;
	//tx.handBiasAngle = 0;
	//tx.mode = 1;
	//tx.panAngle = 205;
	
  /* Infinite loop */
	
  for(;;)
  {
		xQueueSendToBack(myQueue01Handle, &tx, 0);
//		if(xQueueSendToBack(myQueue01Handle, &tx, 0))
//		{
//			printf("successfully send : %d", tx.mode);
//		}
    osDelay(100);
  }
  /* USER CODE END Top_Task */
}

/* USER CODE BEGIN Header_can_Commu */
/**
* @brief Function implementing the caCcommu thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_can_Commu */
void can_Commu(void const * argument)
{
  /* USER CODE BEGIN can_Commu */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END can_Commu */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
