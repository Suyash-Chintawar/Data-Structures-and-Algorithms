/*This program will create a BST(twice) of first 10000 natural numbers (randomly inserted),
and search for a set of 1000 keys randomly(twice),
and compute the avg. no. of comparisons required in each of the two cases.*/
#include <bits/stdc++.h>
using namespace std;

int inserts[10000];
int searches[1000];
int comp=0;

class node
{
public:
    int data;
    node *left,*right;
};

node* create_node(int data)
{
    node* t= new node();
    t->data=data;
    t->left=NULL;
    t->right=NULL;
    return t;
}

node *insert_key(node *curr, int k)
{
    if(curr==NULL) return create_node(k);
    if(k<curr->data)
    {
        curr->left=insert_key(curr->left,k);
    }
    else if(k>curr->data)
    {
        curr->right=insert_key(curr->right,k);
    }
    return curr;
}

node* search_key(node *root, int k)
{
    comp++;
    if((root==NULL)||(root->data==k)) return root;
    if(k<root->data) return search_key(root->left,k);
    else if(k>root->data) return search_key(root->right,k);
}

void del_tree(node *root)
{
    if(root==NULL) return;
    del_tree(root->left);
    del_tree(root->right);
    free(root);
}

void initialize_arr()
{
    int i;
    for(i=0;i<10000;i++) inserts[i]=(i+1);
    for(i=0;i<1000;i++) searches[i]=rand()%10000;
}

float compute_avg()
{
    int i;
    float avg;
    unsigned seed = 0;
    shuffle(inserts,inserts+10000,default_random_engine(seed));
    shuffle(searches,searches+1000,default_random_engine(seed));
    node *root=NULL;
    root=insert_key(root,inserts[0]);
    cout<<"- Creating BST...\n";
    for(i=1;i<10000;i++)
    {
        insert_key(root,inserts[i]);
    }
    cout<<"- Tree constructed!!\n- Searching for 1000 random keys\n";
    comp=0;
    for(i=0; i<1000; i++)
    {
        search_key(root,searches[i]);
    }
    avg = (float)(comp)/1000;
    cout<<"- Search process finished!!\nTotal comparisons: "<<comp<<endl;//cout<<"Average value of comparisons(total/1000): "<<avg<<endl;
    del_tree(root);
    return avg;
}

int main()
{
    float avg1,avg2;
    srand(time(0));
    initialize_arr();
    cout<<"**Computing average first time**\n";
    avg1 = compute_avg();
    cout<<"Average value of comparisons(total/1000): "<<avg1<<endl;
    cout<<endl;
    cout<<"**Computing average second time**\n";
    avg2 = compute_avg();
    cout<<"Average value of comparisons(total/1000): "<<avg2<<endl;
    cout<<"\nHence, we can see that the performance depends upon the order of insertion,\nThe more the random insertion the faster is searching...\n";
    cout<<"If we insert the elements in increasing order the time complexity will be O(n) whereas if it is random insertion\nthe search complexity goes upto O(logn)!!\n";
}
