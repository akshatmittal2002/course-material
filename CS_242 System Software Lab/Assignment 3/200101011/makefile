#The C program file
MAIN = 200101011_Assign03_Q1

#The executable file
FILE = 200101011

#File in which we will save the user input.
TEST = input

#==================================================================================================
#This will run after "execute" has been completed, ie, at the end and will remove both the files.
clean: execute
	@rm $(FILE).out
	@rm $(TEST).txt

#==================================================================================================
#This will run after "input" has been completed and will run our C program taking input from TEST file.
execute: input
	@./$(FILE).out $(TEST).txt

#==================================================================================================
#This will run after "compile" has been completed and will take the user input for name of environment variable.
#If environment variable exists, it will ask user whether to modify or retain the value of environment variable.
#In case of modification, it will ask for a new value.
input: compile
	@while [ -z $$VAR ]; do \
		read -r -p "Enter environment variable: " VAR; \
	done; \
	echo $$VAR >> $(TEST).txt; \
	while [ -z $$SET ]; do \
		read -r -p "Do you want to modify the value of this environment variable? (Y/N): " SET; \
	done; \
	echo $$SET >> $(TEST).txt; \
	if [ $$SET = "Y" ]; then \
		while [ -z $$VAL ]; do \
			read -r -p "Enter value of environment variable: " VAL; \
		done; \
		echo $$VAL >> $(TEST).txt; \
	elif [ $$SET = "y" ]; then \
		while [ -z $$VAL ]; do \
			read -r -p "Enter value of environment variable: " VAL; \
		done; \
		echo $$VAL >> $(TEST).txt; \
	fi;

#==================================================================================================
#This will run at the start and compile our C program.
compile: $(MAIN).c
	@gcc -o $(FILE).out $(MAIN).c

#End of makefile
