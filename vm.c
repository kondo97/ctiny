#include "chunk.h"
#include "vm.h"
#include "compiler.h"

VM vm;

static int run() {
#define READ_BYTE() (*vm.ip++)
  for (;;) {
    switch (READ_BYTE()) {
      case OP_RETURN: return 0;
    }
  }
#undef READ_BYTE
}

int interpret(const char* source) {
  int result = compile(source);

  if(result == 1) {
    return 1;
  }

  return run();
}
