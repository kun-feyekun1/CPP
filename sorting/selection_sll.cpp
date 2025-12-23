#include <iostream>
using namespace std;

struct SNode { int data; SNode* next; };

SNode* insertEnd(SNode* head, int val) {
    SNode* n = new SNode{val,nullptr};
    if(!head) return n;
    SNode* t=head; while(t->next) t=t->next;
    t->next=n; return head;
}

void selectionSortSLL(SNode* head){
    for(SNode* i=head;i;i=i->next){
        SNode* minNode=i;
        for(SNode* j=i->next;j;j=j->next){
            if(j->data<minNode->data) minNode=j;
        }
        swap(i->data,minNode->data);
    }
}

void displaySLL(SNode* head){
    while(head){ cout<<head->data<<" "; head=head->next; }
    cout<<"\n";
}

int main() {
    int n,val; cout << "Number of nodes: "; cin >> n;
    SNode* head=nullptr;
    cout<<"Enter node values: ";
    for(int i=0;i<n;i++){ cin>>val; head=insertEnd(head,val); }

    selectionSortSLL(head);
    cout<<"Sorted list: ";
    displaySLL(head);
}
