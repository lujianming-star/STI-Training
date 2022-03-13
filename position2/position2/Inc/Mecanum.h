#define MAX_CHASSIS_VX_SPEED 1000 
#define MAX_CHASSIS_VY_SPEED 1000 
#define MAX_CHASSIS_VW_SPEED 300 
#define INIT_current 3000 
#define MAX_WHEEL_RPM 	2000						//14976 			//9000rpm = 3732mm/s 	???		14976 when power is 24V;
//#define PI 3.14159265354f
#define MOTOR_DECELE_RATIO (1.0f / 36.0f) 			//jian su bi
#define HIGH_RmeoteSpeed 660 

#define PI 3.14159265354f
#define wheel_perimeter 76*PI		//zhouchang		mm!
#define wheeltrack 235			//hengxiang lunju
#define wheelbase 210       //qianhoulunde zhouju

struct mecanum{
float	rotate_x_offset;
float	rotate_y_offset;
float	xv_mm_s;
float	yv_mm_s;
float zw_deg_s;
float wheel_rpm[4];
};

void MEC_VAL_LIMIT(float val, float min, float max);
void mecanum_calculate(struct mecanum *pchassis);

