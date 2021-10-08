#include <iostream>
#include <queue>
using namespace std;

class stack {
public:
    queue<int> q;
    int size = 0;

    void pop() {
        size--;
        q.pop();
    }

    void push(int value) {
        queue<int> q_tmp;
        size++;
        q_tmp.push(value);

        while (!q.empty()) {
            q_tmp.push(q.front());
            q.pop();
        }

        q = q_tmp;
    }

    int top() {
        return q.front();
    }

    void print() {
        for (int i = 0; i < size; i++) {
            int value = q.front();
            cout << value << " ";
            q.pop(); q.push(value);
        }
        cout << endl;
    }
};


int main() {
    stack s;
    s.push(1); s.push(2); s.push(3); s.push(4); s.print();
    s.pop(); s.print();
    cout << "top: " << s.top() << endl;
}
