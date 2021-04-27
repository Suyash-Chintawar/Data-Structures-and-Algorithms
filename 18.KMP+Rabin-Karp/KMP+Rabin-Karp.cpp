#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#define ALPHABET_SIZE 4 //{A,C,G,T}
#define mod 1000000007  //For computing hash values

//KMP Algorithm
void kmp_algo(string pattern,int num_texts,vector<string> texts)
{
	int m = pattern.length();//pattern length
	vector<int> pi(m,0);//prefix array pi

	pi[0]=0;//base case
	int i,j;

	//compute array pi
	i=1;
	j=0;//j is also alternatively length of longest prefix of pattern[0...i-1]
	while(i<m)
	{
		if(pattern[i]==pattern[j])//if same char are found increment both i and j
		{
			//assign value of pi[i]=j+1 as longest prefix(also suffix of pattern[0..i]) will have length j+1
			pi[i]=j+1;
			i++;
			j++;
		}
		else
		{
			if(j==0)//if we reach start of pattern
			{
				pi[i]=0;
				i++;
			}
			else j=pi[j-1];
		}
	}

	//iterate through every text
	for(int k=0;k<num_texts;k++)
	{
		string text=texts[k];
		int num_occurences=0;//number of times pattern occurs in each text
		i=0;
		j=0;
		while(j<text.length())
		{
			if(pattern[i]==text[j])
			{
				i++;
				j++;
				if(i==m)//pattern fully matched
				{
					cout<<j-m<<" ";//as j will be already incremented so j-m will be index at which pattern found
					num_occurences++;
					i=pi[i-1];
				}
			}
			else
			{
				if(i==0)//mismatch at first char of pattern
				{
					j++;//increment iterator in text
				}
				else i=pi[i-1];//mismatch at ith char, move back to the longest prefix which matches with text substring
			}
		}
		if(num_occurences==0) cout<<"Pattern not found";
		cout<<endl;
	}

}

//calculate hash value of substring of a text
//for a substring s[0..m-1] -> hash(s), when s[m] is added
//hash(s')=((hash(s)-s[0]*a^(m-1))*a + s[m]) % mod
int compute_hash(int hasht,string text,int j,int m,int a)
{
	int temp=pow(a,m-1);
	return ((hasht-(text[j-m]*temp))*a+text[j])%mod;
}

//Rabin Karp Algorithm
void rabin_karp(string pattern,int num_texts,vector<string> texts)
{
	int a=ALPHABET_SIZE;//a=4
	int hashp=0;//hash value of pattern
	int m=pattern.length();
	
	//calculate hash valur of pattern
	hashp=pattern[0];
	for(int i=1;i<m;i++)
	{
		hashp=((hashp*a)+(pattern[i]))%mod;
	}

	//iterate through all texts
	for(int k=0;k<num_texts;k++)
	{

		int num_occurences=0;
		int hasht=0;//hash value of current substring of a text
		string text=texts[k];

		if(text.length()<m)//if text is smaller than pattern..obviously there wont be a match
		{
			cout<<"Pattern not found\n";
			continue;
		}

		//calculate initial value of hasht
		hasht=text[0];
		for(int i=1;i<m;i++)
		{
			hasht=((hasht*a)+(text[i]))%mod;
		}
		
		int j=m-1;//initializing j to last index of current substring which is focused on
		while(j<text.length())
		{
			if(hasht!=hashp)//if hash values of pattern and substring of text are not equal
			{
				if(j==text.length()-1)
					break;
				j++;//then increment j and find new hash value of new substring of length m
				hasht=compute_hash(hasht,text,j,m,a);
			}
			else//if hash values are same, pattern may or may not match completely
			{
				int flag=0,x=0;
				for(int i=j-m+1;i<=j;i++)//check whole substring with pattern char by char
				{
					if(text[i]!=pattern[x++])//mismatch found
					{
						flag=1;
						break;
					}
				}
				if(flag==0)//no mismatch throughout substring,i.e. pattern found
				{
					num_occurences++;
					cout<<j-m+1<<" ";
				}

				if(j==text.length()-1) 
					break;
				j++;
				hasht=compute_hash(hasht,text,j,m,a);
			}
		}

		if(num_occurences==0)//no occurence of pattern in the text
		{
			cout<<"Pattern not found";
		}
		cout<<endl;
	}


}

int main(int argc,char* argv[])
{
	int prob_no=atoi(argv[1]);//second arguement is problem number (1/2 only)
	string filename=argv[2];//third arguement is input filename

	ifstream file;//use ifstream to extract contents of file
	file.open(filename);//open the file

	int num_texts;
	string pattern;
	vector<string> texts;

	file>>pattern;//read pattern
	file>>num_texts;//number of target texts

	for(int i=0;i<num_texts;i++)
	{
		string texti;
		file>>texti;
		texts.push_back(texti);
	}

	if(prob_no==1)
	{
		kmp_algo(pattern,num_texts,texts);
	}
	else if(prob_no==2)
	{
		rabin_karp(pattern,num_texts,texts);
	}
	else//prob_no is invalid..i.e not 1/2
	{
		cout<<"Fault in arguments! Force stopped\n";
	}
}
