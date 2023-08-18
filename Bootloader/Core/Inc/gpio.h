/*
 * gpio.h
 *
 *  Created on: Aug 17, 2023
 *      Author: batma
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "parser.h"
#include "uart_driver.h"
#include "stm32f4xx_hal.h"

// Emir başlangıç ve bitiş değerleri
#define ORDER_START 12336
#define ORDER_END   17790

// Byte katsayısı (256)
#define BYTE_COEFFICIENT 256

// Emir katsayısı (808464432)
#define ORDER_COEFFICIENT 808464432

// İterasyon katsayısı (16777216)
#define ITTER_COEFFICIENT 16777216

// LED durumunu ayarlayan işlevin bildirimi
void adjustLED(Message *responseMessage);

#endif /* INC_GPIO_H_ */
