/*
NOTE:
1) This program performs stable matching for marriage proposals
2) Men will propose to women in this program
3) There can be multiple perfect matches, one of them is computed
4) Tshe program doesn't check for incorrect input so please refrain from inserting wrong inputs
*/

#include<bits/stdc++.h>
using namespace std;

//to store ids of men and women for easy computation
unordered_map<string,int> id; 

//Function to perform stable matching
void matching(int n,vector<string> people,vector<vector<int>> preference)
{
	vector<int> partner(n,-1);// stores partner ids of women
	vector<bool> engaged(n,false); // stores whether a man has been engaged or not
	int free=n; //number of free men left
	while(free>0) //until all men have been paired
	{
		int man;//find the man who is not engaged
		for(int i=0;i<n;i++)
		{
			if(!engaged[i])
			{
				man=i;
				break;
			}
		}

		//find suitable match for him
		for(int i=0;i<n;i++)
		{
			if(engaged[man]) break;// if he's already engaged

			//if the woman in his pref list is not engaged
			if(partner[preference[man][i]-n]==-1) 
			{
				//engage both of them
				partner[preference[man][i]-n] = man;
				engaged[man]=true;
				free--;
			}
			else //if she's engaged, see whether our man has higher pref than the man she's already with
			{
				int prev_man = partner[preference[man][i]-n]; //the man shes engaged with
				int temp;
				for(int j=0;j<n;j++)
				{
					if(preference[preference[man][i]][j]==prev_man or preference[preference[man][i]][j]==man)
					{
						temp = preference[preference[man][i]][j];
						break;
					}
				}
				if(temp==man) //if our man has higher preference in her list, break previous engagement
				{
					partner[preference[man][i]-n] = man;
					engaged[prev_man] = false;
					engaged[man] =true;
				}
			}
		}
	}

	//Final answer is stored in our parnter array 
	cout<<"\nFINAL MATCHING IS: (Format: (woman,man)):\n";
	for(int i=0;i<n;i++)
	{
		cout<<"("<<people[i+n]<<","<<people[partner[i]]<<")"<<'\n';
	}
}

int main()
{
	//Take input
	int n;
	cout<<"Number of men/women: ";
	cin>>n;
	vector<string> people(2*n);
	cout<<"Enter names of men ("<<n<<" space seperated strings):\n";
	for(int i=0;i<n;i++) cin>>people[i];
	cout<<"Enter names of women ("<<n<<" space seperated strings):\n";
	for(int i=0;i<n;i++) cin>>people[i+n];
	
	//assign ids to men and women in order
	for(int i=0;i<2*n;i++)
	{
		id[people[i]]=i;
	}

	//Stores preferences of men and women in order
	vector<vector<int>> preference(2*n,vector<int> (n,-1));
	cout<<"\nEnter preference list of MEN.. \nNOTE:("<<n<<" Space seperated strings of women from highest to lowest preference)\n";
	for(int i=0;i<n;i++)
	{
		string sender=people[i];
		cout<<"Preference list of "<<sender<<":\n";
		for(int j=0;j<n;j++)
		{
			string pref;
			cin>>pref;
			preference[id[sender]][j]=id[pref];
		}
	}
	cout<<"\nEnter preference list of WOMEN.. \nNOTE:("<<n<<" Space seperated strings of men from highest to lowest preference)\n";
	for(int i=n;i<2*n;i++)
	{
		string receiver=people[i];
		cout<<"Preference list of "<<receiver<<":\n";
		for(int j=0;j<n;j++)
		{
			string pref;
			cin>>pref;
			preference[id[receiver]][j]=id[pref];
		}
	}

	matching(n,people,preference);
}