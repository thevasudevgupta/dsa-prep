#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node *next;
    Node(int value) {
        this->value = value;
        next = nullptr;
    }
};

class queue {
public:
    int size = 0;
    Node *head = nullptr, *tail = nullptr;

    void push(int value) {
        Node *node = new Node(value);
        if (head == nullptr) {
            head = node;
        }

        if (tail == nullptr) {
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }

    void pop() {
        if (head == nullptr) { return; }
        Node *tmp_ptr = head;
        head = head->next;
        delete tmp_ptr;
    }

    int front() {
        return head->value;
    }

    void print() {
        Node *ptr = head;
        while (ptr != nullptr) {
            cout << ptr->value << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }
};

int main() {
    queue q;
    q.push(1); q.push(2); q.push(3); q.push(4); q.print();
    q.pop(); q.print(); q.pop(); q.print();
    cout << "front: " << q.front() << endl;
}
