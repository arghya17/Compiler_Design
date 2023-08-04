#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Token types enumeration
typedef enum
{
    TOK_ARITHMETIC_OP,
    TOK_RELATIONAL_OP,
    TOK_LOGICAL_OP,
    TOK_BITWISE_OP,
    TOK_ASSIGN_OP,
    TOK_RESERVED_WORD,
    TOK_IDENTIFIER,
    TOK_INTEGER_CONSTANT,
    TOK_PARENTHESIS,
    TOK_CURLY_BRACES,
    TOK_UNKNOWN
} TokenType;
const char *tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TOK_ARITHMETIC_OP:
        return "Arithmetic Op";
    case TOK_RELATIONAL_OP:
        return "Relational Op";
    case TOK_LOGICAL_OP:
        return "Logical Op";
    case TOK_BITWISE_OP:
        return "Bitwise Op";
    case TOK_ASSIGN_OP:
        return "Assignment Op";
    case TOK_RESERVED_WORD:
        return "Reserved Word";
    case TOK_IDENTIFIER:
        return "Identifier";
    case TOK_INTEGER_CONSTANT:
        return "Integer Constant";
    case TOK_PARENTHESIS:
        return "Parentheses";
    case TOK_CURLY_BRACES:
        return "Curly Braces";
    case TOK_UNKNOWN:
        return "Unknown";
    default:
        return "Invalid Token";
    }
}

// Structure to store token information
typedef struct
{
    TokenType type;
    char lexeme[100];
} Token;

// Global variables
char input[1000];
int pos = 0;
int lineno = 1;

// Function to get the next character from the input
char getNextChar()
{
    if (input[pos] == '\n')
    {
        lineno++;
    }
    return input[pos++];
}

// Function to check if a character is a valid identifier start character
int isIdentifierStartChar(char c)
{
    return isalpha(c) || c == '_';
}

// Function to check if a character is a valid identifier character
int isIdentifierChar(char c)
{
    return isalnum(c) || c == '_';
}

// Function to create a token
Token createToken(TokenType type, const char *lexeme)
{
    Token token;
    token.type = type;
    strcpy(token.lexeme, lexeme);
    return token;
}

// Function to recognize identifiers and reserved words
Token processIdentifier()
{
    char lexeme[100] = {input[pos - 1]};
    while (isIdentifierChar(input[pos]))
    {
        lexeme[strlen(lexeme)] = input[pos++];
    }

    // Check if it is a reserved word or an identifier
    if (strcmp(lexeme, "int") == 0 || strcmp(lexeme, "float") == 0 || strcmp(lexeme, "char") == 0 ||
        strcmp(lexeme, "for") == 0 || strcmp(lexeme, "while") == 0 || strcmp(lexeme, "if") == 0 ||
        strcmp(lexeme, "else") == 0)
    {
        return createToken(TOK_RESERVED_WORD, lexeme);
    }

    return createToken(TOK_IDENTIFIER, lexeme);
}

// Function to recognize integer constants
Token processIntegerConstant()
{
    char lexeme[100] = {input[pos - 1]};
    while (isdigit(input[pos]))
    {
        lexeme[strlen(lexeme)] = input[pos++];
    }
    return createToken(TOK_INTEGER_CONSTANT, lexeme);
}

// Function to recognize operators
Token processOperator()
{
    char lexeme[3] = {input[pos - 1]};
    if (input[pos] == '=')
    {
        lexeme[1] = input[pos++];
    }

    switch (lexeme[0])
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return createToken(TOK_ARITHMETIC_OP, lexeme);

    case '<':
    case '>':
    case '!':
    case '=':
        return createToken(TOK_RELATIONAL_OP, lexeme);

    case '&':
    case '|':
        if (lexeme[1] == '&' || lexeme[1] == '|')
        {
            lexeme[2] = input[pos++];
        }
        return createToken(TOK_LOGICAL_OP, lexeme);

    default:
        return createToken(TOK_UNKNOWN, lexeme);
    }
}

// Function to recognize parentheses and curly braces
Token processSymbol()
{
    char lexeme[2] = {input[pos - 1]};
    return createToken(input[pos++] == '}' ? TOK_CURLY_BRACES : TOK_PARENTHESIS, lexeme);
}

// Lexical analyzer function (yylex)
Token yylex()
{
    char currentChar;
    while ((currentChar = getNextChar()) != '\0')
    {
        if (isspace(currentChar))
        {
            continue; // Skip whitespace
        }

        if (isIdentifierStartChar(currentChar))
        {
            return processIdentifier();
        }

        if (isdigit(currentChar))
        {
            return processIntegerConstant();
        }

        switch (currentChar)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '<':
        case '>':
        case '!':
        case '=':
            return processOperator();

        case '&':
        case '|':
            return processOperator();

        case '(':
        case ')':
        case '{':
        case '}':
            return processSymbol();

        default:
            return createToken(TOK_UNKNOWN, &currentChar);
        }
    }

    // Return EOF token when input ends
    return createToken(TOK_UNKNOWN, "EOF");
}
void readInputFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening the file.\n");
        exit(1);
    }

    char ch;
    int index = 0;
    while ((ch = fgetc(file)) != EOF && index < 999)
    {
        input[index++] = ch;
    }
    input[index] = '\0';

    fclose(file);
}

// Main function for testing the lexical analyzer
int main()
{
    readInputFromFile("input.txt");

    printf("Input Code:\n%s\n\n", input);

    pos = 0;
    lineno = 1;
    Token token;
    do
    {
        token = yylex();
        printf("Token: %-20s Lexeme: %-20s Line: %d\n", tokenTypeToString(token.type), token.lexeme, lineno);
    } while (token.type != TOK_UNKNOWN && token.type != TOK_UNKNOWN);

    return 0;
}