#include "tokenizer.h"

Token *create_token(void)
{
    return malloc(sizeof(Token));
}

void delete_token(Token *t)
{
    free(t);
}

TokenArray *create_token_array(void)
{
    // create an array of tokens
    TokenArray *a = (TokenArray *)malloc(sizeof(TokenArray));
    if (a == NULL)
    {
        printf("memory allocation failed...\n");
        exit(1);
    }
    //allocate memory for the tokens
    a->array = (Token **)malloc(sizeof(Token *) * DEFAULT_ARRAY_CAPACITY);

    a->capacity = DEFAULT_ARRAY_CAPACITY;
    a->size = 0;

    return a;
}


void append(TokenArray *a, Token *t)
{
    // realloocate if necessary
    if (a->size == a->capacity)
    {
        a->capacity *= 2;
        a->array = realloc(a->array, a->capacity * sizeof(Token));
    }
    a->array[a->size] = t;
    a->size++;
    
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
        fprintf(stderr, "[line %d] Error: Unexpected character: %c\n", t->line, t->lexeme[0]);
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

void print_token_array(const TokenArray *a)
{
    for(int i = 0; i < a->size; ++i)
    {
        print_token(a->array[i]);
    }
}

int scan_tokens(char *source)
{
    int current_line = 1;
    int exit_code = 0;

    while(*source)
    {
        Token *t = create_token();
        t->length = 1;
        t->lexeme = source;
        t->lieteral = NULL;
        t->line = current_line;
        
        switch (*source)
        {
        case '(':
            t->type = LEFT_PAREN;
        case ')':
            t->type = RIGHT_PAREN;
        case '{':
            t->type = LEFT_BRACE;
        case '}':
            t->type = RIGHT_BRACE;
        case ',':
            t->type = COMMA;
        case '.':
            t->type =  DOT;
        case '-':
            t->type = MINUS;
        case '+':
            t->type = PLUS;
        case ';':
            t->type = SEMICOLON;
        case '*':
            t->type = STAR;
        case '=':
            char *temp = source;
            ++temp;
            if (*temp == '=')
            {
                t->type = EQUAL_EQUAL;
                t->length = 2;
                ++source;
            }
            else
            {
                t->type = EQUAL;
            }
        default:
            t->type = ERROR;
        }

        print_token(t);

        if(t->type == ERROR)
        {
            exit_code = 65;
        }

        source++;
    }

    return exit_code;
}
