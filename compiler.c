#include "scanner.h"
#include "chunk.h"
#include "value.h"
#include "common.h"

typedef struct {
  Token previous;
  Token current;
  bool hadError;
} Parser;

Parser parser;

Chunk* compilingChunk;

static Chunk* currentChunk() {
  return compilingChunk;
}

static void emitByte(int byte) {
  uint8_t ubyte = (uint8_t)byte;
  writeChunk(currentChunk(), ubyte);
}

static void emitConstant(Value value) {
  emitByte(OP_CONSTANT);
  int constant = addConstant(currentChunk(), value);
  emitByte(constant);
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
}

static void printStatement() {
  int message = 1;
  emitConstant(NUMBER_VAL(message));
  emitByte(OP_PRINT);
}

static void declaration() {
  if (match(TOKEN_PRINT)) {
    printStatement();
  }
}

int compile(const char* source, Chunk* chunk) {
  initScanner(source);
  compilingChunk = chunk;

  advance();
  while (!match(TOKEN_EOF)) {
    declaration();
  }

  return 0;
}
