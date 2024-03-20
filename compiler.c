#include "scanner.h"
#include "chunk.h"
#include "common.h"

typedef struct {
  Token previous;
  Token current;
} Parser;

Parser parser;

static void advance() {
  parser.previous = parser.current;

  for (;;) {
    parser.current = scanToken();
  }
  printf('parser.previous: %d', parser.previous);
  printf('parser.current: %d', parser.current);
}

static bool check(TokenType type) {
  return parser.current.type == type;
}

static bool match(TokenType type) {
  if (!check(type)) return false;
  advance();
  return true;
}

static void declaration() {
}

int compile(const char* source) {
  initScanner(source);

  advance();
  while (!match(TOKEN_EOF)) {
    declaration();
  }

  return 0;
}