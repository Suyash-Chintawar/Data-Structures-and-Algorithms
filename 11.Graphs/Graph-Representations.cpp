/*This program computes the adjacency matrix and adjacency lists
of undirected/directed graphs assuming vertices to be 1,2..,n where n
is the number of vertices.
Adjacency matrix is calculated as the number of edges between two vertices,so as to
be consistent with simple and multigraphs both.(If simple graph is there,then all elements will be either 0/1).
Adjacency list is computed using array of vectors.
User must enter edges as one based vertices only.*/
#include<bits/stdc++.h>
using namespace std;

//Computing Adjacency matrix
void adjacency_matrix(int n,int edges,int edge[][2],int type)
{
    int adj[n][n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++) adj[i][j]=0;
    }
    for(int i=0;i<edges;i++)
    {
        adj[edge[i][0]-1][edge[i][1]-1]++;
        if(type==1 && edge[i][0]!=edge[i][1])
        {
            adj[edge[i][1]-1][edge[i][0]-1]++;
        }
    }
    cout<<"\nAdjacency Matrix:\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<setw(3)<<adj[i][j];
        }
        cout<<endl;
    }
}

//Computing Adjacency list
void adjacency_list(int n,int edges,int edge[][2],int type)
{
    vector<int> adj[n];
    for(int i=0;i<edges;i++)
    {
        adj[edge[i][0]-1].push_back(edge[i][1]);
        if(type==1 && edge[i][0]!=edge[i][1])
        {
            adj[edge[i][1]-1].push_back(edge[i][0]);
        }
    }
    cout<<"\nAdjacency lists:\n";
    for (int i=0; i<n;i++)
    {
        cout<<"Vertex "<<i+1<<"\n head ";
        for (auto x:adj[i])
        {
            cout << "->" << x;
        }
        cout<<endl;
    }
}

int main()
{
    int type,n,edges;
    cout<<"Enter the graph type\n1-Undirected\n2-Directed\nEnter your choice(1/2):";
    cin>>type;
    cout<<"Enter number of vertices in graph:";
    cin>>n;
    cout<<"Enter number of edges:";
    cin>>edges;
    int edge[edges][2];
    cout<<"Enter edges("<<edges<<" lines, 2 space separated integers on each line):\nNOTE: enter edges assuming 1-based vertices\n";
    for(int i=0; i<edges;i++)
    {
        cin>>edge[i][0]>>edge[i][1];
    }
    adjacency_matrix(n,edges,edge,type);
    adjacency_list(n,edges,edge,type);
}
