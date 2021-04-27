#include<bits/stdc++.h>
using namespace std;

class node{
public:
    char data;
    node* next;
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

node* create_list()
{
    node *p,*head;
    int n,i;
    cout<<"No. of nodes: ";
    cin>>n;
    for(i=0;i<n;i++)
    {
        if(i==0)
        {
            head=new node();
            p=head;
        }
        else
        {
            p->next=new node();
            p=p->next;
        }
        cout<<"Enter data of node "<<i+1<<":";
        cin>>p->data;
    }
    p->next=NULL;
    return head;
}

node* insert_node(node *head)
{
    node *new_node,*t;
    new_node= new node();
    int pos,l;
    l=length_ll(head);
    cout<<"Enter data of the new node:";
    cin>>new_node->data;
    cout<<"Enter position to insert:";
    cin>>pos;
    t=head;
    if(pos==1)
    {
        head=new_node;
        head->next=t;
    }
    else if(pos>l)
    {
        while((t->next)!=NULL) t=t->next;
        t->next=new_node;
        new_node->next=NULL;
    }
    else
    {
        for(int temp=1;temp<pos-1;temp++)
        {
            t=t->next;
        }
        new_node->next=t->next;
        t->next=new_node;
    }
    cout<<"***Node inserted!!***"<<endl;
    return head;
}

void display(node *head)
{
    node *t;
    t=head;
    cout<<"The linked list is: ";
    while(t!=NULL)
    {
        cout<<t->data<<" ";
        t=t->next;
    }
    cout<<endl;
}

node* reverse_list(node *head)
{
    node *prev=NULL,*cur=head,*nxt=NULL;
    while(cur!=NULL)
    {
        nxt=cur->next;
        cur->next=prev;
        prev=cur;
        cur=nxt;
    }
    cout<<"***Linked list reversed!!***"<<endl;
    return prev;
}

node* delete_node(node* head)
{
    node *t;
    int pos,l,temp;
    l=length_ll(head);
    t=head;
    cout<<"Enter position no. to delete:";
    cin>>pos;
    if((pos>l)||(l==0))
    {
        cout<<"***Error Occurred!!***"<<endl;
        return head;
    }
    else if(pos==1)
    {
        head=head->next;
        free(t);
    }
    else if(pos==l)
    {
        while((t->next->next)!=NULL) t=t->next;
        free(t->next);
        t->next=NULL;
    }
    else
    {
        for(temp=1;temp<pos-1;temp++)
        {
            t=t->next;
        }
        node *t1=t->next;
        t->next=t->next->next;
        free(t1);
    }
    cout<<"***Node Deleted!!***"<<endl;
    return head;
}

int main()
{
    node *head,*t;
    int k,flag=0;
    head= create_list();
    t=head;
    while(1)
    {
        cout<<"*****Menu*****"<<endl<<"1.Insert"<<endl<<"2.Delete"<<endl<<"3.Reverse"<<endl<<"4.Display"<<endl<<"5.Exit"<<endl;
        cout<<"Enter action no.: ";
        cin>>k;
        switch(k)
        {
            case 1: head=insert_node(head);
                    break;
            case 2: head= delete_node(head);
                    break;
            case 3: head=reverse_list(head);
                    break;
            case 4: display(head);
                    break;
            case 5: flag=1;
                    break;
        }
        if(flag==1) break;
    }
}
