#include "grip.h"
#include "tim.h"
void rm_servo(double angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//GM6020ռ�ձ�Ϊ5%��10%����СֵΪ3599*5%=179.95 ���ֵΪ3599*10%=359.9
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		double arr ;
		arr = (179.0/360)*angle + 180;
		TIM2->CCR1 = arr;
		HAL_Delay(100);

}
void servo1(float angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ3599*2.5%=89.975 ���ֵΪ3599*12.5%=449.875
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR1 = arr;
		HAL_Delay(100);

}
void servo2(float angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ3599*2.5%=89.975 ���ֵΪ3599*12.5%=449.875
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR2 = arr;
		HAL_Delay(100);

}
void servo3(float angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ3599*2.5%=89.975 ���ֵΪ3599*12.5%=449.875
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR3 = arr;
		HAL_Delay(100);

}
void clip(double angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ3599*2.5%=89.975 ���ֵΪ3599*12.5%=449.875
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR4 = arr;
		HAL_Delay(100);

}

//��ʼ��̬
double init_pos()
{
	servo1(27);
	servo2(120);
	servo3(60);
	clip(100);   //���޸�
	return 0;
}

//�½�
double down()
{
	for(double ag1 = 27; ag1 < 33; ag1++)
	{
		servo1(ag1);
		HAL_Delay(10);
	}
	for(double ag2 = 120; ag2 < 122; ag2++)
	{
		servo2(ag2);
		HAL_Delay(10);
	}
	for(double ag3 = 60; ag3 < 66; ag3++)
	{
		servo3(ag3);
		HAL_Delay(10);
	}
	return 0;
}

//����
double up()
{
		for(double ag1 = 33; ag1 > 27; ag1--)
	{
		servo1(ag1);
		HAL_Delay(10);
	}
	for(double ag2 = 122; ag2 > 120; ag2--)
	{
		servo2(ag2);
		HAL_Delay(10);
	}
	for(double ag3 = 66; ag3 > 60; ag3--)
	{
		servo3(ag3);
		HAL_Delay(10);
	}
	return 0;
}

//����ץȡ
double grip()
{
	for(double ag4 = 100; ag4>50; ag4--)
	{
		clip(ag4);		//���޸�
		HAL_Delay(10);
	}
	return 0;
}

//�����ɿ�
double loose()
{
	for(double ag4 = 50; ag4 < 100; ag4++)
	{
		clip(ag4);		//���޸�
		HAL_Delay(10);
	}
	return 0;
}

//ץȡ�������������
void get()
{
	down();
	grip();
	up();
}

//�����������������
void putDown()
{
	down();
	loose();
	up();
}