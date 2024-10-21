#ifndef PASSWORD_ENCRYPTION_H
#define PASSWORD_ENCRYPTION_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


uint32_t crc32_calculate(const void* data, uint32_t size);
uint8_t crc8_calculate(const void* data, uint32_t size);
uint32_t mapBits(uint32_t input, uint8_t reverse);
uint32_t encryptData(uint32_t encryptionKey, uint32_t plaintext);
int32_t decryptData(uint32_t encryptionKey, uint32_t ciphertext);

uint8_t test_main(int argc, char *argv[]);



#endif  // PASSWORD_ENCRYPTION_H

