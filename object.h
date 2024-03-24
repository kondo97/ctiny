#ifndef ctiny_object_h
#define ctiny_object_h

typedef enum {
  OBJ_STRING,
} ObjType;

struct Obj {
  ObjType type;
};

struct ObjString {
  Obj obj;
  int length;
  char* chars;
  uint32_t hash;
};

ObjString* copyString(const char* chars, int length);

#endif