#include "tokenizer.h"

Token *create_token(void)
{
    return calloc(1, sizeof(Token));
}

enum TokenType get_token_type(const char c)
{
    switch (c)
    {
    case '(':
        return LEFT_PAREN;
    case ')':
        return RIGHT_PAREN;
    
    default:
        break;
    }
}

const char* token_type_as_string(const enum TokenType type){
    switch (type)
    {
    case LEFT_PAREN:
        return "LEFT_PAREN";
    case RIGHT_PAREN:
        return "RIGHT_PAREN";
    
    default:
        break;
    }
}

void print_token(const Token *t)
{
    printf("\n");
}

void scan_tokens(const char *source)
{
    while(*source)
    {
        Token *t = create_token();
        
        t->type = get_token_type(*source);
        t->lexeme = source;
        t->length = 1;

        source++;
    }
}
