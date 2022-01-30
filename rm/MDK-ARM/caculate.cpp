#include "caculate.h"
#include "math.h"
using namespace std;
/*
①得到空间点坐标x , y, z
②求θ2，β， cao
③判断θ2正负
④求θ1
⑤求θ3
⑥弧度变角度
*/
/*double caculate(double x, double y, double z)
{
	double L1, L2;
	double xita[3], beta, cao;
	xita[1] = acos((x^2 + y^2 - L1^2 - L2^2)/(-2*L1*L2));
	beta = atan2(y, x);
	cao = acos((x^2 + y^2 + L1^2 - L2^2)/(2*L1*sqrt(x^2 + y^2)));
	xita[0] = xita[1] > 0 ? (beta - cao) : (beta + cao) ;
	xita[2] = - xita[0] - xita[1];
	double angle[3];
	for(int i = 0; i < 3; i++)
	{
		angle[i] = xita[i]*180/pi;
	}
}
*/
class CAC
{
	public:
	double caculate(double x, double y, double z)
	{
		double L1, L2;
		double xita[3], beta, cao;
		xita[1] = acos((x^2 + y^2 - L1^2 - L2^2)/(-2*L1*L2));
		beta = atan2(y, x);
		cao = acos((x^2 + y^2 + L1^2 - L2^2)/(2*L1*sqrt(x^2 + y^2)));
		xita[0] = xita[1] > 0 ? (beta - cao) : (beta + cao) ;
		xita[2] = - xita[0] - xita[1];
		double angle[3];
		for(int i = 0; i < 3; i++)
		{
			angle[i] = xita[i]*180/pi;
		}
		return 0;
	}
};
	