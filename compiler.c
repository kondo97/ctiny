#include "scanner.h"
#include "chunk.h"
#include "common.h"

typedef struct {
  Token previous;
  Token current;
  bool hadError;
} Parser;

Parser parser;

static void advance() {
  parser.previous = parser.current;

  for (;;) {
    parser.current = scanToken();
    if (parser.current.type != TOKEN_ERROR) break;

    parser.hadError = true;
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

  if (parser.hadError) {
    return 1;
  } else {
    return 0;
  }
}