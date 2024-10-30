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
        return ERROR;
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
    case ERROR:
        return "Error";
    default:
        break;
    }
}

void print_token(const Token *t)
{
    if(t->type == ERROR)
    {
        printf("[Line %i] Error: Unexpected character: %c", t->line, t->lexeme[0]);
        return;
    }
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

int scan_tokens(char *source)
{
    int current_line = 1;
    int exit_code = 0;

    while(*source)
    {
        Token *t = create_token();
        
        t->type = get_token_type(*source);
        t->lexeme = source;
        t->length = 1;
        t->lieteral = NULL;
        t->line = current_line;

        print_token(t);

        if(t->type == ERROR)
        {
            exit_code = 65;
        }

        source++;
    }

    printf("EOF  null\n");
    return exit_code;
}
