//Program to compute diameter of undirected graph
#include<bits/stdc++.h>
using namespace std;

//Compute Adjacency lists (undirected graph)
void adjacency_list(int n,int edges,int edge[][2],vector<int> adj_list[])
{
    for(int i=0;i<edges;i++)
    {
        adj_list[edge[i][0]-1].push_back(edge[i][1]);
        adj_list[edge[i][1]-1].push_back(edge[i][0]);
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

//Perform BFS from a starting vertex
vector<int> bfs(int v,vector<int> adj_list[],int n,vector<bool> &visited_bfs)
{
    vector<int> level(n,0);//To store level number of each vertex in BFS tree
    int u=v-1,d=0,flag=0;
    list<int> q;//dispenser(queue)
    visited_bfs[u]=true;
    while(true)
    {
        for(auto x:adj_list[u])
        {

            if(visited_bfs[x-1]==false)
            {
                level[x-1]=level[u]+1;//Level of adjacent will be one more than level of parent
                q.push_back(x);
                visited_bfs[x-1]=true;
            }
        }
        if(q.empty()==1) break;
        else{
            u=q.front()-1;
            q.pop_front();
        }
    }
    return level;
}

//Finds diameter for cyclic, connected graphs
void bft_graph(vector<int> adj_list[],int n)
{
    cout<<"\n*********BFS ON THE GRAPH TO FIND DIAMETER(NORMAL)*********\n";
    int v=1,d=-1,curr;
    for(int i=0;i<n;i++)
    {
        vector<int> level;
        vector<bool> visited_bfs(n,false);
        curr=0;//longest distance obtained from current starting vertex
        level=bfs(i+1,adj_list,n,visited_bfs);
        cout<<"\nDistances of all vertices from vertex "<<i+1<<": ";
        for(int j=0;j<n;j++)//find max level
        {
            cout<<level[j]<<" ";
            if(level[j]>curr) curr=level[j];
        }
        cout<<endl;
        cout<<"Longest path from vertex "<<i+1<<": "<<curr<<endl;
        if(curr>d) d=curr;//store longest distance amongst all vertices(diameter)
    }
    cout<<"\n*****FINAL RESULT*****\nDIAMETER OF THE GRAPH: "<<d<<endl;
}

//Finds diameter for acyclic, connected graphs(i.e. trees)..Optimized method
void bft_tree(vector<int> adj_list[],int n)
{
    cout<<"\n*********BFS ON THE GRAPH TO FIND DIAMETER(OPTIMIZED)*********\n";
    int v,d=-1,curr=0;
    vector<int> level,level1;
    vector<bool> visited_bfs(n,false);
    level=bfs(1,adj_list,n,visited_bfs);//BFS from a random vertex
    cout<<"\nDistances of all vertices from vertex "<<1<<": ";
    for(int j=0;j<n;j++)
    {
        cout<<level[j]<<" ";
        if(level[j]>d) d=level[j];
    }
    cout<<"\nLongest path from vertex "<<1<<": "<<d<<endl;
    for(int j=0;j<n;j++)
    {
        if(level[j]==d)
        {
            v=j+1;
            break;
        }
    }
    for(int j=0;j<n;j++) visited_bfs[j]=false;
    level1=bfs(v,adj_list,n,visited_bfs);//BFS on the farthest vertex obtained from previous call
    cout<<"\nDistances of all vertices from vertex "<<v<<": ";
    for(int j=0;j<n;j++)
    {
        cout<<level1[j]<<" ";
        if(level1[j]>curr) curr=level1[j];
    }
    cout<<"\nLongest path from vertex "<<v<<": "<<curr<<endl;
    if(curr>d) d=curr;
    cout<<"\n*****FINAL RESULT*****\nDIAMETER OF THE GRAPH: "<<d<<endl;
}


//Function to do DFS from a starting vertex (spans one component at one call)
bool dfs(int v,vector<int> adj_list[],int n,vector<bool> &visited_dfs,int parent)
{
    bool isCyclic=false;//to check for cycle in graph
    visited_dfs[v-1]=true;
    cout<<v<<" ";
    for(auto x:adj_list[v-1])
    {
        if(visited_dfs[x-1]==false)
        {
            if(dfs(x,adj_list,n,visited_dfs,v))
                isCyclic=true;
        }
        else if(x!=parent) isCyclic=true;//if adjacent already visited and its not the parent ,then cycle exists
    }
    return isCyclic;
}

//Function to perform DFT(Depth First Traversal on the whole graph)
vector<bool> dft(vector<int> adj_list[],int n,vector<bool> visited_dfs)
{
    vector<bool> verdict(2,false);//verdict[0]->connected or not(true if disconnected), verdict[1]->cyclic or not(true if cyclic)
    cout<<"\n*********DFS ON THE GRAPH TO CHECK CYCLIC AND CONNECTEDNESS*********\n";
    int v=1,n_comp=1;
    cout<<"\nOrder in which vertices are visited:\n";
    if(dfs(v,adj_list,n,visited_dfs,-1)) verdict[1]=true;
    for(int i=0;i<n;i++)
    {
        if(visited_dfs[i]==false)
        {
            n_comp++;
            if(dfs(i+1,adj_list,n,visited_dfs,-1))
                verdict[1]=true;
        }
    }
    if(n_comp!=1)
    {
        verdict[0]=true;
    }
    return verdict;
}

int main()
{
    int n,edges;
    cout<<"Enter number of vertices in the undirected graph:";
    cin>>n;
    cout<<"Enter number of edges in the undirected graph:";
    cin>>edges;
    int edge[edges][2];
    cout<<"Enter edges("<<edges<<" lines, 2 space separated integers on each line):\nNOTE: enter edges assuming 1-based vertices\n";
    for(int i=0; i<edges;i++)
    {
        cin>>edge[i][0]>>edge[i][1];
    }

    vector<int> adj_list[n];
    adjacency_list(n,edges,edge,adj_list);

    vector<bool> visited_dfs(n,false);
    vector<bool> verdict(2);//verdict[0]->connected or not(true if disconnected), verdict[1]->cyclic or not(true if cyclic)
    verdict=dft(adj_list,n,visited_dfs);
    if(verdict[0]==true)
    {
        cout<<"\n\nGraph is disconnected!!\n*****FINAL RESULT*****\nDIAMETER OF THE GRAPH: Infinity!\n";
    }
    else if(verdict[1]==true)
    {
        cout<<"\n\nGraph is connected but cyclic!!\n";
        bft_graph(adj_list,n);
    }
    else{
        cout<<"\n\nGraph is connected as well as acyclic!!\nOptimized method will be applied!!\n";
        bft_tree(adj_list,n);
    }
}
