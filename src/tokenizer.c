#include "tokenizer.h"

Token *create_token(void)
{
    return malloc(sizeof(Token));
}

enum TokenType get_token_type(const char c)
{
    switch (c)
    {
    case '(':
        return LEFT_PAREN;
    case ')':
        return RIGHT_PAREN;
    case '{':
        return LEFT_BRACE;
    case '}':
        return RIGHT_BRACE;
    case ',':
        return COMMA;
    case '.':
        return DOT;
    case '-':
        return MINUS;
    case '+':
        return PLUS;
    case ';':
        return SEMICOLON;
    case '*':
        return STAR;
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
    case LEFT_BRACE:
        return "LEFT_BRACE";
    case RIGHT_BRACE:
        return "RIGHT_BRACE";
    case COMMA:
        return "COMMA";
    case DOT:
        return "DOT";
    case MINUS:
        return "MINUS";
    case PLUS:
        return "PLUS";
    case SEMICOLON:
        return "SEMICOLON";
    case STAR:
        return "STAR";
    default:
        break;
    }
}

void print_token(const Token *t)
{
    printf(token_type_as_string(t->type));
    printf(" ");
    for(int i = 0; i < t->length; ++i)
    {
        printf("%c", t->lexeme[i]);
    }
    printf(" ");
    if (t->lieteral == NULL)
    {
        printf("null\n");
    }
}

void scan_tokens(const char *source)
{
    while(*source)
    {
        Token *t = create_token();
        
        t->type = get_token_type(*source);
        t->lexeme = source;
        t->length = 1;
        t->lieteral = NULL;

        print_token(t);

        source++;
    }
}
