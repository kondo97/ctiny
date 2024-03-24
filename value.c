#include "common.h"
#include "value.h"
#include "memory.h"

void initValueArray(ValueArray* array) {
  array->values = NULL;
  array->count = 0;
}

void writeValueArray(ValueArray *array, Value value) {
  if (array->count == 0) {
    // 初回のwriteの場合はメモリを確保する
    // cloxは動的にメモリを拡張するが、ctinyでは8バイトで固定する
    array->values = GROW_ARRAY(Value, array->values, 8);
  }

  array->values[array->count] = value;
  array->count++;
}