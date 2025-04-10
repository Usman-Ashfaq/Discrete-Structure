#include <iostream>
#include <string>
#include <stack>//This library is used to handle infix to postfix expression in this code
#include <iomanip>// for spacing
using namespace std;

const int mav_variable = 10;
int prec(char c) {
    if (c == '!') {
        return 3;
    }         // NOT
    if (c == '&') {
        return 2;
    }
    // AND
    if (c == '|') {
        return 2;
    }
    // OR
    if (c == '>') {
        return 1;
    }
    // Implication
    if (c == '=') {
        return 1;
    }      // Equivalence
    return 0;                         // Parentheses or invalid
}
bool evaluate(char op, bool a, bool b) {
    switch (op) {// in this switch statement we donot use break statement because we use return in this code when the reurn statement is run then its automatically leave the function
    case '&':
        return a && b;          // AND
    case '|':
        return a || b;          // OR
    case '>':
        return (!a || b);       // a -> b
    case '=':
        return (a == b);        // a == b
    default:
        return false;
    }
}


bool evaluateExpression(const string& str, bool arr[mav_variable], const char variables[mav_variable], int varCount) {
    bool stack[mav_variable];
    int top = -1;

    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if (isalpha(c)) {//isalpha() is used to check the both lower and upper value of charact like a to z & A to Z
            int temp = 0;
            while (temp < varCount && variables[temp] != c) temp++;
            stack[++top] = arr[temp];
        }
        else if (c == '!') {
            stack[top] = !stack[top];// This condion used for Not operator
        }
        else {// This condition is used evaluate operators except not
            
            bool b = stack[top--];
            bool a = stack[top--];
            stack[++top] = evaluate(c, a, b);
        }
    }
    return stack[top];
}



string infixToPostfix(const string& str, char arr[mav_variable], int& varCount) {//infixto postfix expression mean According the adjust of evaluation computer like higher to lower order
    string res;
    stack<char> st;

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];

        if (isalpha(c)) {
            res += c;
            bool found = false;
            for (int j = 0; j < varCount; j++) {
                if (arr[j] == c) {
                    found = true;
                    break;
                }
            }
            if (!found) arr[varCount++] = c;
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                res += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();
        }
        else {
            while (!st.empty() && prec(st.top()) >= prec(c)) {
                res += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    return res;
}

void generateTruthTable(bool** table, int varCount, int rows) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < varCount; ++j) {
            int temp = 1;
            for (int k = 0; k < (varCount - j - 1); ++k) {
                temp *= 2;
            }
            table[j][i] = (i % (temp * 2)) >= temp;  // Check if i falls in the range for the current variable
        }
    }
}

void displayTruthTable(const char variables[mav_variable], int varCount, bool** truthTable,
    const bool results1[], const bool results2[], int rows) {
    cout << setw(8);
    for (int i = 0; i < varCount; ++i) {
        cout << variables[i] << setw(5);
    }
    cout << "  Expr1" << setw(8) << "Expr2" << endl;
    cout << string(8 + (varCount * 5) + 15, '-') << endl;

    for (int i = 0; i < rows; ++i) {
        cout << setw(8);
        for (int j = 0; j < varCount; ++j) {
            cout << truthTable[j][i] << setw(5);
        }
        cout << results1[i] << setw(8) << results2[i] << endl;
    }
}

int main() {
    string expr1, expr2;
    cout << "Enter the first logical expression: ";
    cin >> expr1;
    cout << "Enter the second logical expression: ";
    cin >> expr2;

    char arr[mav_variable];
    int count = 0;

    string postfix1 = infixToPostfix(expr1, arr, count);
    string postfix2 = infixToPostfix(expr2, arr, count);

    int rows = 1;
    for (int i = 0; i < count; ++i) {
        rows *= 2;  
    }

    bool** truthTable = new bool* [mav_variable];
    for (int i = 0; i < mav_variable; ++i) {
        truthTable[i] = new bool[rows];
    }

    generateTruthTable(truthTable, count, rows);

    bool* results1 = new bool[rows];
    bool* results2 = new bool[rows];

    for (int i = 0; i < rows; ++i) {
        bool values[mav_variable];
        for (int j = 0; j < count; ++j) {
            values[j] = truthTable[j][i];
        }
        results1[i] = evaluateExpression(postfix1, values, arr, count);
        results2[i] = evaluateExpression(postfix2, values, arr, count);
    }

    displayTruthTable(arr, count, truthTable, results1, results2, rows);

    bool equivalent = true;
    for (int i = 0; i < rows; ++i) {//This condition check the true or false my expression
        if (results1[i] != results2[i]) {
            equivalent = false;
            break;
        }
    }

    if (equivalent) {
        cout << "The two expressions are logically equivalent.\n";
    }
    else {
        cout << "The two expressions are not logically equivalent.\n";
    }

  
    delete[] results1;
    delete[] results2;
    for (int i = 0; i < mav_variable; ++i) {
        delete[] truthTable[i];
    }
    delete[] truthTable;

    system("pause");
    return 0;
}


