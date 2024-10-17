#ifndef PASSWORD_ENCRYPTION_H
#define PASSWORD_ENCRYPTION_H

#include <stdint.h>

// 密码加密函数声明
void encryptPassword(char* password);

// 密码解密函数声明
void decryptPassword(char* encryptedPassword);

// 8位密码解码并进行校验
int passwardDecrypt(uint32_t encryptedPassword);


uint32_t crc32_calculate(const void* data, uint32_t size);
uint8_t crc8_calculate(const void* data, uint32_t size);
uint32_t mapBits(uint32_t input, uint8_t reverse);




#endif  // PASSWORD_ENCRYPTION_H

