#include <iostream>
#include <string>
using namespace std;

struct Task {
    string name;
    Task* next;
    Task* prev;
};

// Head of the list
Task* head = NULL;

// Add a new task at the end
void addTask(string taskName) {
    Task* newTask = new Task();
    newTask->name = taskName;
    newTask->next = NULL;
    newTask->prev = NULL;

    if (head == NULL) {
        head = newTask;
        return;
    }

    Task* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newTask;
    newTask->prev = temp;
}

// Add urgent task at the beginning
void addUrgentTask(string taskName) {
    Task* newTask = new Task();
    newTask->name = taskName;
    newTask->next = head;
    newTask->prev = NULL;

    if (head != NULL) {
        head->prev = newTask;
    }

    head = newTask;
}

// Remove a task by name
void removeTask(string taskName) {
    Task* temp = head;
    while (temp != NULL) {
        if (temp->name == taskName) {
            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                head = temp->next;  // Removing first task

            if (temp->next != NULL)
                temp->next->prev = temp->prev;

            delete temp;
            cout << "Task \"" << taskName << "\" removed.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Task not found.\n";
}

// Display tasks forward
void displayTasksForward() {
    Task* temp = head;
    cout << "Tasks (First → Last): ";
    while (temp != NULL) {
        cout << temp->name << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Display tasks backward
void displayTasksBackward() {
    Task* temp = head;
    if (temp == NULL) {
        cout << "No tasks.\n";
        return;
    }

    // Move to last task
    while (temp->next != NULL)
        temp = temp->next;

    cout << "Tasks (Last → First): ";
    while (temp != NULL) {
        cout << temp->name << " ";
        temp = temp->prev;
    }
    cout << endl;
}

int main() {
    addTask("Email client");
    addTask("Finish report");
    addTask("Call supplier");
    addUrgentTask("Fix urgent bug");

    displayTasksForward();
    displayTasksBackward();

    removeTask("Finish report");
    displayTasksForward();

    return 0;
}
