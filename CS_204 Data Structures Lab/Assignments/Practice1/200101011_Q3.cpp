#include <iostream>
using namespace std;

///Input Format:
///             size
///             elements of array separated by a space.

//Function for iterated merge sort.
void merge_sort(int*,int);
//Function to merge back the two parts into single sorted array.
void merge_array(int*,int,int,int);

//Start of main function.
int main()
{
    //Variable to store array size.
    int arr_size=0;
    //Take input of array size.
    cin>>arr_size;
    //Variable to store array.
    int arr[arr_size]={0};
    //Take input of array elements.
    for(int i=0; i<arr_size; i++)
    {
        cin>>arr[i];
    }
    //Call merge sort function.
    merge_sort(arr,arr_size);
    //Print sorted array.
    cout<<"Sorted Array:";
    for(int i=0; i<arr_size; i++)
    {
        cout<<" "<<arr[i];
    }
    cout<<endl;
    return 0;
}

void merge_sort(int* arr,int n)
{
    //In this function, we will merge sub-arrays of size 1 to get sub-arrays of size 2.
    //Then sub-arrays of size 2 will be merged to get sub-arrays of size 4.
    //The same process continues till we get our full array.
    for(int i=1; i<n; i*=2)
    {
        //The variable 'i' will keep note of current size of sub-arrays that we are going to merge starting with 1.
        for(int left=0; left<n-1; left+=(2*i))
        {
            //Variable 'left' will keep note of left index of sub-array.
            //Variable 'mid' for the right of first sub-array as well as for left of second sub-array.
            int mid = min(left+i-1,n-1);
            //Variable right for right of second sub-array.
            int right = min(left+(2*i)-1,n-1);
            //Merge the first and second sub-array.
            merge_array(arr,left,mid,right);
            //After every loop, left will be incremented by (2*i), hence it will now point to next to next sub-array's first element.
        }
        //After every loop, size of sub-array will be doubled, hence i = i*2.
    }
    return;
}

void merge_array(int* arr,int left,int mid,int right)
{
    //Variables to keep track of number of elements merged.
    int i = left;
    int j = mid+1;
    int k = 0;
    //A new temporary array.
    int* temp = new int[right-left+1];
    ///MERGING OF ARRAYS START.
    while((i<=mid) && (j<=right))
    {
        //The smaller of the two will go into temporary array.
        if(arr[i]<=arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    //After one of the array is over, put the remaining elements of another array into temporary array.
    for(; i<=mid; i++,k++)
    {
        temp[k] = arr[i];
    }
    for(; j<=right; j++,k++)
    {
        temp[k] = arr[j];
    }
    //Then replace current array with temporary array.
    for(k=0; k<=(right-left); k++)
    {
        arr[left+k] = temp[k];
    }
    //Free the temporary array.
    delete[] temp;
    return;
}
