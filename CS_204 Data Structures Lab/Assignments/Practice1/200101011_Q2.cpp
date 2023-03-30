#include <iostream>
using namespace std;

///Input Format:
///             size
///             elements of array separated by a space.

//Function for recursive merge sort.
void merge_sort(int*,int,int);
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
    merge_sort(arr,0,arr_size-1);
    //Print sorted array.
    cout<<"Sorted Array:";
    for(int i=0; i<arr_size; i++)
    {
        cout<<" "<<arr[i];
    }
    cout<<endl;
    return 0;
}

void merge_sort(int* arr,int left,int right)
{
    //If array has single element or left>right, then return.
    if(left>=right)
    {
        return;
    }
    //Find middle to split array.
    int mid = (left+right)/2;
    //Call merge sort on left part.
    merge_sort(arr,left,mid);
    //Call merge sort on right part.
    merge_sort(arr,mid+1,right);
    //Merge both sorted parts into single sorted array.
    merge_array(arr,left,mid,right);
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
