//Program to search for key element using linear and binary search in a sorted array of size 10
#include<bits/stdc++.h>
using namespace std;
int binary_count=0;//Counter for no. of comparisons in binary search
void linearSearch(int a[],int k)
{
    cout<<"1.Linear Search:"<<endl<<"  Compared Elements:";
    int i,l_index,flag=0;
    int cnt=0;//Counter for no. of comparisons in linear search
    //This loop below will check for key element and will break if the key is found
    for(i=0;i<10;i++)
    {
        cout<<a[i]<<" ";
        if(a[i]==k)
        {
            flag=1;
            cnt++;
            l_index=i;
            break;
        }
        else
        {
            cnt++;
        }
    }
    cout<<endl;
    if(flag==1)
    {
        cout<<"  Key element found at position : "<<l_index+1<<endl;
        cout<<"  No. of comparisons: "<<cnt;
    }
    else
    {
        cout<<"  Key element not found!"<<endl<<"  No. of comparisons: "<<cnt;
    }
}
int binarySearch(int a[],int first,int last,int k)
{
    int b_index,i,mid;
    //binary_count++;
    if(last>=first)
    {
        //binary_count++;
        mid=first+((last-first)/2);
        cout<<a[mid]<<" ";
        binary_count++;
        if(a[mid]==k) return mid;
        else if(a[mid]>k) return binarySearch(a,first,mid-1,k);
        else if(a[mid]<k) return binarySearch(a,mid+1,last,k);
    }
    return -1;
}
int main()
{
    int arr[10],i,k,b_index;

    cout<<"Enter 10 sorted array elements:";
    for(i=0;i<10;i++) cin>>arr[i];
    cout<<"Enter key element to search:";
    cin>>k;
    linearSearch(arr,k);//Linear search function call for array arr[] to search 'k'
    cout<<endl<<"2.Binary Search:"<<endl<<"  Mid Elements compared: ";
    b_index=binarySearch(arr,0,9,k);//Binary search function call to search 'k' in array arr[] from index 0-9
    cout<<endl;
    if(b_index!=-1)
    {
        cout<<"  Key element found at position: "<<b_index+1<<endl<<"  No. of comparisons: "<<binary_count;
    }
    else
    {
        cout<<"  Key element not found!"<<endl<<"  No. of comparisons: "<<binary_count;
    }
}
