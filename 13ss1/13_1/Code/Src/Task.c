#include "Task.h"
#include "Global_Type.h"
#include "Led.h"
#include "Interface.h"
#include "Key.h"
#include "Timer.h"

void Task_1000Hz()
{
	if(SettingManager.timerCount._1000Hz >= SettingManager.taskCount._1000Hz){
		SettingManager.timerCount._1000Hz = 0;
		
	}
}

void Task_500Hz()
{
	if(SettingManager.timerCount._500Hz >= SettingManager.taskCount._500Hz){
		SettingManager.timerCount._500Hz = 0;
		
	}
}

void Task_200Hz()
{
	if(SettingManager.timerCount._200Hz >= SettingManager.taskCount._200Hz){
		SettingManager.timerCount._200Hz = 0;
		
	}
}

void Task_100Hz()
{
	if(SettingManager.timerCount._100Hz >= SettingManager.taskCount._100Hz){
		SettingManager.timerCount._100Hz = 0;
		
		Key_Deal();
		PWM_Task();
		Interface_Task();
	}
}

void Task_10Hz()
{
	if(SettingManager.timerCount._10Hz >= SettingManager.taskCount._10Hz){
		SettingManager.timerCount._10Hz = 0;
		Led_Task();
	}
}

void Task_1Hz()
{
	if(SettingManager.timerCount._1Hz >= SettingManager.taskCount._1Hz){
		SettingManager.timerCount._1Hz = 0;
		
		
	}
}

void Task_0_2Hz()
{
	if(SettingManager.timerCount._0_2Hz >= SettingManager.taskCount._0_2Hz){
		SettingManager.timerCount._0_2Hz = 0;
		
		
	}
}

void Task_Loop()
{
	Task_1000Hz();
	Task_500Hz();
	Task_200Hz();
	Task_100Hz();
	Task_10Hz();
	Task_1Hz();
	Task_0_2Hz();
}
