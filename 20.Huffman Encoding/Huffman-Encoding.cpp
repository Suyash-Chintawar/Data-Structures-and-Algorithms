#include<bits/stdc++.h>
#include<fstream>
using namespace std;
typedef pair<char,string> pcs;//for ease for declarations

ofstream ofile;//output file stream object

//Node structure for huffman tree
struct Node
{
	int freq;
	char symbol;
	struct Node *left,*right;
};

//Custom Comparator for priority queue by using operator overloading
struct CompareNode
{
	bool operator()(Node* n1,Node* n2)
	{
		if((n1->freq==n2->freq) && (n1->symbol!='\0') && n2->symbol!='\0')//for left to right ascending order of leaf characters
		{
			return n1->symbol < n2->symbol;
		}
		return n1->freq > n2->freq;
	}
};

//fucntion to initialize new node in huffman tree
struct Node* newNode()
{
	Node* node=new Node;
	node->freq=0;
	node->left=NULL;
	node->right=NULL;
	node->symbol='\0';
	return node;
}

//get the codes from the already made huffman tree by traversing it and storing the codes in a priority queue 'result'
void getCodes(Node* root,vector<int> &code,priority_queue<pcs,vector<pcs>,greater<pcs>> &result)
{
	if(root->left!=NULL)//left child present
	{
		code.push_back(0);//push 0
		getCodes(root->left,code,result);//go to left child
		code.pop_back();//pop back from code as going to check right child from parent
	}
	if(root->right!=NULL)//right child present
	{
		code.push_back(1);//push 1
		getCodes(root->right,code,result);//go to right child
		code.pop_back();//pop back from code to return to parent
	}
	if(root->left==NULL && root->right==NULL)//leaf node
	{
		char c;
		string s="";//then symbol is present,so get the code for the symbol
		c=root->symbol;
		for(auto x:code) s+=char(x+'0');
		result.push({c,s});//push for eg {a,00} in priority queue
	}
}

//get the encoded text using the map created for the char and their codes
void encodeText(Node *root,string text, map<char,string> m)
{
	string encodedText="";
	for(int i=0;i<text.length();i++)
	{
		encodedText+=m[text[i]];
	}
	ofile << encodedText;//write the encoded text to the output file
}

//get the first and second sequences as defined in the problem statement
void flattenTree(Node* n,string &first_seq,string &second_seq)
{
	if(n!=NULL)
	{
		//first sequence using pre order traversal
		if(n->left!=NULL or n->right!=NULL)
		{
			first_seq+="1";
		}
		else first_seq+="0";
		flattenTree(n->left,first_seq,second_seq);
		//second sequence using in order traversal of the huffman tree
		if(n->left==NULL and n->right==NULL) second_seq+=n->symbol;
		flattenTree(n->right,first_seq,second_seq);
	}
}

//Huffman encoding driver function
void huffman(string text)
{
	priority_queue<Node*,vector<Node*>,CompareNode> q;//using priority queue as min heap with custom comparator
	vector<int> f(26,0);
	for(int i=0;i<text.length();i++)//get frequencies of all char in text
	{
		f[int(text[i]-'a')]++;
	}
	for(int i=0;i<26;i++)
	{
		if(f[i]>0)//push all symbols in min-heap
		{
			struct Node* node=newNode();
			node->symbol=char(i+'a');
			node->freq=f[i];
			q.push(node);
		}
	}
	int num=q.size();
	for(int i=0;i<num-1;i++)//generate the huffman tree by popping two elements from heap and pushing combined one
	{
		struct Node *n1,*n2;
		n1=q.top();
		q.pop();
		n2=q.top();
		q.pop();
		struct Node* tempnode=newNode();
		tempnode->left=n2;
		tempnode->right=n1;
		tempnode->freq=n1->freq+n2->freq;
		q.push(tempnode);
	}

	Node* n=q.top();//get the root of the huffman tree
	vector<int> code;
	priority_queue<pcs,vector<pcs>,greater<pcs>> result;
	map<char, string> m;
	getCodes(n,code,result);//get the codes in 'result'
	//prepare a map of char and its code
	for(int i=0;i<num;i++)
	{
		pcs item=result.top();
		result.pop();
		//cout<<item.first<<": "<<item.second<<"\n";
		m[item.first]=item.second;
	}
	
	ofile.open("output.txt");//open output file
	string first_seq="",second_seq="";
	flattenTree(n,first_seq,second_seq);
	ofile<<first_seq<<endl<<second_seq<<endl;
	encodeText(n,text,m);
	ofile.close();
}

//driver funtion
int main(int argc,char* argv[])
{
	string filename=argv[1];
	ifstream file;
	file.open(filename);

	string text;
	file>>text;

	huffman(text);
}