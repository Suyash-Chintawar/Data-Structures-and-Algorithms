/*This program will build a BST with correctly given
order and preorder traversals and give the output as the postorder for
the resulting tree.It does not check for wrong input traversals.*/
#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    char data;
    node *left,*right;
};

int search_node(char a[], int s, int e, char c)
{
    int i;
    for(i=s;i<=e;i++)
    {
        if(a[i]==c)
        {
            break;
        }
    }
    return i;
}

node* build_tree(char in[], char pre[], int s, int e)
{
    node* t;
    static int p=0;
    int index;
    if(s>e) return NULL;
    t=new node();
    t->data=pre[p];
    p++;
    t->left=NULL;
    t->right=NULL;
    if(s==e) return t;
    index=search_node(in,s,e,t->data);
    t->left=build_tree(in,pre,s,index-1);
    t->right=build_tree(in,pre,index+1,e);
    return t;
}

void print_preorder(node* t)
{
    if (t!=NULL)
    {
        cout<<t->data<<" ";
        print_preorder(t->left);
        print_preorder(t->right);
    }
}

void print_inorder(node* t)
{
    if (t!=NULL)
    {
        print_inorder(t->left);
        cout<<t->data<<" ";
        print_inorder(t->right);
    }
}

void print_postorder(node* t)
{
    if (t!=NULL)
    {
        print_postorder(t->left);
        print_postorder(t->right);
        cout<<t->data<<" ";
    }
}

int main()
{
    int n,i;
    cout<<"Enter no. of nodes in the tree: ";
    cin>>n;
    char in[n],pre[n];
    cout<<"Enter a valid inorder traversal(space seperated "<<n<<" uppercase letters): ";
    for(i=0;i<n;i++)
    {
        cin>>in[i];
    }
    cout<<"Enter its corresponding valid preorder traversal(space seperated "<<n<<" uppercase letters): ";
    for(i=0;i<n;i++)
    {
        cin>>pre[i];
    }
    cout<<"Tree build in process...\n";
    node* root=build_tree(in,pre,0,n-1);
    cout<<"Tree build finished!!\n";
    cout<<"Inorder traversal of the tree formed is: ";
    print_inorder(root);
    cout<<"\nPreorder traversal of the tree formed is: ";
    print_preorder(root);
    cout<<"\nPostorder traversal of the tree formed is: ";
    print_postorder(root);
    cout<<endl;
}
