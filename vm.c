#include "chunk.h"
#include "vm.h"
#include "compiler.h"
#include "value.h"

VM vm;

void initVM() {
  vm.chunk = NULL;
  vm.ip = NULL;
  vm.stackTop = vm.stack;
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

static int run() {
#define READ_BYTE() (*vm.ip++)
  for (;;) {
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
      case OP_CONSTANT: {
        Value constant = vm.chunk->constants.values[READ_BYTE()];
        push(constant);
        break;
      }
      case OP_PRINT: {
        printf("%d", pop());
        printf("\n");
        break;
      }
      case OP_RETURN: {
        return 0;
      }
    }
  }
#undef READ_BYTE
}

int interpret(const char* source) {
  Chunk chunk;
  initChunk(&chunk);

  int result = compile(source, &chunk);

  vm.chunk = &chunk;
  vm.ip = vm.chunk->code;

  if(result == 1) {
    return 1;
  }

  return run();
}
