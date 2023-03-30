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
    int temp=0, j=0;
    for(int i=1; i<arr_size; i++)
    {
		temp = arr[i];
		for(j=(i-1); j>=0; j--)
        {
			if(arr[j] > temp)
			{
				arr[j+1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j+1] = temp;
	}
    cout<<"Sorted Array:";
    for(int i=0; i<arr_size; i++)
    {
        cout<<" "<<arr[i];
    }
    cout<<endl;
    return 0;
}
