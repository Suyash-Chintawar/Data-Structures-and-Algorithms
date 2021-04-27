//Program to implement binary heaps
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define MAX_SIZE 1000//max size of the heap can be 1000(as given in problem statement)

class BinaryHeap
{
public:
	vector<int> a;//array a to store heap
	int heap_size;//current size of the heap
	int max_size;//max size of heap possible

	BinaryHeap(int size)//constructor
	{
		heap_size=0;
		max_size=size;
	}

	void heapify(int i)//call heapify on a node to sustain max heap property
	{
		int l=2*i+1;//as zero based indices left=2i+1
		int r=2*i+2;//right=2i+2
		int largest=i;//index of the largest of the three (a[i],a[r],a[l])
		if(l<=heap_size && a[l]>a[i]) largest=l;
		else largest=i;
		if(r<=heap_size && a[r]>a[largest]) largest=r;
		if(largest!=i)//then swap a[i] and a[largest]
		{
			int temp;
			temp=a[i];
			a[i]=a[largest];
			a[largest]=temp;
			heapify(largest);//maintain heap property
		}
	}

	void insert(int key)//insert a key in heap
	{
		if(heap_size==max_size) //heap full
		{
			cout<<"Cannot insert, heap full!\n";
			return;
		}

		heap_size++;
		int i=heap_size-1;
		a.push_back(key);
		while(i!=0 && a[i]>a[(i-1)/2])//maintain heap property
		{
			int temp;
			temp=a[i];
			a[i]=a[(i-1)/2];
			a[(i-1)/2]=temp;
			i=(i-1)/2;
		}

	}

	void maximum()//get the maximum , i.e. a[0]
	{
		if(heap_size!=0) cout<<a[0]<<endl;
		else cout<<"Heap is empty!\n";
	}

	void extract_max()//extract max and swap last element with root and call heapify on root
	{
		if(heap_size==0)
		{
			cout<<"Heap is empty!\n";
			return;
		}
		if(heap_size==1)//one element in heap only
		{
			cout<<a[0]<<endl;
			heap_size--;
			return;
		}
		cout<<a[0]<<endl;
		a[0]=a[heap_size-1];
		heap_size--;
		a.pop_back();//remove last element
		heapify(0);
	}

	void build_heap(vector<int> v)//take the elements to be added in heap
	{
		heap_size=v.size();
		a.clear();//clear previous heap
		for(int i=0;i<heap_size;i++) a.push_back(v[i]);
		for(int i=(heap_size/2);i>=0;i--)//construct heap in  bottom-up fashion
		{
			heapify(i);
		}
	}
};

int main(int argc,char* argv[])//driver function
{
	string filename=argv[1];
	ifstream file;
	file.open(filename);
	string x;
	getline(file,x);
	stringstream s(x);
	int n;
	s>>n;//get number of commands
	BinaryHeap h(MAX_SIZE);//create heap
	for(int i=0;i<n;i++)
	{
		getline(file,x);
		stringstream s(x);
		int command;
		s>>command;//get command number(0,1,2,3)

		if(command==0)//get maximum
		{
			h.maximum();
		}
		else if(command==1)//insert key
		{
			int y;
			while(s>>y)
			{
				h.insert(y);
			}
		}
		else if(command==2)//extract max
		{
			h.extract_max();
		}
		else if(command==3)//build heap
		{
			int y;
			vector<int> v;
			while(s>>y) v.push_back(y);
			h.build_heap(v);
		}
		else//wrong command number entered
		{
			cout<<"Wrong command!\n";
		}
	}
}