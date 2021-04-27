/*
This program implements Kruskal's Algorithm on undirected graphs
by using priority queue to store the graph in sorted order
based on the edge weights
Union-find data structure has been used to find whether
two vertices belong to the same component in the forest
at a time instance
Time complexity is O(ElogV)
User can give input as 0-based or 1-based vertices
*/
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;//for easier declaration of variables

//Make a set(tree) in a forest - Union-find data structure
void make_set(int v,vector<int> &parent,vector<int> &size)
{
    parent[v]=v;
    size[v]=1;
}

//Find representative of a set(in our case it will be root of a tree in the forest)
int find_set(int v,vector<int> &parent)
{
    if(parent[v]==v)
        return v;
    return parent[v]=find_set(parent[v],parent);
}

//Union by size method has been used to improve time complexity of computation
//of union of sets
void union_sets(int a,int b,vector<int> &parent,vector<int> &size)
{
    int repa,repb;//repa = representative of set containing vertex a
    repa=find_set(a,parent);
    repb=find_set(b,parent);
    if(repa!=repb)//If vertices a and b don't belong to same set, then perform union operation
    {
        if(size[repa]<size[repb])
        {
            //swap repa and repb
            int temp;
            temp=repa;
            repa=repb;
            repb=temp;
        }
        parent[repb]=repa;//update representative/root of smaller set/tree as larger set/tree
        size[repa]+=size[repb];//update size of union set
    }
}

//Kruskal's Algorithm
void kruskal(int n,int edges,priority_queue<pair<int,pii>,vector<pair<int,pii>>,greater<pair<int,pii>>> q)
{
    int n_mst=0,flag=0,mst_cost=0;
    vector<pair<int,pii>> mst;
    vector<int> parent(n+1,-1);//keeps track of root of vertex in tree in forest
    vector<int> size(n+1,0);//keep track size of a trees in forest
    for(int i=0;i<=n;i++)
    {
        make_set(i,parent,size);//initialize each vertex as a tree in forest
    }
    for(int i=0;i<edges;i++)
    {
        int w=q.top().first;//smallest edge weight currently on top of queue
        int v1,v2;
        v1=q.top().second.first;//first vertex of edge
        v2=q.top().second.second;//second vertex of edge
        q.pop();
        if(find_set(v1,parent)!=find_set(v2,parent))//if edge doesn't forms cycle
        {
            mst_cost+=w;//update mst cost
            mst.push_back({w,{v1,v2}});
            union_sets(v1,v2,parent,size);//combine two trees into one
            n_mst++;//increment number of edges in mst
            if(n_mst==n-1)//If mst has n-1 required egdes
            {
                flag=1;
                break;
            }
        }
    }
    if(flag==0)//priority queue is empty but mst doesn't have n-1 edges
    {
        cout<<"MST cannot be computed as graph is disconnected!!\n";
    }
    else//Print data to console
    {
        cout<<"\nMST created successfully!!\nCost of MST is: "<<mst_cost<<"\n\n";
        cout<<"Edges in MST are:\n\n";
        cout<<"Vertex1  Vertex2  Weight\n";//Tabular format output
        for(auto x:mst)
        {
            cout<<"   "<<x.second.first<<"\t   "<<x.second.second<<"\t   "<<x.first<<"\n";
        }
    }
}

int main()
{
    int n,edges;//n->no.of vertices, edges->no. of edges
    priority_queue<pair<int,pii>,vector<pair<int,pii>>,greater<pair<int,pii>>> q;//priority queue of form pair(int,pair(int,int))
    cout<<"Enter no. of vertices:";
    cin>>n;
    cout<<"Enter no. of edges:";
    cin>>edges;
    cout<<"Enter edges("<<edges<<" lines, 3 space separated integers on each line,\nformat: vertex1 vertex2 edge_weight):\n";
    int v1,v2,w;
    for(int i=0;i<edges;i++)
    {
        cin>>v1>>v2>>w;
        q.push({w,{v1,v2}});
    }
    kruskal(n,edges,q);
}
