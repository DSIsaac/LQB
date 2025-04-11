#include "Key.h"
#include "main.h"
#include "Global_Type.h"
#include "string.h"

typedef enum{
	idle = 0,
	pressed = 1,
	debouncing = 2,
	released = 3,
}Key_State_Type;

Key_State_Type key_current_state[4] = {0, 0, 0, 0};
GPIO_PinState key_last_state[4] = {0};
uint8_t key_state_count[4] = {0, 0, 0, 0};
GPIO_TypeDef* key_port[4] = {GPIOB, GPIOB, GPIOB, GPIOA};
uint16_t key_pin[4] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_0};

uint8_t debouncing_count = 5;

Key_State_Type checkState = released;

_Bool Check_Password();

void Key_Scan(void)
{
	for(uint8_t i = 0; i < 4; i++){
		GPIO_PinState state = HAL_GPIO_ReadPin(key_port[i], key_pin[i]);
		if(state == GPIO_PIN_RESET){
			if(key_current_state[i] == idle){
				key_current_state[i] = debouncing;
				key_state_count[i] = 1;
			}
			else if(key_current_state[i] == debouncing){
				if(key_state_count[i] > debouncing_count){
					key_state_count[i] = 0;
					key_current_state[i] = pressed;
				}
				else{
					key_state_count[i]++;
				}
			}
		}
		else if(state == GPIO_PIN_SET){
			if(key_current_state[i] == idle || key_current_state[i] == released){
				continue;
			}
			else if(key_current_state[i] == pressed){
				key_current_state[i] = released;
			}
			else if(key_current_state[i] == debouncing){
				key_current_state[i] = idle;
				key_state_count[i] = 0;
			}
		}
	}
}



void Key_Deal(void)
{
	Key_Scan();
	
	for(uint8_t i = 0; i < 4; i++){
		if(SettingManager.Interface == Interface2_Type){
			if((key_current_state[i] == checkState) && i < 3){
				if((SettingManager.inputPassword[i] == 0x40) || (SettingManager.inputPassword[i] >= 0x39)){
					SettingManager.inputPassword[i] = 0x30;
				}
				else{
					SettingManager.inputPassword[i]++;
				}
				key_current_state[i] = idle;
			}
			else if((key_current_state[i] == checkState) && (i == 3)){
				if(Check_Password()){
					SettingManager.Interface = Interface1_Type;
					SettingManager.Interface_Need_Change = 1;
					SettingManager.passwordRight = 1;
					SettingManager.passwordWrongCount = 0;
				}
				else{
					SettingManager.inputPassword[0] = 0x40;
					SettingManager.inputPassword[1] = 0x40;
					SettingManager.inputPassword[2] = 0x40;
					SettingManager.passwordWrongCount++;
				}
				key_current_state[i] = idle;
			}
		}
	}
}

_Bool Check_Password()
{
	if((SettingManager.currentPassword[0] == SettingManager.inputPassword[0] - 0x30) &&
	   (SettingManager.currentPassword[1] == SettingManager.inputPassword[1] - 0x30) &&
	   (SettingManager.currentPassword[2] == SettingManager.inputPassword[2] - 0x30))
		return 1;
	else
		return 0;
}
