#ifndef ctiny_value_h
#define ctiny_value_h

typedef double Value;

typedef struct {
  // valuesの要素数
  // cloxとは異なり、 実装を簡略化するため、
  // 動的にメモリを拡張せずに8バイトで固定している
  int count;
  Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);

#define NUMBER_VAL(value) value

#endif