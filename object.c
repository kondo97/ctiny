#include "common.h"
#include "object.h"
#include "memory.h"
#include "value.h"
#include "vm.h"
#include "table.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)


static Obj* allocateObject(size_t size, ObjType type) {
  Obj* object = (Obj*)reallocate(NULL, 0, size);
  object->type = type;
//> Garbage Collection init-is-marked
  object->isMarked = false;
//< Garbage Collection init-is-marked
//> add-to-list
  
  object->next = vm.objects;
  vm.objects = object;
//< add-to-list
//> Garbage Collection debug-log-allocate

#ifdef DEBUG_LOG_GC
  printf("%p allocate %zu for %d\n", (void*)object, size, type);
#endif

//< Garbage Collection debug-log-allocate
  return object;
}

static uint32_t hashString(const char* key, int length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash ^= (uint8_t)key[i];
    hash *= 16777619;
  }
  return hash;
}

ObjString* copyString(const char* chars, int length) {
    // ハッシュ値を生成する
    uint32_t hash = hashString(chars, length);
    // ハッシュ値を元に既に存在する文字列を検索する
    ObjString* interned = tableFindString(&vm.strings, chars, length,
                                        hash);
    // 既に同じハッシュ値が存在すればそれを返す                                  
    if (interned != NULL) return interned;

    // ヒープ領域に文字列をコピーする
    char* heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';

    //
    return allocateString(heapChars, length, hash);
}

static ObjString* allocateString(char* chars, int length, uint32_t hash) {
  ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  string->length = length;
  string->chars = chars;
  string->hash = hash;

  return string;
}