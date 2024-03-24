#include "common.h"

// typeがuint8_tの場合、sizeof(uint8_t)は1バイト
// 8バイトのメモリを確保する場合は、Szie=8を指定する
#define GROW_ARRAY(type, pointer, Size) \
    (type*)reallocate(pointer, sizeof(type) * Size)

void* reallocate(void* pointer, size_t Size);
