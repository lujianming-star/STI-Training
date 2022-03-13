#include "Mecanum.h"
#include "main.h"


void MEC_VAL_LIMIT(float val, float min, float max) 
{
				do 
				{
						if ((val) <= (min)) 
						{ 
							(val) = (min); 
						} 
						else if ((val) >= (max)) 
						{
							(val) = (max);
						}
				} while (0);
}


void mecanum_calculate(struct mecanum *pchassis)
{ static float rotate_ratio_fr;
	static float rotate_ratio_fl;
	static float rotate_ratio_bl;
	static float rotate_ratio_br;
	static float wheel_rpm_ratio; 
	
//	//  Initialization
//	pchassis->wheel_perimeter=152*PI;
//	pchassis->wheeltrack=430;
//	pchassis->wheelbase=360;
//	pchassis->rotate_x_offset=0;
//	pchassis->rotate_y_offset=0;
//	pchassis->xv_mm_s=1500;
//	pchassis->yv_mm_s=2000;
//	pchassis->zw_deg_s=0;
//	pchassis->wheel_rpm[0] = 1;
//	pchassis->wheel_rpm[1] = 0;
//	pchassis->wheel_rpm[2] = 0;
//	pchassis->wheel_rpm[3] = 0;
	

	rotate_ratio_fr = ((wheelbase + wheeltrack) / 2.0f - pchassis->rotate_x_offset + pchassis->rotate_y_offset) / 57.3f; 
	rotate_ratio_fl = ((wheelbase + wheeltrack) / 2.0f - pchassis->rotate_x_offset - pchassis->rotate_y_offset) / 57.3f;
	rotate_ratio_bl = ((wheelbase + wheeltrack) / 2.0f + pchassis->rotate_x_offset - pchassis->rotate_y_offset) / 57.3f; 
	rotate_ratio_br = ((wheelbase + wheeltrack) / 2.0f + pchassis->rotate_x_offset + pchassis->rotate_y_offset) / 57.3f;
	wheel_rpm_ratio = 60.0f / (wheel_perimeter * MOTOR_DECELE_RATIO);		// r/mm		??
	

	MEC_VAL_LIMIT(pchassis->xv_mm_s, -MAX_CHASSIS_VX_SPEED, MAX_CHASSIS_VX_SPEED);
	MEC_VAL_LIMIT(pchassis->yv_mm_s, -MAX_CHASSIS_VY_SPEED, MAX_CHASSIS_VY_SPEED);
	MEC_VAL_LIMIT(pchassis->zw_deg_s, -MAX_CHASSIS_VW_SPEED, MAX_CHASSIS_VW_SPEED);

	float TEPwheel_rpm[4];
	float max = 0;
	// Unit change to rpm: 
	TEPwheel_rpm[0] = (pchassis->xv_mm_s - pchassis->yv_mm_s + pchassis->zw_deg_s * rotate_ratio_fr) * wheel_rpm_ratio; 
	TEPwheel_rpm[1] = (pchassis->xv_mm_s + pchassis->yv_mm_s + pchassis->zw_deg_s * rotate_ratio_fl) * wheel_rpm_ratio;
	TEPwheel_rpm[2] = (-pchassis->xv_mm_s + pchassis->yv_mm_s + pchassis->zw_deg_s * rotate_ratio_bl) * wheel_rpm_ratio; 
	TEPwheel_rpm[3] = (-pchassis->xv_mm_s - pchassis->yv_mm_s + pchassis->zw_deg_s * rotate_ratio_br) * wheel_rpm_ratio;
	
//	printf("%f\n",wheel_rpm_ratio);
//	printf("%f\n",TEPwheel_rpm[0]);
//	printf("%f\n",TEPwheel_rpm[1]);
//	printf("%f\n",TEPwheel_rpm[2]);
//	printf("%f\n",TEPwheel_rpm[3]);
//	HAL_Delay(2000);
	
	// FIND max item
	int abs[4];
	for (int i = 0; i < 4; i++)
	{ 
		if(TEPwheel_rpm[i] > 0)		
			abs[i] = 	TEPwheel_rpm[i];
		else 
			abs[i] = 	-TEPwheel_rpm[i];
	}
	
	for (int i = 0; i < 4; i++)
	{ 
		if(abs[i] > max)		
			max = abs[i];
	}
	
//	printf("%f\n",max);
//	HAL_Delay(2000);
	
//  Equal proportion 
	if (max > MAX_WHEEL_RPM) 
	{ 
		float rate = MAX_WHEEL_RPM / max; 
		for (int i = 0; i < 4; i++) 
			TEPwheel_rpm[i] *= rate; 
	}
	
	pchassis->wheel_rpm[0]=TEPwheel_rpm[0];
	pchassis->wheel_rpm[1]=TEPwheel_rpm[1]; 
	pchassis->wheel_rpm[2]=TEPwheel_rpm[2]; 
	pchassis->wheel_rpm[3]=TEPwheel_rpm[3];
	

}

