//Question 3: Create a music player using circular doubly list
#include <bits/stdc++.h>
using namespace std;

class node{
public:
    node* prev,*next;
    string name;
};

void display(node *head)
{
    node *t=head;
    int flag=0;
    while((t!=head)||(flag!=1))
    {
        flag=1;
        cout<<t->name<<" ";
        t=t->next;
    }
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

node* create_dll(int n)
{
    node *head,*t;
    int i;
    string temp,offset;
    for(i=0;i<n;i++)
    {
        temp="song";
        if(i==0)
        {
            head = new node();
            t=head;
            offset=to_string(i+1);
            temp+=offset;
            t->name=temp;
            t->prev=head;
            t->next=head;
        }
        else
        {
            node* new_node;
            new_node= new node();
            offset=to_string(i+1);
            temp+=offset;
            new_node->name=temp;
            new_node->prev=t;
            new_node->next=head;
            head->prev=new_node;
            t->next=new_node;
            t=t->next;
        }
    }
    cout<<"The playlist is: ";
    display(head);
    cout<<"\nCurrent song is: "<<head->name<<endl;
    return head;
}

void play_all(node *head)
{
    node *t=head;
    int flag=0;
    while((t!=head)||(flag!=1))
    {
        flag=1;
        cout<<"Playing...";
        cout<<t->name<<"...Song finished!"<<endl;
        t=t->next;
    }
}

node* delete_song(node *head,node *curr)
{
    int x,flag=0,l;
    l=length(head);
    node *t=curr;
    if(l==1)
    {
        head=NULL;
        flag=1;
        cout<<"Current song deleted!!\nNo song left in playlist!!\n";
    }
    else
    {
        if(curr==head)
        {
            curr->prev->next=curr->next;
            curr->next->prev=curr->prev;
            head=head->next;
            free(t);
        }
        else
        {
            curr->prev->next=curr->next;
            curr->next->prev=curr->prev;
            free(t);
        }
        cout<<"Current song deleted!!\n";
    }
    if(flag==0)
    {
        cout<<"The playlist is: ";
        display(head);
        cout<<endl;
    }
    return head;
}

int main()
{
    int n,k,c,flag=0;
    node *head,*curr;
    cout<<"Enter the no. of songs in playlist:";
    cin>>n;
    if(n<=0)
    {
        cout<<"This playlist is empty!! No operations can be performed!!\n";
        c==2;
        goto last;
    }
    head=create_dll(n);
    curr=head;
    again:
    cout<<"*Menu*\n   1-Play current song\n   2-Play previous song\n   3-Play next song\n   4-Play entire playlist\n   5-Delete current song\nEnter choice no.: ";
    cin>>k;
    switch(k)
    {
        case 1:cout<<"Playing...";
            cout<<curr->name<<"...Song finished!"<<endl;
            cout<<"Now current song is:"<<curr->name<<endl;
            break;
        case 2:cout<<"Playing...";
            curr=curr->prev;
            cout<<curr->name<<"...Song finished!"<<endl;
            cout<<"Now current song is:"<<curr->name<<endl;
            break;
        case 3:cout<<"Playing...";
            curr=curr->next;
            cout<<curr->name<<"...Song finished!"<<endl;
            cout<<"Now current song is:"<<curr->name<<endl;
            break;
        case 4:play_all(head);
            cout<<"Now current song is:"<<curr->name<<endl;
            break;
        case 5:head=delete_song(head,curr);
            curr=head;
            if(head==NULL)
            {
                cout<<"No operations can be performed further!!(Program will end)\n";
                flag=1;
            }
            else cout<<"Now current song is:"<<curr->name<<endl;
            break;
    }
    if(flag==1)
    {
        c=2;
        goto last;
    }
    cout<<"Do you want to continue(1-yes/2-no):";
    cin>>c;
    last:if(c==1) goto again;

}
