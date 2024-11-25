#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
    friend class Selection;
    protected:
        int value;
        Node* next;

    public:
        Node(int value) : value(value), next(nullptr) {}

        void setNext(Node* nextNode) {
            next = nextNode;
        }

        Node* getNext(){
            return next;
        }

        int getValue(){
            return value;
        }
};

#endif