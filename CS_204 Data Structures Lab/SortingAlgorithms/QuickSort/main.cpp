#include <iostream>

using namespace std;

int partition_index(int*,int,int);
void quick_sort(int*,int,int);
void do_swap(int*,int*);

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
    quick_sort(arr,0,arr_size-1);
    cout<<"Sorted Array:";
    for(int i=0; i<arr_size; i++)
    {
        cout<<" "<<arr[i];
    }
    cout<<endl;
    return 0;
}

void do_swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int* arr, int low, int high)
{
    if(low >= high)
    {
        return;
    }
    int mid = partition_index(arr,low,high);
    quick_sort(arr,low,mid-1);
    quick_sort(arr,mid+1,high);
}

int partition_index(int* arr, int low, int high)
{
    int pivot = arr[high];
    int i = low-1;
    for(int j=low; j<high; j++)
    {
        if(arr[j]<=pivot)
        {
            do_swap(&(arr[i+1]),&(arr[j]));
            i++;
        }
    }
    do_swap(&(arr[i+1]),&(arr[high]));
    return (i+1);
}
