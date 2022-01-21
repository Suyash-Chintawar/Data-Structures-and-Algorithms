/*
This program implements currency conversion problem using Bellman Ford Algorithm.
The exchange rates have been fixed in the main program.
The user will ask for required currency. (3 capital-letter word)
*/
#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second
typedef vector<double> vd;
typedef pair<int,int> pii;

vd distances(11,INT_MAX); // stores the final distances or costs in this case

void bellman_ford(int n, vector<pair<pii,double>> edges,int src)
{
	distances[src]=0; // distance of source is zero frm itself
	int num_edges = edges.size();
	for(int i=0;i<n-1;i++) //run |v|-1 times
	{
		for(int j=0;j<num_edges;j++) // check for updates in each edge
		{
			int s,e;
			double cost;
			s=edges[j].f.f; //starting of edge
			e=edges[j].f.s; // end of edge
			cost=edges[j].s;
			if(distances[s]<INT_MAX) //update min cost distance found
			{
				distances[e] = min(distances[e],distances[s]+cost);
			}
		}
	}
}

int main()
{
	vector<vd> exchange_rates(11,vd(11,0.0)); // 10 currencies and one for gold

	//INR
	exchange_rates[0] = {1.000000, 17.724539, 9.530317, 86.139734, 99.777132, 53.513617, 13.703974, 54.523953, 0.663123, 74.222804, 128459.86};
	//MYR
	exchange_rates[1] = {0.056414, 1.000000, 0.537729, 4.860339, 5.628941, 3.019212, 0.773179, 3.076402, 0.037416, 4.187656, 7247.64};
	//HKD
	exchange_rates[2] = {0.104903, 1.859603, 1.000000, 9.038162, 10.466745, 5.614247, 1.437896, 5.721106, 0.069576, 7.787864, 13478.81};
	//EUR
	exchange_rates[3] = {0.011608, 0.205774, 0.110638, 1.000000, 1.158182, 0.621268, 0.159103, 0.632969, 0.007698, 0.861727, 1491.30};
	//GBP
	exchange_rates[4] = {0.010022, 0.177707, 0.095533, 0.863531, 1.000000, 0.536466, 0.137388, 0.546556, 0.006648, 0.744113, 1288.22};
	//AUD
	exchange_rates[5] = {0.018682, 0.331209, 0.178073, 1.609861, 1.864179, 1.000000, 0.256061, 1.018777, 0.012391, 1.386866, 2401.03};
	//BRL
	exchange_rates[6] = {0.072960, 1.293367, 0.695444, 6.285954, 7.279477, 3.904688, 1.000000, 3.978708, 0.048390, 5.416152, 9375.98};
	//SGD
	exchange_rates[7] = {0.018337, 0.325103, 0.174791, 1.579799, 1.829643, 0.981478, 0.251352, 1.000000, 0.012162, 1.361363, 2355.88};
	//JPY
	exchange_rates[8] = {1.507872, 26.731656, 14.371931, 129.908580, 150.454451, 80.711814, 20.665924, 82.223337, 1.000000, 111.929783, 193733.04};
	//USD
	exchange_rates[9] = {0.013470, 0.238783, 0.128405, 1.160558, 1.344010, 0.720917, 0.184633, 0.734616, 0.008934, 1.000000, 1730.97};
	//GOLD
	exchange_rates[10] = {0.000007, 0.000138, 0.000074, 0.000671, 0.000777, 0.000417, 0.000106, 0.000424, 0.000005, 0.000577, 1.00000};

	int n=11; //num_vertices
	string target; 
	cout<<"Enter the currency code (3 letter word. All caps): ";
	cin>>target;

	vector<pair<pii,double>> edges(n*n); //stores our graph
	unordered_map<string,int> s_id; //map from string to id
	unordered_map<int,string> id_s; // map from id to string
	vector<string> currencies = {"INR","MYR","HKD","EUR","GBP","AUD","BRL","SGD","JPY","USD","GOLD"};

	for(int i=0;i<currencies.size();i++) s_id[currencies[i]]=i;
	for(int i=0;i<currencies.size();i++) id_s[i]=currencies[i];

	//generate graph edges
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			edges.push_back({{j,i},-1*log10(exchange_rates[i][j])});
			edges.push_back({{i,j},-1*log10(double(1)/exchange_rates[i][j])});
		}
	}

	//call bellman ford function with gold as source
	bellman_ford(n,edges,s_id["GOLD"]);

	//print all values
	for(int i=0;i<n;i++) 
	{
		cout<<id_s[i]<<": "<<pow(10,-1*distances[i]);
		if(i==s_id[target]) cout<<" (Final Answer)";
		cout<<endl;
	}

}