#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

// 自定义栈类
template<typename T>
class Stack {
private:
    std::stack<T> s;

public:
    void push(T value) {
        s.push(value);
    }

    T pop() {
        T value = s.top();
        s.pop();
        return value;
    }

    T top() {
        return s.top();
    }

    bool isEmpty() {
        return s.empty();
    }
};// 优先级表
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// 判断是否为运算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 执行运算
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : throw std::invalid_argument("Division by zero");
        default: throw std::invalid_argument("Invalid operator");
    }
}

// 计算表达式的值
int evaluate(const std::string& expression) {
    Stack<int> values;
    Stack<char> ops;

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];

        if (isspace(c)) continue;

        if (isdigit(c)) {
            int value = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            values.push(value);
        } else if (isOperator(c)) {
            while (!ops.isEmpty() && precedence(ops.top()) >= precedence(c)) {
                int val2 = values.pop();
                int val1 = values.pop();
                char op = ops.pop();

                values.push(applyOp(val1, val2, op));
            }
            ops.push(c);
        }
    }

    while (!ops.isEmpty()) {
        int val2 = values.pop();
        int val1 = values.pop();
        char op = ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    return values.pop();
}// 扩展applyOp函数以支持更多运算
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : throw std::invalid_argument("Division by zero");
        case 's': return sin(a);
        case 'c': return cos(a);
        case 't': return tan(a);
        case 'l': return log(a);
        default: throw std::invalid_argument("Invalid operator");
    }
}int main() {
    std::string expression = "3+5*2";
    try {
        std::cout << "Result: " << evaluate(expression) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
