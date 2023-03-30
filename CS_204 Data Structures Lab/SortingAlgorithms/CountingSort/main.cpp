#include <iostream>

using namespace std;

int main()
{
    int arr_size=0;
    cout<<"Enter Size of Array: ";
    cin>>arr_size;
    int arr[arr_size]={0};
    cout<<"Enter Array: ";
    cin>>arr[0];
    int maximum=arr[0], minimum=arr[0];
    for(int i=1; i<arr_size; i++)
    {
        cin>>arr[i];
        maximum = max(maximum,arr[i]);
        minimum = min(minimum,arr[i]);
    }
    int ans[arr_size]={0};
    int count_arr[maximum-minimum+1]={0};
    for(int i=0; i<arr_size; i++)
    {
        count_arr[arr[i]-minimum]++;
    }
    for(int i=1; i<(maximum-minimum+1); i++)
    {
        count_arr[i] = count_arr[i]+count_arr[i-1];
    }
    for(int i=arr_size-1; i>=0; i--)
    {
        ans[count_arr[arr[i]-minimum]-1] = arr[i];
        count_arr[arr[i]-minimum]--;
    }
    cout<<"Sorted Array:";
    for(int i=0; i<arr_size; i++)
    {
        cout<<" "<<ans[i];
    }
    cout<<endl;
    return 0;
}
