#ifndef _HMI_H
#define _HMI_H

void HMISends(char *buf1);	//字符串发送函数
void HMISendb(uint8_t k);	//函数功能：连续3次发送一个字节（一般用来发送0xff作为结束符） 



#endif