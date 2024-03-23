#include <string.h>

#include "scanner.h"
#include "common.h"

typedef struct {
  const char* start;
  const char* current;
  int line;
} Scanner;

Scanner scanner;

void initScanner(const char* source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;
}

static bool isAtEnd() {
  return *scanner.current == '\0';
}

static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
          c == '_';
}

static char advance() {
  scanner.current++;
  return scanner.current[-1];
}

static char peek() {
  return *scanner.current;
}

static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
      case ' ':
      case '\r':
      case '\t':
        advance();
        break;
      case '\n':
        scanner.line++;
        advance();
        break;
      default:
        return;
    }
  }
}

static Token makeToken(TokenType type) {
  Token token;
  token.type = type;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.line = scanner.line;
  return token;
}

static TokenType checkKeyword(int start, int length, const char* rest, TokenType type) {
  if (scanner.current - scanner.start == start + length &&
      memcmp(scanner.start + start, rest, length) == 0) {
    return type;
  }

  return TOKEN_IDENTIFIER;
}

static TokenType identifierType() {
  switch (scanner.start[0]) {
    case 'p': return checkKeyword(1, 3, "uts", TOKEN_PRINT);
    case 'c': return checkKeyword(1, 4, "lass", TOKEN_CLASS);
    case 'd': return checkKeyword(1, 2, "ef", TOKEN_METHOD);
  }
  return TOKEN_IDENTIFIER;
}

static Token identifier() {
  while (isAlpha(peek())) advance();
  return makeToken(identifierType());
}

static Token string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') scanner.line++;
    advance();
  }

  advance();
  return makeToken(TOKEN_STRING);
}

Token scanToken() {
  skipWhitespace();
  scanner.start = scanner.current;
  if (isAtEnd()) return makeToken(TOKEN_EOF);

  char c = advance();
  if (isAlpha(c)) return identifier();
  switch (c) {
    case '"': return string();
    // case '(': return makeToken(TOKEN_LEFT_PAREN);
  }
}