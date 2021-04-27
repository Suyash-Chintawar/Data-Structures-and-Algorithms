//Question 1: Imitation of a web browser using doubly list
#include<bits/stdc++.h>
using namespace std;

class node{
public:
    node *prev,*next;
    int page_no;
};

void display(node *head)
{
    node *t=head;
    while(t)
    {
        cout<<t->page_no<<" ";
        t=t->next;
    }
}

node* insert_node(node *curr,node* head)
{
    int page=curr->page_no;
    curr->next=new node();
    curr->next->prev=curr;
    curr=curr->next;
    curr->next=NULL;
    curr->page_no=page+1;
    cout<<"You are now on page no. "<<curr->page_no<<endl;
    cout<<"The browsed web pages are: ";
    display(head);
    cout<<endl;
    return curr;
}

node* previous_of(node* curr,node* head)
{
    if(curr->prev!= NULL)
    {
        curr=curr->prev;
        cout<<"You are now on page no. "<<curr->page_no<<endl;
    }
    else
    {
        cout<<"Previous page does not exist!!\n";
        cout<<"You are now on page no. "<<curr->page_no<<endl;
    }
    cout<<"The browsed web pages are: ";
    display(head);
    cout<<endl;
    return curr;
}

node* next_of(node* curr,node* head)
{
    if(curr->next!= NULL)
    {
        curr=curr->next;
        cout<<"You are now on page no. "<<curr->page_no<<endl;
    }
    else
    {
        cout<<"Next page does not exist!!\n";
        cout<<"You are now on page no. "<<curr->page_no<<endl;
    }
    cout<<"The browsed web pages are: ";
    display(head);
    cout<<endl;
    return curr;
}


int main()
{
    node *curr=NULL,*head;
    int a,c;
    node* first= new node();
    curr=first;
    head=curr;
    cout<<"***Browser is opened***"<<endl;
    curr->page_no=1;
    curr->next=NULL;
    curr->prev=NULL;
    cout<<"You are on page no."<<curr->page_no<<endl;
    again:
    cout<<"   *Menu*\n   1-Go to new page from current\n   2-Fetch previous page\n   3-Fetch next page\n   Enter your choice:";
    cin>>a;
    switch(a)
    {
        case 1:curr=insert_node(curr,head);
            break;
        case 2:curr=previous_of(curr,head);
            break;
        case 3:curr=next_of(curr,head);
            break;

    }
    cout<<"Do you want to continue(1-yes/2-no):";
    cin>>c;
    if(c==1) goto again;
    else{
        cout<<"***Browser has been closed***\n";
    }

}
