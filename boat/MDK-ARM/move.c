#include "gpio.h"
#include "move.h"
#include "tim.h"
//extern uint8_t m_dir[4]={1,2,3,4};
 uint16_t m_dir[4]={GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,GPIO_PIN_4};
 uint16_t v_pwm[2]={300,300};
 uint8_t v_dir[2]={1,1};
 //�ı䷽��
void change_pwm(int ch,int dir,int vel)
{
	HAL_GPIO_WritePin(GPIOD,m_dir[2*ch],dir);
	HAL_GPIO_WritePin(GPIOD,m_dir[2*ch+1],!dir);
	v_pwm[ch]=vel;
}
//��ʼ������
void dir_init()
{	for(int i=0;i<2;i++)
		{	HAL_GPIO_WritePin(GPIOD,m_dir[2*i],v_dir[i]);
			HAL_GPIO_WritePin(GPIOD,m_dir[2*i+1],!v_dir[i]);
		}
}
//�˶�
void go_pwm()
{	TIM3->CCR1=v_pwm[0]; //��ֵ����������uint16_t
	TIM3->CCR2=v_pwm[1];

}
//ֱ��
void straight()
{	change_pwm(0,1,300);
	change_pwm(1,1,300);
	go_pwm();
}
//ֹͣ
void pause()
{	change_pwm(0,0,0);
	change_pwm(1,0,0);
	go_pwm();
}
//��ת
void left()
{	change_pwm(0,0,150);
	change_pwm(1,1,400);
	go_pwm();
}
//��ת
void right()
{	change_pwm(0,1,400);
	change_pwm(1,0,150);
	go_pwm();
}
//����
void avoid()
{	uint8_t a1=HAL_GPIO_ReadPin(GPIOA,8);
	uint8_t a2=HAL_GPIO_ReadPin(GPIOA,9);
	if (a1==0)
	{	right();}
	if (a2==0)
	{	left();}
}
	