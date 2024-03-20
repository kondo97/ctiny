#include "scanner.h"
#include "chunk.h"
#include "common.h"

typedef struct {
  Token current;
  Token previous;
} Parser;

Parser parser;

static void advance() {
  parser.previous = parser.current;

  for (;;) {
    parser.current = scanToken();
  }
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