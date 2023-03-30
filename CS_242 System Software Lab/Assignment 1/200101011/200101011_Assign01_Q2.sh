#! /bin/bash

count=$1	# Storing first argument in a variable
length=$2	# Storing secong argument in a variable

# Declaring required variables
previous=""			# Variable to keep track of previous alphabet used
current=""			# Variable to keep track of current alphabet being used
substring=""			# Variable to store current subtring
substringlength=0		# Variable to keep track of length of current substring
inputstring=""			# Variable to store the letters given through input data file
repeat=0			# Variable to store number of times current letter is to be repeated

# loop to read all lines of given input file and store them as a single string
while read -n1 char
do
	inputstring="${inputstring}${char}"
done

# Removing continuous duplicate characters from inputstring because we require atleast two distinct characters to run the program till it terminates
inputstring=$(echo $inputstring | tr -s 'a-z')

inputstringlength=${#inputstring}	# Variable to store total number of letters in given input

# Checking if input file is empty or not
if [ $inputstringlength == 0 ]
then
	echo INPUT FILE IS EMPTY
	exit
fi

# Checking if count is greater than 1 or not since repitions shouldn't exceed count
# Count = 1 is also invalid
while [ $count -le 1 ]
do
	echo INVALID FIRST ARGUMENT
	echo MUST BE GREATER THAN 1
	read -p "PLEASE RE-ENTER: " count < /dev/tty
	printf "\n"
done

# Checking if length is non-negative or not
while [ $length -lt 0 ]
do
	echo INVALID SECOND ARGUMENT
	echo MUST NOT BE NEGATIVE
	read -p "PLEASE RE-ENTER: " length < /dev/tty
	printf "\n"
done

# Checking if input file has only single character otherwise repitions will exceed count
if [ $inputstringlength == 1 ] && [ $count -le $length ]
then
	i=1
	while [ $i -lt $count ]
	do
		substring="${substring}${inputstring}"
		i=$(( $i + 1 ))
	done
	echo ERROR : INPUT FILE HAS A UNIQUE CHARACTER
	echo ONLY POSSIBLE STRING IS OF LENGTH: $(( $count - 1 ))
	printf "\n"
	echo $substring
	
# Else if file has single character and length is less than count
elif [ $inputstringlength == 1 ] && [ $count -gt $length ]
then
	i=1
	while [ $i -le $length ]
	do
		substring="${substring}${inputstring}"
		i=$(( $i + 1 ))
	done
	echo $substring
	
# Else run the normal program	
else	
	# Loop which will run till we get a string of required length
	while [ $substringlength -lt $length ]
	do
		position=$(( $RANDOM % $inputstringlength ))	# First random number generator to determine the index of character to be repeated
		current=${inputstring:$position:1}		# Update current letter as per first random number in the input file
		repeat=$(( $RANDOM % $count ))		# Second random number generator to update value of repeat
		
		# Conditions to be checked on random numbers generated before generating string to meet the given criterion
		# Current and previous letter shouldn't be same
		# Total length shouldn't exceed the given length and repeat should not be zero
		if [ "$current" != "$previous" ] && [ $(( $length - $substringlength )) -ge $repeat ] && [ $repeat != 0 ]
		then
			# After correct random number has been generated, concatenate the string
			i=1
			while [ $i -le $repeat ]
			do
				substring="${substring}${current}"
				i=$(( $i + 1 ))
			done
		
			# Update value of previous (to current) and substringlength (add 'repeat') after concatenating strings
			previous=$current
			substringlength=$(( $substringlength + $repeat ))
			echo $substring
		fi
	done
	# While loop ends when substringlength equals length
fi
printf "\n"
# SCRIPT  END
