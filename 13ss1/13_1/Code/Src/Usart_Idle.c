#include "Usart_Idle.h"
#include "main.h"
#include "string.h"
#include "Global_Type.h"
#include "usart.h"

uint8_t usart1_rx_buf[20] = {0};

void Usart_Idle_Init()
{
	HAL_Delay(10);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	__HAL_UART_CLEAR_IDLEFLAG(&huart1);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, usart1_rx_buf, sizeof(usart1_rx_buf));
//	HAL_UART_Receive_IT(&huart1, usart1_rx_buf, sizeof(usart1_rx_buf));
//	HAL_UART_Receive_DMA(&huart1, usart1_rx_buf, sizeof(usart1_rx_buf));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1){
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		HAL_UART_DMAStop(&huart1);
		if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET ){
			__HAL_UART_CLEAR_IDLEFLAG(&huart1);
			if(strlen(usart1_rx_buf) == 7 && usart1_rx_buf[3] == 0x2d){
				if(usart1_rx_buf[0] == SettingManager.currentPassword[0] &&
				   usart1_rx_buf[1] == SettingManager.currentPassword[1] &&
				   usart1_rx_buf[2] == SettingManager.currentPassword[2]){
					SettingManager.currentPassword[0] = usart1_rx_buf[4];
					SettingManager.currentPassword[1] = usart1_rx_buf[5];
					SettingManager.currentPassword[2] = usart1_rx_buf[6];
				}
			}
			memset(usart1_rx_buf, 0, 7);
		}
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart == &huart1){
//		HAL_UART_DMAStop(&huart1);
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		if(Size == 7 && usart1_rx_buf[3] == 0x2d){
			if(usart1_rx_buf[0] == SettingManager.currentPassword[0] &&
			   usart1_rx_buf[1] == SettingManager.currentPassword[1] &&
			   usart1_rx_buf[2] == SettingManager.currentPassword[2]){
				SettingManager.currentPassword[0] = usart1_rx_buf[4];
				SettingManager.currentPassword[1] = usart1_rx_buf[5];
				SettingManager.currentPassword[2] = usart1_rx_buf[6];
			}
		}
		memset(usart1_rx_buf, 0, 7);
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, usart1_rx_buf, sizeof(usart1_rx_buf));
	}
}
