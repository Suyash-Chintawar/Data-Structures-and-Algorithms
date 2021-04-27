//Program to check whether an undirected graph is 2-edge connected or not and print out the bridge edges if any
//(README,working,assumptions provided in the attached pdf in folder)
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

//DFS on graph to check whether it is 2-edge connected or not(spans one component at one call)
int two_edge_conn(int v,vector<int> adj_list[],int n,vector<bool> &visited_2ec,vector<int> &arrival,int parent,vector<pair<int,int>> &bridge,int &time,int &flag)
{
    visited_2ec[v-1]=true;
    arrival[v-1]=time++;
    int deepest_be = arrival[v-1];
    for(auto x: adj_list[v-1])
    {
        if(visited_2ec[x-1]==false)
        {
            deepest_be = min(deepest_be,two_edge_conn(x,adj_list,n,visited_2ec,arrival,v,bridge,time,flag));
        }
        else if(x!=parent)
        {
            deepest_be = min(deepest_be,arrival[x-1]);
        }
    }
    if(deepest_be == arrival[v-1] && parent!=-1)//bridge is present between v and parent
    {
        flag=1;
        bridge.push_back(make_pair(parent,v));//store the edge
    }
    return deepest_be;
}

//Function to do DFS from a starting vertex (spans one component at one call)
void dfs(int v,vector<int> adj_list[],int n,vector<bool> &visited_dfs)
{
    visited_dfs[v-1]=true;
    cout<<v<<" ";
    for(auto x:adj_list[v-1])
    {
        if(visited_dfs[x-1]==false)
        {
            dfs(x,adj_list,n,visited_dfs);
        }
    }
}

//Function to perform DFS to check connectedness and 2-edge connectedness of the graph
void dft(vector<int> adj_list[],int n,vector<bool> visited_dfs)
{
    cout<<"\n*********DFS ON THE GRAPH TO CHECK CONNECTEDNESS*********\n";
    int v=1,n_comp=1;
    cout<<"\nOrder in which vertices are visited:\n";
    dfs(v,adj_list,n,visited_dfs);
    for(int i=0;i<n;i++)
    {
        if(visited_dfs[i]==false)
        {
            n_comp++;
            dfs(i+1,adj_list,n,visited_dfs);
        }
    }
    cout<<"\n\n*********DFS ON THE GRAPH TO CHECK 2-EDGE CONNECTEDNESS*********\n";
    vector<bool> visited_2ec(n,false);
    vector<int> arrival(n,-1);
    int time=0,flag=0,comp_no=0;
    vector<pair<int,int>> bridge;
    if(n_comp!=1)
    {
        cout<<"\nGraph is disconnected!!\nNo. of components: "<<n_comp<<"\n";
        for(int j=0;j<n;j++)
        {
            if(visited_2ec[j]==false)
            {
                comp_no++;
                time=0;
                flag=0;
                bridge.clear();
                int _=two_edge_conn(j+1,adj_list,n,visited_2ec,arrival,-1,bridge,time,flag);
                if(flag==1)
                {
                    cout<<"Component "<<comp_no<<" is not 2-edge connected!!\nBridge edges are:\n";
                    for(auto x:bridge)
                    {
                        cout<<x.first<<" "<<x.second<<"\n";
                    }
                }
                else{
                    cout<<"Component "<<comp_no<<" is 2-edge connected!! No bridge edges in this component!!\n";
                }
            }
        }
    }
    else{
        cout<<"\nGraph is connected!!\nNo. of components: "<<n_comp<<"\n";
        int _=two_edge_conn(v,adj_list,n,visited_2ec,arrival,-1,bridge,time,flag);
        if(flag==1)
        {
            cout<<"Graph is not 2-edge connected!!\nBridge edges are:\n";
            for(auto x:bridge)
            {
                cout<<x.first<<" "<<x.second<<"\n";
            }
        }
        else{
            cout<<"Graph is 2-edge connected!!\nNo bridge edges!!\n";
        }
    }
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
    dft(adj_list,n,visited_dfs);
}
