#ifndef ctiny_vm_h
#define ctiny_vm_h

#include "common.h"

typedef struct {
   uint8_t* ip;
} VM;

int interpret(const char* source);

#endif