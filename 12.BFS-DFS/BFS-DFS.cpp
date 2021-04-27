/*
This program implements BFS and DFS on any combination of undirected/directed,
simple/multigraphs, by computing the adjacency list by taking all edges as input from the user.
The program also checks for disconnected graphs and outputs the number of components
alongwith its status(whether connected/disconnected).
Time complexity is O(E+V) for both BFS as DFS as adjacency list has been used.
Space complexity is O(V), where V is no. of vertices and E, no.of edges.
NOTE: User MUST input vertices as one-based integers, i.e for eg. for a graph with four vertices,
the vertices will be 1,2,3,4.
In case of directed graphs, number of strongly connected components have been shown
(depending upon the starting vertex)
*/

/*
Variables:
1) n - no. of vertices
2) edges - no. of edges
3) edge[][] - edge set
4) adj_list[] - adjacency list
5) v - starting vertex for BFS/DFS(to be taken by user)
6) visited_bfs - boolean array for BFS
7) visited_dfs - boolean array for DFS
8) n_comp - no.of components
9) type - undirected(1)/directed(2)
10) q - queue for BFS
*/
#include<bits/stdc++.h>
using namespace std;

//Function to compute adjacency list using array of vectors
void adjacency_list(int n,int edges,int edge[][2],int type,vector<int> adj_list[])
{
    for(int i=0;i<edges;i++)
    {
        adj_list[edge[i][0]-1].push_back(edge[i][1]);
        if(type==1)
        {
            adj_list[edge[i][1]-1].push_back(edge[i][0]);
        }
    }
    cout<<"\nAdjacency lists:\n";
    for (int i=0; i<n;i++)
    {
        cout<<"Vertex "<<i+1<<"\n head ";
        for (auto x:adj_list[i])
        {
            cout << "->" << x;
        }
        cout<<endl;
    }
}

//Function to do BFS from a starting vertex (spans one component at one call)
vector<bool> bfs(int v,vector<int> adj_list[],int n,vector<bool> visited_bfs)
{
    int u=v-1;
    list<int> q;//using a queue to keep track of unexplored vertices
    visited_bfs[u]=1;
    cout<<v<<" ";
    while(true)
    {
        for(auto x:adj_list[u])
        {
            if(visited_bfs[x-1]==false)
            {
                q.push_back(x);
                cout<<x<<" ";
                visited_bfs[x-1]=true;
            }
        }
        if(q.empty()==1) return visited_bfs;
        else{
            u=q.front()-1;
            q.pop_front();
        }
    }
}

//Function to perform BFT(Breadth first traversal on the whole graph)
void bft(vector<int> adj_list[],int n,vector<bool> visited_bfs,int type)
{
    cout<<"\n*********BFS ON THE GRAPH*********\n";
    int v,n_comp=1;
    cout<<"Enter starting vertex(integer between 1 and "<<n<<"):";
    cin>>v;
    cout<<"\nOrder in which vertices are visited:\n";
    visited_bfs=bfs(v,adj_list,n,visited_bfs);
    for(int i=0;i<n;i++)//If there are more components
    {
        if(visited_bfs[i]==false)
        {
            n_comp++;
            visited_bfs=bfs(i+1,adj_list,n,visited_bfs);
        }
    }
    if(type==1)
    {
        if(n_comp!=1) cout<<"\nGraph is disconnected!!\nNo. of components:"<<n_comp<<endl;
        else cout<<"\nGraph is connected!!\nNo. of components:"<<n_comp<<endl;
    }
    else{
        cout<<"\n\nNo. of strongly connected components:"<<n_comp<<endl;
    }
}

//Function to do DFS from a starting vertex (spans one component at one call)
vector<bool> dfs(int v,vector<int> adj_list[],int n,vector<bool> visited_dfs)
{
    visited_dfs[v-1]=true;
    cout<<v<<" ";
    for(auto x:adj_list[v-1])
    {
        if(visited_dfs[x-1]==false) visited_dfs=dfs(x,adj_list,n,visited_dfs);
    }
    return visited_dfs;
}

//Function to perform DFT(Depth First Traversal on the whole graph)
void dft(vector<int> adj_list[],int n,vector<bool> visited_dfs,int type)
{
    cout<<"\n*********DFS ON THE GRAPH*********\n";
    int v,n_comp=1;
    cout<<"Enter starting vertex(integer between 1 and "<<n<<"):";
    cin>>v;
    cout<<"\nOrder in which vertices are visited:\n";
    visited_dfs=dfs(v,adj_list,n,visited_dfs);
    for(int i=0;i<n;i++)//If there are more components
    {
        if(visited_dfs[i]==false)
        {
            n_comp++;
            visited_dfs=dfs(i+1,adj_list,n,visited_dfs);
        }
    }
    if(type==1)
    {
        if(n_comp!=1) cout<<"\nGraph is disconnected!!\nNo. of components:"<<n_comp<<endl;
        else cout<<"\nGraph is connected!!\nNo. of components:"<<n_comp<<endl;
    }
    else{
        cout<<"\n\nNo. of strongly connected components:"<<n_comp<<endl;
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

    vector<int> adj_list[n];
    adjacency_list(n,edges,edge,type,adj_list);

    vector<bool> visited(n,false);
    bft(adj_list,n,visited,type);

    vector<bool> visited_dfs(n,false);
    dft(adj_list,n,visited_dfs,type);

    cout<<"\n**See the comments in the source code for detailed explanation regarding the code**\n";
}
