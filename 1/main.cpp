/*

Задано числовое выражение. Необходимо вычислить его значение или
установить, что оно содержит ошибку. В выражении могут встречаться знаки
сложения, вычитания, умножения, скобки и пробелы (пробелов внутри чисел
быть не должно). Приоритет операций стандартный. Все числа в выражении
целые и по модулю не превосходят 2×109 . Также гарантируется, что все
промежуточные вычисления также не превосходят 2×109 .

*/
#include <iostream>
#include <algorithm>
#include "../dst/stack.hpp"

using namespace std;

int calculateSimpleOp(char op, int n1, int n2) {
    switch (op)
    {
    case '+':
        return n1 + n2;
    case '-':
        return n1 - n2;
    case '*':
        return n1 * n2;
    default:
        throw runtime_error("invalid op");
    }
}

int opPriority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*') {
        return 2;
    } else {
        return 0;
    }
}

int calculate(string line) {
    Stack<char> ops;
    Stack<int> nums;
    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line[i])) {
            int num = 0;
            while (i < line.length() && isdigit(line[i])) {
                num = (num * 10) + (line[i] - '0');
                i++;
            }
            nums.push(num);
            i--;
        } else if (line[i] == '(') {
            ops.push(line[i]);
        } else if (line[i] == ')') {
            while (ops.size() != 0 && ops.top() != '(') {
                int num2 = nums.pop();
                int num1 = nums.pop();
                char op = ops.pop();

                nums.push(calculateSimpleOp(op, num1, num2));
            }
            if (ops.size() != 0) {
                ops.pop(); // pop '('
            }
        } else {
            while (ops.size() != 0 && opPriority(ops.top()) >= opPriority(line[i])) {
                int num2 = nums.pop();
                int num1 = nums.pop();
                char op = ops.pop();

                nums.push(calculateSimpleOp(op, num1, num2));
            }
            ops.push(line[i]);
        }
    }

    while (ops.size() != 0) {
        int num2 = nums.pop();
        int num1 = nums.pop();
        char op = ops.pop();

        nums.push(calculateSimpleOp(op, num1, num2));
    }

    return nums.pop();
}


int main() {
    string line;

    cout << ">> ";
    getline(cin, line);
    line.erase(remove(line.begin(), line.end(), ' '), line.end());

    cout << "Result: " << calculate(line) << endl;

    return 0;
}