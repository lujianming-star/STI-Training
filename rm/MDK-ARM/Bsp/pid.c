/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
 
#include "pid.h"

/**
  * @brief  init pid parameter
  * @param  pid struct
    @param  parameter
  * @retval None
  */
void pid_init(pid_struct_t *pid,
              float kp,
              float ki,
              float kd,
              float i_max,
              float out_max)
{
  pid->kp      = kp;
  pid->ki      = ki;
  pid->kd      = kd;
  pid->i_max   = i_max;
  pid->out_max = out_max;
}

/**
  * @brief  pid calculation
  * @param  pid struct
    @param  reference value
    @param  feedback value
  * @retval calculation result
  */
float pid_calc(pid_struct_t *pid, float ref, float fdb)
{
  pid->ref = ref;			//目标值
  pid->fdb = fdb;			//反馈值
  pid->err[1] = pid->err[0];							//更新误差
  pid->err[0] = pid->ref - pid->fdb;			//计算误差
  
  pid->p_out  = pid->kp * pid->err[0];		//p值
  pid->i_out += pid->ki * pid->err[0];		//i值	
  pid->d_out  = pid->kd * (pid->err[0] - pid->err[1]);	//d值
  LIMIT_MIN_MAX(pid->i_out, -pid->i_max, pid->i_max);		//限制i的范围
  
  pid->output = pid->p_out + pid->i_out + pid->d_out;			//计算完的pid
  LIMIT_MIN_MAX(pid->output, -pid->out_max, pid->out_max); //限制pid的范围
  return pid->output;
}
