#include <iostream>
#include "Node.h"
#include <limits> 
using namespace std;

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->setNext(top);
        top = newNode;
        cout << "Pushed " << value << " to the stack." << endl;
    }

    void pop() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return;
        }
        Node* temp = top;
        cout << "Popped " << top->getValue() << " from the stack." << endl;
        top = top->getNext();
        delete temp;
    }

    int peek() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return top->getValue();
    }

    void swap(int index1, int index2) {
        if (index1 == index2) {
            cout << "Indices are the same, no swap needed." << endl;
            return;
        }

        Node* prev1 = nullptr, *prev2 = nullptr;
        Node* node1 = top, *node2 = top;
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
        else top = node2;

        if (prev2 != nullptr) prev2->setNext(node1);
        else top = node1;

        Node* temp = node1->getNext();
        node1->setNext(node2->getNext());
        node2->setNext(temp);

        cout << "Swapped elements at indices " << index1 << " and " << index2 << endl;
    }
    void edit(int index1, int value){
       Node* prev1 = nullptr, *prev2 = nullptr;
       Node* node1 = top, *node2 = top;
       int pos1 = 0, pos2 = 0;

       while (node1 != nullptr && pos1 != index1){
            prev1 = node1;
       }
       if (index1 == value){
            cout << "Nilai Value sama" << "dari" << index1;
       }
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void display() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return;
        }
        Node* current = top;
        cout << "Stack contents: ";
        while (current != nullptr) {
            cout << current->getValue() << " ";
            current = current->getNext();
        }
        cout << endl;
    }
};

int main() {
    Stack stack;
    int choice = 0, value, index1, index2;

    do {
        cout << "\n1. Push\n2. Pop\n3. Peek\n4. Display\n5. Swap\n6. edit\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Check for invalid input
        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter value to push: ";
            cin >> value;

            // Check if input is valid
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
                break;
            }
            stack.push(value);
            break;
        case 2:
            stack.pop();
            break;
        case 3:
            cout << "Top element is: " << stack.peek() << endl;
            break;
        case 4:
            stack.display();
            break;
        case 5:
            cout << "Enter two indices to swap: ";
            cin >> index1 >> index2;

            // Check if input is valid
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter valid numbers." << endl;
                break;
            }

            stack.swap(index1, index2);
            break;
        case 6:
            cout << "Masukkan Index, Dan Value yang diinginkan" << endl;               
        case 7:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please select a valid option." << endl;
        }
    } while (choice != 6);

    return 0;
}
