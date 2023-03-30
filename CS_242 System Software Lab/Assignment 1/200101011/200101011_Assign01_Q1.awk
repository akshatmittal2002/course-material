BEGIN{
	# All the code here will ony be executed once and before reading a record
	# Using a variable "x" to make an array to store the input lines.
	print("")
	print("File After Sorting:")
	print("")
	x = 0
}

{
	# This part will run for each record of given input
	line[x] = $0		# Storing complete record
	sum[x] = $2 + $3	# Taking sum of field 2 and field 3 to sort them
	x = x + 1		# Incrementing x
}

END{
	# All the code here will ony be executed once and after reading all records
	
	# Algoritm to sort the array of sum[] along with corresponding line[]
	# Bubble Sort
	for(i=1; i<=x-1; i=i+1){
		for(j=0; j<=x-1-i; j=j+1){
			if(sum[j] > sum[j+1]){
				temp = sum[j]		#
				sum[j] = sum[j+1]	# Sorting Array Of Sum
				sum[j+1] = temp	#
				
				temp = line[j]		#
				line[j] = line[j+1]	# Correspondingly sorting records
				line[j+1] = temp	#
			}
		}
	}
	
	# Printing records after sorting
	for(i=0; i<=x-1; i=i+1){
		print(line[i])
	}
	print("")
}
# END OF SCRIPT
