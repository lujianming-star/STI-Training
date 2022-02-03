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
struct Msg
{
	uint8_t num;
	uint8_t source[20];
};
struct Msg mess[2] = 
{
	{100, "openled2"},
	{200, "task2"}
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t *sendmsg[] = 
{
	"openled1",
	"openled2",
	"openled3",
	"openled4"
};
uint16_t led[4] =
{
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4
};
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId transmitTaskHandle;
osThreadId ReceiveTaskHandle;
osThreadId myTask03Handle;
osMessageQId cmdQueueHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void transmit_Task(void const * argument);
void Receive_Task(void const * argument);
void my_Task03(void const * argument);

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
  /* definition and creation of cmdQueue */
  osMessageQDef(cmdQueue, 5, uint64_t);
  cmdQueueHandle = osMessageCreate(osMessageQ(cmdQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of transmitTask */
  osThreadDef(transmitTask, transmit_Task, osPriorityNormal, 0, 128);
  transmitTaskHandle = osThreadCreate(osThread(transmitTask), NULL);

  /* definition and creation of ReceiveTask */
  osThreadDef(ReceiveTask, Receive_Task, osPriorityAboveNormal, 0, 128);
  ReceiveTaskHandle = osThreadCreate(osThread(ReceiveTask), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, my_Task03, osPriorityIdle, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_transmit_Task */
/**
  * @brief  Function implementing the transmitTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_transmit_Task */
void transmit_Task(void const * argument)
{
    
    
    
    

  /* USER CODE BEGIN transmit_Task */
	uint8_t recevie_msg[] = "openled2 \n";

	portBASE_TYPE xStatus;
  /* Infinite loop */
  for(;;)
  {
//		xStatus = xQueueSendToBack(cmdQueueHandle, &mess[0] , 0); 		//将数据发送到消息队列中
		xStatus = xQueueSendToBack(cmdQueueHandle, recevie_msg , 0); 		//将数据发送到消息队列中
		//队列中每个数据单元设置为uint8_t，即单个字节，而不是指针,不能使用地址传递
		//使用结构体来发送字符串
		if(xStatus == pdPASS)
		{
//			printf("send: %d \n", mess[0].num);
//			printf("send: %s ", mess[0].source);
			printf("send: %s \n", recevie_msg);
			//taskYIELD();
			
		}

		osDelay(500);
    
  }
  /* USER CODE END transmit_Task */
}

/* USER CODE BEGIN Header_Receive_Task */
/**
* @brief Function implementing the ReceiveTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Receive_Task */
void Receive_Task(void const * argument)
{
  /* USER CODE BEGIN Receive_Task */
	uint32_t lReceivedValue[50];				//定义接收缓冲区大小，注意内存溢出问题
	//cubemx配置单个数据内存为u64, 缓冲区大小要小于u64
	struct Msg receiveData;
	portBASE_TYPE xStatus;

  /* Infinite loop */
  for(;;)
  {


		xStatus = xQueueReceive( cmdQueueHandle,lReceivedValue, portMAX_DELAY );//在队列里读出一个数据
		if(xStatus == pdPASS)
		{	
			HAL_GPIO_WritePin(GPIOG, led[0], 0);
			while(xQueueReceive( cmdQueueHandle, lReceivedValue,100 ))	{}
				//保证接收到完整数据
				printf("receive: %s \n",lReceivedValue);
//			printf("receive: %d \n",receiveData.num);
//			printf("receive: %s",receiveData.source);
			for(int i=0; i < 4; i++)
			{	
				if(strcmp(lReceivedValue, sendmsg[i]) == 0)
				{
					HAL_GPIO_WritePin(GPIOG, led[i], 0);
					printf("Cmd is %s \n", sendmsg[i]);
					
				}
			}
			
		}

    
  }
  /* USER CODE END Receive_Task */
}

/* USER CODE BEGIN Header_my_Task03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_my_Task03 */
void my_Task03(void const * argument)
{
  /* USER CODE BEGIN my_Task03 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END my_Task03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
