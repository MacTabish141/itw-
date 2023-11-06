#include <iostream>
#include <algorithm>
using namespace std;
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};
int height(struct Node* node) {
    if (node == nullptr)
        return 0;
    return node-&gt;height;
}
void updateHeight(struct Node* node) {
    if (node != nullptr) {
        int leftHeight = height(node-&gt;left);
        int rightHeight = height(node-&gt;right);
        node-&gt;height = max(leftHeight, rightHeight) + 1;
    }
}
int balanceFactor(struct Node* node) {
    if (node == nullptr)
        return 0;
    return height(node-&gt;left) - height(node-&gt;right);
}
struct Node* rotateRight(struct Node* y) {
    struct Node* x = y-&gt;left;
    struct Node* T2 = x-&gt;right;
    x-&gt;right = y;
    y-&gt;left = T2;
    updateHeight(y);
    updateHeight(x);

    return x;
}
struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x-&gt;right;
    struct Node* T2 = y-&gt;left;
    y-&gt;left = x;
    x-&gt;right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}
struct Node* insert(struct Node* node, int key) {
    if (node == nullptr)
        return new Node{key, nullptr, nullptr, 1};
    if (key &lt; node-&gt;key)
        node-&gt;left = insert(node-&gt;left, key);
    else if (key &gt; node-&gt;key)
        node-&gt;right = insert(node-&gt;right, key);
    else
        return node;
    updateHeight(node);
    int balance = balanceFactor(node);
    if (balance &gt; 1) {
        printf(&quot;Balance factor: %d\n&quot;, balance);
        if (key &lt; node-&gt;left-&gt;key){ // LL
            printf(&quot;LL Rotation\n&quot;);
            return rotateRight(node);
        }
        else { // LR
            printf(&quot;LR Rotation\n&quot;);
            node-&gt;left = rotateLeft(node-&gt;left);
            return rotateRight(node);
        }
    }
    if (balance &lt; -1) {
        printf(&quot;Balance factor: %d\n&quot;, balance);
        if (key &gt; node-&gt;right-&gt;key){ // RR

            printf(&quot;RR Roation\n&quot;);
            return rotateLeft(node);
        }
        else { // RL
            printf(&quot;RL Roation\n&quot;);
            node-&gt;right = rotateRight(node-&gt;right);
            return rotateLeft(node);
        }
    }
    printf(&quot;Inserted %d\n&quot;, key);
    return node;
}
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current-&gt;left != nullptr)
        current = current-&gt;left;
    return current;
}
struct Node* deleteNode(struct Node* root, int key) {
    if (root == nullptr)
        return root;
    if (key &lt; root-&gt;key)
        root-&gt;left = deleteNode(root-&gt;left, key);
    else if (key &gt; root-&gt;key)
        root-&gt;right = deleteNode(root-&gt;right, key);
    else {
        if ((root-&gt;left == nullptr) || (root-&gt;right == nullptr)) {
            struct Node* temp = root-&gt;left ? root-&gt;left : root-&gt;right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            struct Node* temp = minValueNode(root-&gt;right);
            root-&gt;key = temp-&gt;key;
            root-&gt;right = deleteNode(root-&gt;right, temp-&gt;key);
        }
    }
    if (root == nullptr)
        return root;
    updateHeight(root);

    int balance = balanceFactor(root);
    if (balance &gt; 1) {
        if (balanceFactor(root-&gt;left) &gt;= 0) // LL
            return rotateRight(root);
        else { // LR
            root-&gt;left = rotateLeft(root-&gt;left);
            return rotateRight(root);
        }
    }
    if (balance &lt; -1) {
        if (balanceFactor(root-&gt;right) &lt;= 0) // RR
            return rotateLeft(root);
        else { // RL
            root-&gt;right = rotateRight(root-&gt;right);
            return rotateLeft(root);
        }
    }
    return root;
}
void inorderTraversal(struct Node* root) {
    if (root != nullptr) {
        inorderTraversal(root-&gt;left);
        cout &lt;&lt; root-&gt;key &lt;&lt; &quot; &quot;;
        inorderTraversal(root-&gt;right);
    }
}
void freeTree(struct Node* root) {
    if (root != nullptr) {
        freeTree(root-&gt;left);
        freeTree(root-&gt;right);
        delete root;
    }
}
int main() {
    struct Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);

    root = insert(root, 25);
    cout &lt;&lt; &quot;In-order traversal of the AVL tree: &quot;;
    inorderTraversal(root);
    cout &lt;&lt; endl;
    root = deleteNode(root, 30);
    cout &lt;&lt; &quot;In-order traversal after deleting 30: &quot;;
    inorderTraversal(root);
    cout &lt;&lt; endl;
    freeTree(root);
    return 0;
}