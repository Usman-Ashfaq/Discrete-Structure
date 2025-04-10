//#include <iostream>
//#include <string>
//#include <stack>
//#include <iomanip>
//using namespace std;
//const int MAX_VARS = 10;
//bool evaluate(char op, bool a, bool b) 
//{
//    switch (op) 
//    {
//    case '&': return a && b;          // AND
//    case '|': return a || b;          // OR
//    case '>': return (!a || b);       // Implication
//    case '=': return (a == b);        // Biconditional
//    default: return false;
//    }
//}
//void printStep(const string& expr, bool result) 
//{
//    cout << expr << " = " << (result ? "1" : "0") << endl;
//}
//bool evaluateExpression(const string& str, bool values[MAX_VARS], const char variables[MAX_VARS], int varCount)
//{
//    bool stack[MAX_VARS];
//    int top = -1;
//    string currentExpr;
//    for (int i = 0; i < str.size(); i++) 
//    {
//        char c = str[i];
//        if (isalpha(c)) 
//        {
//            int idx = 0;
//            while (idx < varCount && variables[idx] != c) idx++;
//            stack[++top] = values[idx];
//            currentExpr += c; 
//        }
//        else if (c == '!') 
//        {
//            bool a = stack[top--];
//            stack[++top] = !a;
//            currentExpr = "!" + currentExpr; 
//            printStep(currentExpr, stack[top]); 
//        }
//        else 
//        {
//            bool b = stack[top--];
//            bool a = stack[top--];
//            char op = c;
//            stack[++top] = evaluate(op, a, b);
//            currentExpr = "(" + to_string(a) + " " + op + " " + to_string(b) + ")";
//            printStep(currentExpr, stack[top]);
//        }
//    }
//    return stack[top];
//}
//int prec(char c) 
//{
//    if (c == '!') return 3;           // NOT
//    if (c == '&') return 2;           // AND
//    if (c == '|') return 2;           // OR
//    if (c == '>') return 1;           // Implication
//    if (c == '=') return 1;           // Biconditional
//    return 0;                         // Parentheses or invalid
//}
//string infixToPostfix(const string& str, char arr[MAX_VARS], int& varCount)
//{
//    string res;
//    stack<char> st;
//    for (int i = 0; i < str.length(); i++) 
//    {
//        char c = str[i];
//        if (isalpha(c))
//        {
//            res += c;
//            bool found = false;
//            for (int j = 0; j < varCount; j++) 
//            {
//                if (arr[j] == c) 
//                {
//                    found = true;
//                    break;
//                }
//            }
//            if (!found) arr[varCount++] = c;
//        }
//        else if (c == '(') 
//        {
//            st.push(c);
//        }
//        else if (c == ')') 
//        {
//            while (!st.empty() && st.top() != '(') 
//            {
//                res += st.top();
//                st.pop();
//            }
//            if (!st.empty()) st.pop();
//        }
//        else 
//        {
//            while (!st.empty() && prec(st.top()) >= prec(c)) 
//            {
//                res += st.top();
//                st.pop();
//            }
//            st.push(c);
//        }
//    }
//    while (!st.empty()) 
//    {
//        res += st.top();
//        st.pop();
//    }
//    return res;
//}
//void generateTruthTable(bool** table, int varCount, int rows) 
//{
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < varCount; ++j) {
//            int temp = 1 << (varCount - j - 1);
//            table[j][i] = (i & temp) != 0; 
//        }
//    }
//}
////void displayTruthTable(const char variables[MAX_VARS], int varCount, bool** truthTable,
////    const bool results1[], const bool results2[], int rows)
////{
////    cout << setw(8);
////    for (int i = 0; i < varCount; ++i) 
////    {
////        cout << variables[i] << setw(5);
////    }
////    cout << "Expr1" << setw(8) << "Expr2" << endl;
////    cout << string(8 + (varCount * 5) + 15, '-') << endl;
////    for (int i = 0; i < rows; ++i)
////    {
////        cout << setw(8);
////        for (int j = 0; j < varCount; ++j) 
////        {
////            cout << truthTable[j][i] << setw(5);
////        }
////        cout << results1[i] << setw(8) << results2[i] << endl;
////    }
////}
//void displayTruthTable(const char variables[MAX_VARS], int varCount, bool** truthTable,
//    const bool results1[], const bool results2[], int rows, const string& expr1, const string& expr2)
//{
//    // Header
//    cout << setw(5);
//    for (int i = 0; i < varCount; ++i)
//    {
//        cout << variables[i] << setw(5);
//    }
//    cout << expr1 << setw(10) << expr2 << endl;
//    cout << string(8 + (varCount * 5) + expr1.size() + expr2.size() + 15, '-') << endl;
//
//    // Rows
//    for (int i = 0; i < rows; ++i)
//    {
//        cout << setw(5);
//        for (int j = 0; j < varCount; ++j)
//        {
//            cout << truthTable[j][i] << setw(5);
//        }
//        cout << results1[i] << setw(10) << results2[i] << endl;
//    }
//    cout << endl;
//}
//
//
//int main() 
//{
//    cout << "Instructions: use ! for NOT operations use & for AND operations\n"
//        << "use | for OR operations use > for Implies operations\n"
//        << "use = for Biconditional operations use only () parenthesis:\n";
//    string expr1, expr2;
//    cout << "Enter Expression 1: ";
//    cin >> expr1;
//    cout << "Enter Expression 2: ";
//    cin >> expr2;
//    char arr[MAX_VARS];
//    int varCount = 0;
//    string postfix1 = infixToPostfix(expr1, arr, varCount);
//    string postfix2 = infixToPostfix(expr2, arr, varCount);
//    int rows = 1 << varCount;
//    bool** truthTable = new bool* [MAX_VARS];
//    for (int i = 0; i < MAX_VARS; ++i) 
//    {
//        truthTable[i] = new bool[rows];
//    }
//    generateTruthTable(truthTable, varCount, rows);
//    bool* results1 = new bool[rows];
//    bool* results2 = new bool[rows];
//    cout << endl;
//    cout << " -------------------------------------------------" << endl;
//    cout << " Displaying the final outputs " << endl;
//    for (int i = 0; i < rows; ++i) 
//    {
//        bool values[MAX_VARS];
//        for (int j = 0; j < varCount; ++j) 
//        {
//            values[j] = truthTable[j][i];
//        }
//        evaluateExpression(postfix1, values, arr, varCount);
//        results1[i] = evaluateExpression(postfix1, values, arr, varCount);
//        evaluateExpression(postfix2, values, arr, varCount);
//        results2[i] = evaluateExpression(postfix2, values, arr, varCount);
//        cout << endl;
//    }
//   // displayTruthTable(arr, varCount, truthTable, results1, results2, rows);
//    displayTruthTable(arr, varCount, truthTable, results1, results2, rows, expr1, expr2);
//
//    
//    bool equivalent = true;
//
//    for (int i = 0; i < rows; ++i) 
//    {
//        if (results1[i] != results2[i])
//        {
//            equivalent = false;
//            break;
//        }
//    }
//    if (equivalent)
//    {
//        cout << "\nBoth Expressions are logically equivalent.\n";
//    }
//    else {
//        cout << "\nThe two expressions are not logically equivalent.\n";
//    }
//    delete[] results1;
//    delete[] results2;
//    for (int i = 0; i < MAX_VARS; ++i) {
//        delete[] truthTable[i];
//    }
//    delete[] truthTable;
//    system("pause");
//    return 0;
//}