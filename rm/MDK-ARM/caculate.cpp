#include "caculate.h"
#include "math.h"
using namespace std;
/*
�ٵõ��ռ������x , y, z
�����2���£� cao
���жϦ�2����
�����1
�����3
�޻��ȱ�Ƕ�
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
	