#include <iostream>
using namespace std;

struct Node {
    string song;
    Node* next;
    Node* prev;
};

Node* front = nullptr;

bool isEmpty() { return front == nullptr; }

void addSong(string s) { // insert at rear
    Node* n = new Node{s, nullptr, nullptr};
    if (isEmpty()) {
        n->next = n->prev = n;
        front = n;
        return;
    }
    Node* rear = front->prev;
    n->next = front;
    n->prev = rear;
    rear->next = n;
    front->prev = n;
}

void playNext() { // remove from front
    if (isEmpty()) { cout << "Playlist empty\n"; return; }
    cout << "Playing: " << front->song << endl;
    if (front->next == front) { delete front; front = nullptr; return; }
    Node* rear = front->prev;
    Node* temp = front;
    front = front->next;
    rear->next = front;
    front->prev = rear;
    delete temp;
}

void display() {
    if (isEmpty()) { cout << "Playlist empty\n"; return; }
    Node* temp = front;
    cout << "Playlist: ";
    do {
        cout << temp->song << " ";
        temp = temp->next;
    } while (temp != front);
    cout << endl;
}

int main() {
    addSong("Song1");
    addSong("Song2");
    addSong("Song3");
    display();

    playNext();
    display();
}
