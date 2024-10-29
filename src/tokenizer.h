#ifndef TOKENIZER
#define TOKENIZER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TokenType{
    // Character tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    STAR,
};


// opaque type to discourage acces of token properties
typedef struct Token{
    enum TokenType type;
    char *lexeme; // const pointer to first character of the lexeme
    char *lieteral;
    int length; // length of the lexeme defaults to single character
} Token;

Token *create_token(void);

enum TokenType get_token_type(const char c);

void print_token(const Token *t);

int scan_tokens(char *source);

#endif