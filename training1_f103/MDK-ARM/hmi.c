#include "hmi.h"
unsigned char buf[64];
void HMISends(char *buf1);
{
	uint8_t i=0;
	while(1)
	{
		if(buf1[i]!=0)
		{
			HAL_UART_Transmit(&huart2,buf1[i],sizeof(buf1[i]),10000);
			while(HAL_UART_GetState(&huart2)!=RESET) {};  //ÅÐ¶Ï´®¿Ú×´Ì¬
			i++;
		}
		else
			return;
	}
}
//void HMISendb(uint8_t k);