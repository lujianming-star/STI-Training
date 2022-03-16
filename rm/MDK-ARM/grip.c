#include "grip.h"
#include "tim.h"
#include "motor_pid.h"
#include "math.h"
#define pi 3.1415
extern float servoAngle[4];
void rm_servo(double angle, float target_speed)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//GM6020ռ�ձ�Ϊ5%��10%����СֵΪ3599*5%=179.95 ���ֵΪ3599*10%=359.9
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		double arr ;
		arr = (179.0/360)*angle + 165;
		TIM8->CCR1 = arr;
		rotor_pid_task(target_speed);
		HAL_Delay(100);

}
void servo1(float angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ4199*2.5%=105 ���ֵΪ4199*12.5%=524
		//��Ӧ�Ƕ� ccr = 0.5*angle + 179
		float arr ;
		arr = 2.3*angle + 315;
		TIM2->CCR1 = arr;
		HAL_Delay(100);
		//-90~90

}
void servo2(float angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ3599*2.5%=89.975 ���ֵΪ3599*12.5%=449.875
		//��Ӧ�Ƕ� ccr = 2.3*angle + 524
		float arr ;
		arr = 2.3*angle + 524;
		TIM2->CCR2 = arr;
		HAL_Delay(100);
		//-180��0
}
void servo3(float angle)
{
		//�󽮰��Ӷ�ӦAPB1���裬ʱ��Ƶ�ʶ�Ӧ36Mhz
		//���߶��ռ�ձ�Ϊ2.5%��12.5%����СֵΪ4199*2.5%=105 ���ֵΪ4199*12.5%=524
		//��Ӧ�Ƕ� ccr = 2.3*angle + 315
		float arr ;
		arr = 2.3*angle + 315;
		TIM2->CCR3 = arr;
		HAL_Delay(100);
		//-90~90
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


void init_pos()
{
//	attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta);
//	servo1(servoAngle[0]);
//	servo2(servoAngle[1]);
//	servo3(servoAngle[2]);
//	rm_servo(servoAngle[3], target_speed);
}
void move_get()
{
//	attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta);
//	servo1(servoAngle[0]);
//	servo2(servoAngle[1]);
//	servo3(servoAngle[2]);
//	rm_servo(servoAngle[3], target_speed);
}
void move_put()
{
//	attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta);
//	servo1(servoAngle[0]);
//	servo2(servoAngle[1]);
//	servo3(servoAngle[2]);
//	rm_servo(servoAngle[3], target_speed);
}

//���㲿��
uint8_t attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta)
{
	
	float L1 = 0.20; //�˳�
	float L2 = 0.12;
	float L3 = 0.13;
	float alpha, beta, lp, By, Bz;
	By = S.pointY-L3; //�������æ�Ϊ-90
	Bz = S.pointZ;
	lp = By*By + Bz*Bz;
	
	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
		return 1;
	alpha = atan2(Bz,By);
	
	beta = acos((L1*L1+lp-L2*L2)/(2.0*L1*sqrt(lp))); //����ʹ�û�����

	ptheta[0] = (-(pi/2.0-alpha-beta))*180.f/pi;								//1�Ŷ���Ƕ�
	ptheta[1] = (acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi)*180.f/pi;	//2�Ŷ���Ƕ�
	ptheta[2] = (-ptheta[0] -ptheta[1]- 90);										//3�Ŷ���Ƕ�,ע��ptheta2�ǽǶ�����
	ptheta[3] = (atan2(S.pointX, S.pointY))*180.f/pi;						//��̨����Ƕ�
	return 0;
}

uint8_t attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta)
{
	
	float L1 = 0.20; //�˳�
	float L2 = 0.12;
	float L3 = 0.13;
	float alpha, beta, lp, By, Bz;
	By = S.pointY; //�������æ�Ϊ-90
	Bz = S.pointZ + L3;
	lp = By*By + Bz*Bz;
	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
		return 1;
	alpha = atan2(Bz,By);
	beta = acos((L1*L1+lp-L2*L2)/(2*L1*sqrt(lp))); //����ʹ�û�����,ע�����������ת�����Լ�ת��Ϊ�Ƕ���
	ptheta[0] = (-(pi/2.0-alpha-beta))*180.f/pi;
	ptheta[1] = (acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi)*180.f/pi;
	ptheta[2] = (-ptheta[0] -ptheta[1]- 180);
	ptheta[3] = (atan2(S.pointX, S.pointY))*180.f/pi;
	return 0;
}
	