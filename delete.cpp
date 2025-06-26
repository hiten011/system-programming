// #include <iostream>

// struct Node {
//     int val;
//     Node* left;
//     Node* right;

//     Node(Node* left, Node* right, int val) {
//         this->left = left;
//         this->right = right;
//         this->val = val;
//     }

//     Node(int val): Node(nullptr, nullptr, val) {};
//     Node(): Node(nullptr, nullptr, -1) {};
// };

// int searchNode(Node* cur, int target) {
//     if (cur == nullptr) {
//         return -1;
//     } 

//     Node* left = cur->left;
//     Node* right = cur->right;

//     if (left->val == target) {
//         cur->left = deleteNode(left);
//         return 0;
//     } else if (right->val == target) {
//         cur->right = deleteNode(right);
//         return 0;
//     }

//     if (cur->val > target) {
//         return searchNode(left, target);
//     } else {
//         return searchNode(right, target);
//     }
// }

// Node* deleteNode(Node* cur) {
//     Node* left = cur->left;
//     Node* right = cur->right;

//     if (left == nullptr && right == nullptr) {
//         // leaf Node
//         return nullptr;
//     } else if (left == nullptr) {
//         return right;
//     } else if (right == nullptr) {
//         return left;
//     } else {
//         Node* pos = findPos(left);
//         pos->right = right;
//         return left;
//     }
// }

// Node* findPos(Node* cur) {
//     Node* right = cur->right;

//     if (right == nullptr) {
//         return cur;
//     } else {
//         return findPos(right);
//     }
// }

// int main() {
//     searchNode();
// }


#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(Node* left, Node* right, int val) {
        this->left = left;
        this->right = right;
        this->val = val;
    }

    Node(int val): Node(nullptr, nullptr, val) {};
    Node(): Node(nullptr, nullptr, -1) {};
};

Node* deleteNode(Node* cur);
Node* findPos(Node* cur);

int searchNode(Node* cur, int target) {
    if (cur == nullptr) {
        return -1;
    }

    Node* left = cur->left;
    Node* right = cur->right;

    if (left && left->val == target) {
        cur->left = deleteNode(left);
        return 0;
    } else if (right && right->val == target) {
        cur->right = deleteNode(right);
        return 0;
    }

    if (target < cur->val) {
        return searchNode(left, target);
    } else {
        return searchNode(right, target);
    }
}

Node* deleteNode(Node* cur) {
    Node* left = cur->left;
    Node* right = cur->right;

    if (left == nullptr && right == nullptr) {
        // leaf Node
        delete cur;
        return nullptr;
    } else if (left == nullptr) {
        Node* temp = right;
        delete cur;
        return temp;
    } else if (right == nullptr) {
        Node* temp = left;
        delete cur;
        return temp;
    } else {
        Node* pos = findPos(left);
        pos->right = right;
        delete cur;
        return left;
    }
}

Node* findPos(Node* cur) {
    if (cur->right == nullptr) {
        return cur;
    } else {
        return findPos(cur->right);
    }
}

void printTree(Node* root, string indent = "", bool isLeft = true) {
    if (root != nullptr) {
        cout << indent;
        if (isLeft) {
            cout << "L--";
            indent += "|  ";
        } else {
            cout << "R--";
            indent += "   ";
        }
        cout << root->val << endl;
        printTree(root->left, indent, true);
        printTree(root->right, indent, false);
    }
}

void inOrder(Node *root) {
  if (root == nullptr) {
    return;
  }
  inOrder(root->left);
  cout << root->val << " ";
  inOrder(root->right);
}

// Helper to insert into BST
Node* insert(Node* root, int val) {
    if (root == nullptr) return new Node(val);
    if (val < root->val) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

// MAIN TESTS
int main() {
    Node* root = nullptr;
    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for (int v : values) {
        root = insert(root, v);
    }

    cout << "Initial Tree:\n";
    printTree(root);

    int testCases[] = {20, 30, 50}; // leaf, one child, two children

    for (int target : testCases) {
        cout << "\nDeleting " << target << ":\n";
        searchNode(root, target);
        printTree(root);
    }

    return 0;
}
