#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx_hal.h"

// Başlangıç karakteri ve bitiş karakteri tanımlamaları
#define START_CHAR  163U
#define END_CHAR    '%'

// Beklenen mesaj uzunluğu
#define MESSAGE_LENGTH 28

// Mesajın durumunu belirten enum
typedef enum status{
    READ_COMMAND = 0,   // Okuma komutunu temsil eder
    WRITE_COMMAND = 1   // Yazma komutunu temsil eder
} status;

// Veri türlerini belirten enum
typedef enum {
    CHAR = 0,   // Karakter veri türünü temsil eder
    FLOAT = 1,  // Ondalıklı sayı (float) veri türünü temsil eder
    INT = 2,    // Tam sayı (integer) veri türünü temsil eder
} DataType;

// Mesaj yapısı
typedef struct {
    uint16_t emirNumarasi;  // Emir numarası
    uint8_t slaveNo;        // Cihaz numarası
    uint32_t emirAdresi;     // Emir adresi
    uint8_t komut;           // Komut
    DataType dataType;       // Veri türü
    union {
        char charData[8];    // Karakter veri türü için veri dizisi
        float floatData;     // Ondalıklı sayı (float) veri türü
        int intData;         // Tam sayı (integer) veri türü
    } data;                  // Veri (union ile farklı veri türlerini saklayabilir)
} Message;

// Hata kodları enum'u
typedef enum {
    NO_ERROR,               // Hata yok
    INVALID_START,          // Geçersiz başlangıç karakteri
    INVALID_END,            // Geçersiz bitiş karakteri
    INVALID_COMMAND,        // Geçersiz komut
    INVALID_DATA_TYPE       // Geçersiz veri türü
} ErrorCode;

// Mesaj çözümleme fonksiyonu
ErrorCode parseMessage(const char *message, Message *parsedMessage);

// Yanıt hazırlama fonksiyonu
void prepareResponse(Message *parsedMessage, Message *responseMessage, int responseData);

#endif /* INC_PARSER_H_ */
