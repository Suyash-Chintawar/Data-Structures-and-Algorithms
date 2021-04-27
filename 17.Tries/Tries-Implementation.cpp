#include<bits/stdc++.h>
#include<fstream>
using namespace std;

map<char,int> m;//map for each char in alphabet to number
map<int,char> minv;// inverse map from number to char in alphabet
int node_id_itr=0;//iterator for assigning node ids

//Trie node structure
struct Node{
	int node_id;
	struct Node *next[4];//4 pointers corresponding to each char in alphabet
	bool endofword;//end of a pattern
	bool isleaf;//node is leaf or not
};

//Function to create and initialize a new node
struct Node* newNode()
{
	Node* node=new Node;
	node->node_id=node_id_itr++;
	node->endofword=false;
	node->isleaf=false;
	for(int i=0;i<4;i++) 
	{
		node->next[i]=NULL;
	}

	return node;
}

//Insert a pattern into trie
void insert(struct Node* root,string pattern)
{
	int flag=0;
	for(int i=0;i<pattern.length();i++)
	{
		if(root->next[m[pattern[i]]]==NULL) root->next[m[pattern[i]]]=newNode();
		root=root->next[m[pattern[i]]];
		if(root->isleaf==true)//if substring is alredy there, we extend this branch
		{
			root->isleaf=false;
			flag=1;
		}
	}
	root->isleaf=true;//last node will be leaf
	root->endofword=true;//pattern will also end
}

//print the trie nodes(as 0->1:A)
void print(struct Node* root)
{
	for(int i=0;i<4;i++)
	{
		if(root->next[i]!=NULL)
		{
			cout<<root->node_id<<"->"<<root->next[i]->node_id<<":"<<minv[i]<<endl;
			print(root->next[i]);
		}
	}
}

//search operation if patterns are not substring of each other
int search_prob2(int start_index,string text,struct Node* root)
{
	int temp=start_index;
	int flag=0;//whether pattern found or not
	while(temp<text.length())
	{
		
		char c=text[temp++];	
		if(root->next[m[c]]!=NULL)
		{
			root=root->next[m[c]];
			if(root->isleaf==true)//pattern found
			{
				flag=1;
				break;
			}
		}
		else//pattern not found
		{	
			flag=0;
			break;
		}
	}
	if(flag==1) return start_index;
	else return -1;
}

//search opeation if patterns are substring of each other
int search_prob3(int start_index,string text,struct Node* root)
{
	int temp=start_index;
	int flag=0;
	while(temp<text.length())
	{
		char c=text[temp++];	
		if(root->next[m[c]]!=NULL)
		{
			root=root->next[m[c]];
			if(root->endofword==true)//pattern found
			{
				flag=1;
				break;
			}
		}
		else//pattern not found
		{	
			flag=0;
			break;
		}
	}
	if(flag==1) return start_index;
	else return -1;
}

//when problem 1 is called
Node* problem1(int num_patterns,vector<string> patterns,int prob_no)
{
	Node *root;
	root=newNode();//create root
	for(int i=0;i<num_patterns;i++)//insert each pattern
	{
		insert(root,patterns[i]);
	}
	if(prob_no==1) print(root);//print trie only for problem 1
	return root;//else return the trie
}

//when problem 2 is called
void problem2(string text,int num_patterns,vector<string> patterns,int prob_no)
{
	Node *root;
	int flag=0;
	root=problem1(num_patterns,patterns,prob_no);//call problem1() to form trie of patterns
	for(int i=0;i<text.length();i++)
	{
		int index=-1;
		index=search_prob2(i,text,root);//search for pattern from every index
		if(index!=-1) //pattern found
		{
			flag=1;
			cout<<index<<" ";
		}
	}
	if(flag==0) cout<<"No matching pattern found!";//if not even single pattern is found throughout the text
	cout<<endl;
}

//when problem 3 is called
void problem3(string text,int num_patterns,vector<string> patterns,int prob_no)
{
	Node *root;
	int flag=0;
	root=problem1(num_patterns,patterns,prob_no);//call problem1() to form trie of patterns
	for(int i=0;i<text.length();i++)
	{
		int index=-1;
		index=search_prob3(i,text,root);
		if(index!=-1) 
		{
			flag=1;
			cout<<index<<" ";
		}
	}
	if(flag==0) cout<<"No matching pattern found!";//if not even single pattern is found throughout the text
	cout<<endl;
}

int main(int argc,char *argv[])//take CLI arguements
{
	int prob_no=atoi(argv[1]);//second arguement is problem number (1/2/3 only)
	string filename=argv[2];//third arguement is input filename

	char alphabet[]={'A','C','G','T'};//alphabet
	for(int i=0;i<4;i++)
	{
		m[alphabet[i]]=i;//compute map
		minv[i]=alphabet[i];//compute inverse map
	}

	if(prob_no==1)
	{
		ifstream file;//use ifstream to extract contents of file
		file.open(filename);
		int num_patterns;//number of patterns
		vector<string> patterns;//input patterns
		file>>num_patterns;
		string s;
		for(int i=0;i<num_patterns;i++)
		{
			file>>s;
			patterns.push_back(s);
		}
		Node *_=problem1(num_patterns,patterns,1);
	}
	else if(prob_no==2)
	{
		ifstream file;
		file.open(filename);
		int num_patterns;
		string text;//input text
		file>>text;
		vector<string> patterns;//input patterns
		file>>num_patterns;
		string s;
		for(int i=0;i<num_patterns;i++)
		{
			file>>s;
			patterns.push_back(s);
		}
		problem2(text,num_patterns,patterns,2);
	}
	else if(prob_no==3)
	{
		ifstream file;
		file.open(filename);
		int num_patterns;//number of patterns
		string text;//input text
		file>>text;
		vector<string> patterns;//input patterns
		file>>num_patterns;
		string s;
		for(int i=0;i<num_patterns;i++)
		{
			file>>s;
			patterns.push_back(s);
		}
		problem3(text,num_patterns,patterns,3);
	}
}