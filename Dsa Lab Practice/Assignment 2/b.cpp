#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Node structure for the expression tree
struct Node {
    char value;
    Node* left;
    Node* right;
    Node(char val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to construct the expression tree from a postfix expression
Node* constructExpressionTree(const string& postfix) {
    stack<Node*> stk;

    for (char ch : postfix) {
        if (isalnum(ch)) {
            // Operand: Create a node and push it onto the stack
            stk.push(new Node(ch));
        } else {
            // Operator: Pop two nodes, create a new node, and push back onto the stack
            Node* right = stk.top(); stk.pop();
            Node* left = stk.top(); stk.pop();
            Node* operatorNode = new Node(ch);
            operatorNode->left = left;
            operatorNode->right = right;
            stk.push(operatorNode);
        }
    }

    // The remaining node in the stack is the root of the expression tree
    return stk.top();
}

// Non-recursive in-order traversal
void inOrder(Node* root) {
    if (!root) return;
    stack<Node*> stk;
    Node* curr = root;

    while (curr != nullptr || !stk.empty()) {
        while (curr != nullptr) {
            stk.push(curr);
            curr = curr->left;
        }
        curr = stk.top(); stk.pop();
        cout << curr->value << " ";
        curr = curr->right;
    }
}

// Non-recursive pre-order traversal
void preOrder(Node* root) {
    if (!root) return;

    stack<Node*> stk;
    stk.push(root);

    while (!stk.empty()) {
        Node* curr = stk.top(); stk.pop();
        cout << curr->value << " ";

        // Push right child first so left child is processed first
        if (curr->right) stk.push(curr->right);
        if (curr->left) stk.push(curr->left);
    }
}

// Non-recursive post-order traversal
void postOrder(Node* root) {
    if (!root) return;

    stack<Node*> stk1, stk2;
    stk1.push(root);

    // Create a second stack to reverse the order
    while (!stk1.empty()) {
        Node* curr = stk1.top(); stk1.pop();
        stk2.push(curr);

        if (curr->left) stk1.push(curr->left);
        if (curr->right) stk1.push(curr->right);
    }

    // Process the second stack
    while (!stk2.empty()) {
        cout << stk2.top()->value << " ";
        stk2.pop();
    }
}

int main() {
    Node* root = nullptr;
    string postfix;
    int choice;

    do {
        cout << "\n--- Expression Tree Menu ---\n";
        cout << "1. Input Postfix Expression\n";
        cout << "2. Construct Expression Tree\n";
        cout << "3. Non-Recursive In-Order Traversal\n";
        cout << "4. Non-Recursive Pre-Order Traversal\n";
        cout << "5. Non-Recursive Post-Order Traversal\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the postfix expression: ";
            cin >> postfix;
            root = nullptr; // Clear any existing tree
            cout << "Postfix expression set successfully.\n";
            break;

        case 2:
            if (postfix.empty()) {
                cout << "Postfix expression not set. Please set it first (Option 1).\n";
            } else {
                root = constructExpressionTree(postfix);
                cout << "Expression tree constructed successfully.\n";
            }
            break;

        case 3:
            if (root == nullptr) {
                cout << "Expression tree not constructed. Please construct it first (Option 2).\n";
            } else {
                cout << "In-Order Traversal: ";
                inOrder(root);
                cout << endl;
            }
            break;

        case 4:
            if (root == nullptr) {
                cout << "Expression tree not constructed. Please construct it first (Option 2).\n";
            } else {
                cout << "Pre-Order Traversal: ";
                preOrder(root);
                cout << endl;
            }
            break;

        case 5:
            if (root == nullptr) {
                cout << "Expression tree not constructed. Please construct it first (Option 2).\n";
            } else {
                cout << "Post-Order Traversal: ";
                postOrder(root);
                cout << endl;
            }
            break;

        case 6:
            cout << "Exiting the program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
