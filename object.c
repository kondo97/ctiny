
#include <string.h>
#include "common.h"

typedef struct ObjString ObjString;

ObjString* copyString(const char* chars, int length) {
  char* heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';

  return takeString(heapChars, length);
}