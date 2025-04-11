#include "Timer.h"
#include "main.h"
#include "stdint.h"
#include "Global_Type.h"
#include "tim.h"

uint16_t PWM_Count = 0;
uint8_t PWM_State = 0;

void PWM_Task()
{
	if(PWM_State == 0){
		if(SettingManager.passwordRight == 0){
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, htim2.Instance->ARR / 2);
		}
		else if(SettingManager.passwordRight == 1 && PWM_Count == 0){
			__HAL_TIM_SetAutoreload(&htim2, htim2.Instance->ARR / 2);
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, htim2.Instance->ARR / 10);
			PWM_State = 1;
		}
	}
	else if(PWM_State == 1){
		if(PWM_Count < 500){
			PWM_Count++;
		}
		else{
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, htim2.Instance->ARR / 2);
			PWM_State = 2;
		}
	}
}