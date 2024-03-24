#include <stdlib.h>

// 指定されたサイズのメモリを確保する
void* reallocate(void* pointer, size_t Size) {
  void* result = realloc(pointer, Size);
  if (result == NULL) exit(1);
  return result;
}
