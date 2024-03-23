#include <stdio.h>

#include "vm.h"

static void repl() {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    printf("line: %s\n", line);

    interpret(line);
  }
}

int main2() {
  repl();
}
