#include <iostream>

using namespace std;

void merge_sort(int*,int,int);
void merge_array(int*,int,int,int);

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
    merge_sort(arr,0,arr_size-1);
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
    if(left>=right)
    {
        return;
    }
    int mid = (left+right)/2;
    merge_sort(arr,left,mid);
    merge_sort(arr,mid+1,right);
    merge_array(arr,left,mid,right);
    return;
}

void merge_array(int* arr,int left,int mid,int right)
{
    int i = left;
    int j = mid+1;
    int k = 0;
    int* temp = new int[right-left+1];
    while((i<=mid) && (j<=right))
    {
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

    for(; i<=mid; i++,k++)
    {
        temp[k] = arr[i];
    }
    for(; j<=right; j++,k++)
    {
        temp[k] = arr[j];
    }
    for(k=0; k<=(right-left); k++)
    {
        arr[left+k] = temp[k];
    }
    delete[] temp;
    return;
}
