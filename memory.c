#include <stdlib.h>

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  // reallocはC標準ライブラリの関数
  void* result = realloc(pointer, newSize);
  if (result == NULL) exit(1);
  return result;
}