#include "caculate.h"
#include "math.h"
/*
①得到空间点坐标x , y, z
②求θ2，β， cao
③判断θ2正负
④求θ1
⑤求θ3
⑥弧度变角度
*/
//double angle[3];
//double caculate(double x, double y, double z)
//{
//	double L1, L2;
//	double xita[3], beta, cao;
//	xita[1] = acos((x*x + y*y - L1*L1 - L2*L2)/(-2*L1*L2));
//	beta = atan2(y, x);
//	cao = acos((x*x + y*y + L1*L1 - L2*L2)/(2*L1*sqrt(x*x + y*y)));
//	xita[0] = xita[1] > 0 ? (beta - cao) : (beta + cao) ;
//	xita[2] = - xita[0] - xita[1];
//	
//	for(int i = 0; i < 3; i++)
//	{
//		angle[i] = xita[i]*180/pi;
//	}
//	return 0;
//}

uint8_t attitudeGetAngle(const MecArmAttiSturcture S, float* pTheta)
{
    float lp = 0;
		int L1 = 140, L2 = 110;
		#define PI 3.14
		lp = sqrt(S.pointX*S.pointX + S.pointY*S.pointY);

	if(lp >= L1+L2 || lp <= fabs(L1-L2))
		return 1;

	if(S.mode == 1)
	{
		if(S.pointX < 0.05f)
			return 1;
		if(lp < 0.1f)
			return 1;
		
		pTheta[0] = 180.f/PI * (atanf(S.pointY/S.pointX) + acosf((L1*L1 + lp*lp - L2*L2) / (2.f*L1*lp)));
		pTheta[1] = 180.f/PI * (-acosf(-(L1*L1 + L2*L2 - lp*lp) / (2.f*L1*L2)));
		pTheta[2] = -pTheta[0] - pTheta[1] + S.handBiasAngle;
		return 0;
	}
	else if(S.mode == 2)
	{
		if(S.pointX < 0.f)
		{
			pTheta[0] = 180.f + 180.f/PI * (atanf(S.pointY/S.pointX) - acosf((L1*L1 + lp*lp - L2*L2) / (2.f*L1*lp)));
			pTheta[1] = 180.f/PI * (acosf(-(L1*L1 + L2*L2 - lp*lp) / (2.f*L1*L2)));
			pTheta[2] = 180.f - pTheta[0] - pTheta[1]+ S.handBiasAngle;
		}
		else
		{
			pTheta[0] = 180.f/PI * (atanf(S.pointY/S.pointX) - acosf((L1*L1 + lp*lp - L2*L2) / (2.f*L1*lp)));
			pTheta[1] = 180.f/PI * (acosf(-(L1*L1 + L2*L2 - lp*lp) / (2.f*L1*L2)));
			pTheta[2] = 180.f - pTheta[0] - pTheta[1]+ S.handBiasAngle;
		}
		return 0;
	}
	return 1;
}

	
	