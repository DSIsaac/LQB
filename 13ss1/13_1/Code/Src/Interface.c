#include "Interface.h"
#include "lcd.h"
#include "stdlib.h"
#include "string.h"
#include "Global_Type.h"
#include "Led.h"

#define Column(x)	335 - 16 * x

void Interface1(uint8_t changeInterface);
void Interface2(uint8_t changeInterface);

void Interface_Init()
{
	LCD_SetTextColor(White);
	LCD_SetBackColor(Black);
	LCD_Clear(Black);
	Interface_Task();
}

void Interface_Task()
{
	if(SettingManager.Interface == Interface1_Type){
		LCD_ClearLine(Line6);
		Interface1(SettingManager.Interface_Need_Change);
	}
	else if(SettingManager.Interface == Interface2_Type)
		Interface2(SettingManager.Interface_Need_Change);
	Led_Set_State(SettingManager.ledState);
}

static inline void Interface1_Update(char* str1, char* str2)
{
	str1[0] = SettingManager.frequency / 1000 + 0x30;
	str1[1] = SettingManager.frequency % 1000 / 100 + 0x30;
	str1[2] = SettingManager.frequency % 100 / 10 + 0x30;
	str1[3] = SettingManager.frequency % 10 + 0x30;
	
	str2[0] = SettingManager.duty / 10 + 0x30;
	str2[1] = SettingManager.duty % 10 + 0x30;
}

void Interface1(uint8_t changeInterface)
{
	static char line1[] = "       STA";
	static char line2_static1[] = "    F:";	static char line2_static2[] = "Hz";	static char line2_update[] = "0000";
	static char line3_static1[] = "    D:";	static char line3_static2[] = "%";	static char line3_update[] = "00";
	static char line2[20] = {0};	static char line3[20] = {0};
	
	Interface1_Update(line2_update, line3_update);
	
	if(changeInterface){
		memset(line2, 0, 20);			memset(line3, 0, 20);
		strcat(line2, line2_static1);	strcat(line2, line2_update);	strcat(line2, line2_static2);
		strcat(line3, line3_static1);	strcat(line3, line3_update);	strcat(line3, line3_static2);
		
		LCD_DisplayStringLine(Line2, line1);
		LCD_DisplayStringLine(Line4, line2);
		LCD_DisplayStringLine(Line5, line3);
		SettingManager.Interface_Need_Change = 0;
	}
	else{
		LCD_DisplayChar(Line4,  Column(7), line2_update[0]);
		LCD_DisplayChar(Line4,  Column(8), line2_update[1]);
		LCD_DisplayChar(Line4,  Column(9), line2_update[2]);
		LCD_DisplayChar(Line4, Column(10), line2_update[3]);
		
		LCD_DisplayChar(Line5,  Column(7), line3_update[0]);
		LCD_DisplayChar(Line5,  Column(8), line3_update[1]);
	}
}

static inline void Interface2_Update(char* str1, char* str2, char* str3)
{
	str1[0] = SettingManager.inputPassword[0];
	str2[0] = SettingManager.inputPassword[1];
	str3[0] = SettingManager.inputPassword[2];
}

void Interface2(uint8_t changeInterface)
{
	static char line1[] = "       PSD";
	static char line2_static[] = "    B1:";	static char line2_update[] = "0";
	static char line3_static[] = "    B2:";	static char line3_update[] = "0";
	static char line4_static[] = "    B3:";	static char line4_update[] = "0";
	static char line2[20] = {0};	static char line3[20] = {0};	static char line4[20] = {0};
	
	Interface2_Update(line2_update, line3_update, line4_update);
	
	if(changeInterface){
		memset(line2, 0, 20);			memset(line3, 0, 20);
		strcat(line2, line2_static);	strcat(line2, line2_update);
		strcat(line3, line3_static);	strcat(line3, line3_update);
		strcat(line4, line4_static);	strcat(line4, line4_update);
		
		LCD_DisplayStringLine(Line2, line1);
		LCD_DisplayStringLine(Line4, line2);
		LCD_DisplayStringLine(Line5, line3);
		LCD_DisplayStringLine(Line6, line4);
		SettingManager.Interface_Need_Change = 0;
	}
	else{
		LCD_DisplayChar(Line4,  Column(8), line2_update[0]);		
		LCD_DisplayChar(Line5,  Column(8), line3_update[0]);
		LCD_DisplayChar(Line6,  Column(8), line4_update[0]);
	}
}