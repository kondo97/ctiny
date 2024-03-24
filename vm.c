#include "chunk.h"
#include "vm.h"
#include "compiler.h"

VM vm;

static int run() {
  for (;;) {
    switch (*vm.ip++) {
      case OP_PRINT: return 0;
    }
  }
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

  printf("== vm ==\n");
  printf("vm.ip: %p\n", vm.ip);
  printf("== chunk ==\n");
  printf("chunk.count: %d\n", vm.chunk->count);
  printf("chunk.code: %p\n", vm.chunk->code);
  printf("chunk.code[0]: %d\n", vm.chunk->code[0]);
  printf("chunk.code[1]: %d\n", vm.chunk->code[1]);
  printf("chunk.code[2]: %d\n", vm.chunk->code[2]);
  printf("== constants ==\n");
  printf("constants.count: %d\n", vm.chunk->constants.count);
  printf("constants.values: %p\n", vm.chunk->constants.values);
  printf("constants.values[0]: %f\n", vm.chunk->constants.values[0]);

  return run();
}
