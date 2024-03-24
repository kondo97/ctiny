#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->code = NULL;
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk *chunk, uint8_t byte) {
  // 初回のwriteの場合はメモリを確保する
  // cloxは動的にメモリを拡張するが、ctinyでは8バイトで固定する
  if (chunk->count == 0) {
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, 8);
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}
