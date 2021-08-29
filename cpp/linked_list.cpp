#include <iostream>

class Node {
    public:
        int data;
        Node *next;
        Node() {next = NULL;}
};

class List {
    public:
        void insert(int value);
        bool find(int value);
        void remove(int value);
        void print();
        int size();
        List() {head = NULL; tail=NULL; length = 0;}
    private:
        Node *head, *tail;
        int length;
};

void List::insert(int value) {
    Node *new_node = new Node();
    new_node->data = value;

    if (head == NULL) {head = tail = new_node;}
    else {
        tail->next = new_node;
        tail = new_node;
    }

    length += 1;
};

bool List::find(int value) {
    if (length == 0) {return false;}
    Node *ptr = head;
    for (int i = 0; i < length; i++) {
        if (ptr->data == value) {return true;}
        ptr = ptr->next;
    }
    return false;
};

void List::remove(int value) {
    if (length == 0) {return;}

    Node *obj_to_delete = head;
    if (head->data == value) {
        head = head->next;
        free(obj_to_delete);
        length -= 1;
    }

    Node *ptr = head;
    for (int i = 0; i < length - 1; i++) {
        if (ptr->next->data == value) {
            obj_to_delete = ptr->next;
            ptr->next = ptr->next->next;
            free(obj_to_delete);
            length -= 1;
        }
        if (ptr->next != NULL) {ptr = ptr->next;}
    }
    tail = ptr;
};

void List::print() {
    if (length == 0) {return;}
    Node *ptr = head;
    for (int i = 0; i < length; i++) {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
};

int List::size() {
    return length;
};


int main() {
    List list;

    list.insert(3);
    list.insert(4);
    list.insert(7);
    list.insert(3);
    list.insert(5);
    list.insert(8);
    list.insert(3);

    list.print();
    std::cout << "size: " << list.size() << std::endl;

    list.remove(3);
    list.remove(9);
    std::cout << "is_found: " << list.find(3) << std::endl;
    list.insert(3);
    std::cout << "is_found: " << list.find(3) << std::endl;
    list.print();
    std::cout << "size: " << list.size() << std::endl;
};
