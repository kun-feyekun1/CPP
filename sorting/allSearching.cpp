

#include <iostream>
using namespace std;

//ARRAY SEARCHING

int linearSearchArray(int arr[], int n, int key){
    for(int i=0;i<n;i++) if(arr[i]==key) return i; // 0-based index
    return -1;
}

int binarySearchArray(int arr[], int n, int key){
    int l=0, r=n-1;
    while(l<=r){
        int mid = l + (r-l)/2;
        if(arr[mid]==key) return mid;
        else if(arr[mid]<key) l = mid+1;
        else r = mid-1;
    }
    return -1;
}

/* ------------------------
   SINGLY LINKED LIST
   ------------------------ */

struct SNode { int data; SNode* next; };

SNode* insertEndSLL(SNode* head, int val){
    SNode* n = new SNode{val, nullptr};
    if(!head) return n;
    SNode* t=head;
    while(t->next) t=t->next;
    t->next = n;
    return head;
}

int linearSearchSLL(SNode* head, int key){
    int idx = 0;
    while(head){
        if(head->data == key) return idx;
        head = head->next; idx++;
    }
    return -1;
}

// find middle between left (inclusive) and right (exclusive)
SNode* findMiddleSLL(SNode* left, SNode* right){
    if(left==nullptr) return nullptr;
    SNode* slow = left;
    SNode* fast = left;
    while(fast != right && fast->next != right){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

int indexOfNodeSLL(SNode* head, SNode* node){
    int idx = 0;
    while(head){
        if(head == node) return idx;
        head = head->next; idx++;
    }
    return -1;
}

int binarySearchSLL(SNode* head, int key){
    SNode* left = head;
    SNode* right = nullptr; // exclusive
    while(left != right){
        SNode* mid = findMiddleSLL(left, right);
        if(!mid) break;
        if(mid->data == key){
            return indexOfNodeSLL(head, mid);
        } else if(mid->data < key){
            left = mid->next;
        } else {
            right = mid;
        }
    }
    return -1;
}

   //DOUBLY LINKED LIST

struct DNode { 
    int data; 
    DNode* next; 
    DNode* prev; 
};

DNode* insertEndDLL(DNode* head, int val){
    DNode* n = new DNode{val,nullptr,nullptr};
    if(!head) return n;
    DNode* t=head;
    while(t->next) t=t->next;
    t->next = n; n->prev = t;
    return head;
}

int linearSearchDLL(DNode* head, int key){
    int idx=0;
    while(head){
        if(head->data==key) return idx;
        head=head->next; idx++;
    }
    return -1;
}

DNode* findMiddleDLL(DNode* left, DNode* right){
    if(!left) return nullptr;
    DNode* slow = left;
    DNode* fast = left;
    while(fast != right && fast->next != right){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

int indexOfNodeDLL(DNode* head, DNode* node){
    int idx=0;
    while(head){
        if(head==node) return idx;
        head=head->next; idx++;
    }
    return -1;
}

int binarySearchDLL(DNode* head, int key){
    DNode* left = head;
    DNode* right = nullptr;
    while(left != right){
        DNode* mid = findMiddleDLL(left, right);
        if(!mid) break;
        if(mid->data == key) return indexOfNodeDLL(head, mid);
        else if(mid->data < key) left = mid->next;
        else right = mid;
    }
    return -1;
}

/* ------------------------
   CIRCULAR SINGLY LINKED LIST
   (we temporarily break circularity -> linearize)
   ------------------------ */

struct CSNode { int data; CSNode* next; };

CSNode* insertEndCSLL(CSNode* head, int val){
    CSNode* n = new CSNode{val,nullptr};
    if(!head){ n->next = n; return n; }
    CSNode* t=head;
    while(t->next != head) t = t->next;
    t->next = n; n->next = head;
    return head;
}

int linearSearchCSLL(CSNode* head, int key){
    if(!head) return -1;
    int idx=0;
    CSNode* t = head;
    do{
        if(t->data == key) return idx;
        t = t->next; idx++;
    } while(t != head);
    return -1;
}

// helper to break circularity and return tail pointer (so we can restore)
CSNode* breakCircularCSLL(CSNode*& head){
    if(!head) return nullptr;
    CSNode* tail = head;
    while(tail->next != head) tail = tail->next;
    tail->next = nullptr; // break
    return tail;
}

void restoreCircularCSLL(CSNode*& head, CSNode* tail){
    if(!head){
        if(tail) { head = tail; tail->next = head; }
        return;
    }
    if(tail) tail->next = head;
}

// reuse singly linked list functions by casting types carefully
int binarySearchCSLL(CSNode* &head, int key){
    if(!head) return -1;
    // linearize
    CSNode* tail = breakCircularCSLL(head);

    // perform pointer-based binary search treating CSNode* as SNode*
    // convert head type for reuse
    SNode* sHead = reinterpret_cast<SNode*>(head); // same memory layout for first two pointers
    // But we cannot safely reinterpret next pointer arithmetic with different types.
    // Safer: Implement search for CSNode directly using same logic as SLL.

    // direct implementation for CSNode:
    CSNode* left = head;
    CSNode* right = nullptr;
    auto findMid = [](CSNode* left, CSNode* right)->CSNode*{
        if(!left) return nullptr;
        CSNode* slow = left;
        CSNode* fast = left;
        while(fast != right && fast->next != right){
            if(fast->next) fast = fast->next->next; else fast = nullptr;
            slow = slow->next;
        }
        return slow;
    };

    auto indexOf = [&](CSNode* h, CSNode* node)->int{
        int idx=0;
        CSNode* t=h;
        while(t){
            if(t==node) return idx;
            t = t->next; idx++;
        }
        return -1;
    };

    int result = -1;
    while(left != right){
        CSNode* mid = findMid(left, right);
        if(!mid) break;
        if(mid->data == key){
            result = indexOf(head, mid);
            break;
        } else if(mid->data < key){
            left = mid->next;
        } else right = mid;
    }

    // restore circularity
    restoreCircularCSLL(head, tail);
    return result;
}

/* ------------------------
   CIRCULAR DOUBLY LINKED LIST
   (temporarily break circularity)
   ------------------------ */

struct CDNode { 
    int data; 
    CDNode* next; 
    CDNode* prev; 
};

CDNode* insertEndCDLL(CDNode* head, int val){
    CDNode* n = new CDNode{val,nullptr,nullptr};
    if(!head){ n->next = n->prev = n; return n; }
    CDNode* tail = head->prev;
    tail->next = n; n->prev = tail;
    n->next = head; head->prev = n;
    return head;
}

int linearSearchCDLL(CDNode* head, int key){
    if(!head) return -1;
    int idx=0;
    CDNode* t=head;
    do{
        if(t->data==key) return idx;
        t=t->next; idx++;
    } while(t!=head);
    return -1;
}

CDNode* breakCircularCDLL(CDNode*& head){
    if(!head) return nullptr;
    CDNode* tail = head->prev;
    tail->next = nullptr;
    head->prev = nullptr;
    return tail;
}

void restoreCircularCDLL(CDNode*& head, CDNode* tail){
    if(!head && tail){ 
        head = tail; 
        head->next = head; 
        head->prev = head; 
    return; 
   }
    if(head && tail){
        tail->next = head;
        head->prev = tail;
    }
}

CDNode* findMidCDLL(CDNode* left, CDNode* right){
    if(!left) return nullptr;
    CDNode* slow = left;
    CDNode* fast = left;
    while(fast != right && fast->next != right){
        fast = fast->next;
        if(fast) fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

int indexOfNodeCDLL(CDNode* head, CDNode* node){
    int idx=0;
    while(head){
        if(head==node) return idx;
        head=head->next; idx++;
    }
    return -1;
}

int binarySearchCDLL(CDNode*& head, int key){
    if(!head) return -1;
    CDNode* tail = breakCircularCDLL(head);

    CDNode* left = head;
    CDNode* right = nullptr;
    int result = -1;
    while(left != right){
        CDNode* mid = findMidCDLL(left, right);
        if(!mid) break;
        if(mid->data == key){ result = indexOfNodeCDLL(head, mid); break; }
        else if(mid->data < key) left = mid->next;
        else right = mid;
    }

    restoreCircularCDLL(head, tail);
    return result;
}

/* ------------------------
   DEMO MENU & UTILITIES
   ------------------------ */

void pause(){ cout << "Press Enter to continue..."; cin.ignore(); cin.get(); }

int main(){
    cout << "==== allSearching.cpp ====\n";
    cout << "Choose data structure:\n";
    cout << "1. Array\n2. Singly Linked List\n3. Doubly Linked List\n4. Singly Circular Linked List\n5. Doubly Circular Linked List\nChoice: ";
    int ds; if(!(cin>>ds)) return 0;

    if(ds==1){
        cout << "Enter n: "; int n; cin>>n;
        int *arr = new int[n];
        cout << "Enter " << n << " values (sorted for binary search):\n";
        for(int i=0;i<n;i++) cin>>arr[i];
        cout << "1. Linear Search\n2. Binary Search\nChoice: "; int c; cin>>c;
        cout << "Enter key: "; int key; cin>>key;
        if(c==1){
            int idx = linearSearchArray(arr,n,key);
            if(idx>=0) cout<<"Found at index (0-based): "<<idx<<"\n"; else cout<<"Not found\n";
        } else {
            int idx = binarySearchArray(arr,n,key);
            if(idx>=0) cout<<"Found at index (0-based): "<<idx<<"\n"; else cout<<"Not found\n";
        }
        delete[] arr;
    }

    else if(ds==2){
        cout << "Enter n: "; int n; cin>>n;
        SNode* head = nullptr;
        cout << "Enter values (sorted for binary search):\n";
        for(int i=0;i<n;i++){ int v; cin>>v; head = insertEndSLL(head, v); }
        cout << "1. Linear Search\n2. Binary Search\nChoice: "; int c; cin>>c;
        cout << "Enter key: "; int key; cin>>key;
        int idx = (c==1) ? linearSearchSLL(head, key) : binarySearchSLL(head, key);
        if(idx>=0) cout<<"Found at index (0-based): "<<idx<<"\n"; else cout<<"Not found\n";
    }

    else if(ds==3){
        cout << "Enter n: "; int n; cin>>n;
        DNode* head = nullptr;
        cout << "Enter values (sorted for binary search):\n";
        for(int i=0;i<n;i++){ int v; cin>>v; head = insertEndDLL(head, v); }
        cout << "1. Linear Search\n2. Binary Search\nChoice: "; int c; cin>>c;
        cout << "Enter key: "; int key; cin>>key;
        int idx = (c==1) ? linearSearchDLL(head, key) : binarySearchDLL(head, key);
        if(idx>=0) cout<<"Found at index (0-based): "<<idx<<"\n"; else cout<<"Not found\n";
    }

    else if(ds==4){
        cout << "Enter n: "; int n; cin>>n;
        CSNode* head = nullptr;
        cout << "Enter values (sorted for binary search):\n";
        for(int i=0;i<n;i++){ int v; cin>>v; head = insertEndCSLL(head, v); }
        cout << "1. Linear Search\n2. Binary Search\nChoice: "; int c; cin>>c;
        cout << "Enter key: "; int key; cin>>key;
        if(c==1){
            int idx = linearSearchCSLL(head,key);
            if(idx>=0) cout<<"Found at index (0-based): "<<idx<<"\n"; else cout<<"Not found\n";
        } else {
            int idx = binarySearchCSLL(head, key);
            if(idx>=0) cout<<"Found at index (0-based): "<<idx<<"\n"; else cout<<"Not found\n";
        }
    }

    else if(ds==5){
        cout << "Enter n: "; int n; cin>>n;
        CDNode* head = nullptr;
        cout << "Enter values (sorted for binary search):\n";
        for(int i=0;i<n;i++){ int v; cin>>v; head = insertEndCDLL(head, v); }
        cout << "1. Linear Search\n2. Binary Search\nChoice: "; int c; cin>>c;
        cout << "Enter key: "; int key; cin>>key;
        if(c==1){
            int idx = linearSearchCDLL(head,key);
            if(idx>=0) cout<<"Found at index (0-based): "<<idx<<"\n"; else cout<<"Not found\n";
        } else {
            int idx = binarySearchCDLL(head, key);
            if(idx>=0) cout<<"Found at index (0-based): "<<idx<<"\n"; else cout<<"Not found\n";
        }
    }

    else cout<<"Invalid choice\n";

    return 0;
}
