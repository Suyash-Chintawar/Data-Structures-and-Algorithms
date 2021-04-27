//Question 2: Delete all even nodes in circular singly list
#include <bits/stdc++.h>
using namespace std;

class node{
public:
    int data;
    node* next;
};

node* create_list(int n,int a[])
{
    node *p,*head;
    int i;
    for(i=0;i<n;i++)
    {
        if(i==0)
        {
            head=new node();
            p=head;
            p->data=a[i];
        }
        else
        {
            p->next=new node();
            p=p->next;
            p->data=a[i];
        }
    }
    p->next=head;
    return head;
}

void display(node *head)
{
    node *t=head;
    int flag=0;
    if(head!=NULL)
    {
        while((t!=head)||(flag!=1))
        {
            flag=1;
            cout<<t->data<<" ";
            t=t->next;
        }
        cout<<endl;
    }
    else cout<<"List empty!!\n";
}

int length(node *head)
{
    int l=0;
    node *t=head;
    int flag=0;
    while((t!=head)||(flag!=1))
    {
        flag=1;
        l++;
        t=t->next;
    }
    return l;
}

node* delete_even_nodes(node *head)
{
    int flag;
    node *tail,*p=head,*q,*t=head;
    while((t->next)!=head)
    {
        t=t->next;
    }
    tail=t;
    q=t;
    while(p!=q)
    {
        flag=0;
        if((p->data )%2==0)
        {
            if(p==head)
            {
                tail->next=head->next;
                head=head->next;
            }
            else{
                t->next=p->next;
            }
            flag=1;
        }
        p=p->next;
        if(flag==0) t=t->next;
    }

    int l= length(head);
    if((l==1)&&(head->data%2==0))
    {
        head=NULL;
    }
    else if(tail->data % 2==0)
    {
        t=head;
        q=head;
        while(q->next != tail)
        {
            t=t->next;
            q=q->next;
        }
        t=t->next;
        q->next=head;
        tail=q;
        free(t);
    }
    return head;
}

int main()
{
again:
    int n,c;
    node *head;
    cout<<"Enter no. of nodes: ";
    cin>>n;
    int a[n],i;
    cout<<"Enter "<<n<<" int data for each node(space seperated): ";
    for(i=0;i<n;i++) cin>>a[i];
    head=create_list(n,a);
    display(head);
    cout<<"Deleting nodes with even data...\n";
    head=delete_even_nodes(head);
    cout<<"Process Completed!!\n";
    cout<<"List is: ";
    display(head);
    cout<<"Do you want to continue(1-yes/2-no):";
    cin>>c;
    if(c==1) goto again;
}
