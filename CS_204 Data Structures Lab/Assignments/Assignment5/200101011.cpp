#include <iostream>

using namespace std;

///Function to find sum of digits of a given number.
int sum_of_digits(int);

///Function to swap value of two variables.
void do_swap(int*, int*);

///Function to print an array.
void print_array(int*, int);

///Main function.
int main()
{
    //Declare variable for size of array.
    int arr_size;

    //Take input for array size from user.
    cin>>arr_size;

    //Declare array to store elements.
    int arr[arr_size];

    //Take input for array elements from user.
    for(int i=0; i<arr_size; i++)
    {
        cin>>arr[i];
    }

    //Perform sorting of given array with given criteria.
    ///I am using Bubble Sort.
    for(int i=1 ; i<arr_size ; i++)
    {
		for(int j=0 ; j<(arr_size-i) ; j++)
        {
			//If sum of digit of jth number is more than that of (j+1)th number, swap these to numbers.
			if(sum_of_digits(arr[j]) > sum_of_digits(arr[j+1]))
			{
				do_swap(&(arr[j]) , &(arr[j+1]));
			}

			//Else if sum of digit of jth number is equal to that of (j+1)th number and value of jth number is more that (j+1)th number, swap them.
			else if((sum_of_digits(arr[j]) == sum_of_digits(arr[j+1])) && (arr[j] > arr[j+1]))
            {
                do_swap(&(arr[j]) , &(arr[j+1]));
            }
		}
	}

	//Print final array after sorting.
	print_array(arr , arr_size);
}

///Function to find sum of digits of a given number.
int sum_of_digits(int n)
{
    //Initialize sum to 0.
    int sum = 0;

    //While the number not become 0, perform this:
    //Add last digit of number to the sum and then remove last digit.
    //Perform till all digits are not removed.
    while(n!=0)
    {
        sum += (n%10);

        n/=10;
    }

    //Return the sum of digits.
    return sum;
}

///Function to swap value of two variables.
void do_swap(int* a, int* b)
{
    //Store value of one variable into temporary variable.
    int temp = *a;

    //Store the other variable value into first variable.
    *a = *b;

    //Then store temporary variable value into other variable.
    *b = temp;
}

///Function to print an array.
void print_array(int* arr, int n)
{
    //Print array elements separated by a single space.
    for(int i=0 ; i<n ; i++)
    {
        if(i!=0) cout<<" ";

        cout<<arr[i];
    }

    //Output a new line character.
    cout<<"\n";
}
