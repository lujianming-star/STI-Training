/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2022 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "bsp_can.h"
#include "pid.h"
#include "Remote_Control.h"

#include <stdio.h>    //标准基础库函数，Printf函数必须
#include "string.h"   //标准库函数，字符串操作
#include "ctype.h"    //标准库函数，字符操作
// 最简重定向printf函数方式


#include "stm32f4xx_it.h"
#include "Mecanum.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define ABS(x)	( (x>0) ? (x) : (-x) )
//#define PI 3.14159265354f
//#define wheel_perimeter 150*PI		//zhouchang		mm!
//#define wheeltrack 430			//hengxiang lunju
//#define wheelbase 360		//qianhoulunde zhouju


//#define CNT_PER_ROUND 8192    // zhuanzi rolls one circle -> pulses
//#define REDUCTION_RATIO 36    // reduction ratio 
//#define MOTOR_TOLERANCE 688	// position loop's tolerance  30du
//#define CNT_PER_ROUND_OUT (CNT_PER_ROUND * REDUCTION_RATIO) // motor rolls one circle -> pulses


//float ANGLE_BASE = 0 ; 

/* Private variables ---------------------------------------------------------*/
//extern void get_total_angle(moto_measure_t *p);
PID_TypeDef outer_ppid[3];		//	x, y, angle
//PID_TypeDef big_vpid[3];			// mecanum speed
PID_TypeDef motor_vpid[4];		// motor speed

float distance[3] ={0};

//  Initialization
struct mecanum chassis ={0, 0, 0, 0,0,0};
struct mecanum *pchassis = &chassis;

//int32_t set_angle = 8192;		//8192 is 1 roll!
//int32_t set_spd = 4000;

//static int key_sta = 0;
//int speed_step_sign = +1;

uint16_t TIM_COUNT[2];
//int16_t round_CNT;

//#define SpeedStep 	8192.f/3.f

int fputc(int ch, FILE *f)
	{
	 HAL_UART_Transmit(&huart2,(uint8_t *)&ch,1,1000);
		return ch;
	}
	
	
	
	
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void Goto(float x, float y, float angle)		//  x:right ;  y: front!
{
		outer_ppid[0].target = x;
		outer_ppid[1].target = y;
		outer_ppid[2].target = angle;
//		mecanum_calculate(pchassis);
		pid_calculate(&outer_ppid[0],distance[0]);						//PID calculate** distance : speed integral = pass distance 
		pid_calculate(&outer_ppid[1],distance[1]);
		pid_calculate(&outer_ppid[2],distance[2]);
	 
//		big_vpid[0].target = outer_ppid[0].output;			//	Vx!
//		big_vpid[1].target = outer_ppid[1].output;			//	Vy!
//		big_vpid[2].target = outer_ppid[2].output;			//	Vw!
//		pchassis->xv_mm_s = x;			//	Vx!
//		pchassis->yv_mm_s = y;			//	Vy!
//		pchassis->zw_deg_s= angle;			//	Vw!
		pchassis->xv_mm_s = outer_ppid[0].output;			//	Vx!
		pchassis->yv_mm_s = outer_ppid[1].output;			//	Vy!
		pchassis->zw_deg_s= outer_ppid[2].output;			//	Vw!

		mecanum_calculate(pchassis);
		for(int i=0; i<4; i++)
    {	
      motor_vpid[i].target = pchassis->wheel_rpm[i]; 								//	vpid reduce to small		
			pid_calculate(&motor_vpid[i],moto_chassis[i].speed_rpm);						//PID calculate	
    }
		set_moto_current(&hcan1, motor_vpid[0].output,   
                        motor_vpid[1].output,
                        motor_vpid[2].output,
                        motor_vpid[3].output);
// Here : whether to calculate again?		
//		int v_tx = (moto_chassis[1].speed_rpm - moto_chassis[2].speed_rpm)/2;
//		int v_ty = (moto_chassis[0].speed_rpm + moto_chassis[1].speed_rpm)/2;
//		int v_tz = (moto_chassis[0].speed_rpm - moto_chassis[2].speed_rpm )/(wheelbase + wheeltrack);
	
// Here : whether to calculate again?		
// pass distance!   all use one time just ok ,it's the same. here-> motor[0] 		
		distance[0] += (moto_chassis[1].speed_rpm - moto_chassis[2].speed_rpm)/4320.0f*wheel_perimeter * motor_vpid[0].dtime /1000.0f;		// motor_vpid's "dtime" use to cal Integral of chassis distance
		distance[1] += (-moto_chassis[0].speed_rpm + moto_chassis[1].speed_rpm)/4320.0f*wheel_perimeter * motor_vpid[0].dtime /1000.0f;
	// Here!  	angle needs to be corrected	!!!		ignore temporarily
		distance[2] += (-moto_chassis[0].speed_rpm - moto_chassis[2].speed_rpm )/(wheelbase + wheeltrack)/2160.0f*wheel_perimeter * motor_vpid[0].dtime /1000.0f;

//			distance[0] += pchassis->xv_mm_s * motor_vpid[0].dtime *1000;				//dtime unit is ms
//			distance[1] += pchassis->yv_mm_s * motor_vpid[0].dtime *1000;				//dtime unit is ms				here distance unit is mm
//			distance[2] += pchassis->zw_deg_s * motor_vpid[0].dtime *1000;				//dtime unit is ms
		
//	printf("%f/t%f/t%f/n",distance[0],distance[1],distance[2]);
		
}


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN1_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */
  my_can_filter_init_recv_all(&hcan1);     //配置CAN过滤器
  HAL_CAN_Receive_IT(&hcan1, CAN_FIFO0);   //启动CAN接收中断
  HAL_UART_Receive_IT_IDLE(&huart1,UART_Buffer,100);   //启动串口接收
  HAL_TIM_IC_Start_DMA(&htim1,TIM_CHANNEL_2,(uint32_t *)TIM_COUNT,2);		// encoder's necessity -> tim 
	
	
	/*< 初始化PID参数 >*/
	for(int i=0; i<3; i++)
  {	
    pid_init(&outer_ppid[i]);
//		pid_init(&big_vpid[i]);
		outer_ppid[i].f_param_init(&outer_ppid[i],PID_Position,16384,5000,10,0,8000,0,1.5,6,0);  
//		big_vpid[i].f_param_init(&big_vpid[i],PID_Speed,16384,5000,10,0,8000,0,1.5,0,0);
  }
	
  for(int i=0; i<4; i++)
  {	
    pid_init(&motor_vpid[i]);
    motor_vpid[i].f_param_init(&motor_vpid[i],PID_Speed,2000,5000,10,0,8000,0,1.5,0.1,0);    
  }

	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	

//    if(HAL_GetTick() - Latest_Remote_Control_Pack_Time >500){   //如果500ms都没有收到遥控器数据，证明遥控器可能已经离线，切换到按键控制模式。
//      Key_Scan();
//    }else{		
//      set_spd = remote_control.ch4*8000/660;
//    }
	

//		printf("%d\t%f\n",moto_chassis[1].speed_rpm,moto_chassis[1].real_current);
//		printf("set: %d\treal: %d\n",set_spd, moto_chassis[1].speed_rpm);

//		set_moto_current(&hcan1,100,300,500,700);
//		printf("rpm:%d\tcurrent:%f\n",moto_chassis[0].speed_rpm,moto_chassis[0].real_current);
//		printf("rpm:%d\tcurrent:%f\n",moto_chassis[1].speed_rpm,moto_chassis[1].real_current);
//		printf("rpm:%d\tcurrent:%f\n",moto_chassis[2].speed_rpm,moto_chassis[2].real_current);
//		printf("rpm:%d\tcurrent:%f\n",moto_chassis[3].speed_rpm,moto_chassis[3].real_current);
			Goto(0,1000,0);					//	x>0 left |||  y>0 front
		
			HAL_Delay(10);      //PID控制频率100HZ
//		cnt++;
		
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
/* USER CODE BEGIN Callback 0 */
//  TIM6 is unavailable!
/* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
/* USER CODE BEGIN Callback 1 */

/* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
