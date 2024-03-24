#ifndef ctiny_vm_h
#define ctiny_vm_h

#include "common.h"
#include "value.h"
#include "table.h"

typedef struct {
   uint8_t* ip;
   Table strings;
} VM;

extern VM vm;

int interpret(const char* source);

#endif