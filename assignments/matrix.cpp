#include <iostream>

class Node {
    public:
        int data;
        Node *right;
        Node *down;
        Node() {right = NULL; down = NULL;}
        void print() {std::cout << data;}
};

class Matrix {
    public:
        void createMatrix(int m, int n);
        void printRowCol();
        void printColRow();
        void insertRow(int index);
        void insertCol(int index);
        void delRow(int index);
        void delCol(int index);
        Matrix();
    private:
        Node *head;
        int num_rows, num_columns;
};

Matrix::Matrix() {
    head = NULL;
    num_rows = 0;
    num_columns = 0;
};

void Matrix::createMatrix(int m, int n) {
    std::cout << "##########" << std::endl;

    num_rows = m, num_columns = n;
    head = NULL;

    Node *ptr = head, *vertical_ptr = head;
    Node *above_ptr = head, *above_vertical_ptr = head;
    int tmp_value;

    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_columns; j++) {
            std::cin >> tmp_value;

            Node *new_node = new Node();
            new_node->data = tmp_value;

            // this is getting executed at start of every new row
            if (ptr == NULL) {
                if (i == 0) {
                    head = vertical_ptr = new_node;
                }
                else {
                    vertical_ptr->down = new_node;
                    vertical_ptr = vertical_ptr->down;
                }
                ptr = new_node;
            }
            else {
                // if (i != 0) {
                //     above_ptr->down = new_node;
                //     above_ptr = above_ptr->right;
                // }
                ptr->right = new_node;
                ptr = ptr->right;
            }
        }

        // if (i == 0) {
        //     above_ptr = above_vertical_ptr = head;
        // }
        // else {
        //     above_ptr = above_vertical_ptr->down;
        //     above_vertical_ptr = above_vertical_ptr->down;
        // }
        ptr = vertical_ptr->down;
    }
    std::cout << "##########" << std::endl;
};

void Matrix::printRowCol() {
    std::cout << "##########" << std::endl;
    Node *ptr = head;
    Node *vertical_ptr = head;
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_columns; j++) {
            std::cout << ptr->data << " ";
            ptr = ptr->right;
        }
        ptr = vertical_ptr->down;
        vertical_ptr = ptr;
        std::cout << std::endl;
    }
    std::cout << "##########" << std::endl;
};

void Matrix::printColRow() {
    std::cout << "##########" << std::endl;
    Node *ptr = head;
    Node *horizontal_ptr = head;
    for (int i = 0; i < num_columns; i++){
        for (int j = 0; j < num_rows; j++) {
            std::cout << ptr->data << " ";
            ptr = ptr->down;
        }
        ptr = horizontal_ptr->right;
        horizontal_ptr = ptr;
        // std::cout << "okay" << std::endl;
        // std::cout << ptr->data << " " << (ptr->down == NULL);
        std::cout << std::endl;
    }
    std::cout << "##########" << std::endl;
};

void Matrix::insertRow(int index) {
};

void Matrix::insertCol(int index) {
};

void Matrix::delRow(int index) {
    // index is starting from 1
    std::cout << "del row at index " << index << std::endl;
    index -= 1;
    num_rows -= 1;
    Node *ptr = head, *obj_to_delete = head;

    if (index == 0) {
        head = head->down;
        for (int i = 0; i < num_columns; i++) {
            obj_to_delete = ptr;
            ptr = ptr->right;
            free(obj_to_delete);
        }
    }
    else {
        for (int i = 0; i < index - 1; i++) {
            ptr = ptr->down;
        }
        for (int i = 0; i < num_columns; i++) {
            obj_to_delete = ptr->down;
            ptr->down = ptr->down->down;
            // if (obj_to_delete != NULL) {std::cout << obj_to_delete->data << std::endl;}
            // else {std::cout << "NULL" << std::endl;}
            free(obj_to_delete);
            ptr = ptr->right;
        }
    }
};

void Matrix::delCol(int index) {
    // index is starting from 1
    std::cout << "del col at index " << index << std::endl;
    index -= 1;
    num_columns -= 1;
    Node *ptr = head, *obj_to_delete = head;

    if (index == 0) {
        head = head->right;
        for (int i = 0; i < num_rows; i++) {
            obj_to_delete = ptr;
            ptr = ptr->down;
            free(obj_to_delete);
        }
    }
    else {
        for (int i = 0; i < index - 1; i++) {
            ptr = ptr->right;
        }
        for (int i = 0; i < num_rows; i++) {
            obj_to_delete = ptr->right;
            ptr->right = ptr->right->right;
            // if (obj_to_delete != NULL) {std::cout << obj_to_delete->data << std::endl;}
            // else {std::cout << "NULL" << std::endl;}
            free(obj_to_delete);
            ptr = ptr->down;
        }
    }
};

int main()
{
    Matrix M;
    int m;
    int n;
    int index;

    int flag;

    while(true)
    {
        std::cin>>flag;
        
        if(flag == -1)
        {
            break;
        }
        switch(flag)
        {
            case 0:
                std::cin>>m>>n;
                M.createMatrix(m,n);
                break;
            case 1:
                M.printRowCol();
                break;
            case 2:
                M.printColRow();
                break;
            case 3:
                std::cin>>index;
                M.insertRow(index);
                break;
            case 4:
                std::cin>>index;
                M.insertCol(index);
                break;
            case 5:
                std::cin>>index;
                M.delRow(index);
                break;
            case 6:
                std::cin>>index;
                M.delCol(index);
                break;
            default:
                break;       
        }   
    }
}