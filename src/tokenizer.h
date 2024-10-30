#ifndef TOKENIZER
#define TOKENIZER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t DEFAULT_ARRAY_CAPACITY = 4096;


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
    EQUAL,
    EQUAL_EQUAL,
    
    ERROR,
};


typedef struct Token{
    enum TokenType type;
    char *lexeme; // pointer to first character of the lexeme
    char *lieteral;
    int line;
    int length; // length of the lexeme defaults to single character
} Token;


typedef struct {
    size_t capacity; // arbiratry large array capacity to avoid resizing on every call
    size_t size; // will start empty
    Token **array;
} TokenArray;


Token *create_token(void);

void delete_token(Token *t);

TokenArray *create_token_array(void);

void append(TokenArray *array, Token *t);

const char* token_type_as_string(const enum TokenType type);

void print_token(const Token *t);

void print_token_array(const TokenArray *a);

int scan_tokens(char *source);

#endif