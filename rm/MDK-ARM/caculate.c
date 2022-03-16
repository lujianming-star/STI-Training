//#include "caculate.h"
//#include "math.h"
//#define pi 3.1415



//uint8_t attitudeGetAngle_get(const MecArmAttiSturcture S, float *ptheta)
//{
//	float L1 = 0.14; //杆长
//	float L2 = 0.11;
//	float L3 = 0.04;
//	float alpha, beta, lp, By, Bz;
//	By=S.pointY-L3; //这里设置γ为-90
//	Bz=S.pointZ;
//	lp=S.pointY*S.pointY+S.pointZ*S.pointZ;
//	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
//		return 1;
//	alpha = atan2(Bz,By);
//	beta = acos((L1*L1+lp-L2*L2)/(2*L1*sqrt(lp))); //这里使用弧度制
//	ptheta[0] = -(pi/2.0-alpha-beta);								//1号舵机角度
//	ptheta[1] = acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi;	//2号舵机角度
//	ptheta[2] = -ptheta[0] -ptheta[1]- pi/2.0;				//3号舵机角度
//	ptheta[3] = atan2(S.pointX, S.pointY);						//云台舵机角度
//	return 0;
//}

//uint8_t attitudeGetAngle_put(const MecArmAttiSturcture S, float *ptheta)
//{
//	float L1 = 0.14; //杆长
//	float L2 = 0.11;
//	float L3 = 0.04;
//	float alpha, beta, lp, By, Bz;
//	By=S.pointY-L3; //这里设置γ为-90
//	Bz=S.pointZ;
//	lp=S.pointY*S.pointY+S.pointZ*S.pointZ;
//	if (sqrt(lp)>=L1+L2 || sqrt(lp)<=fabs(L1-L2))
//		return 1;
//	alpha = atan2(Bz,By);
//	beta = acos((L1*L1+lp-L2*L2)/(2*L1*sqrt(lp))); //这里使用弧度制,注意除法的类型转换，以及转换为角度制
//	ptheta[0] = -(pi/2.0-alpha-beta);
//	ptheta[1] = acos((L1*L1+L2*L2-lp)/(2*L1*L2))-pi;
//	ptheta[2] = -ptheta[0] -ptheta[1]- pi;
//	ptheta[3] = atan2(S.pointX, S.pointY);
//	return 0;
//}
//	
//	