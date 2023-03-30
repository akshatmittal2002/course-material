#include <iostream>
using namespace std;

///Input Format:
///             size
///             elements of array separated by a space.

//Start of main
int main()
{
    //Variable to store array size.
    int arr_size=0;
    //Take input of size.
    cin>>arr_size;
    //Array of given size.
    int arr[arr_size]={0};
    //Take input of array elements.
    for(int i=0; i<arr_size; i++)
    {
        cin>>arr[i];
    }
    ///Selection Sort Starts.
    ///In this, at step 'i', we get 'i'th smallest element and place it at 'i'th index.
    //Variable to keep track of index that has minimum value.
    int min_index=0;
    int temp=0;
    //Iterate all over the array.
    for(int i=0; i<arr_size-1; i++)
    {
        //Find index of minimum value in remaining array.
        min_index=i;
        for(int j=(i+1); j<arr_size; j++)
        {
            //If element at index 'j' is smaller, then change minimum index to 'j'.
            if(arr[j]<arr[min_index])
            {
                min_index=j;
            }
        }
        //Swap the minimum value with the value at current index.
        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
    //At the end of loop, we get a well sorted array.

    ///Print sorted array.
    cout<<"Sorted Array:";
    for(int i=0; i<arr_size; i++)
    {
        cout<<" "<<arr[i];
    }
    cout<<endl;
    return 0;
    //End of main.
}
