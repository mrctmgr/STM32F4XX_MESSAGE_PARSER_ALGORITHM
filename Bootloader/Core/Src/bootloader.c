/*
 * bootloader.c
 *
 *  Created on: Aug 18, 2023
 *      Author: mirac.tumgor
 */


#include "bootloader.h"
#include <string.h>

void jumpApp(void) {
    void (*user_app_reset_handler)(void);

    uint32_t user_app_reset_address = *((volatile uint32_t *)(FLASH_ADDRESS + 4));

    user_app_reset_handler = (void (*)(void))user_app_reset_address;

    __disable_irq();

    user_app_reset_handler();
}

void flashErase(uint32_t sectorAddress) {
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef eraseInit;
    eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInit.Banks = FLASH_BANK_1;
    eraseInit.Sector = GetFlashSector(sectorAddress);
    eraseInit.NbSectors = 1;

    uint32_t pageError = 0;
    HAL_FLASHEx_Erase(&eraseInit, &pageError);

    HAL_FLASH_Lock();
}

void flashWrite(uint32_t data, uint32_t memAddress) {
    HAL_FLASH_Unlock();

    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, memAddress, data);

    HAL_FLASH_Lock();
}

uint32_t *flashRead() {
    return (uint32_t *)FLASH_ADDRESS;
}

uint32_t GetFlashSector(uint32_t sector) {
    return sector / FLASH_SIZE; 
}
