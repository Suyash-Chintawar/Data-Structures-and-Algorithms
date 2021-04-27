#include<bits/stdc++.h>
using namespace std;

//Defining a node structure for the BST
struct node
{
    int data;
    struct node *left;
    struct node *right;
};

//These arrays will be the keys which are to be inserted in BST. One is randomly arranged
//and the other is the sorted form of the previous one
int keys[1000];
int sorted_keys[1000];

//This function will generate and fill the above two arrays
void generate_keys()
{
    int i;

    //rand()%10000 will generate a random number below 10000
    for (i=0;i<1000;i++)
    {
        keys[i]=rand()%10000;
        //The same value of keys[i] will be stored in sorted_keys
        sorted_keys[i]=keys[i];
    }
    //Sorting the sorted_keys array which will create a tree similar to liked list
    sort(sorted_keys,sorted_keys+1000);
}

//This function will create and initialize a new node with
//the parameter as its data
node* create_node(int data)
{
    node *t=(node *)malloc(sizeof(node));
    t->data=data;
    t->left=NULL;
    t->right=NULL;
    return t;
}

//Inserting a key into the tree with current node and its data given
node* insert_key(node *curr,int key)
{
    //if node pointer is empty create a new node or a place for insertion if found
    if(curr==NULL)
    {
        return create_node(key);
    }
    //searching for a place recursively to insert the key
    if(key < curr->data )
    {
        curr->left=insert_key(curr->left,key);
    }
    if(key >= curr->data )
    {
        curr->right=insert_key(curr->right,key);
    }
    return curr;
}

//This function will create a BST with the input node as root
void create_BST(node *root,int keys[],int n)
{
    int i;
    //Inserting keys one by one in the order of their presence in the array
    for(i=1;i<n;i++)
    {
        insert_key(root, keys[i]);
    }
}

//This function will print the preorder traversal of the tree
void print_preorder(node* t)
{
    if (t!=NULL)
    {
        cout<<t->data<<" ";
        print_preorder(t->left);
        print_preorder(t->right);
    }
}

//This function will print the inorder traversal of the tree
void print_inorder(node* t)
{
    if (t!=NULL)
    {
        print_inorder(t->left);
        cout<<t->data<<" ";
        print_inorder(t->right);
    }
}

//This function will print the postorder traversal of the tree
void print_postorder(node* t)
{
    if (t!=NULL)
    {
        print_postorder(t->left);
        print_postorder(t->right);
        cout<<t->data<<" ";
    }
}

//Thsi function will copy the contents of the original tree in the copy tree
void copy_bst(node *&rootcopy, node *originalTree)
{
    //If the node is empty the same will be copied
    if(originalTree==NULL) rootcopy=NULL;
    else
    {
        //Else creating a new node and copying the contents and then moving
        //to the left and right sub trees
        rootcopy= (node *)malloc(sizeof(node));
        rootcopy->data=originalTree->data;
        copy_bst(rootcopy->left,originalTree->left);
        copy_bst(rootcopy->right,originalTree->right);
    }
}

//This function will traverse tree in postorder and
//delete and free the space occupied by the BST
void deleteTree(node* t)
{
    if (t == NULL)
    {
        return;
    }
    //Delete the left and right subtree
    deleteTree(t->left);
    deleteTree(t->right);
    //Free up the space
    free(t);
}

//Calculating height of tree
int height(node* t)
{
    if (t == NULL)
        return 0;
    else
    {
        //Compute the height of each subtree
        int hleft = height(t->left);
        int hright = height(t->right);

        //Return the larger one
        if (hleft > hright) return(hleft + 1);
        else return(hright + 1);
    }
}

int main()
{
    //This array a[] will be used to implement sub-question 2 and 3 for better understanding
    int i,a[20];

    cout<<"**Creating two BSTs of 1000 keys by changing the order of insertions**\n";

    //Generating 1000 random keys below 10000(for ease of representation) and storing into keys[] and sorted_keys[] arrays
    generate_keys();

    //'root1' will be the root of the BST formed by keys[] array
    //Creating root node dynamically
    node *root1=(node *)malloc(sizeof(node));

    //Initializing the data of root
    root1->data=keys[0];
    root1->left=NULL;
    root1->right=NULL;

    //Creating BST with root1 as root
    create_BST(root1, keys, 1000);
    cout<<"First BST has been created by random insertion!!\nPreorder traversal of first BST is:\n";

    //Printing preorder traversal of the BST(1000 keys will be printed)
    print_preorder(root1);
    cout<<endl;

    //Creating the BST by using sorted_keys[] array using same process
    node *root2=(node *)malloc(sizeof(node));
    root2->data=sorted_keys[0];
    root2->left=NULL;
    root2->right=NULL;
    create_BST(root2, sorted_keys,1000);
    cout<<"\nSecond BST has been created by insertion in sorted order!!\nPreorder traversal of second BST is:\n";
    print_preorder(root2);
    cout<<endl;

    int h1 = height(root1);
    int h2 = height(root2);

    cout<<"\nHeight of First BST is : "<<h1<<endl;
    cout<<"Height of Second BST is : "<<h2<<endl;
    cout<<"\nFor the ease of understanding, further sub-Questions are implemented using BST of random 20 keys\n";

    //Creating a BST of small size for easier understanding(size=20)
    for(i=0;i<20;i++)
    {
        a[i]=(rand()%10000);
    }
    node *root3=(node *)malloc(sizeof(node));
    root3->data=a[0];
    root3->left=NULL;
    root3->right=NULL;
    create_BST(root3, a ,20);
    cout<<"\nThird BST has been created by random insertion(20 keys)!!\nTraversals are:\n";
    cout<<"1)Preorder Traversal: ";
    print_preorder(root3);
    cout<<"\n2)Inorder Traversal: ";
    print_inorder(root3);
    cout<<"\n3)Postorder Traversal: ";
    print_postorder(root3);
    cout<<endl<<endl;

    //Copying the original tree into a new tree
    node *rootcopy;
    copy_bst(rootcopy,root3);
    cout<<"Copy of third BST id created!!\nTraversals are:\n";
    cout<<"1)Preorder Traversal: ";
    print_preorder(rootcopy);
    cout<<"\n2)Inorder Traversal: ";
    print_inorder(rootcopy);
    cout<<"\n3)Postorder Traversal: ";
    print_postorder(rootcopy);
    cout<<endl<<endl;

    cout<<"Deleting Copy BST...\n";
    deleteTree(rootcopy);
    cout<<"Copy BST has been deleted successfully!!\n";

}
