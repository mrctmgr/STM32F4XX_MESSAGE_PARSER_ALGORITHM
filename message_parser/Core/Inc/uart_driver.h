/*
 * uart_driver.h
 *
 *  Created on: Aug 15, 2023
 *      Author: batma
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include <stdint.h>

// Define your UART peripheral here
#define UART_HANDLE huart2
#define RX_BUFFER_SIZE 28

typedef struct {
    uint8_t* buffer;
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t count;
} uartBufferT;

void UART_Init(void);
void UART_Transmit(const uint8_t *data, uint16_t size);
void UART_Receive(uint8_t *data, uint16_t size);
void USART_SendByte(uint8_t data);
uint8_t USART_IsBuffEmpty(volatile uartBufferT* buffer);
int32_t USART_ReadByte();
uint32_t USART_BytesToRead();
void USART_SendByteArray(uint8_t* buffer, uint32_t size);

#endif /* UART_DRIVER_H_ */

