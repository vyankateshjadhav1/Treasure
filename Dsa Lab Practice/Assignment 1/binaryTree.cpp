
// //1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1 

#include<iostream>
#include<queue>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

node* buildTree(node* root) {
    cout << "Enter the data: ";
    int data;
    cin >> data;
    root = new node(data);

    if (data == -1) {
        return NULL;
    }

    cout << "Enter data for inserting in left of " << data << ": ";
    root->left = buildTree(root->left);
    cout << "Enter data for inserting in right of " << data << ": ";
    root->right = buildTree(root->right);
    return root;
}

void levelOrderTraversal(node* root) {
    if (root == NULL) return;

    queue<node*> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        if (temp == NULL) {
            cout << endl;
            if (!q.empty()) {
                q.push(NULL);
            }
        } else {
            cout << temp->data << " ";
            if (temp->left) {
                q.push(temp->left);
            }
            if (temp->right) {
                q.push(temp->right);
            }
        }
    }
}

void inorder(node* root) {
    if (root == NULL) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(node* root) {
    if (root == NULL) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(node* root) {
    if (root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Height of a tree
int depth(node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);

    return max(leftDepth, rightDepth) + 1;
}

void displayLeaves(node* root) {
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            cout << root->data << " ";
        }
        displayLeaves(root->left);
        displayLeaves(root->right);
    }
}

node* copyTree(node* root) {
    if (root == NULL) {
        return NULL;
    }

    node* newRoot = new node(root->data);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}

void menu() {
    cout << "\nMenu:\n";
    cout << "1. Build Tree\n";
    cout << "2. Level Order Traversal\n";
    cout << "3. Inorder Traversal\n";
    cout << "4. Preorder Traversal\n";
    cout << "5. Postorder Traversal\n";
    cout << "6. Depth of the Tree\n";
    cout << "7. Display Leaves\n";
    cout << "8. Copy Tree\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    node* root = NULL;
    int choice;

    do {
        menu();
        cin >> choice;

        switch (choice) {
            case 1:
                root = buildTree(root);
                break;

            case 2:
                levelOrderTraversal(root);
                break;

            case 3:
                inorder(root);
                cout << endl;
                break;

            case 4:
                preorder(root);
                cout << endl;
                break;

            case 5:
                postorder(root);
                cout << endl;
                break;

            case 6:
                cout << "Depth of the tree: " << depth(root) << endl;
                break;

            case 7:
                displayLeaves(root);
                cout << endl;
                break;

            case 8:
                {
                    node* newRoot = copyTree(root);
                    cout << "Copied Tree Level Order Traversal: " << endl;
                    levelOrderTraversal(newRoot);
                }
                break;

            case 9:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 9);

    return 0;
}
