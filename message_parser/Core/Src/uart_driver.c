#include "uart_driver.h"

extern UART_HandleTypeDef huart2;

uartBufferT rxBuffer; // Alım tamponu

void UART_Init(void) {
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&huart2);

    rxBuffer.buffer = malloc(RX_BUFFER_SIZE + 1);
    rxBuffer.size = RX_BUFFER_SIZE;
    rxBuffer.head = 0;
    rxBuffer.tail = 0;
    rxBuffer.count = 0;
    HAL_UART_Receive_IT(&huart2, &rxBuffer.buffer[rxBuffer.tail], 1);
}

void USART_SendByte(uint8_t data) {
    HAL_UART_Transmit(&huart2, &data, 1, HAL_MAX_DELAY);
}

uint8_t USART_IsBuffEmpty(volatile uartBufferT* buffer) {
    return (buffer->count == 0);
}

int32_t USART_ReadByte() {
    if (rxBuffer.count > 0) {
        int32_t value = rxBuffer.buffer[rxBuffer.head++];
        rxBuffer.head %= rxBuffer.size;
        rxBuffer.count--;
        return value;
    }
    return -1; // Veri yok
}

uint32_t USART_BytesToRead() {
    return rxBuffer.count;
}

void USART_SendByteArray(uint8_t* buffer, uint32_t size) {
    HAL_UART_Transmit(&huart2, buffer, size, HAL_MAX_DELAY);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart2) {
        if (rxBuffer.count < rxBuffer.size) {
            rxBuffer.buffer[rxBuffer.tail] = rxBuffer.buffer[rxBuffer.head];
            rxBuffer.head = (rxBuffer.head + 1) % rxBuffer.size; 
            rxBuffer.tail = (rxBuffer.tail + 1) % rxBuffer.size; 
            rxBuffer.count++; // Tampon sayısını artır
        }
        HAL_UART_Receive_IT(huart, &rxBuffer.buffer[rxBuffer.tail], 1);
    }
}
