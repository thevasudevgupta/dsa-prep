#include <iostream>
using namespace std;


class Node {
    public:
        int data;
        Node *right;
        Node *down;
        Node() {right = NULL; down = NULL;}
        void print() {cout << data;}
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
    if (m == 0 || n == 0) {return;}

    num_rows = m, num_columns = n;
    head = NULL;

    Node *ptr = head, *above_ptr = head;
    Node *vertical_ptr = head;
    int tmp_value;

    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_columns; j++) {
            cin >> tmp_value;

            Node *new_node = new Node();
            new_node->data = tmp_value;

            // this is getting executed at start of every new row
            if (ptr == NULL) {
                if (i == 0) {
                    vertical_ptr = above_ptr = head = new_node;
                    ptr = new_node;
                }
                else {
                    above_ptr->down = ptr = new_node;
                    above_ptr = above_ptr->right;
                }
            }
            else {
                ptr->right = new_node;
                ptr = ptr->right;
                if (i != 0) {
                    above_ptr->down = new_node;
                    above_ptr = above_ptr->right;
                }
            }
        }
        if (i != 0) {
            vertical_ptr = vertical_ptr->down;
            above_ptr = vertical_ptr;
        }
        ptr = vertical_ptr->down;
    }
};

void Matrix::printRowCol() {
    if (num_rows == 0 || num_columns == 0) {return;}

    Node *ptr = head;
    Node *vertical_ptr = head;
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_columns; j++) {
            cout << ptr->data << " ";
            ptr = ptr->right;
        }
        ptr = vertical_ptr->down;
        vertical_ptr = ptr;
        cout << std::endl;
    }
};

void Matrix::printColRow() {
    if (num_rows == 0 || num_columns == 0) {return;}

    Node *ptr = head;
    Node *horizontal_ptr = head;
    for (int i = 0; i < num_columns; i++){
        for (int j = 0; j < num_rows; j++) {
            cout << ptr->data << " ";
            ptr = ptr->down;
        }
        ptr = horizontal_ptr->right;
        horizontal_ptr = ptr;
        cout << std::endl;
    }
};

void Matrix::insertRow(int index) {
    // index is starting from 1
    if (num_rows == 0 || num_columns == 0) {return;}
    if (index > num_rows + 1) {return;}

    index -= 1;
    num_rows += 1;

    Node *ptr = head;
    Node *horizontal_ptr;
    int tmp_value;

    if (index == 0) {
        for (int i = 0; i < num_columns; i++) {
            cin >> tmp_value;

            Node *new_node = new Node();
            new_node->data = tmp_value;

            if (i == 0) {head = horizontal_ptr = new_node;}
            else {
                horizontal_ptr->right = new_node;
                horizontal_ptr = horizontal_ptr->right;
            }

            new_node->down = ptr;
            ptr = ptr->right;
        }        
    }
    else {
        for (int i = 0; i < index - 1; i++) {
            ptr = ptr->down;
        }

        for (int i = 0; i < num_columns; i++) {
            cin >> tmp_value;

            Node *new_node = new Node();
            new_node->data = tmp_value;

            if (i == 0) {horizontal_ptr = new_node;}
            else {
                horizontal_ptr->right = new_node;
                horizontal_ptr = horizontal_ptr->right;
            }

            new_node->down = ptr->down;
            ptr->down = new_node;

            ptr = ptr->right;
        }
    }
};

void Matrix::insertCol(int index) {
    if (num_rows == 0 || num_columns == 0) {return;}
    if (index > num_columns + 1) {return;}

    // index is starting from 1
    index -= 1;
    num_columns += 1;

    Node *ptr = head;
    Node *vertical_ptr;
    int tmp_value;

    if (index == 0) {
        for (int i = 0; i < num_rows; i++) {
            cin >> tmp_value;

            Node *new_node = new Node();
            new_node->data = tmp_value;

            if (i == 0) {head = vertical_ptr = new_node;}
            else {
                vertical_ptr->down = new_node;
                vertical_ptr = vertical_ptr->down;
            }

            new_node->right = ptr;
            ptr = ptr->down;
        }
    }
    else {
        for (int i = 0; i < index - 1; i++) {
            ptr = ptr->right;
        }

        for (int i = 0; i < num_rows; i++) {
            cin >> tmp_value;

            Node *new_node = new Node();
            new_node->data = tmp_value;

            if (i == 0) {vertical_ptr = new_node;}
            else {
                vertical_ptr->down = new_node;
                vertical_ptr = vertical_ptr->down;
            }

            new_node->right = ptr->right;
            ptr->right = new_node;

            ptr = ptr->down;
        }
    }
};

void Matrix::delRow(int index) {
    if (num_rows == 0 || num_columns == 0) {return;}
    if (index > num_rows) {return;}

    // index is starting from 1
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
            free(obj_to_delete);
            ptr = ptr->right;
        }
    }
};

void Matrix::delCol(int index) {
    if (num_rows == 0 || num_columns == 0) {return;}
    if (index > num_columns) {return;}

    // index is starting from 1
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
        cin>>flag;
        
        if(flag == -1)
        {
            break;
        }
        switch(flag)
        {
            case 0:
                cin>>m>>n;
                M.createMatrix(m,n);
                break;
            case 1:
                M.printRowCol();
                break;
            case 2:
                M.printColRow();
                break;
            case 3:
                cin>>index;
                M.insertRow(index);
                break;
            case 4:
                cin>>index;
                M.insertCol(index);
                break;
            case 5:
                cin>>index;
                M.delRow(index);
                break;
            case 6:
                cin>>index;
                M.delCol(index);
                break;
            default:
                break;       
        }   
    }
}
