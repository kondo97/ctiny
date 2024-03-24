#ifndef ctiny_value_h
#define ctiny_value_h

typedef uint64_t Value;

typedef struct ObjString ObjString;

#define SIGN_BIT ((uint64_t)0x8000000000000000)
#define QNAN     ((uint64_t)0x7ffc000000000000)

// Objのポインタを受け取り、それを64ビットの値に変換する
// 生成された値は、ハッシュ表のキーとして使用される
#define OBJ_VAL(obj) \
    (Value)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(obj))

#endif