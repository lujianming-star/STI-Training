#include "grip.h"
#include "tim.h"
void rm_servo(double angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//GM6020占空比为5%到10%，最小值为3599*5%=179.95 最大值为3599*10%=359.9
		//对应角度 ccr = 0.5*angle + 179
		double arr ;
		arr = (179.0/360)*angle + 180;
		TIM2->CCR1 = arr;
		HAL_Delay(100);

}
void servo1(float angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR1 = arr;
		HAL_Delay(100);

}
void servo2(float angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR2 = arr;
		HAL_Delay(100);

}
void servo3(float angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR3 = arr;
		HAL_Delay(100);

}
void clip(double angle)
{
		//大疆板子对应APB1外设，时钟频率对应36Mhz
		//三线舵机占空比为2.5%到12.5%，最小值为3599*2.5%=89.975 最大值为3599*12.5%=449.875
		//对应角度 ccr = 0.5*angle + 179
		float arr ;
		arr = angle + 90;
		TIM2->CCR4 = arr;
		HAL_Delay(100);

}

//初始姿态
double init_pos()
{
	servo1(27);
	servo2(120);
	servo3(60);
	clip(100);   //需修改
	return 0;
}

//下降
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

//上升
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

//夹子抓取
double grip()
{
	for(double ag4 = 100; ag4>50; ag4--)
	{
		clip(ag4);		//需修改
		HAL_Delay(10);
	}
	return 0;
}

//夹子松开
double loose()
{
	for(double ag4 = 50; ag4 < 100; ag4++)
	{
		clip(ag4);		//需修改
		HAL_Delay(10);
	}
	return 0;
}

//抓取物体的整个动作
void get()
{
	down();
	grip();
	up();
}

//放下物体的整个动作
void putDown()
{
	down();
	loose();
	up();
}