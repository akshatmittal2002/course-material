//Include all necessary libraries for our mini shell.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
//=================================================================================================
//Following are various define statements since these are used in our program regularly.
#define print_error_message fprintf(stderr,"\033[1;91mERROR: Sorry! No such command exists in my mini shell.\n\033[0m");
#define print_to_file fprintf(history_ptr, "\t%d. %s\n", serial, user_input);
#define RESET printf("\033[0m");
#define RED printf("\033[1;91m");
#define GREEN printf("\033[1;92m");
#define YELLOW printf("\033[1;93m");
#define BLUE printf("\033[1;94m");
#define PURPLE printf("\033[1;95m");
#define CYAN printf("\033[1;96m");
#define CLEAR printf("\e[1;1H\e[2J");
//=================================================================================================
//Variable to store all the paths. It is declared globally since it is used in many functions.
int total_paths = 1;
//=================================================================================================
//Various functions to build our shell which are to be used several times and make our main function easier.
//Description of all functions are given after main.
int count_argument_numbers(char*);
char** find_all_paths();
char** separate_user_input(char*, int);
int is_present(char**, int, char*);
int find_positions(char**,int,char*,int**);
char*** split_commands(char**, int, int);
char** find_command(char**,int,int);
char* get_program_path(char*, char**);
void print_message(char*,char);
void print_env_var_error(char**);
void execute_cd_command(char**,int);
void execute_history(char **);
void execute_commands(char**,char**,int);
char** execute_env_var(char**,int,char**);
//=================================================================================================
int main()
{
	//Clear screen.
	system("clear");
	//Store the result of "find all paths function".
	char** all_paths = find_all_paths();
	
	//Set value of PATH to all paths and store the value.
	char* temp_path = (char *)malloc(PATH_MAX*sizeof(char));
	for(int j=0; j<total_paths; j++)
	{
		strcat(temp_path,all_paths[j]);
		if(j != (total_paths-1)) strcat(temp_path,":");
	}
	char* t = "PATH";
	setenv(t,temp_path,1);
	//Create a file to store the user commands in "w+" mode.
	FILE* history_ptr = fopen("/tmp/history.txr", "w");
	
	//Print Welcome Message
	YELLOW
	print_message("Welcome To My Mini Shell",'*');
	printf("\n");
	RESET
	
	//Variable to keep track of number of inputs to maintain in history file.
	int serial = 0;
	//=========================================================================================
	//Start an infinite loop.
	while(1)
	{
		//Variable to store current direcory.
		char current_directory[PATH_MAX];
		//=================================================================================
		//getcwd() will get the current directory in which program is executed.
		//If it returns NULL, then it means we are unable to access current working directory and stops our program.
		if(getcwd(current_directory, sizeof(current_directory)) == NULL)
		{
			fprintf(stderr,"\033[1;91mERROR: Not able to access current working directory.\nProcess Terminated!\n\033[0m");
			break;
		}
		//=================================================================================
		//Variable to store user input.
		char* user_input = (char *)malloc(1024*sizeof(char));
		//Till user input is empty, prompt for user input and print current directory.
		while(!strcmp(user_input,""))
		{
			//Print current directory.
			GREEN
			printf("Current Directory");
			RESET
			printf(": ");
			BLUE
			printf("%s", current_directory);
			RESET
			printf("$ ");
			
			//Scanf the user input till he/she hits enter.
			scanf("%[^\n]",user_input);
			//To scan but not store the new line character.
			scanf("%*c");
		}
		//=================================================================================
		//Store total number of arguments entered.
		int argument_numbers = count_argument_numbers(user_input);
		//=================================================================================
		//If input is empty, do nothing.
		if(argument_numbers == 0)
		{
			free(user_input);
			continue;
		}
		//=================================================================================
		//If a redirection operation other than specified is used.
		if(strstr(user_input,"<<") || strstr(user_input,"<<<") || strstr(user_input,">>>") || strstr(user_input,"<&") || strstr(user_input,">&") || strstr(user_input,"||"))
		{
			//Print error.
			fprintf(stderr,"\033[1;91mERROR: Sorry! This operation is not supported in my mini shell\n\033[0m");
			//Free the allocated memory and continue.
			free(user_input);
			continue;
		}
		//=================================================================================
		//Store the parsed user input whuch is obtained by corresponding using a function.
		char** user_input_array = separate_user_input(user_input, argument_numbers);
		//=================================================================================
		//Print input to file.
		serial++;
		print_to_file
		fflush(history_ptr); //flush
		//=================================================================================
		//If input calls for an environment variable, call the corresponding function it.
		user_input_array = execute_env_var(user_input_array,argument_numbers,all_paths);
		//=================================================================================
		//If setenv is called, execute it.
		if(!strcmp(user_input_array[0],"setenv"))
		{
			if(argument_numbers!=4 || user_input_array[2]!="=") printf("\033[1;91mERROR: Incorrect format of command!\n\033[0mUSE: setenv VAR_NAME = value\nBoth VAR_NAME and value should not have whitespaces or else please use double quotes!\n");
			else setenv(user_input_array[1],user_input_array[3],1);
                    	//Free the allocated memory and continue.
                    	free(user_input_array);
                    	continue;
		}
		//=================================================================================
		//If input calls for an environment variable without echo or printenv, then print error.
		if(getenv(user_input_array[0]))
		{
			//Call the corresponding function.
			print_env_var_error(user_input_array);
                    	//Free the allocated memory and continue.
                    	free(user_input_array);
                    	continue;
		}
		//=================================================================================
		//If input calls for a "cd", execute it.
		if(!strcmp(user_input_array[0], "cd"))
		{
			//Call the corresponding function.
			execute_cd_command(user_input_array,argument_numbers);
                    	//Free the allocated memory and continue.
			free(user_input_array);
                    	continue;
		}
		
		//=================================================================================
		//if input calls for history, then print the history file.
		if(!strcmp(user_input_array[0], "history") && argument_numbers==1)
		{
			//Call the corresponding function.
			execute_history(all_paths);
                    	//Free the allocated memory and continue.
			free(user_input_array);
                    	continue;
		}
		//=================================================================================
		//If user calls for exit, then free all memory, remove history file and break the while loop.
		if(!strcmp(user_input_array[0], "exit") || !strcmp(user_input_array[0], "quit") || !strcmp(user_input_array[0], "x"))
		{
			//If only exit is typed, then just exit.
			if(argument_numbers==1)
			{
				//Free the allocated memory and break.
				free(user_input_array);
				remove("/tmp/history.txr");
				break;
			}
			//Else check with user if he really wants to exit or run a command having exit.
			else
			{
				char c;
				while(1)
				{
					printf("Did u mean exit? (Y/N) : ");
					scanf("%c%*c",&c);
					if(c=='y' || c=='Y')
					{
						//If yes, free the allocated memory and break.
						free(user_input_array);
						remove("/tmp/history.txr");
						break;
					}
					else if(c=='n' || c=='N') break;
				}
				//If yes, then exit.
				if(c=='y' || c=='Y') break;
				//Else check the other possibilities.
			}
		}
		//=================================================================================
		//If a pipe is present in the command.
		if(is_present(user_input_array, argument_numbers, "|"))
		{
			//Get the number of pipes and their positions.
			int* positions;
			int total_count = find_positions(user_input_array, argument_numbers, "|", &positions);
			//If we have more than one pipe, then print error.
			if(total_count>1)
			{
				fprintf(stderr,"\033[1;91mERROR: Sorry! This operation of multi-level piping is not supported in my mini shell\n\033[0m");
				goto label1;
			}
			int pipe_position = positions[0];
			//If there is no command after/before pipe, print error.
			if(pipe_position==0 || pipe_position==argument_numbers-1)
			{
				if(pipe_position==0) fprintf(stderr,"\033[1;91mSyntax Error: No command found before '|'\n\033[0m");
				else fprintf(stderr,"\033[1;91mSyntax Error: No command found after '|'\n\033[0m");
				goto label1;
			}
			//Split the user input array into two commands via calling the corresponding function.
			char*** splitted_commands = split_commands(user_input_array, argument_numbers, pipe_position);
			//Create two child processes
			int fd[2];
			pid_t child1, child2;
			//If creation of child is successful, then execute.
			if(pipe(fd) >=0 )
			{
				//Fork child 1.
				child1 = fork();
				//If fork is un-successful, print error.
				if(child1 < 0) fprintf(stderr,"\033[1;91mERROR: Could not fork!\n\033[0m");
				//Else if it return 0, then execute the child 1.
				else if(child1 == 0)
				{
					//Child 1 will output to the input of second child.
					close(fd[0]);
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					//Execute all internal and external commands.
					execute_commands(splitted_commands[0],all_paths,pipe_position);
				}
				//Else fork second child
				else
				{
					//Fork child 2.
					child2 = fork();
					//If fork is un-successful, print error.
					if(child2 < 0) fprintf(stderr,"\033[1;91mERROR: Could not fork!\n\033[0m");
					//Else if it return 0, then execute the child 2.
					else  if(child2 == 0)
					{
						//Child 2 will output to screen.
						close(fd[1]);
						dup2(fd[0], STDIN_FILENO);
						close(fd[0]);
						//Execute all internal and external commands.
						execute_commands(splitted_commands[1],all_paths,argument_numbers - pipe_position -1);
					}
					//Else wait for the process to finish.
					else
					{
						close(fd[0]);
						close(fd[1]);
						waitpid(-1,NULL,0);
						waitpid(-1,NULL,0);
					}
				}
			}
			//Else if creation of child is un-successful, then execute.
			else fprintf(stderr,"\033[1;91mERROR: Pipes could not be initialized! Please try again!\n\033[0m");
			//Free the allocated memory and continue.
			free(splitted_commands);
			//A label.
			label1:
			free(positions);
			free(user_input_array);
                   	continue;
		}
		//=================================================================================
		//If a redirection is present in the command.
		if(is_present(user_input_array, argument_numbers, ">>") || is_present(user_input_array, argument_numbers, ">") || is_present(user_input_array, argument_numbers, "<"))
		{
			//Find count and positions of redirections in the user input array and store them via functions.
			int* read,*write,*append;
			int read_count = find_positions(user_input_array, argument_numbers, "<", &read);
			int write_count = find_positions(user_input_array, argument_numbers, ">", &write);
			int append_count = find_positions(user_input_array, argument_numbers, ">>", &append);
			//If more than one input or output operations are present, print error.
			if(read_count>1 || (write_count+append_count)>1)
			{
				fprintf(stderr,"\033[1;91mERROR: Sorry! This operation of redirection from/to multiple files is not supported in my mini shell\n\033[0m");
				goto label2;
			}
			//If no file is specified after redirection sign, print error.
			if((read[0]+1)==argument_numbers || (write[0]+1)==argument_numbers || (append[0]+1)==argument_numbers)
			{
				fprintf(stderr,"\033[1;91mERROR: No file specified!\n\033[0m");
				goto label2;
			}
			//After these checks, find the main process command and it's length.
			int length = argument_numbers - 2*(read_count+write_count+append_count);
			//If length is zero, it means no command is given but only files. Print error.
			if(length==0)
			{
				fprintf(stderr,"\033[1;91mERROR: No command found!\n\033[0m");
				goto label2;
			}
			//If input redirection is present.
			if(read_count==1)
			{
				//Check if the given input file is available, else print error.
				if(access(user_input_array[read[0] + 1], F_OK) != 0)
				{
					fprintf(stderr,"\033[1;91mERROR: Could not access file! No such file exists!\n\033[0m");
					goto label2;
				}
			}
			//Store the main command after removing the files.
			char** process_command = find_command(user_input_array, argument_numbers,length);
			int fd1,fd2;
			//Create a child process.
			pid_t process = fork();
			//If it is un_successful, return error.
			if(process < 0) fprintf(stderr,"\033[1;91mERROR: Could not fork!\n\033[0m");
			//Else if it return 0, then execute the child.
			else  if(process == 0)
			{
				//If there are read files, open them and direct the input to them.
				if(read_count==1)
				{
					fd1 = open(user_input_array[read[0] + 1], O_RDONLY , 0666);
					dup2(fd1,0);
				}
				//If there are write/append files, open them and direct the output to them.
				if(write_count==1)
				{
					fd2 = open(user_input_array[write[0] + 1], O_WRONLY | O_CREAT | O_TRUNC , 0666);
					dup2(fd2,1);
				}
				else if(append_count==1)
				{
					fd2 = open(user_input_array[append[0] + 1], O_CREAT | O_APPEND | O_RDWR, 0666);
					dup2(fd2,1);
				}
				//Execute all internal and external commands.
				execute_commands(process_command,all_paths,length);
				//Close the files.
				close(fd1);
				close(fd2);
			}
			//Else wait for parent.
			else waitpid(-1,NULL,0);
			//Free the allocated memory and continue.
			free(process_command);
			//A label
			label2:
			free(read);
			free(write);
			free(append);
			free(user_input_array);
                    	continue;
		}
		//=================================================================================
		//Else run the external commands by a child.
		pid_t process = fork();
		//If fork is un-successful, print error.
		if(process < 0) fprintf(stderr,"\033[1;91mERROR: Could not fork!\n\033[0m");
		//Else if it return 0, then execute the child.
		else if (process == 0) execute_commands(user_input_array , all_paths,argument_numbers);
		//Else wait for parent process.
		else waitpid(-1,NULL,0);
		//Free the memory.
		free(user_input_array);
	}
	//Free all memory.
	free(all_paths);
	fclose(history_ptr);
	//Clear
	CLEAR
	//Print good bye message.
	YELLOW
	print_message("Good Bye",'*');
	print_message("This Mini Shell is created by Akshat Mittal @ 200101011",' ');
	printf("\n");
	RESET
	//END OF MAIN FUNCTION.
	return 0;
}
//=================================================================================================
//This function will find all paths that are available in shell to execute the external commands.
char** find_all_paths()
{
	//This can be done via PATH environment variable.
	char* PATH = getenv("PATH");
	//Only thing remains is to separate them into different strings.
	for(int i=0; i<strlen(PATH); i++)
	{
		//Increment the value of this global variable.
		if(PATH[i] == ':') total_paths++;
	}
	//Allocate memory for storing paths.
	char** result = (char **)malloc(total_paths * sizeof(char *));
	for(int i=0; i<total_paths; i++) result[i] = (char *)malloc(PATH_MAX * sizeof(char));
	//Separate the PATH value, whenever you find a ':' symbol.
        char* token = strtok(PATH, ":");
        int i=0;
        while(token != NULL)
        {
        	strcpy(result[i], token);
        	i++;
        	token = strtok(NULL, ":");
        }
        //Return the array of all paths.
        return result;
}
//=================================================================================================
//This function counts the number of arguments in user input keeping in mind all whitespaces, double quotes, redirection and piping symbols.
int count_argument_numbers(char* user_input)
{
	//Start with 1.
	int result = 1;
	int i=0;
	//If first element is a whitespace of string is empty,then decrement result.
	if(user_input[0] == ' ' || user_input[0] == '\t' || user_input[0]=='\0') result--;
	//If first element is a symbol, then move to second element and also increment result.
	if(user_input[0] == '|' || user_input[0]=='<' || (user_input[0] == '>' && user_input[1]!='>') || user_input[i]=='=')
	{
		i++;
		result++;
	}
	//If first two are symbols,then move to third element and also increment result.
	if(user_input[0] == '>' && user_input[1]=='>')
	{
		i+=2;
		result++;
	}
	//Start a loop for all next elelments.
	for(i; i<strlen(user_input); i++)
	{
		//If a double quote is there, then skip the loop till it's closing partner is found.
		if(user_input[i] == '\"' || user_input[i] == '\'')
		{
			int j;
			for(j=i+1; j<strlen(user_input); j++)
			{
				if(user_input[j] == '\"' || user_input[j] == '\'') break;
			}
			//Skip part of main loop
			i=j;
		}
		//If a symbol is there.
		else if(user_input[i]=='<')
		{
			//Increment by 2.
			result+=2;
			//But if it is followed by a whitespace, decrement by 1.
			if(user_input[i+1]==' ' || user_input[i+1]=='\t' || user_input[i+1]=='\0') result--;
		}
		//If another symbol.
		else if(user_input[i]=='=')
		{
			//Increment by 2.
			result+=2;
			//But if it is followed by a whitespace, decrement by 1.
			if(user_input[i+1]==' ' || user_input[i+1]=='\t' || user_input[i+1]=='\0') result--;
		}
		//If another symbol.
		else if(user_input[i]=='|')
		{
			//Increment by 2.
			result+=2;
			//But if it is followed by a whitespace, decrement by 1.
			if(user_input[i+1]==' ' || user_input[i+1]=='\t' || user_input[i+1]=='\0') result--;
		}
		//If another symbol.
		else if(user_input[i]=='>')
		{
			//Increment by 2.
			result+=2;
			//But if it is followed by a whitespace, decrement by 1.
			if(user_input[i+1]==' ' || user_input[i+1]=='\t' || user_input[i+1]=='\0') result--;
			//Else if it is followed by another same symbol,skip that.
			else if(user_input[i+1]=='>')
			{
				i++;
				//But if it is followed by a whitespace, decrement by 1.
				if(user_input[i+1]==' ' || user_input[i+1]=='\t' || user_input[i+1]=='\0') result--;
			}
		}
		//Else if whitespace is there, which is not followed by a whitespace or a symbol, increment by 1.
		else if((user_input[i] == ' ' || user_input[i] == '\t') && user_input[i+1]!=' ' && user_input[i+1]!='\t' && user_input[i+1]!='>' && user_input[i+1]!='<' && user_input[i+1]!='\0' && 			user_input[i+1]!='|' && user_input[i+1]!='=') result++;
	}
	//Return result.
	return result;
}
//=================================================================================================
//This function parse the user input into different arrays keeping in mind all whitespaces, double quotes, redirection and piping symbols.
//This is similar to previous function.
char** separate_user_input(char* user_input, int n)
{
	//Allocate memory.
	char** result = (char **)malloc((n+1) * sizeof(char *));
	for(int i=0; i<=n; i++) result[i] = (char *)malloc(1024 * sizeof(char));
	//Set two variables, one for input and another for current position in result.
	int i=0,j=0;
	//If start is whitespace, decremwent j.
	if(user_input[0] == ' ' || user_input[0] == '\t' || user_input[0]=='\0') j--;
	//If only first is symbol, store it in first location. Increment i and j by 1.
	if(user_input[0] == '|' || user_input[0]=='<' || (user_input[0] == '>' && user_input[1]!='>') || user_input[0]=='=' )
	{
		strncat(result[0],&user_input[0],1);
		i++;
		j++;
	}
	//If first two are symbol, store it in first location. Increment i by 2 and j by 1.
	if(user_input[0] == '>' && user_input[1]=='>')
	{
		strncat(result[0],&user_input[0],2);
		i+=2;
		j++;
	}
	//Start the loop.
	for(i; i<strlen(user_input); i++)
	{
		//If a double quote is there, then skip the loop till it's closing partner is found and store all chararcters in between in a single string.
		if(user_input[i] == '\"' || user_input[i] == '\'')
		{
			int k;
			for(k=i+1; k<strlen(user_input); k++)
			{
				strncat(result[j],&user_input[k],1);
				if(user_input[k+1] == '\"' || user_input[k+1] == '\'') break;
			}
			//Skip to closing quote.
			i=k+1;
		}
		//If a symbol is there.
		else if(user_input[i]=='<')
		{
			//Store that in next location and increment j by 2.
			result[j+1] = "<";
			j+=2;
			//But if it is followed by a whitespace, decrement j by 1.
			if(user_input[i+1]==' ' || user_input[i+1]=='\t' || user_input[i+1]=='\0') j--;
		}
		//If a symbol is there.
		else if(user_input[i]=='=')
		{
			//Store that in next location and increment j by 2.
			result[j+1] = "=";
			j+=2;
			//But if it is followed by a whitespace, decrement j by 1.
			if(user_input[i+1]==' ' || user_input[i+1]=='\t' || user_input[i+1]=='\0') j--;
		}
		//If a symbol is there.
		else if(user_input[i]=='|')
		{
			//Store that in next location and increment j by 2.
			result[j+1] = "|";
			j+=2;
			//But if it is followed by a whitespace, decrement j by 1.
			if(user_input[i+1]==' ' || user_input[i+1]=='\t' || user_input[i+1]=='\0') j--;
		}
		//If another symbol.
		else if(user_input[i]=='>')
		{
			//Store that in next location and increment j by 2.
			result[j+1] = ">";
			j+=2;
			//But if it is followed by a whitespace, decrement j by 1.
			if(user_input[i+1]==' ' || user_input[i+1]=='\t' || user_input[i+1]=='\0') j--;
			//Else if it is followed by another same symbol, store that at same location and increment i by 1.
			else if(user_input[i+1]=='>')
			{
				result[j-1] = ">>";
				i++;
				//But if it is followed by a whitespace, decrement j by 1.
				if(user_input[i+1]==' ' || user_input[i+1]=='\t' || user_input[i+1]=='\0') j--;
			}
		}
		//Else if whitespace is there, which is not followed by a whitespace or a symbol, increment j by 1.
		else if((user_input[i] == ' ' || user_input[i] == '\t') && user_input[i+1]!=' ' && user_input[i+1]!='\t' && user_input[i+1]!='>' && user_input[i+1]!='<' && user_input[i+1]!='\0' && 			user_input[i+1]!='|' && user_input[i+1]!='=') j++;
		//Else if not a whitespace, strore it in current location.
		else if((user_input[i] != ' ' && user_input[i] != '\t')) strncat(result[j],&user_input[i],1);
	}
	//Last string is set to NULL to mark the end.
	result[n] = NULL;
	//Return parsed input.
	return result;
}
//=================================================================================================
//This function checks whether a particular string is present in the parsed user input.
int is_present(char** string, int count, char* to_find)
{
	//For all strings, check!
	for(int i=0; i<count; i++)
	{
		//If found, return 1.
		if(!strcmp(string[i], to_find)) return 1;
	}
	//If not found return 0.
	return 0;
}
//=================================================================================================
//This function counts and finds all accurance of a particular string in the parsed user input.
int find_positions(char** string, int count, char* to_find, int** result)
{
	//Allocate memory to store the positions.
	*result = (int *)malloc(sizeof(int));
	int total_count=0;
	for(int i=0; i<count; i++)
	{
		//Check all strings, if found, increse the count and store the position.
		if(!strcmp(string[i], to_find))
		{
			total_count++;
			*result = (int *)realloc(*result,total_count*sizeof(int));
			*result[total_count-1] = i;
		}
	}
	//Retrun count.
	//Positions will automatically be updated in original function because of the use of pointer arithmetic.
	return total_count;
}
//=================================================================================================
//This function will split the parsed user input into two different commands at given position.
char*** split_commands(char** command, int command_size, int position)
{
	//Allocate memory for two commands.
	char*** result;
	result = (char ***)malloc(2 * sizeof(char **));
	result[0] = (char **)malloc((position+1) * sizeof(char *));
	result[1] = (char **)malloc((command_size - position) * sizeof(char *));
	for(int i=0; i<=position; i++) result[0][i] = (char *)malloc(1024 * sizeof(char));
	for(int i=0; i<=(command_size - position - 1); i++) result[1][i] = (char *)malloc(1024 * sizeof(char));
	//Traverse all strings.
	for(int i=0; i<command_size; i++)
	{
		//For all strings previous to given position, store them in first command.
		if(i < position) strcpy(result[0][i], command[i]);
		//Rest all will go to second command.
		else if(i > position) strcpy(result[1][i - position -1], command[i]);
	}
	//Add a NULL to end of both command since execv() function requires a null-terminated array.
	result[0][position] = NULL;
	result[1][command_size-position-1] = NULL;
	//Return result.
	return result;
}
//=================================================================================================
//This function finds the main command after removing symbols and redirected files.
char** find_command(char** str,int n1,int n2)
{
	//Allocate memory for command.
	char** result = (char**)malloc((n2+1)*sizeof(char*));
	for(int i=0; i<=n2;i++) result[i] = (char*)malloc(1024*sizeof(char));
	int j=0;
	//Traverse all input.
	for(int i=0;i<n1;i++)
	{
		//If there is a redirection, ignore that and next string
		if(!strcmp(str[i],">") || !strcmp(str[i],">>") || !strcmp(str[i],"<")) i++;
		//Rest all goes to main coommand,
		else
		{
			result[j] = str[i];
			j++;
		}
	}
	//Add a NULL to end of command since execv() function requires a null-terminated array.
	result[n2]=NULL;
	//Return command.
	return result;
}
//=================================================================================================
//This function finds the path of the external command.
char* get_program_path(char* command, char** all_paths)
{
	//Travese all the paths.
	for(int i=0; i<total_paths; i++)
	{
		char* buf;
		buf = (char *)malloc(1024 * sizeof(char));
		sprintf(buf, "%s/%s", all_paths[i], command);
		//Check if the command is present at this location. If yes, then return the location, else next path.
		if(access(buf, X_OK) == 0) return buf;
		free(buf);
	}
	//If command is not present at any path, return NULL.
	return NULL;
}
//=================================================================================================
//This function prints a center-aligned message on screen.
void print_message(char* str, char c)
{
	struct winsize width;
	//Find width od screen.
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &width);
	//Find the number of blank spaces.
	int initial_gap = (width.ws_col - strlen(str) - 2)/2;
	//Print centre aligned message.
	printf("\n");
	for(int i=0; i<initial_gap; i++) printf("%c",c);
	printf(" %s ",str);
	for(int i=0; i<initial_gap; i++) printf("%c",c);
	printf("\n");
}
//=================================================================================================
//This function replaces the value of environment variable into our input array.
char** execute_env_var(char** str,int n,char** paths)
{
	//Allocate new memory.
	char** result = (char **)malloc((n+1) * sizeof(char *));
	for(int i=0; i<=n; i++) result[i] = (char *)malloc(1024 * sizeof(char));
	//Traverse each string.
	for(int i=0;i<n;i++)
	{
		//If string is "$VAR" where VAR is environment variable, then place it's value in new.
		if(str[i][0]=='$' && getenv(&str[i][1])) result[i] = getenv(&str[i][1]);
		//If not, then copy as it is.
		else result[i] = str[i];
	}
	//Free old array.
	free(str);
	//Set last element to NULL.
	result[n] = NULL;
	//Return new array.
	return result;
}
//=================================================================================================
//If user type an environment variable without echo or printenv, then show error and correct form.
void print_env_var_error(char **str)
{
	RED
	print_error_message
	RESET
	printf("To get the value of ");
	CYAN
	printf("%s",str[0]);
	RESET
	printf(" : type ");
	CYAN
	printf("echo $%s",str[0]);
	RESET
	printf(" or use ");
	CYAN
	printf("printenv %s",str[0]);
	RESET
	printf(" command.\n");
}
//=================================================================================================
//This function executes the change directory operation.
void execute_cd_command(char** str, int n)
{
	//Store in user path, the location of home directory of user.
	char* user_path = (char *)malloc(PATH_MAX * sizeof(char));
	sprintf(user_path, "/home/%s", getenv("USER"));
	//If only cd is input, change directory to home directory.
	if(n == 1)
	{
		//If it is not accessible, print error.		
		if(chdir(user_path) != 0) fprintf(stderr,"\033[1;91mOperation Failed!\nNo Such File or Directory exists!\n\033[0m");
	}
	//Else change directory to given location using chdir() function.
	else
	{
		//If not accessible, print error.
		if(chdir(str[1]) != 0) fprintf(stderr,"\033[1;91mOperation Failed!\nNo Such File or Directory exists!\n\033[0m");
	}
}
//=================================================================================================
//This function executes the history command using cat, i.e., print the history file.
void execute_history(char** paths)
{
	//Store a null-terminated array.
	char* command_history[3] = {"cat", "/tmp/history.txr",NULL};
	//Create a child process
	pid_t process = fork();
	//If un-successful, print error.
	if(process < 0) fprintf(stderr,"\033[1;91mERROR: Could not display history! Please try again.\n\033[0m");
	//Else if successful, execute child.
	else if (process == 0)
	{
		//Execute cat command.
		execv(get_program_path(command_history[0], paths), command_history);
		exit(0);
	}
	//Else wait.
	else waitpid(-1,NULL,0);
}
//=================================================================================================
//This function executes all internal and external commands in the shell.
void execute_commands(char** command, char** paths, int n)
{
	//Execute history.
	if(!strcmp(command[0], "history") && n==1)
	{
		execute_history(paths);
		exit(0);
	}
	char* command_path;
	//Execute which which prints the path of given external command..
	if(!strcmp(command[0], "which"))
	{
		//Print the paths of all commands after which.
		for(int i=1; i<n ;i++)
		{
			command_path = get_program_path(command[i], paths);
			if(access(command_path, X_OK) == 0) printf("%s\n",command_path);
		}
		exit(0);
	}
	//Else execute the external commands using execv().
	command_path = get_program_path(command[0], paths);
	//If Path is accessible, execute command.
	if(access(command_path, X_OK) == 0)
	{
		//IF command can not be executed because of some other reason, print error.
		if(execv(command_path , command)<0)
		{
			fprintf(stderr,"\033[1;91mERROR: Could not execute command\n\033[0m");
			exit(0);
		}
	}
	//If can not access path, print error,
	else
	{
		RED
		print_error_message
		RESET
		exit(0);
	}
	//Free memory
	free(command_path);
	exit(0);
}
//=================================================================================================
// End Of Our Mini Shell.
