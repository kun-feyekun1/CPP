#include <iostream>
using namespace std;

struct DNode { int data; DNode* next; DNode* prev; };

DNode* insertEnd(DNode* head,int val){
    DNode* n=new DNode{val,nullptr,nullptr};
    if(!head) return n;
    DNode* t=head; while(t->next) t=t->next;
    t->next=n; n->prev=t;
    return head;
}

DNode* insertionSortDLL(DNode* head){
    if(!head) return nullptr;
    DNode* sorted=nullptr;

    while(head){
        DNode* cur=head;
        head=head->next;
        cur->next=nullptr; cur->prev=nullptr;

        if(!sorted || cur->data<sorted->data){
            cur->next=sorted;
            if(sorted) sorted->prev=cur;
            sorted=cur;
        } else {
            DNode* temp=sorted;
            while(temp->next && temp->next->data<cur->data)
                temp=temp->next;
            cur->next=temp->next;
            if(temp->next) temp->next->prev=cur;
            temp->next=cur;
            cur->prev=temp;
        }
    }
    return sorted;
}

void displayDLL(DNode* head){
    while(head){ cout<<head->data<<" "; head=head->next; }
    cout<<"\n";
}

int main(){
    int n,val; cout<<"Number of nodes: "; cin>>n;
    DNode* head=nullptr;
    cout<<"Enter node values: ";
    for(int i=0;i<n;i++){ cin>>val; head=insertEnd(head,val); }

    head=insertionSortDLL(head);
    cout<<"Sorted list: "; displayDLL(head);
}
