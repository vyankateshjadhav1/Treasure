#include <iostream>
#include <stack>
#include <cctype> 
using namespace std;

class Node {
public:
    char data;
    Node* left;
    Node* right;

    Node(char val) {   
        data = val;
        left = NULL;
        right = NULL;
    }
};

class ExpressionTree {
private:
    Node* root;

    void inorder(Node* node) {
        if (node == NULL) return;

        stack<Node*> s;
        Node* current = node;

        while (current != NULL|| !s.empty()) {
            while (current != NULL) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
            s.pop();

            cout << current->data << " ";

            current = current->right;
        }
    }

    void preorder(Node* node) {
        if (node == NULL) return;

        stack<Node*> s;
        s.push(node);

        while (!s.empty()) {
            Node* current = s.top();
            cout << current->data << " ";
            s.pop();

            if (current->right) {
                s.push(current->right);
            }
            if (current->left) {
                s.push(current->left);
            }
        }
    }

    void postorder(Node* node) {
        if (node == NULL) return;

        stack<Node*> s1, s2;
        s1.push(node);
        Node* current;

        while (!s1.empty()) {
            current = s1.top();
            s1.pop();
            s2.push(current);

            if (current->left) {
                s1.push(current->left);
            }
            if (current->right) {
                s1.push(current->right);
            }
        }

        while (!s2.empty()) {
            current = s2.top();
            s2.pop();
            cout << current->data << " ";
        }
    }

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }

    string infixToPostfix(const string& infix) {
        stack<char> s;
        string postfix;

        for (char ch : infix) {
            if (isalpha(ch) || isdigit(ch)) {
                postfix += ch;
            } else if (ch == '(') {
                s.push(ch);
            } else if (ch == ')') {
                while (!s.empty() && s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                s.pop(); 
            } else { 
                while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                    postfix += s.top();
                    s.pop();
                }
                s.push(ch);
            }
        }

        while (!s.empty()) {
            postfix += s.top();
            s.pop();
        }

        return postfix;
    }

public:
    ExpressionTree() {
        root = NULL;
    }

    void constructTreeFromInfix(const string& infix) {
        string postfix = infixToPostfix(infix);
        constructTree(postfix);
    }

    void constructTree(const string& postfix) {
        stack<Node*> s;

        for (char ch : postfix) {
            if (isalpha(ch) || isdigit(ch)) { // Operand
                s.push(new Node(ch));
            } else { // Operator
                Node* operatorNode = new Node(ch);
                operatorNode->right = s.top();
                s.pop();
                operatorNode->left = s.top();
                s.pop();
                s.push(operatorNode);
            }
        }

        root = s.top();
    }

    void displayInorder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }
        cout << "In-order Traversal: ";
        inorder(root);
        cout << endl;
    }

    void displayPreorder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }
        cout << "Pre-order Traversal: ";
        preorder(root);
        cout << endl;
    }

    void displayPostorder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }
        cout << "Post-order Traversal: ";
        postorder(root);
        cout << endl;
    }
};

int main() {
    ExpressionTree tree;
    string expression;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Construct Expression Tree (Infix Expression)\n";
        cout << "2. Display In-order Traversal\n";
        cout << "3. Display Pre-order Traversal\n";
        cout << "4. Display Post-order Traversal\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter infix expression: ";
                cin >> expression;
                tree.constructTreeFromInfix(expression);
                cout << "Expression tree constructed.\n";
                break;
            case 2:
                tree.displayInorder();
                break;
            case 3:
                tree.displayPreorder();
                break;
            case 4:
                tree.displayPostorder();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

// X 5 + 3/3 X + -
// A*B+C/D
// 2*3/(2-1)+5*(4-1)
// 4/(2-(-8*3))
// 2+3-(6*4/8)