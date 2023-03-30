Name:		Akshat Mittal
Roll No:	200101011
Assignment No:	1
--------------------------------------------------------------------------
--------------------------------------------------------------------------
For first task run this command to execute the program:
	awk -f 200101011_Assign01_Q1.awk input_Q1.txt

		where, 200101011_Assign01_Q1.awk is awk program
		       input_Q1.txt is the input file

Also, my program will work for any other input file (having same format as given).
--------------------------------------------------------------------------
--------------------------------------------------------------------------
For second task run this command to execute the program:
	bash -f 200101011_Assign01_Q2.sh arg_1 arg_2 < input_Q2.txt

		where, 200101011_Assign01_Q2.sh is shell script
		       arg_1 is first argument representing count
		       arg_2 is second argument representing length
		       input_Q2.txt is input file

If user inputs invalid argument like count<2 or length<0, then the program will generate an error message and prompt user to re-enter it.
Also if input file is empty, then program will show error message.
If input file has only one distinct character, then the string will be generated only upto minimum(count-1 , length) otherwise rules will be violated.
Note: input alphabet set- "aa...a" also comes in above category as it has only one distinct character.
