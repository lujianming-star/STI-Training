#ifndef _CACULATE_H
#define _CACULATE_H
#include "stdint.h"

//#define pi 3.141
//double caculate(double x, double y, double z);

typedef struct
{
    float pointX;
	float pointY;
	float handBiasAngle;
	uint8_t mode;	//	1 normal
	float panAngle;
} MecArmAttiSturcture;
uint8_t attitudeGetAngle(const MecArmAttiSturcture S, float* pTheta);

#endif