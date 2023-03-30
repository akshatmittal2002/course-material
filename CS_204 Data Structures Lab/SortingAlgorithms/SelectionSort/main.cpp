#include <iostream>

using namespace std;

int main()
{
    int arr_size=0;
    cout<<"Enter Size of Array: ";
    cin>>arr_size;
    int arr[arr_size]={0};
    cout<<"Enter Array: ";
    for(int i=0; i<arr_size; i++)
    {
        cin>>arr[i];
    }
    int min_index=0;
    int temp=0;
    for(int i=0; i<arr_size-1; i++)
    {
        min_index=i;
        for(int j=(i+1); j<arr_size; j++)
        {
            if(arr[j]<arr[min_index])
            {
                min_index=j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
    cout<<"Sorted Array:";
    for(int i=0; i<arr_size; i++)
    {
        cout<<" "<<arr[i];
    }
    cout<<endl;
    return 0;
}
