//AES-128加密解密
//密钥长度：16字节
//加密轮数：10
#include <iostream>

using byte_t = unsigned char;
using word_t = uint32_t;

void byte_sub(byte_t block[4][4], bool encrypt);
void shift_rows(byte_t block[4][4], bool encrypt);
void mix_cols(byte_t block[4][4], bool encrypt);
void add_round_key(byte_t block[4][4], byte_t key[4][4]);
void key_expansion(byte_t key[4][4], byte_t result[11][4][4]);
byte_t operator_multi(byte_t a, byte_t b);

void aes_128(byte_t plainText[4][4], byte_t key[4][4], bool encrypt);
void printBlock(byte_t block[4][4]);