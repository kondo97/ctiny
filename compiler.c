#include "scanner.h"
#include "chunk.h"
#include "common.h"
#include "value.h"

typedef struct {
  Token previous;
  Token current;
} Parser;

Parser parser;

static void emitByte(uint8_t byte) {
  writeChunk(currentChunk(), byte, parser.previous.line);
}

static string() {
  emitConstant(OBJ_VAL(copyString(parser.previous.start + 1,
                                  parser.previous.length - 2)));
}

static void expression() {
  advance();
  string();
}

static void advance() {
  parser.previous = parser.current;

  for (;;) {
    parser.current = scanToken();
    if (parser.current.type != TOKEN_ERROR) break;
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

static void consume(TokenType type, const char* message) {
  if (parser.current.type == type) {
    advance();
    return;
  }

  printf("Error: %s\n", message);
}

static void printStatement() {
  expression();
  consume(TOKEN_SEMICOLON, "Expect ';' after value.");
  emitByte(OP_PRINT);
}

static void statement() {
  if (match(TOKEN_PRINT)) {
     printStatement();
  }
}

static void declaration() {
  statement();
}

int compile(const char* source) {
  initScanner(source);

  advance();
  while (!match(TOKEN_EOF)) {
    declaration();
  }

  return 0;
}