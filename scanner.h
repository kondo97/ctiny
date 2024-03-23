#ifndef ctiny_scanner_h
#define ctiny_scanner_h

typedef enum {
  TOKEN_IDENTIFIER,
  TOKEN_ERROR,
  TOKEN_PRINT,
  TOKEN_CLASS,
  TOKEN_METHOD,
  TOKEN_STRING,
  TOKEN_SPACE,
  TOKEN_EOF,
  OP_PRINT,
  TOKEN_SEMICOLON
} TokenType;

typedef struct {
  TokenType type;
  const char* start;
  int length;
  int line;
} Token;

void initScanner(const char* source);

Token scanToken();

#endif