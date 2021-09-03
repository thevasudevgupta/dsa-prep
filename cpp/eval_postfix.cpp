#include <iostream>
#include <stack>
using namespace std;

const char *ADD_OP = "+";
const char *SUB_OP = "-";
const char *MUL_OP = "*";
const char *DIV_OP = "*";

bool is_operator(const char *input) {
    return (*input == *ADD_OP || *input == *SUB_OP || *input == *MUL_OP || *input == *DIV_OP);
}

int convert_to_int(const char *input) {
    const char *zero = "0";
    return *input - *zero;
}

int apply_op(int val1, int val2, const char *op) {
    if (*op == *ADD_OP) { return val1 + val2; }
    else if (*op == *SUB_OP) { return val1 - val2; }
    else if (*op == *MUL_OP) { return val1 * val2; }
    else if (*op == *DIV_OP) { return val1 / val2; }
    return -1;
}

int evaluate_postfix(string input) {
    stack<int> stack;
    int val1, val2;
    for (int i = 0; i < input.length(); i++) {
        if (is_operator(&input[i])) {
            val2 = stack.top(); stack.pop();
            val1 = stack.top(); stack.pop();
            stack.push(apply_op(val1, val2, &input[i]));
        } else {
            stack.push(convert_to_int(&input[i]));
        }
    }
    int answer = stack.top();
    stack.pop();
    return answer;
};


int main() {
    string input = "123*4-+";
    int output = evaluate_postfix(input);
    cout << input << " : " << output << endl;
};
