#include "stdio.h"
extern int yyparse();
extern FILE* yyin ;

int main(int argc, char* argv[])
{   
    // Open input file in read mode
	yyin = fopen(argv[1], "r");

	if (yyin == NULL) 
	{
		printf("File %s could not be opened\n", argv[1]);
		return 0;
	}

    // Parse
    yyparse();

    // Close input file
	fclose(yyin);

    return 0 ;
}