#! /bin/sh

#Variable to store total number of arguments.
argument_numbers=$#
#A random string delimeter that will separate different files within archive file.
random_delimiter="#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"
#A random string that will mark the end of the archive file.
end_of_file="END_OF_FILE##END_OF_FILE##END_OF_FILE##END_OF_FILE##END_OF_FILE##END_OF_FILE#END_OF_FILE##END_OF_FILE"

#If appropriate number of arguments are not given, print error and exit.
if [ $argument_numbers -lt 2 ]
then
	echo "ERROR: less number of arguments: [options] [archive-file] [files-to-be-archived]"
	echo "Program terminating..."
	exit
fi

#Store first argument in options.
options=$1
#Store the archive file name in variable called target file.
target_file=$2
#Remaining arguments will be the files that are to be archived/extracted/listed.
number_of_files=$(( $argument_numbers - 2 ))
#This command shifts the argument by two positions left, i.e., options and target file will be removed and all remaining files would be present as inline arguments.
shift 2

#==================================================================================================
#Now doing scanning of options to find which all options are given.

#total number of options in { c, r, t, x }.
crxt_combine=0
# -c not present
c_present=0
#If present make it 1.
if [[ $options =~ "c" ]]
then
	c_present=1
	crtx_combine=$(( $crtx_combine + 1 ))
fi
#Similar for -x option
x_present=0
if [[ $options =~ "x" ]]
then
	x_present=1
	crtx_combine=$(( $crtx_combine + 1 ))
fi
#Similar for -r option
r_present=0
if [[ $options =~ "r" ]]
then
	r_present=1
	crtx_combine=$(( $crtx_combine + 1 ))
fi
#Similar for -t option
t_present=0
if [[ $options =~ "t" ]]
then
	t_present=1
	crtx_combine=$(( $crtx_combine + 1 ))
fi
#Similar for -v option
v_present=0
if [[ $options =~ "v" ]]
then
	v_present=1
fi
#If none of { c, r, t, x } option is given, then display error and exit.
if [ $crtx_combine = 0 ]
then
	echo "ERROR: You must specify one of the '-crtx' options"
	echo "Program terminating..."
	exit
fi
#If more than one of { c, r, t, x } option is given, then display error and exit.
if [ $crtx_combine -gt 1 ]
then
	echo "ERROR: You may not specify more than one '-crtx' options"
	echo "Program terminating..."
	exit
fi

#If -f option is not given, tar file will be created on tape which is to be avoided as confirmed from professor.
#Hence display error message and exit, if -f is not given.
if [[ ! $options =~ "f" ]]
then
	echo "ERROR: Refusing to read archive contents from terminal: missing -f option"
	echo "Program terminating..."
	exit
fi

#==================================================================================================
#New command creted to check whether given archive file, if exists, is created using this script only or not.
validity_check()
{
	#First argument is file to be checked.
	file_to_be_checked=$1
	#Second argument is delimiter.
	delimiter=$2
	#Third argument is end file.
	end_file=$3
	#Variable to store whether file is valid or not.
	valid="false"
	#First line of file should be random string delimeter as defined initially.
	read -r line < $file_to_be_checked
	#If it is, then check for end file string.
	if [ "$line" = "$delimiter" ]
	then
		#Scan through whole file
		while IFS= read -r line
		do
			#If end file character found, break the while loop and make valid as true.
			if [ "$line" = "$end_file" ]
			then
				valid="true"
				break
			fi
		done < $file_to_be_checked
	fi
	#Now if valid is true, we have to do nothing.
	#But if not, then print error and exit the script.
	if [ "$valid" = "false" ]
	then
		echo "ERROR: $target_file is in invalid format: Not created using this script"
		echo "Program terminating..."
		exit
	fi
}

#==================================================================================================
#Now the script of -c option if present.
# "-cf" only creates new archive of given files.
# "-cvf" creates new archive and list the names of files that are included in archive.
if [ $c_present = 1 ]
then
	#If no file is given after the archive file, then print error and exit since a empty tar file couldn't be created by the "tar" command.
	if [ $number_of_files = 0 ]
	then
		echo "ERROR: Cowardly refusing to create an empty archive"
		echo "Program terminating..."
		exit
	fi
	#Now if files are specified, remove the tar file, if it is present already, since user wants to create a new tar file.
	rm -f $target_file
	#Create a new file with given name.
	touch $target_file
	#For every file given in argument after archive file, repeat this process.
	for file in "$@"
	do
		#If the file exists, then move it's content into archive file.
		if [[ -f "$file" ]]
		then
			#First given delimeter
			echo "$random_delimiter" >> $target_file
			#Then file name
			echo "$file" >> $target_file
			#Then file details
			ls -lh $file >> $target_file
			#Then all content of that file.
			cat $file >> $target_file
		#If file is not present, then display an error message and skip that file.
		else
			number_of_files=$(( $number_of_files - 1 ))
			echo "ERROR: $file: No such file or directory: Not included in archive"
		fi
	done
	#After doing this for all files, put end of file character into the archive file to mark the end.
	echo "$end_of_file" >> $target_file
	
	#Now if -v option is also present, display the names of all that files which we have included in archive.
	if [ $v_present = 1 ]
	then
		for file in "$@"
		do
			#If file is present, display it's name.
			if [[ -f "$file" ]]
			then
				echo "$file"
			#If file is not present, display error.
			else
				echo "ERROR: $file: No such file or directory"
			fi
		done
	fi
fi

#==================================================================================================
#Now the script of -t option if present.
# "-tf" lists all the files present in given archive file.
# "-tvf" lists all files in archive with complete details.
if [ $t_present = 1 ]
then
	#First check if specified archive file is present or not.
	#If present check for validity.
	if [[ -f "$target_file" ]]
	then
		validity_check $target_file $random_delimiter $end_of_file
	#If not present, display an error message and exit.
	else
		echo "ERROR: $target_file: No such file or directory"
		echo "Program terminating..."
		exit
	fi
	#Now if no file name is specified after archive file name, then display all the files present.
	if [ $number_of_files = 0 ]
	then
		#Read archive line by line and based on positions of delimeter and end of file string, list available files.
		while IFS= read -r line
		do
			#If line becomes the delimeter, then:
			if [ "$line" = "$random_delimiter" ]
			then
				#Read next line which will have name of file.
				read -r line
				#If "-v" is present, read next line which contains details of that file.
				if [ $v_present = 1 ]
				then
					read -r line
				fi
				#Display name/details.
				echo "$line"
			#If line becomes end of file, then break the loop.
			elif [ "$line" = "$end_of_file" ]
			then
				exit
			fi
		done < $target_file
	#Else list names/details of only those files, which are specified and present in archive.
	else
		#Variable to keep track of number of files that has been listed.
		files_covered=0
		#Almost similar to previous case but will display the name/details iff it given in command line.
		while IFS= read -r line
		do
			if [ "$line" = "$random_delimiter" ]
			then
				read -r line
				#If the argument contain file name, then only display
				if [[ "$@" =~ "$line" ]]
				then
					if [ $v_present = 1 ]
					then
						read -r line
					fi
					echo "$line"
					files_covered=$(( $files_covered + 1 ))
				fi
			elif [ "$line" = "$end_of_file" ]
			then
				#At the time of exiting, check whether all files that are given as arguments are covered or not.
				#If not, then display error message, since some files are not present in tar.
				if [ $files_covered -lt $number_of_files ]
				then
					echo "SORRY: Some of the listed files couldn't be found in the archived file"
				fi
				exit
			fi
		done < $target_file
	fi
fi

#==================================================================================================
#Now the script of -r option if present.
# "-rf" option appends the files at end of existing archive.
# "-rvf" appends the file as well as lists the name of files, that are appended.
if [ $r_present = 1 ]
then
	#First check if the archive file already exists or not.
	#If present check for validity.
	if [[ -f "$target_file" ]]
	then
		validity_check $target_file $random_delimiter $end_of_file
	#If not then run the same program again but with "-c" option as the affect will be excatly same.
	else
		if [ $v_present = 1 ]
		then
			bash -f 200101011_Assign03_Q2.sh -cvf $target_file $@
		else
			bash -f 200101011_Assign03_Q2.sh -cf $target_file $@
		fi
		exit
	fi
	#Now if archive file already exists.
	#Then we have to append the files.
	#For this, we will make a temp file, extract all the previous files of archive file into that directory and then re-make the same file with new files as well.
	#Make a temp directory.
	mkdir temp
	#Copy our target file and shell script into new directory.
	cp 200101011_Assign03_Q2.sh temp/200101011_Assign03_Q2.sh
	cp $target_file temp/$target_file
	#Create a array to store all the previously present file's names; can be achieved easily using "-tf" option.
	declare -a new_file_list=($(bash -f 200101011_Assign03_Q2.sh -tf $target_file | tr " " " "))
	#For every new file given to append, copy that file into new temp directory.
	for file in "$@"
	do
		#If file exists, then copy it and add that file into the array of file names.
		if [[ -f $file ]]
		then
			cp $file temp/$file
			new_file_list[${#new_file_list[@]}]=$file
		#If file doesn't exist, then display error message.
		else
			number_of_files=$(( $number_of_files - 1 ))
			echo "ERROR: $file: No such file or directory"
		fi
	done
	#Now move into new directory.
	cd temp
	#Extract all the previously present files into the directory.
	bash -f 200101011_Assign03_Q2.sh -xf $target_file
	#Now, using "-cf" option, create a new archive file of all the files together.
	# ${new_file_list[*]} means all the files in array.
	bash -f 200101011_Assign03_Q2.sh -cf $target_file ${new_file_list[*]}
	#Now move the newly created archive file back into initial directory.
	mv $target_file ../$target_file
	#Move back to initial directory.
	cd ..
	#Remove the temp directory.
	rm -r temp
	#Now if "-v" is present, display names of all those files which are successfully appended to archive file.
	if [ $v_present = 1 ]
	then
		for file in "$@"
		do
			if [[ -f "$file" ]]
			then
				echo "$file"
			#If file is not present, print error.
			else
				echo "ERROR: $file: No such file or directory: Not included in archive"
			fi
		done
	fi
fi

#==================================================================================================
#Now the script of -x option if present.
# "-xf" extracts the files from archive.
# "-xvf" extracts the file from archive as well as list them as they are been extracted.
if [ $x_present = 1 ]
then
	#If archive file that is to be extracted is not present than print error and exit.
	#If present check for validity.
	if [[ -f "$target_file" ]]
	then
		validity_check $target_file $random_delimiter $end_of_file
	else
		echo "ERROR: $target_file: No such file or directory"
		echo "Program terminating..."
		exit
	fi
	
	#If no file is specified inside tar file, extract all files.
	if [ $number_of_files = 0 ]
	then
		#Variable to store the current file name being extracted.
		current_file=""
		#Read archive file line-by-line.
		while IFS= read -r line
		do
			#If a delimeter is found, it means a new file is starting.
			if [ "$line" = "$random_delimiter" ]
			then
				#read the name of that file.
				read -r line
				#Store the name into variable.
				current_file="$line"
				#If that file exists, remove it.
				rm -f $line
				#Create a new file with given name.
				touch $line
				#If "-v" is given, display the name of file as well.
				if [ $v_present = 1 ]
				then
					echo "$line"
				fi
				#Read the line containing details of file and go on.
				read -r line
			#If line equals the end file, then exit the loop and program.
			elif [ "$line" = "$end_of_file" ]
			then
				exit
			#For all other lines, append that line into the current file being extracted.
			else
				echo "$line" >> $current_file
			fi
		done < $target_file
	#Else extract only those files which are given by user.
	else
		#Variable to store the current file name being extracted.
		current_file=""
		#Variable to keep track of number of files that has been listed.
		files_covered=0
		#Almost similar to previous case but only extract files given in command line.
		#Read archive file line-by-line.
		while IFS= read -r line
		do
			#If a delimeter is found, it means a new file is starting.
			if [ "$line" = "$random_delimiter" ]
			then
				#Read name of file.
				read -r line
				#Till we get a file name which is present in command line, skip the content.
				while [[ ! "$@" =~ "$line" ]]
				do
					#Skip the file content.
					while [ "$line" != "$random_delimiter" ]
					do
						#Read all lines.
						read -r line
						#If we reach end, then our program ends.
						if [ "$line" = "$end_of_file" ]
						then
							if [ $files_covered -lt $number_of_files ]
							then
								echo "SORRY: Some of the listed files couldn't be found in the archived file"
							fi
							exit
						fi
					done
					#Above loop ends when we get a delimeter.
					#Read next file name.
					read -r line
				done
				#Above loop ends when we get a file which is to be extarcted.
				#Remove that file, if it exists already.
				rm -f $line
				#Store the name in current file variable.
				current_file="$line"
				#Create a new file with given name.
				touch $line
				#If "-v" is given, display the name of file as well.
				if [ $v_present = 1 ]
				then
					echo "$line"
				fi
				#Read the line containing details of file and go on.
				read -r line
				files_covered=$(( $files_covered + 1 ))
			#If line equals the end file, then exit the loop and program.
			elif [ "$line" = "$end_of_file" ]
			then
				#If extracted file number is less than given number of file, then there is a file which doesn't exist in tar file and hence, display error.
				if [ $files_covered -lt $number_of_files ]
				then
					echo "SORRY: Some of the listed files couldn't be found in the archived file"
				fi
				exit
			#For all other lines, append that line into the current file being extracted.
			else
				echo "$line" >> $current_file
			fi
		done < $target_file
	fi
fi
#==================================================================================================
#End of shell script.
