/*
 * bootloader.h
 *
 *  Created on: Aug 18, 2023
 *      Author: batma
 */

#ifndef INC_BOOTLOADER_H_
#define INC_BOOTLOADER_H_

#include "main.h"
#include "stdint.h"

#define FLASH_ADDRESS 0x080E0000
#define FLASH_SIZE	0x800

void jumpApp(void);
void flashErase(uint32_t pageAddress);
void flashWrite(uint32_t data, uint32_t memAddress);
uint32_t *flashRead();
uint32_t GetFlashSector(uint32_t sector);

#endif /* INC_BOOTLOADER_H_ */
