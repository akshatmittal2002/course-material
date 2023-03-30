//Include necessary libraries.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Various define statements as they are used frequently in our program.
#define file_scan(var) fscanf(input,"%[^\n]%*c",var)
#define scan(var) scanf("%[^\n]%*c",var)
#define error printf("\033[1;91mERROR: No such environment variable exists!\n\033[0m")
#define Mem_alloc(var) char* var = (char*)malloc(1024*sizeof(char))

//Start of main function.
//We have an inline argument as a "test.txt" file.
int main(int argc, char** argv)
{
	//Open the "test.txt" file.
	FILE* input = fopen(argv[1],"r");
	//Variable to store the name of environment variable.
	Mem_alloc(variable);
	//Scan it from file.
	file_scan(variable);
	//Scan the input for whether to modify that vaiable or not.
	Mem_alloc(set);
	file_scan(set);
	//If it is an invalid environment variable, print error.
	if(!getenv(variable))
	{
		error;
	}
	//If set is true, i.e., YES, then set it.
	if(!strcmp(set,"Y") || !strcmp(set,"y"))
	{
		//If invalid environment variable, then ask user whether to set it as a new variable.
		if(!getenv(variable))
		{
			//Allocate memory.
			Mem_alloc(cont);
			printf("Do you want to set this as new variable? (Y/N): ");
			scan(cont);
			//If input is NO, then terminate the process, else set it as new variable.
			if(strcmp(cont,"Y") && strcmp(cont,"y"))
			{
				//Free memory.
				free(cont);
				//Goto defined location, since we now have to terminate the program.
				goto label_end;
			}
			//Free memory.
			free(cont);
		}
		//Variable to store the value of environment variable.
		Mem_alloc(value);
		//Scan the value.
		file_scan(value);
		//Set the new value of environment variable using setenv(), i.e., over-write.
		setenv(variable,value,1);
		//Free the value.
		free(value);
		//Print success message.
		printf("\033[1;96mValue of %s set successfully.\n\033[0m",variable);
	}
	//Print the new/old variable of that environment variable.
	if(getenv(variable))
	{
		printf("\033[1;93m%s = %s\n\033[0m",variable,getenv(variable));
	}
	//Free the set
	free(set);
	//The desired location.
	label_end:
	//Free the variable.
	free(variable);
	//Close the file.
	fclose(input);
	return 0;
	//End of main.
}
