#include "parser.h"

// Gelen mesajı çözümleme işlevi
ErrorCode parseMessage(const char *message, Message *parsedMessage) {
    if (message[0] != START_CHAR) {
        return INVALID_START; // Başlangıç karakteri kontrolü
    }

    // Mesajın farklı bölümlerini çözümle ve parsedMessage yapısına doldur
    parsedMessage->emirNumarasi = *((uint16_t*)(message + 1)); // 2 byte: Emir Numarası
    parsedMessage->slaveNo = *((uint8_t*)(message + 5)); // 1 byte: Cihaz Numarası
    parsedMessage->emirAdresi = *((uint32_t*)(message + 7)); // 4 byte: Emir Adresi
    parsedMessage->komut = *((status*)(message + 15)) % 2; // 1 byte: Komut
    parsedMessage->dataType = *((DataType*)(message + 17)) % 3; // 1 byte: Veri Türü

    // Veri türüne göre farklı veri alanlarını çözümle
    switch (parsedMessage->dataType) {
        case CHAR:
            strncpy(parsedMessage->data.charData, message + 19, sizeof(parsedMessage->data.charData));
            break;
        case FLOAT:
            parsedMessage->data.floatData = *((float*)(message + 19));
            break;
        case INT:
            parsedMessage->data.intData = *((int*)(message + 19));
            break;
        default:
            return INVALID_DATA_TYPE; // Geçersiz veri türü hatası
    }
    return NO_ERROR; // Hata yok
}

// Yanıt hazırlama işlevi
void prepareResponse(Message *parsedMessage, Message *responseMessage, int responseData) {
    // Gelen mesajın bazı alanlarını yanıt mesajına taşı
    responseMessage->emirNumarasi = parsedMessage->emirNumarasi;
    responseMessage->slaveNo = parsedMessage->slaveNo;
    responseMessage->emirAdresi = parsedMessage->emirAdresi;

    // Okuma veya yazma komutuna göre farklı yanıt hazırla
    if (parsedMessage->komut == READ_COMMAND) {
        responseMessage->komut = READ_COMMAND; // Okuma komutu
        responseMessage->dataType = parsedMessage->dataType; // Veri türü
        switch (parsedMessage->dataType) {
            case CHAR:
                strncpy(responseMessage->data.charData, parsedMessage->data.charData, sizeof(responseMessage->data.charData));
                break;
            case FLOAT:
                responseMessage->data.floatData = parsedMessage->data.floatData;
                break;
            case INT:
                responseMessage->data.intData = responseData; // İlgili veriyi ekle
                break;
            default:
                // Geçersiz veri türü işleme alınabilir
                break;
        }
    } else if (parsedMessage->komut == WRITE_COMMAND) {
        responseMessage->komut = WRITE_COMMAND; // Yazma komutu
        responseMessage->dataType = parsedMessage->dataType; // Veri türü (yazma komutunda da aynı kalır)
        switch (parsedMessage->dataType) {
            case CHAR:
                strncpy(responseMessage->data.charData, parsedMessage->data.charData, sizeof(responseMessage->data.charData));
                break;
            case FLOAT:
                responseMessage->data.floatData = parsedMessage->data.floatData;
                break;
            case INT:
                responseMessage->data.intData = parsedMessage->data.intData;
                break;
            default:
                // Geçersiz veri türü işleme alınabilir
                break;
        }
    }
}
