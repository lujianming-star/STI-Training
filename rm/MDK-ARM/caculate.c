//#include "caculate.h"
//#include "math.h"
//#define pi 3.1415



//uint8_t attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta)
//{
//	float L1 = 0.14; //�˳�
//	float L2 = 0.11;
//	float L3 = 0.04;
//	float alpha, beta, lp, By, Bz;
//	By=S.pointY-L3; //�������æ�Ϊ-90
//	Bz=S.pointZ;
//	lp=S.pointY*S.pointY+S.pointZ*S.pointZ;
//	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
//		return 1;
//	alpha = atan2(Bz,By);
//	beta = acos((L1*L1+lp-L2*L2)/(2*L1*sqrt(lp))); //����ʹ�û�����
//	ptheta[0] = -(pi/2.0-alpha-beta);								//1�Ŷ���Ƕ�
//	ptheta[1] = acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi;	//2�Ŷ���Ƕ�
//	ptheta[2] = -ptheta[0] -ptheta[1]- pi/2.0;				//3�Ŷ���Ƕ�
//	ptheta[3] = atan2(S.pointX, S.pointY);						//��̨����Ƕ�
//	return 0;
//}

//uint8_t attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta)
//{
//	float L1 = 0.14; //�˳�
//	float L2 = 0.11;
//	float L3 = 0.04;
//	float alpha, beta, lp, By, Bz;
//	By=S.pointY-L3; //�������æ�Ϊ-90
//	Bz=S.pointZ;
//	lp=S.pointY*S.pointY+S.pointZ*S.pointZ;
//	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
//		return 1;
//	alpha = atan2(Bz,By);
//	beta = acos((L1*L1+lp-L2*L2)/(2*L1*sqrt(lp))); //����ʹ�û�����,ע�����������ת�����Լ�ת��Ϊ�Ƕ���
//	ptheta[0] = -(pi/2.0-alpha-beta);
//	ptheta[1] = acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi;
//	ptheta[2] = -ptheta[0] -ptheta[1]- pi;
//	ptheta[3] = atan2(S.pointX, S.pointY);
//	return 0;
//}
//	
//	