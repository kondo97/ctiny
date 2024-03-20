#ifndef ctiny_scanner_h
#define ctiny_scanner_h

typedef enum {
  TOKEN_EOF
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