
#include <iostream>
using namespace std;

void bubbleSortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {

                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void insertionSortArray(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}


void displayArray(int arr[], int n){
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

    //SINGLY LINKED LIST

struct SNode {
    int data;
    SNode* next;
};

SNode* insertEndSLL(SNode* head, int val){
    SNode* newNode = new SNode{val, nullptr};
    if(!head) return newNode;

    SNode* temp = head;
    while(temp->next) 
      temp = temp->next;
    temp->next = newNode;
    return head;
}

void bubbleSortSLL(SNode* head){
    if(!head) return;
    bool swapped;
    do{
        swapped = false;
        SNode* temp = head;
        while(temp->next){
            if(temp->data > temp->next->data){
                swap(temp->data, temp->next->data);
                swapped = true;
            }
            temp = temp->next;
        }
    }while(swapped);
}

void selectionSortSLL(SNode* head){
    for(SNode* i = head; i != nullptr; i = i->next){
        SNode* minNode = i;
        for(SNode* j = i->next; j != nullptr; j = j->next){
            if(j->data < minNode->data)
                minNode = j;
        }
        swap(i->data, minNode->data);
    }
}

SNode* insertionSortSLL(SNode* head){
    SNode* sorted = nullptr;

    while(head){
        SNode* cur = head;
        head = head->next;

        if(!sorted || cur->data < sorted->data){
            cur->next = sorted;
            sorted = cur;
        } else {
            SNode* temp = sorted;
            while(temp->next && temp->next->data < cur->data)
                temp = temp->next;

            cur->next = temp->next;
            temp->next = cur;
        }
    }
    return sorted;
}

void displaySLL(SNode* head){
    while(head){
        cout << head->data << " ";
        head = head->next;
    }
    cout << "\n";
}

    //DOUBLY LINKED LIST

struct DNode {
    int data;
    DNode* next;
    DNode* prev;
};

DNode* insertEndDLL(DNode* head, int val){
    DNode* newNode = new DNode{val, nullptr, nullptr};
    if(!head) return newNode;

    DNode* temp = head;
    while(temp->next) temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

void bubbleSortDLL(DNode* head){
    if(!head) return;
    bool swapped;

    do {
        swapped = false;
        DNode* temp = head;
        while(temp->next){
            if(temp->data > temp->next->data){
                swap(temp->data, temp->next->data);
                swapped = true;
            }
            temp = temp->next;
        }
    } while(swapped);
}

void selectionSortDLL(DNode* head){
    for(DNode* i = head; i != nullptr; i = i->next){
        DNode* minNode = i;
        for(DNode* j = i->next; j != nullptr; j = j->next)
            if(j->data < minNode->data)
                minNode = j;

        swap(i->data, minNode->data);
    }
}

DNode* insertionSortDLL(DNode* head){
    if(!head) return nullptr;

    DNode* sorted = nullptr;

    while(head){
        DNode* cur = head;
        head = head->next;
        cur->next = nullptr;
        cur->prev = nullptr;

        if(!sorted || cur->data < sorted->data){
            cur->next = sorted;
            if(sorted) sorted->prev = cur;
            sorted = cur;
        } else {
            DNode* temp = sorted;
            while(temp->next && temp->next->data < cur->data)
                temp = temp->next;

            cur->next = temp->next;
            if(temp->next) temp->next->prev = cur;
            temp->next = cur;
            cur->prev = temp;
        }
    }
    return sorted;
}

void displayDLL(DNode* head){
    while(head){
        cout << head->data << " ";
        head = head->next;
    }
    cout << "\n";
}

/* -------------------------
    CIRCULAR SINGLY LINKED LIST
------------------------- */

struct CSNode {
    int data;
    CSNode* next;
};

CSNode* insertEndCSLL(CSNode* head, int val){
    CSNode* newNode = new CSNode{val, nullptr};
    if(!head){
        newNode->next = newNode;
        return newNode;
    }
    
    CSNode* temp = head;
    while(temp->next != head) temp = temp->next;

    temp->next = newNode;
    newNode->next = head;
    return head;
}

void bubbleSortCSLL(CSNode* head){
    if(!head) return;
    CSNode* end = nullptr;

    while(end != head){
        CSNode* p = head;
        while(p->next != end){
            if(p->data > p->next->data)
                swap(p->data, p->next->data);
            p = p->next;
        }
        end = p;
    }
}

void displayCSLL(CSNode* head){
    if(!head) return;

    CSNode* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    }while(temp != head);

    cout << "\n";
}

/* -------------------------
    CIRCULAR DOUBLY LINKED LIST
------------------------- */

struct CDNode {
    int data;
    CDNode* next;
    CDNode* prev;
};

CDNode* insertEndCDLL(CDNode* head, int val){
    CDNode* n = new CDNode{val, nullptr, nullptr};

    if(!head){
        n->next = n->prev = n;
        return n;
    }

    CDNode* last = head->prev;

    last->next = n;
    n->prev = last;
    n->next = head;
    head->prev = n;

    return head;
}

void bubbleSortCDLL(CDNode* head){
    if(!head) return;

    CDNode* end = head;
    do {
        CDNode* p = head;
        do {
            if(p->data > p->next->data)
                swap(p->data, p->next->data);
            p = p->next;
        } while(p->next != end);
        end = end->prev;
    } while(end != head);
}

void displayCDLL(CDNode* head){
    if(!head) return;
    CDNode* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while(temp != head);
    cout << "\n";
}

/* -------------------------
          MAIN MENU
------------------------- */

int main(){
    int choice;

    cout << "\n========== ALL SORTINGS ==========\n";
    cout << "1. Array Sorting\n";
    cout << "2. Singly Linked List Sorting\n";
    cout << "3. Doubly Linked List Sorting\n";
    cout << "4. Circular Singly List Sorting\n";
    cout << "5. Circular Doubly List Sorting\n";
    cout << "Enter option: ";
    cin >> choice;

    int n, val;

    if(choice == 1){
        cout << "Enter number of elements: ";
        cin >> n;
        int arr[100];

        cout << "Enter values: ";
        for(int i=0; i<n; i++) cin >> arr[i];

        cout << "1. Bubble\n2. Selection\n3. Insertion\nChoose: ";
        int c; cin >> c;

        if(c==1) bubbleSortArray(arr,n);
        else if(c==2) selectionSortArray(arr,n);
        else insertionSortArray(arr,n);

        cout << "Sorted: ";
        displayArray(arr,n);
    }

    else if(choice == 2){
        SNode* head = nullptr;
        cout << "Enter number of nodes: ";
        cin >> n;
        cout << "Enter values: ";
        for(int i=0; i<n; i++){
            cin >> val;
            head = insertEndSLL(head,val);
        }
        cout << "1. Bubble\n2. Selection\n3. Insertion\nChoose: ";
        int c; cin >> c;

        if(c==1) bubbleSortSLL(head);
        else if(c==2) selectionSortSLL(head);
        else head = insertionSortSLL(head);

        displaySLL(head);
    }

    else if(choice == 3){
        DNode* head = nullptr;
        cout << "Enter number of nodes: ";
        cin >> n;
        cout << "Enter values: ";
        for(int i=0; i<n; i++){
            cin >> val;
            head = insertEndDLL(head,val);
        }
        cout << "1. Bubble\n2. Selection\n3. Insertion\nChoose: ";
        int c; cin >> c;

        if(c==1) bubbleSortDLL(head);
        else if(c==2) selectionSortDLL(head);
        else head = insertionSortDLL(head);

        displayDLL(head);
    }

    else if(choice == 4){
        CSNode* head = nullptr;
        cout << "Enter number of nodes: ";
        cin >> n;
        cout << "Enter values: ";
        for(int i=0; i<n; i++){
            cin >> val;
            head = insertEndCSLL(head,val);
        }

        bubbleSortCSLL(head); // Only Bubble implemented here

        displayCSLL(head);
    }

    else if(choice == 5){
        CDNode* head = nullptr;
        cout << "Enter number of nodes: ";
        cin >> n;
        cout << "Enter values: ";
        for(int i=0; i<n; i++){
            cin >> val;
            head = insertEndCDLL(head,val);
        }

        bubbleSortCDLL(head); // Only Bubble implemented here
        
        displayCDLL(head);
    }

    return 0;
}
