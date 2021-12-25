#include "hmi.h"
#include "main.h"
#include "stm32f1xx_it.h"
#include "usart.h"
//uint8_t buf[64];
void HMISends(uint8_t *buf1)
{
	uint8_t i = 0;
	while(1)
	{
		if(buf1[i]!=0)
		{
			HAL_UART_Transmit(&huart2,buf1,sizeof(buf1),10000);
			while(HAL_UART_GetState(&huart2)!=RESET) {};  //ÅÐ¶Ï´®¿Ú×´Ì¬
			i++;
		}
		else
			return;
	}
}
void HMISendb(uint8_t k)
{
	uint8_t i;
	for(i=0;i<3;i++)
	{
		if(k!=0)
		{
			HAL_UART_Transmit(&huart2,&k,sizeof(k),10000);
			while(HAL_UART_GetState(&huart2)!=RESET) {};  //ÅÐ¶Ï´®¿Ú×´Ì¬
		}
		else
		return;
	}
}