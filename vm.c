#include "chunk.h"
#include "vm.h"
#include "compiler.h"

VM vm;

static int run() {
  for (;;) {
    switch (*vm.ip++) {
    }
  }
}

int interpret(const char* source) {
  int result = compile(source);

  if(result == 1) {
    return 1;
  }

  return run();
}
