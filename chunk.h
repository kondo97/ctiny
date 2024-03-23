#ifndef ctiny_chunk_h
#define ctiny_chunk_h

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  int* lines;
} Chunk;

typedef enum {
  OP_RETURN
} OpCode;

#endif