/*
 * gpio.c
 *
 *  Created on: Aug 17, 2023
 *      Author: batma
 */


#include "gpio.h"


void adjustLED(Message *responseMessage)
{
	switch (responseMessage->emirNumarasi) //EMİR NUMARASI ISLEMI BİLDİRİR
	{
	case BYTE_COEFFICIENT + 256 * 2:
		//TIMER1 İŞLEMLERİ
		break;
	case ORDER_START + 1 : //GPIO ISLEMLERI
		switch (responseMessage->slaveNo) //SLAVE NO 1 İSE LED ISLEMI OLACAK
		{
		case 1 + '0': //LED İŞLEMLERİ
			switch (responseMessage->emirAdresi) // EMIR ADRESİ 0X0000 808464432 VE HER BİT ARASINDA 16777216 DEC DEĞER VAR
			{
			case ORDER_COEFFICIENT: //0X0000 GİRİLMİŞSE
				if (responseMessage->komut == READ_COMMAND) //R/W KOMUTU DEĞERLENDİRİLİR
				{
					if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12) == GPIO_PIN_SET)
						USART_SendByteArray("LED ON\n", 7);
					else
						USART_SendByteArray("LED OFF\n", 8);
				}
				else
				{
					if (responseMessage->data.charData[0] == 'A' && responseMessage->data.charData[1] == 'A')
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, SET);
					else if (responseMessage->data.charData[0] == 'F' && responseMessage->data.charData[1] == 'F')
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, RESET);
				}
				break;
			case ORDER_COEFFICIENT + (ITTER_COEFFICIENT * 1): //0X0001 GİRİLMİŞSE
				if (responseMessage->komut == READ_COMMAND)
				{
					if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13) == GPIO_PIN_SET)
						USART_SendByteArray("LED ON\n", 7);
					else
						USART_SendByteArray("LED OFF\n", 8);
				}
				else
				{
					if (responseMessage->data.charData[0] == 'A' && responseMessage->data.charData[1] == 'A')
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, SET);
					else if (responseMessage->data.charData[0] == 'F' && responseMessage->data.charData[1] == 'F')
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, RESET);
				}
				break;
			case ORDER_COEFFICIENT + (ITTER_COEFFICIENT * 2): //OXOOO2 GİRİLMİŞSE
				if (responseMessage->komut == READ_COMMAND)
				{
					if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14) == GPIO_PIN_SET)
						USART_SendByteArray("LED ON\n", 7);
					else
						USART_SendByteArray("LED OFF\n", 8);
				}
				else
				{
					if (responseMessage->data.charData[0] == 'A' && responseMessage->data.charData[1] == 'A')
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, SET);
					else if (responseMessage->data.charData[0] == 'F' && responseMessage->data.charData[1] == 'F')
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, RESET);
				}
				break;
			case ORDER_COEFFICIENT + (ITTER_COEFFICIENT * 3): //0X0003 GİRİLMİŞSE
				if (responseMessage->komut == READ_COMMAND)
				{
					if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15) == GPIO_PIN_SET)
						USART_SendByteArray("LED ON\n", 7);
					else
						USART_SendByteArray("LED OFF\n", 8);
				}
				else
				{
					if (responseMessage->data.charData[0] == 'A' && responseMessage->data.charData[1] == 'A')
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, SET);
					else if (responseMessage->data.charData[0] == 'F' && responseMessage->data.charData[1] == 'F')
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, RESET);
				}
				break;
			}
			break;
		case 2 + '0':
			//ADC ISLEMLERI
			break;
		}

	}
}
