#ifndef ctiny_vm_h
#define ctiny_vm_h

#include "common.h"
#include "chunk.h"

#define STACK_MAX 256

typedef struct {
   Chunk* chunk;
   uint8_t* ip;
   Value* stackTop;
   Value stack[STACK_MAX];
} VM;

int interpret(const char* source);
void initVM();

#endif