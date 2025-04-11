#ifndef GLOBAL_TYPE_H
#define GLOBAL_TYPE_H

#include <stdint.h>

typedef struct{
	uint16_t _1000Hz;
	uint16_t _500Hz;
	uint16_t _200Hz;
	uint16_t _100Hz;
	uint16_t _10Hz;
	uint16_t _1Hz;
	uint16_t _0_2Hz;
}Timer_Flag;

typedef struct{
	uint16_t _1000Hz;
	uint16_t _500Hz;
	uint16_t _200Hz;
	uint16_t _100Hz;
	uint16_t _10Hz;
	uint16_t _1Hz;
	uint16_t _0_2Hz;
}Task_Flag;

typedef enum{
	Interface1_Type = 1,
	Interface2_Type = 2,
}Interface_Type;

typedef struct{
	Timer_Flag timerCount;
	Task_Flag taskCount;
	uint8_t ledState;
	uint16_t frequency;
	uint8_t duty;
	Interface_Type Interface;
	uint8_t Interface_Need_Change;
	uint8_t passwordRight;
	uint8_t passwordWrongCount;
	uint8_t defaultPassword[3];
	uint8_t currentPassword[3];
	uint8_t inputPassword[3];
}Setting;

extern Setting SettingManager;


#endif