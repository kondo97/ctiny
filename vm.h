#ifndef ctiny_vm_h
#define ctiny_vm_h

#include "common.h"
#include "chunk.h"

typedef struct {
   Chunk* chunk;
   uint8_t* ip;
} VM;

int interpret(const char* source);

#endif