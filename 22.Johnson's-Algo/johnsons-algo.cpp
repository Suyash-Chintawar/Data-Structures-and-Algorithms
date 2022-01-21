/*
This program implements Johnson's Algorithm 
with time complexity O(VE+V^2logE)
Adjacency list has been used to store modified graph
NOTE: 
1) Vertices must be 0-based
2) Please refrain from giving wrong inputs
*/
#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second
typedef pair<int,int> pii;

//Compute adjacency list of graph
void adjacency_list(int v,int edges,vector<pair<pii,int>> edge,vector<pii> adj_list[])
{
    for(int i=0;i<edges;i++)
    {
        adj_list[edge[i].f.f].push_back({edge[i].f.s,edge[i].s});
    }
}

//Perform Bellman-Ford Algorithm
void bellman_ford(int v, int src, vector<pair<pii,int>> edge, vector<int> &d)
{
	d[src]=0; // distance of source is zero from itself
	int num_edges = edge.size();
	for(int i=0;i<v-1;i++) //run |v|-1 times
	{
		for(int j=0;j<num_edges;j++) // check for updates in each edge
		{
			int s,e;
			int cost;
			s=edge[j].f.f; //starting of edge
			e=edge[j].f.s; // end of edge
			cost=edge[j].s;
			if(d[s]<INT_MAX) //update min cost distance found
			{
				d[e] = min(d[e],d[s]+cost);
			}
		}
	}
}

//Implement Dijkstra's Algorithm
vector<int> dijkstra(int src,int n, vector<pii> adj_list[])
{
    vector<int> d(n,INT_MAX);//distances/costs of all vertices, initialized to infinte
    vector<int> found(n,0);//to store shortest distances/costs
    d[src]=0;
    priority_queue<pii,vector<pii>,greater<pii>> q;//min-heap
    q.push({0,src});//pushing starting vertex as distance is zero from itself
    while(!q.empty())
    {
        int dv=q.top().first;//distance of shortest distanced vertex
        int v=q.top().second;//vertex with shortest distance
        q.pop();
        if(dv!=d[v]) continue;//occur when path of adjacent vertex already is shortest
        found[v]=dv;
        for(auto x:adj_list[v])//check and update adjacent vertices' distances
        {
            int adj_x=x.first;
            int weight=x.second;
            if(dv+weight < d[adj_x])//shorter path found
            {
                d[adj_x]=dv+weight;
                q.push({d[adj_x],adj_x});
            }
        }
    }
    return d;
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
	cout<<"Enter "<<edges<<" edges (each line format: v1 v2 cost):\nNOTE: vertices must be 0-based\n";
	for(int i=0;i<edges;i++)
	{
		int s,e,cost;
		cin>>s>>e>>cost;
		edge.push_back({{s,e},cost});
	}

	//distances we get from Bellman Ford Algorithm
	vector<int> d(v+1,INT_MAX);

	//add new vertex and generate edges to all vertices with weight 0
	for(int i=0;i<v;i++)
	{
		edge.push_back({{v,i},0});
	}

	// Call bellman ford with source vertex as the new vertex
	bellman_ford(v+1,v,edge,d);

	//remove the extra added edges after Bellman Ford is finished
	edge.erase(edge.begin()+edges,edge.end());

	//update edge costs so that no negative edge weights remain
	for(int i=0;i<edges;i++)
	{
		int s,e;
		int cost;
		s=edge[i].f.f; //starting of edge
		e=edge[i].f.s; // end of edge
		cost=edge[i].s;
		edge[i].s=cost+d[s]-d[e];
	}

	cout<<"\nModified graph(edge list):\n";
	for(int i=0;i<edges;i++)
	{
		cout<<edge[i].f.f<<" "<<edge[i].f.s<<" "<<edge[i].s<<endl;
	}
	
	//storing adjacency list
	vector<pii> adj_list[v];
    adjacency_list(v,edges,edge,adj_list);
    	
    //Stores our final distance matrix
    vector<vector<int>> dist_matrix;

	//dijkstra on all vertices
    for(int i=0;i<v;i++)
    {
    	vector<int> temp=dijkstra(i,v,adj_list);
    	dist_matrix.push_back(temp);
    }

    cout<<"\n*****FINAL DISTANCE MATRIX*****\n";
    for(int i=0;i<v;i++)
    {
    	for(int j=0;j<v;j++)
    	{
    		if(dist_matrix[i][j]!=INT_MAX) dist_matrix[i][j]=dist_matrix[i][j]-d[i]+d[j];
    		if(dist_matrix[i][j]!=INT_MAX) cout<<setw(3)<<dist_matrix[i][j]<<" ";
    		else cout<<"INF ";

    	}
    	cout<<endl;
    }
}