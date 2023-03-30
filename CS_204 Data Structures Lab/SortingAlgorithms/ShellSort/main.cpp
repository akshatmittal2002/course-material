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
    int temp,j;
    for(int gap=(arr_size/2); gap>0; gap/=2)
    {
        for(int i=gap; i<arr_size; i++)
        {
           temp = arr[i];
           for(j=i; ((j>=gap) && (arr[j-gap]>temp)); j-=gap)
           {
               arr[j]=arr[j-gap];
           }
           arr[j]=temp;
        }
    }
    cout<<"Sorted Array:";
    for(int i=0; i<arr_size; i++)
    {
        cout<<" "<<arr[i];
    }
    cout<<endl;
    return 0;
}
