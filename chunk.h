#ifndef ctiny_chunk_h
#define ctiny_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_PRINT,
  OP_RETURN
} OpCode;

typedef struct {
  // codeのバイト数(要素数)
  // cloxとは異なり、実装を簡略化するため、
  // 動的にメモリを拡張せずに8バイトで固定している
  int count;
  // バイトコードを格納する配列
  uint8_t* code;
  // 定数を格納する配列
  ValueArray constants;
} Chunk;

void writeChunk(Chunk* chunk, uint8_t byte);
void initChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);

#endif