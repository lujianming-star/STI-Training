//#include <stdio.h>
//#include <stdint.h>
//#include <usart.h>

///**
//  * ��������: �ض���c�⺯��printf��DEBUG_USARTx
//  * �������: ��
//  * �� �� ֵ: ��
//  * ˵    ������
//  */
//int fputc(int ch, FILE *f)
//{
//  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);
//  return ch;
//}
// 
///**
//  * ��������: �ض���c�⺯��getchar,scanf��DEBUG_USARTx
//  * �������: ��
//  * �� �� ֵ: ��
//  * ˵    ������
//  */
//int fgetc(FILE *f)
//{
//  uint8_t ch = 0;
//  HAL_UART_Receive(&huart3, &ch, 1, 0xffff);
//  return ch;
//}
