#include "tokenizer.h"

const size_t DEFAULT_ARRAY_CAPACITY = 4096;

Token *create_token(void)
{
    Token *t = (Token *)malloc(sizeof(Token));
    
    if (t == NULL)
    {
        printf("Token memory allocation failed...\n");
        exit(1);
    }

    return t;
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

void delete_token_array(TokenArray *a)
{
    for(int i = 0; i < a->size; ++i)
    {
        delete_token(a->array[i]);
    }
    free(a);
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
    case EQUAL:
        return "EQUAL";
    case EQUAL_EQUAL:
        return "EQUAL_EQUAL";
    case BANG:
        return "BANG";
    case BANG_EQUAL:
        return "BANG_EQUAL";
    case LESS:
        return "LESS";
    case LESS_EQUAL:
        return "LESS_EQUAL";
    case GREATER:
        return "GREATER";
    case GREATER_EQUAL:
        return "GREATER_EQUAL";
    case SLASH:
        return "SLASH";
    case STRING:
        return "STRING";
    case END_OF_FILE:
        return "EOF";
    default:
        break;
    }
}

void print_token(const Token *t)
{
    printf("%s ", token_type_as_string(t->type));
    for(int i = 0; i < t->length; ++i)
    {
        printf("%c ", t->lexeme[i]);
    }
    printf(" ");
    if (t->string != NULL)
    {
        printf("%s", t->string);
    }
    else if (t->number)
    {
        printf("%d", t->number);
    }
    else
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

int scan_tokens(TokenArray *a, char *source)
{
    int current_line = 1;
    int exit_code = 0;

    while(*source)
    {
        Token *t = create_token();
        t->length = 1;
        t->lexeme = source;
        t->line = current_line;
        t->string = NULL;
        
        char *temp = source; // temporary pointer for peeking forward

        switch (*source)
        {
        case '(':
            t->type = LEFT_PAREN;
            append(a, t);
            break;
        case ')':
            t->type = RIGHT_PAREN;
            append(a, t);
            break;
        case '{':
            t->type = LEFT_BRACE;
            append(a, t);
            break;
        case '}':
            t->type = RIGHT_BRACE;
            append(a, t);
            break;
        case ',':
            t->type = COMMA;
            append(a, t);
            break;
        case '.':
            t->type =  DOT;
            append(a, t);
            break;
        case '-':
            t->type = MINUS;
            append(a, t);
            break;
        case '+':
            t->type = PLUS;
            append(a, t);
            break;
        case ';':
            t->type = SEMICOLON;
            append(a, t);
            break;
        case '*':
            t->type = STAR;
            append(a, t);
            break;
        case '=':
            ++temp;
            if (*temp == '=')
            {
                t->type = EQUAL_EQUAL;
                t->length = 2;
                ++source;
                append(a, t);
            }
            else
            {
                t->type = EQUAL;
                append(a, t);
            }
            break;
        case '!':
            ++temp;
            if (*temp == '=')
            {
                t->type = BANG_EQUAL;
                t->length = 2;
                ++source;
                append(a, t);
            }
            else
            {
                t->type = BANG;
                append(a, t);
            }
            break;
        case '<':
            ++temp;
            if (*temp == '=')
            {
                t->type = LESS_EQUAL;
                t->length = 2;
                ++source;
                append(a, t);
            }
            else
            {
                t->type = LESS;
                append(a, t);
            }
            break;
        case '>':
            ++temp;
            if (*temp == '=')
            {
                t->type = GREATER_EQUAL;
                t->length = 2;
                ++source;
                append(a, t);
            }
            else
            {
                t->type = GREATER;
                append(a, t);
            }
            break;
        case '/':
            ++temp;
            if (*temp == '/')
            {
                while(*temp != '\n' && *temp != '\0')
                {
                    ++temp;
                    ++source;
                }
            }
            else
            {
                t->type = SLASH;
                append(a, t);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
            ++current_line;
            break;
        case '"':
            ++temp;
            while(*temp != '"' && *temp != '\0')
            {
                if(*temp == '\n')
                {
                    ++current_line;
                }
                ++temp;
            }
            if (*temp == '\0')
            {
                log_error(current_line, "Unterminated string.");
                exit_code = 65;
            }
            if (*temp == '"')
            {
                t->type = STRING;
                t->lexeme = source;
                int l = (temp - source);
                t->length = l;
                t->string = (char *)malloc(l * sizeof(char));
                strncpy(t->string, source+1, l-1);
                t->string[l-1] = '\n';
                append(a, t);
                source = temp;
            }
            break;
        default:
            log_error(current_line, "Unexpected character: " + *source);
            exit_code = 65;
        }

        source++;
    }
    
    Token *t = create_token();
    t->type = END_OF_FILE;
    t->lexeme = source;
    t->length = 0;

    append(a, t);

    return exit_code;
}


void log_error(int line, char *msg)
{
    fprintf(stderr, "[line %d] Error: %s\n", line, msg);
}