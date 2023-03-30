#include <iostream>

using namespace std;

void merge_sort(int*,int);
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
    merge_sort(arr,arr_size);
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
    for(int i=1; i<n; i*=2)
    {
        for(int left=0; left<n-1; left+=(2*i))
        {
            int mid = min(left+i-1,n-1);
            int right = min(left+(2*i)-1,n-1);
            merge_array(arr,left,mid,right);
        }
    }
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
