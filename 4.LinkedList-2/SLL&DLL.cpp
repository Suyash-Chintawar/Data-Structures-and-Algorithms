/*This program will delete a student id previous to the given id
 and will implement both singly linked lists as well as
doubly linked list for the same.(Output will be shown for both methods.)*/
#include<bits/stdc++.h>
using namespace std;

class node{
public:
    string name;
    string id;
    node* next;
};

class dllNode{
public:
    string name;
    string id;
    dllNode *prev,*next;
};

int length_ll(node *head)
{
    node *t;
    t=head;
    int l=0;
    while(t!=NULL)
    {
        l++;
        t=t->next;
    }
    return l;
}

int length_dll(dllNode *dhead)
{
    dllNode *t;
    t=dhead;
    int l=0;
    while(t!=NULL)
    {
        l++;
        t=t->next;
    }
    return l;
}

node* create_list(int n,string s[][2])
{
    node *p,*head;
    int i;
    for(i=0;i<n;i++)
    {
        if(i==0)
        {
            head=new node();
            p=head;
            p->id=s[i][1];
            p->name=s[i][0];
        }
        else
        {
            p->next=new node();
            p=p->next;
            p->id=s[i][1];
            p->name=s[i][0];
        }
        //cout<<"Enter data of node "<<i+1<<":";
        //cin>>p->data;
    }
    p->next=NULL;
    return head;
}

void display(node *head)
{
    node *t;
    t=head;
    cout<<"  The singly linked list currently is: ";
    while(t!=NULL)
    {
        cout<<t->name<<" ";
        t=t->next;
    }
    cout<<endl;
}

node* delete_node(node* head,string d_id)
{
    node *t;
    int pos=1,l;
    l=length_ll(head);
    if(l<=1)
    {
        cout<<"  No. of students not sufficient to delete an ID!!"<<endl;
        return head;
    }
    t=head;
    while((t!=NULL)&&(t->id != d_id))
    {
        pos++;
        t=t->next;
    }
    t=head;
    if(pos>l) cout<<"  Student id not present!!"<<endl;
    else if(pos==1)
    {
        cout<<"  Previous node doesn't exist!!"<<endl;
    }
    else if(pos==2)
    {
        head=head->next;
        free(t);
        cout<<"  ***ID deleted!!***"<<endl;
    }
    else
    {
        while(t->next->next->id!=d_id) t=t->next;
        node *t1=t->next;
        t->next=t->next->next;
        free(t1);
        cout<<"  ***ID deleted!!***"<<endl;
    }
    display(head);
    return head;
}

dllNode* create_dll(int n,string s[][2])
{
    dllNode *p,*dhead;
    int i;
    for(i=0;i<n;i++)
    {
        if(i==0)
        {
            dhead=new dllNode();
            dhead->prev=NULL;
            p=dhead;
            p->id=s[i][1];
            p->name=s[i][0];
        }
        else
        {
            dllNode *temp;
            p->next=new dllNode();
            temp=p->next;
            temp->prev=p;
            p=p->next;
            p->id=s[i][1];
            p->name=s[i][0];
        }
    }
    p->next=NULL;
    return dhead;
}

void display_dll(dllNode *dhead)
{
    dllNode *t;
    t=dhead;
    cout<<"  The doubly linked list currently is: ";
    while(t!=NULL)
    {
        cout<<t->name<<" ";
        t=t->next;
    }
    cout<<endl;
}

dllNode* delete_node_dll(dllNode* dhead,string d_id)
{
    dllNode *t;
    int pos=1,l;
    l=length_dll(dhead);
    if(l<=1)
    {
        cout<<"  No. of students not sufficient to delete an ID!!"<<endl;
        return dhead;
    }
    t=dhead;
    while((t!=NULL)&&(t->id != d_id))
    {
        pos++;
        t=t->next;
    }
    t=dhead;
    if(pos>l) cout<<"  Student id not present!!"<<endl;
    else if(pos==1)
    {
        cout<<"  Previous node doesn't exist!!"<<endl;
    }
    else if(pos==2)
    {
        dhead=dhead->next;
        dhead->prev=NULL;
        free(t);
        cout<<"  ***ID deleted!!***"<<endl;
    }
    else
    {
        while(t->next->next->id!=d_id) t=t->next;
        dllNode *t1=t->next;
        t->next=t->next->next;
        t1->next->prev=t1->prev;
        free(t1);
        cout<<"  ***ID deleted!!***"<<endl;
    }
    display_dll(dhead);
    return dhead;
}

int main()
{
    int n;
    node *head;
    dllNode *dhead;
    cout<<"Enter the no. of students:";
    cin>>n;
    string s[n][2],d_id;
    cout<<"Enter "<<n<<" student names and their respective unique IDs:\n";
    for(int i=0;i<n;i++)
    {
        cin>>s[i][0]>>s[i][1];
    }
    cout<<"Enter student ID whose previous has to be deleted:";
    cin>>d_id;
    cout<<"Singly Linked List Implementation"<<endl;
    head=create_list(n,s);
    display(head);
    delete_node(head,d_id);
    cout<<"Doubly Linked List Implementation"<<endl;
    dhead=create_dll(n,s);
    display_dll(dhead);
    delete_node_dll(dhead,d_id);
}

