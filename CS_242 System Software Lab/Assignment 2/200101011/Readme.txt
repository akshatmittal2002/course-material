Name:			Akshat Mittal
Roll No:		200101011
Assign No:		2
Programming Language:	C
Operating System:	LINUX
===================================================================================================
The submitted zip folder contains three files:
	1. 200101011_Assign02.c
	2. Readme.txt
	3. 200101011

To compile my .c file, use this command in LINUX terminal:

			gcc 200101011_Assign02.c

An a.out file will be created. To execute that file, use:

			./a.out
			
I am using latest gcc compiler for this. In my system, the program is compiled successfully. If any error occurred during compilation, I'm also submitting the executable file: 200101011.
You can run it directly (i.e., without compiling) using:

			./200101011

===================================================================================================
The entire mini shell is based on the flowchart shared by prof.
Features of my mini shell:

	1. Internal commands:
		a. cd : to change current directory.
		b. setenv : to set an environment variable.
		c. printenv : to print an environment variable.
		d. history : to see history of all commands typed so far.
		e. exit/quit/x : to exit from mini shell.
		
	2. Single level piping without redirection (as mentioned by prof.)
	
	3. Redirection without piping: These 5 cases are handled (as mentioned by prof.)
		a. <input.txt
		b. >output.txt
		c. >>append.txt
		d. <input.txt >output.txt
		e. <input.txt >>append.txt
		
	4. A reasonable set of external commands
	
===================================================================================================
Important points to be kept in mind while running the mini shell:
	1. Please run my program only in LINUX terminal since I have used pre-installed libraries of linux which are not-available in windows.
	2. I have managed all whitespaces in input. You can type your command in any format (with or without extra spaces). It will be valid as long as it is valid in LINUX Shell.
		EG. For "cat < 1.txt", u can use "cat <1.txt" or "cat<1.txt" or "cat < 1.txt". All are fine.
		But to use "ls -l", u have to type it with a whitespace only since otherwise it is not supported even in LINUX Shell.
		i.e., they should be in same format as given in LINUX Shell

Some more points:
	1. To view all logics and process followed, see the .c file. Code is properly documented.
	2. All clarifications mentioned here are confirmed from professor as well.
===================================================================================================
A brief description of my code:

	1. An infinite while loop is created, printing current directory and waiting for single line user input.
	2. If user calls for cd, then directory is changed to given path if the path exists.
	3. If user calls setenv with proper format, then a new environment varibale is created with specified value. If environment variable already exists, then it's value is cahnged.
	4. If user calls printenv, then:
		a. If no envirionment varibale is given, then all envirionment variables is printed with their values.
		b. Else the values of specified variables are printed.
	5. If user calls history, then the history file is printed.
	6. If user type exit/quit/x, history file is deleted, all memory is freed, loop is broken and program terminates.
	6. If there is piping in input, after all validity checks, two child processes are created and then both internal and external commands are executed.
	7. If there is redirection, after all validity checks, a child process is created and both internal and external commands are executed with proper redirections to the file descriptors.
	8. In all other cases, user input is executed using a child process and if anything invalid, error is displayed.
	9. In all these cases, the input is saved in the history file in sequeunce.
	10. Then all memory is freed and loop continues from step 1.
===================================================================================================
