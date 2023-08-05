// ---------------------------------------- //
//          CS348 Assignment 3              //
//  By Group 16: Ujwal Kumar    200101100   //
//               Akshat Mittal  200101011   //
// ---------------------------------------- //

#include <stdio.h>
#define KEYWORD                 258
#define IDENTIFIER              259
#define INT_CONST               260
#define CHAR_CONST              261
#define STRING_LIT              262
#define PUNCTUATOR              263
#define MULTI_COMMENT_BEGIN     264
#define MULTI_COMMENT_END       265
#define MULTI_COMMENT           266
#define SINGLE_COMMENT_BEGIN    267
#define SINGLE_COMMENT_END      268
#define SINGLE_COMMENT          269
#define WHITESPACE              270

extern char * yytext ;
extern FILE * yyin ;

int main(int arc, char **argv)
{
    // Open the input file
    yyin = fopen(argv[1], "r");
	if (yyin == NULL) 
	{
		printf("Error: Could not open input file\n");
		return 1;
	}

    // Begin the tokenization
    int token;
    while(token = yylex())
    {
        switch(token) 
        {
            case KEYWORD: printf("<KEYWORD, %d, %s>\n", token, yytext); break;
            case IDENTIFIER: printf("<IDENTIFIER, %d, %s>\n", token, yytext); break;
            case INT_CONST: printf("<INT_CONST, %d, %s>\n", token, yytext); break;
            case CHAR_CONST: printf("<CHAR_CONST, %d, %s>\n", token, yytext); break;
            case STRING_LIT: printf("<STRING_LIT, %d, %s>\n", token, yytext); break;
            case PUNCTUATOR: printf("<PUNCTUATOR, %d, %s>\n", token, yytext); break;
            case MULTI_COMMENT_BEGIN: printf("<MULTI_COMMENT_BEGIN, %d, %s>\n", token, yytext); break;
            case MULTI_COMMENT_END: printf("<MULTI_COMMENT_END, %d, %s>\n", token, yytext); break;
            case MULTI_COMMENT: printf("%s", yytext); break;
            case SINGLE_COMMENT_BEGIN: printf("<SINGLE_COMMENT_BEGIN, %d, %s>\n", token, yytext); break;
            case SINGLE_COMMENT_END: printf("<SINGLE_LINE_COMMENT_ENDS, %d, %s>\n", token, yytext); break;
            case SINGLE_COMMENT: printf("%s", yytext); break;
            case WHITESPACE: break;
            default: fprintf(stderr, "<INVALID_TOKEN,%s>", yytext); break;
        }
    }
    
    // Clost the input file
	fclose(yyin);
    
    return 0;
}