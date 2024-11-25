#include <iostream>
#include "Node.h"
#include <limits>
using namespace std;

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->setNext(newNode);
            rear = newNode;
        }
        cout << "Enqueued " << value << " to the queue." << endl;
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        cout << "Dequeued " << front->getValue() << " from the queue." << endl;
        front = front->getNext();
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    void swap(int index1, int index2) {
        
        if (index1 == index2) {
            cout << "Indices are the same, no swap needed." << endl;
            return;
        }

        Node* prev1 = nullptr, *prev2 = nullptr;
        Node* node1 = front, *node2 = front;
        int pos1 = 0, pos2 = 0;

        while (node1 != nullptr && pos1 != index1) {
            prev1 = node1;
            node1 = node1->getNext();
            pos1++;
        }
        while (node2 != nullptr && pos2 != index2) {
            prev2 = node2;
            node2 = node2->getNext();
            pos2++;
        }

        if (node1 == nullptr || node2 == nullptr) {
            cout << "Invalid indices for swapping." << endl;
            return;
        }

        if (prev1 != nullptr) prev1->setNext(node2);
        else front = node2;

        if (prev2 != nullptr) prev2->setNext(node1);
        else front = node1;

        Node* temp = node1->getNext();
        node1->setNext(node2->getNext());
        node2->setNext(temp);

        if (node1->getNext() == nullptr) rear = node1;
        if (node2->getNext() == nullptr) rear = node2;

        cout << "Swapped elements at indices " << index1 << " and " << index2 << endl;
    }

    void display() {
        if (front == nullptr) {

            cout << "Queue is empty!" << endl;
            return;
        }
        Node* current = front;
        cout << "Queue contents: ";
        while (current != nullptr) {
            cout << current->getValue() << " ";
            current = current->getNext();
        }
        cout << endl;
    }
};

int main() {
    Queue queue;
    int choice = 0, value, index1, index2;

    do {
        cout << "\n1. Enqueue\n2. Dequeue\n3, Swap\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Check for invalid input
        if(cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter value to enqueue: ";
            cin >> value;

            // Check if input is valid
            if(cin.fail()) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
                break;
            }
            queue.enqueue(value);
            break;
        case 2:
            queue.dequeue();
            break;
        // case 3:
        //     queue.display();
        //     break;
        case 3:
            cout << "Enter two indices to swap: ";
            cin >> index1 >> index2;

            // Check if input is valid
            if(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter valid numbers." << endl;
                break;
            }

            queue.swap(index1, index2);
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please select a valid option." << endl;
        }
    } while (choice != 4);

    return 0;
    
}