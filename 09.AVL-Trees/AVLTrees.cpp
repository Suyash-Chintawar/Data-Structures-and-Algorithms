//This program will input a BST, convert it to AVL,
//and then prompt to insert one new element to the AVL generated

#include <bits/stdc++.h>
using namespace std;

//Defining node structure
struct node{
    int data;//Key
    struct node *left;
    struct node *right;
    int bf;//Balance factor
    int h;//Height
};

//Printing preorder of the tree
void print_preorder(node* t)
{
    if (t!=NULL)
    {
        cout<<t->data<<" ";
        print_preorder(t->left);
        print_preorder(t->right);
    }
}

//Printing inorder of the tree
void print_inorder(node* t)
{
    if (t!=NULL)
    {
        print_inorder(t->left);
        cout<<t->data<<" ";
        print_inorder(t->right);
    }
}

//Printing postorder of the tree
void print_postorder(node* t)
{
    if (t!=NULL)
    {
        print_postorder(t->left);
        print_postorder(t->right);
        cout<<t->data<<" ";
    }
}

//Creating a new node and initializing
node* create_node(int data)
{
    node *t=(node *)malloc(sizeof(node));
    t->data=data;
    t->left=NULL;
    t->right=NULL;
    t->h=1;
    return t;
}

//Global variable for preorder[] array traversing for recursion
int index=0;

//Constructing BST from the given preorder taken as input
node* constructBST(int preorder[], int* index, int s,int e, int n)
{
    if (*index>=n || s>e) return NULL;

    node* root = create_node(preorder[*index]);
    *(index)=*index+1;

    if (s == e) return root;

    int i;
    for (i=s;i<=e;i++) if (preorder[i]>root->data) break;

    root->left = constructBST(preorder, index, *index, i-1, n);
    root->right= constructBST(preorder, index, i, e, n);

    return root;
}

//Calculating height of a node
int height(node* t)
{
    if (t == NULL)
        return 0;
    else
    {
        //Calculating heights of left and right sub-trees
        int hleft = height(t->left);
        int hright = height(t->right);

        //Returning the larger one
        if (hleft > hright) return(hleft + 1);
        else return(hright + 1);
    }
}

//Calculating balance factors of all nodes
void calculate_balance_factors(node* t)
{
    int hl,hr;
    if (t!=NULL)
    {
        hl=height(t->left);
        hr=height(t->right);
        t->bf=hl-hr;
        calculate_balance_factors(t->left);
        calculate_balance_factors(t->right);
    }
}

//Printing balance factors of all nodes
void print_balance_factors(node* t)
{
    if (t!=NULL)
    {
        print_balance_factors(t->left);
        if((t->left!=NULL)||(t->right!=NULL))
        {
            cout<<"=>Balance factor of "<<t->data<<" is: "<<t->bf;
            if((t->bf>=-1)&&(t->bf<=1)) cout<<"(balanced)\n";
            else cout<<"(unbalanced)\n";
        }
        else{
            cout<<"=>"<<t->data<<" is a leaf node\n";
        }
        print_balance_factors(t->right);
    }
}

//Converting BST to AVL using the inorder of BST(equivalent to sorted elements of preorder)
node* BSTtoAVL(int a[],int s,int e)
{
    if (s>e) return NULL;

    int mid = (s + e)/2;
    node *root = create_node(a[mid]);
    root->left = BSTtoAVL(a, s,mid - 1);
    root->right = BSTtoAVL(a, mid + 1, e);
    return root;
}

//Computing heights of the nodes in AVL tree
void calculate_avl_heights(node* t)
{
    if (t!=NULL)
    {
        t->h=height(t);
        calculate_avl_heights(t->left);
        calculate_avl_heights(t->right);
    }
}

//Printing the heights calculated from above(Optional, not used in this program)
void print_avl_heights(node* t)
{
    if (t!=NULL)
    {
        print_avl_heights(t->left);
        if((t->left!=NULL)||(t->right!=NULL))
        {
            cout<<"=>Height of "<<t->data<<" is:"<<t->h<<endl;
        }
        else{
            cout<<"=>Height of "<<t->data<<" is:"<<t->h<<"(leaf node)\n";
        }
        print_avl_heights(t->right);
    }
}

int height1(node *N)
{
    if (N == NULL)
        return 0;
    return N->h;
}

//Calculating maximum between two numbers
int max(int a, int b)
{
    return (a > b)? a : b;
}

//Performing right rotation
node* right_rotate(node *t)
{
    cout<<"Right rotation\n";
    node *x = t->left;
    node *t2 = x->right;

    // Perform rotation
    x->right = t;
    t->left = t2;

    // Update heights
    t->h = max(height1(t->left),height1(t->right)) + 1;
    x->h = max(height1(x->left),height1(x->right)) + 1;


    return x;
}

//Performing left rotation
node* left_rotate(node *x)
{
    cout<<"Left rotation\n";
    node *t = x->right;
    node *t2 = t->left;

    // Perform rotation
    t->left = x;
    x->right = t2;

    // Update heights
    x->h = max(height1(x->left),height1(x->right)) + 1;
    t->h = max(height1(t->left),height1(t->right)) + 1;

    return t;
}

//Finding balance factor of the node
int get_balance(node *t)
{
    if (t == NULL)
        return 0;
    return (height1(t->left) - height1(t->right));
    //return (t->left->h)-(t->right->h);
}

//Inserting a new node in the AVL tree
node* insert(node* root, int key)
{
    if (root == NULL)
        return(create_node(key));

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    else return root;


    root->h = max(height1(root->left),height1(root->right))+1;


    int balance = get_balance(root);
    //int balance =root->bf;

    // Left Left Case
    if (balance > 1 && key < root->left->data)
        return right_rotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->data)
        return left_rotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->data)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->data)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

//Main function can be better analyzed by running the code(All necessary comments printed onto console)
int main()
{
    node *root,*avl_root;
    int n,i;

    cout<<"*****QUESTION 1*****\n\nNOTE:This program does'nt check for invalid traversals,\n     so please refrain from putting invalid BST preorders.\n";
    cout<<"     Only input the valid preorder traversal of a valid BST.\n\n";
    cout<<"Enter the number of nodes in the BST: ";
    cin>>n;
    int preorder[n];
    cout<<"Enter preorder traversal of the BST("<<n<<" space separated unique natural numbers): ";
    for(i=0;i<n;i++) cin>>preorder[i];

    root= constructBST(preorder,&index,0,n-1,n);
    cout<<"\nBST created successfully!!";
    cout<<"\nPreorder of BST constructed: ";
    print_preorder(root);
    cout<<"\nInorder of BST constructed: ";
    print_inorder(root);
    cout<<"\nPostorder of BST constructed: ";
    print_postorder(root);
    cout<<"\n\nCalculating balance factors for all nodes...";
    calculate_balance_factors(root);
    cout<<"\nBalance factors calculated successfully!!\n";
    cout<<"\nBalance factors of all \"INTERNAL\" nodes: \n";
    print_balance_factors(root);

    cout<<"\n*****QUESTION 2*****\n";
    cout<<"\nConverting above BST to AVL tree...\n";

    sort(preorder,preorder+n);

    avl_root=BSTtoAVL(preorder,0,n-1);
    cout<<"\nPreorder of AVL constructed: ";
    print_preorder(avl_root);
    cout<<"\nInorder of AVL constructed: ";
    print_inorder(avl_root);
    cout<<"\nPostorder of AVL constructed: ";
    print_postorder(avl_root);
    cout<<"\n\nCalculating balance factors for all nodes...";
    calculate_balance_factors(avl_root);
    cout<<"\nBalance factors calculated successfully!!\n";
    cout<<"\nBalance factors of all \"INTERNAL\" nodes: \n";
    print_balance_factors(avl_root);
    cout<<"\nHence our BST has been converted to AVL tree!!\n";

    calculate_avl_heights(avl_root);

    int avl_insert;
    cout<<"\n****INSERTING ONE ELEMENT IN AVL TREE****\n";
    cout<<"\nEnter unique key for inserting in AVL tree:";
    cin>>avl_insert;
    cout<<"\nRotations:\n";
    avl_root=insert(avl_root,avl_insert);

    cout<<"\nPreorder of AVL tree after insertion: ";
    print_preorder(avl_root);
    cout<<"\nInorder of AVL tree after insertion: ";
    print_inorder(avl_root);
    cout<<"\nPostorder of AVL tree after insertion: ";
    print_postorder(avl_root);
    cout<<"\n\nCalculating balance factors for all nodes...";
    calculate_balance_factors(avl_root);
    cout<<"\nBalance factors calculated successfully!!\n";
    cout<<"\nBalance factors of all \"INTERNAL\" nodes: \n";
    print_balance_factors(avl_root);
}

