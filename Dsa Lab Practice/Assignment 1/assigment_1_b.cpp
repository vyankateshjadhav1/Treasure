#include<iostream>
#include<queue>
using namespace std;

class node{
    public:
    int data;
    node*left;
    node*right;

    node(int val){
        data=val;
        left=NULL;
        right=NULL;
    }
};

node* insert(node*root,int val){
    if(root == NULL) {
        root = new node(val);
        return root;
    } 

    if(val < root->data){
        root->left = insert(root->left,val);
    }   
    else{
        root->right = insert(root->right,val);
    }
    return root;
}    

void levelOrderTraversal(node*root){
    if(root == NULL) return;
    queue<node*>q;
    q.push(root);
    q.push(NULL);

    while(!q.empty()){
        node*temp = q.front();
        q.pop();

        if(temp != NULL){
            cout<<endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
        else{
            cout<<temp->data<<" ";
            if(temp->left){
            q.push(temp->left);
            }

            if(temp->right){
            q.push(temp->right);
            }
       }
        
    }
}

void takeInput(node*root)
{
    int data;
    cin>>data;

    while(data != -1){
        root = insert(root,data);
        cin>>data;
    }
}

node* maxVal(node*root){
    node*temp = root;
    while(temp->right != NULL){
        temp = temp->right;
    }
}


node* minVal(node*root){
    node*temp = root;
    while(temp->left != NULL){
        temp = temp->left;
    }
}

node*deleteNode(node* root, int val){
    
    if(root == NULL){
        return NULL;
    }

     if(root->data == val) {
        if(root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        if(root->left != NULL && root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        }
         if(root->left == NULL && root->right != NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        }
         if(root->left != NULL && root->right != NULL) {
            int mini = minVal(root->right)->data;
            root->data = mini;
            root->right = deleteNode(root->right, mini);
            return root;
        }
    }    

     else if(val < root->data) {
        root->left = deleteNode(root->left, val);
        return root;
    }
    else {
        root->right = deleteNode(root->right, val);
        return root;
    }
}

bool search(node* root, int val) {

    if(root == NULL) {
        return false;
    }

    if(root->data == val) {
        return true;
    }
    else if(val < root->data) {
        return search(root->left, val);
    }
    else {
        return search(root->right, val);
    }
}


int main() {
    node* root = NULL;
    int choice, value;

    while(true) {
        cout << "\nMenu:\n";
        cout << "1. Insert Node\n";
        cout << "2. Delete Node\n";
        cout << "3. Search Node\n";
        cout << "4. Display Level Order Traversal\n";
        cout << "5. Find Min Value\n";
        cout << "6. Find Max Value\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter value to insert (-1 to stop): ";
                takeInput(root);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                cout << "Node deleted.\n";
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if(search(root, value)) {
                    cout << "Value found in the tree.\n";
                } else {
                    cout << "Value not found.\n";
                }
                break;
            case 4:
                cout << "Level Order Traversal:\n";
                levelOrderTraversal(root);
                break;
            case 5:
                if(root != NULL) {
                    cout << "Min value: " << minVal(root)->data << endl;
                } else {
                    cout << "Tree is empty.\n";
                }
                break;
            case 6:
                if(root != NULL) {
                    cout << "Max value: " << maxVal(root)->data << endl;
                } else {
                    cout << "Tree is empty.\n";
                }
                break;
            case 7:
                cout << "Exiting...\n";
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}


