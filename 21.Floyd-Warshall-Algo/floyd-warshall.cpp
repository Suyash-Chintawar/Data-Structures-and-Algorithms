/*
This program solves all pair shortest path problem
using Floyd-Warshall Algorithm
NOTE: 
1) vertices must be 1-based
2) Refrain from giving wrong inputs
*/
#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second
typedef pair<int,int> pii;

//Printing the distance mattrix
void print(vector<vector<int>> d)
{
	for(int i=0;i<d.size();i++)
	{
		for(int j=0;j<d[0].size();j++) 
		{
			if(d[i][j]!=INT_MAX) cout<<setw(3)<<d[i][j]<<" ";
			else cout<<"INF ";
		}
		cout<<endl;
	}
}

//Floyd-Warshall Algorithm
void floyd_warshall(int v, int edges, vector<pair<pii,int>> edge, vector<vector<int>> &d)
{	
	//Initialize distance matrix with infintes
	for(int i=0;i<v;i++)
	{
		for(int j=0;j<v;j++) d[i][j]=INT_MAX;
	}
	
	// As there would be no loops, main diagonal will be zeros
	for(int i=0;i<v;i++) d[i][i]=0;
	
	//Fill the initial state using the edges in graph
	for(int i=0;i<edges;i++)
	{
		d[edge[i].f.f-1][edge[i].f.s-1] = edge[i].s;
		d[edge[i].f.s-1][edge[i].f.f-1] = edge[i].s;
	}

	cout<<"\n***INITIAL STATE OF DISTANCE MATRIX"<<":***\n";
	print(d);
	
	//Floyd-Warshall main code
	for(int k=0;k<v;k++) //k will be our intermediate vertex
	{
		//run for each d[i][j] via vertex 'k'
		for(int i=0;i<v;i++) 
		{
			for(int j=0;j<v;j++)
			{
				if(d[i][k]<INT_MAX and d[k][j]<INT_MAX)
				{
					//update distance
					d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
				}
			}
		}
		print matrix as stated in question
		if(k==0 or k==2 or k==4)
		{
			cout<<"\n***STATE OF DISTANCE MATRIX AT K = "<<k+1<<":***\n";
			print(d);
		}
	}
}

int main()
{
	//Take input from user
	int v,edges;
	vector<pair<pii,int>> edge;
	cout<<"Enter number of vertices: ";
	cin>>v;
	cout<<"Enter number of edges: ";
	cin>>edges;
	cout<<"Enter "<<edges<<" edges (each line format: v1 v2 cost):\nNOTE: vertices must be 1-based\n";
	for(int i=0;i<edges;i++)
	{
		int s,e,cost;
		cin>>s>>e>>cost;
		edge.push_back({{s,e},cost});
	}

	//Distance matrix
	vector<vector<int>> d(v,vector<int> (v,INT_MAX));
	
	//Call floyd-warshall algorithm
	floyd_warshall(v,edges,edge,d);
	
	//Print final state
	cout<<"\n***FINAL STATE OF DISTANCE MATRIX"<<":***\n";
	print(d);

}