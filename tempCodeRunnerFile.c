#include <stdio.h>
#include <string.h>
#include <openssl/blowfish.h>

#define BLOCK_SIZE 8  // Blowfish的块大小为8字节

void print_hex(const char* label, const unsigned char* data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    // Blowfish的密钥，改为"743619"
    unsigned char key[] = "743619";

    // 明文（必须是8字节，因为Blowfish的块大小是8字节）
    unsigned char plaintext[BLOCK_SIZE] = "12312345";

    // 加密后的密文
    unsigned char ciphertext[BLOCK_SIZE];

    // 解密后的明文
    unsigned char decryptedtext[BLOCK_SIZE];

    // 初始化Blowfish加密上下文
    BF_KEY bf_key;
    BF_set_key(&bf_key, strlen((char*)key), key);

    // 执行Blowfish加密
    BF_ecb_encrypt(plaintext, ciphertext, &bf_key, BF_ENCRYPT);
    print_hex("Ciphertext", ciphertext, BLOCK_SIZE);

    // 执行Blowfish解密
    BF_ecb_encrypt(ciphertext, decryptedtext, &bf_key, BF_DECRYPT);
    print_hex("Decrypted text", decryptedtext, BLOCK_SIZE);

    return 0;
}
