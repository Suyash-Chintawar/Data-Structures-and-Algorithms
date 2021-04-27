//Program to analyze comparisons and exchanges of quadratic sorting techniques
#include<bits/stdc++.h>
using namespace std;

//Function to sort using bubble sort
void bubbleSort(int a[],int n)
{
	int temp,i,j;
	int comparisons=0,exchanges=0;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-1-i;j++)
		{
			comparisons++;
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
				exchanges++;
			}
		}
	}
	if(floor(log2(n))==ceil(log2(n)))
	{
		cout<<"Array size: "<<n<<endl;
		cout<<"->No. of comparisons: "<<comparisons<<endl;
		cout<<"->No. of exchanges  : "<<exchanges<<"\n\n";
	}
}

//Function to sort using selection sort
void selectionSort(int a[],int n)
{
	int pos,temp,min_value,comparisons=0,exchanges=0,i,j;
	for(i=0;i<n;i++)
	{
		min_value=INT_MAX;
		for(j=i+1;j<n;j++)
		{
			comparisons++;
			if(a[j]<min_value)
			{
				pos=j;
				min_value=a[j];
			}
		}
		if(min_value<a[i])
		{
			exchanges++;
			temp=a[i];
			a[i]=min_value;
			a[pos]=temp;
		}
	}
	if(floor(log2(n))==ceil(log2(n)))
	{
		cout<<"Array size: "<<n<<endl;
		cout<<"->No. of comparisons: "<<comparisons<<endl;
		cout<<"->No. of exchanges  : "<<exchanges<<"\n\n";
	}
}

//Function to sort using insertion sort
void insertionSort(int a[],int n)
{
	int exchanges=0,comparisons=0,temp,i,j;
	for(i=1;i<n;i++)
	{
		j=i-1;
		temp=a[i];
		while(j>=0 && a[j]>temp)
		{
			comparisons++;
			exchanges++;
			a[j+1]=a[j];
			j--;
		}
		comparisons++;
		a[j+1]=temp;
	}

	if(floor(log2(n))==ceil(log2(n)))
	{
		cout<<"Array size: "<<n<<endl;
		cout<<"->No. of comparisons: "<<comparisons<<endl;
		cout<<"->No. of exchanges  : "<<exchanges<<"\n\n";
	}
}

//Main function
int main()
{
    cout<<"***SORTING ANALYSIS***\n";
	int n,choice,i;//n is the size of array
	char con='y';
	while((con=='Y')||(con=='y'))
	{
		n=2;
		int arr[1024];//we are not going beyond 1024 size as per question
		cout<<"*Menu*\n1-Selection sort\n2-Bubble sort\n3-Insertion Sort\nEnter the number of the sorting technique to be analyzed(1/2/3):";
		cin>>choice;
        if(choice==1)
        {
            while(n<=1024)
            {
                for(i=0;i<n;i++) arr[i]=rand()%100000;
                selectionSort(arr,n);
                n*=2;
            }
        }
        else if(choice==2)
        {
            while(n<=1024)
            {
                for(i=0;i<n;i++) arr[i]=rand()%100000;
                bubbleSort(arr,n);
                n*=2;
            }
        }
        else if(choice==3)
        {
            while(n<=1024)
            {
                for(i=0;i<n;i++) arr[i]=rand()%100000;
                insertionSort(arr,n);
                n*=2;
            }
        }
        else
        {
            cout<<"Select a number in 1-3 only,Please run again!!\n";
            con='n';
            goto last;
        }
		cout<<"Do you want to continue?(y/n): ";
		cin>>con;
    last:;
	}
    cout<<"***THANK YOU***\n";
	return 0;
}
