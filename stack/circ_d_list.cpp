#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    Song* next;
    Song* prev;
};

Song* head = NULL;

void addSongEnd(string title) {
    Song* newSong = new Song();
    newSong->title = title;

    if (head == NULL) {
        newSong->next = newSong;
        newSong->prev = newSong;
        head = newSong;
        return;
    }

    Song* last = head->prev;

    newSong->next = head;
    head->prev = newSong;

    newSong->prev = last;
    last->next = newSong;
}

// INSERT AT BEGINNING
void addSongBeginning(string title) {
    addSongEnd(title);
    head = head->prev;
}

// INSERT AT POSITION (1-based index)
void addSongAtPos(string title, int pos) {
    if (pos <= 1 || head == NULL) {
        addSongBeginning(title);
        return;
    }

    Song* temp = head;
    int count = 1;

    while (count < pos - 1 && temp->next != head) {
        temp = temp->next;
        count++;
    }

    // temp = node before insertion point
    Song* newSong = new Song();
    newSong->title = title;

    newSong->next = temp->next;
    newSong->prev = temp;

    temp->next->prev = newSong;
    temp->next = newSong;
}

// DISPLAY FORWARD
void displayForward() {
    if (head == NULL) {
        cout << "Playlist is empty.\n";
        return;
    }

    Song* temp = head;
    cout << "Playlist (Forward): ";

    do {
        cout << temp->title << " -> ";
        temp = temp->next;
    } while (temp != head);

    cout << "(back to start)\n";
}

// DISPLAY BACKWARD
void displayBackward() {
    if (head == NULL) {
        cout << "Playlist is empty.\n";
        return;
    }

    Song* temp = head->prev;
    cout << "Playlist (Backward): ";

    do {
        cout << temp->title << " -> ";
        temp = temp->prev;
    } while (temp != head->prev);

    cout << "(back to end)\n";
}

// SEARCH SONG BY NAME
Song* searchSong(string title) {
    if (head == NULL) return NULL;

    Song* temp = head;
    do {
        if (temp->title == title)
            return temp;
        temp = temp->next;
    } while (temp != head);

    return NULL;
}

// DELETE FROM BEGINNING
void deleteBeginning() {
    if (head == NULL) {
        cout << "Playlist empty.\n";
        return;
    }

    if (head->next == head) {
        delete head;
        head = NULL;
        return;
    }

    Song* last = head->prev;
    Song* newHead = head->next;

    last->next = newHead;
    newHead->prev = last;

    delete head;
    head = newHead;
}

// DELETE FROM END
void deleteEnd() {
    if (head == NULL) {
        cout << "Playlist empty.\n";
        return;
    }

    if (head->next == head) {
        delete head;
        head = NULL;
        return;
    }

    Song* last = head->prev;
    Song* secondLast = last->prev;

    secondLast->next = head;
    head->prev = secondLast;

    delete last;
    last = secondLast;
}

// DELETE SONG BY NAME
void deleteByName(string title) {
    Song* target = searchSong(title);

    if (target == NULL) {
        cout << "Song not found.\n";
        return;
    }

    if (target == head)
        deleteBeginning();
    else if (target == head->prev)
        deleteEnd();
    else {
        Song* prevNode = target->prev;
        Song* nextNode = target->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete target;
    }
    cout << "Deleted: " << title << endl;
}

// DELETE AT POSITION
void deleteAtPos(int pos) {
    if (head == NULL) return;

    if (pos <= 1) {
        deleteBeginning();
        return;
    }

    Song* temp = head;
    int count = 1;

    while (count < pos && temp->next != head) {
        temp = temp->next;
        count++;
    }

    if (count < pos) {
        cout << "Invalid position.\n";
        return;
    }

    if (temp == head)
        deleteBeginning();
    else if (temp == head->prev)
        deleteEnd();
    else {
        Song* prevNode = temp->prev;
        Song* nextNode = temp->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete temp;
    }
}

// PLAY NEXT
void playNext() {
    if (head == NULL) return;

    head = head->next;
    cout << "Now playing: " << head->title << endl;
}

// PLAY PREVIOUS
void playPrev() {
    if (head == NULL) return;

    head = head->prev;
    cout << "Now playing: " << head->title << endl;
}

// MAIN MENU
int main() {
    int choice, pos;
    string title;

    while (true) {
        cout << "\n========== PLAYLIST MENU ==========\n";
        cout << "1. Add Song at Beginning\n";
        cout << "2. Add Song at End\n";
        cout << "3. Add Song at Position\n";
        cout << "4. Delete Beginning\n";
        cout << "5. Delete End\n";
        cout << "6. Delete by Name\n";
        cout << "7. Delete at Position\n";
        cout << "8. Search Song\n";
        cout << "9. Display Forward\n";
        cout << "10. Display Backward\n";
        cout << "11. Play Next\n";
        cout << "12. Play Previous\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter title: ";
                cin >> title;
                addSongBeginning(title);
                break;

            case 2:
                cout << "Enter title: ";
                cin >> title;
                addSongEnd(title);
                break;

            case 3:
                cout << "Enter title: ";
                cin >> title;
                cout << "Enter position: ";
                cin >> pos;
                addSongAtPos(title, pos);
                break;

            case 4:
                deleteBeginning();
                break;

            case 5:
                deleteEnd();
                break;

            case 6:
                cout << "Enter title: ";
                cin >> title;
                deleteByName(title);
                break;

            case 7:
                cout << "Enter position: ";
                cin >> pos;
                deleteAtPos(pos);
                break;

            case 8:
                cout << "Search title: ";
                cin >> title;
                if (searchSong(title))
                    cout << "Found: " << title << endl;
                else
                    cout << "Not found.\n";
                break;

            case 9:
                displayForward();
                break;

            case 10:
                displayBackward();
                break;

            case 11:
                playNext();
                break;

            case 12:
                playPrev();
                break;

            case 0:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid option.\n";
        }
    }
}
