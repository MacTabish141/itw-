#include <stdio.h>
#include <stdlib.h>
struct node {
   int data;
   struct node *leftChild, *rightChild;
};
struct node* newNode(int data){
   struct node* Node = (struct node*)malloc(sizeof(struct node));
   Node-&gt;data = data;
   Node-&gt;leftChild = Node-&gt;rightChild = NULL;
   return (Node);
}
struct node* rightRotate(struct node *x){
   struct node *y = x-&gt;leftChild;
   x-&gt;leftChild = y-&gt;rightChild;
   y-&gt;rightChild = x;
   return y;
}
struct node* leftRotate(struct node *x){
   struct node *y = x-&gt;rightChild;
   x-&gt;rightChild = y-&gt;leftChild;
   y-&gt;leftChild = x;
   return y;
}
struct node* splay(struct node *root, int data){
   if (root == NULL || root-&gt;data == data)
      return root;
   if (root-&gt;data &gt; data) {
      if (root-&gt;leftChild == NULL) return root;
      if (root-&gt;leftChild-&gt;data &gt; data) {
         root-&gt;leftChild-&gt;leftChild = splay(root-&gt;leftChild-&gt;leftChild, data);
         root = rightRotate(root);
      } else if (root-&gt;leftChild-&gt;data &lt; data) {
         root-&gt;leftChild-&gt;rightChild = splay(root-&gt;leftChild-&gt;rightChild,
data);
         if (root-&gt;leftChild-&gt;rightChild != NULL)
            root-&gt;leftChild = leftRotate(root-&gt;leftChild);
      }

      return (root-&gt;leftChild == NULL)? root: rightRotate(root);
   } else {
      if (root-&gt;rightChild == NULL) return root;
      if (root-&gt;rightChild-&gt;data &gt; data) {
         root-&gt;rightChild-&gt;leftChild = splay(root-&gt;rightChild-&gt;leftChild,
data);
         if (root-&gt;rightChild-&gt;leftChild != NULL)
            root-&gt;rightChild = rightRotate(root-&gt;rightChild);
      } else if (root-&gt;rightChild-&gt;data &lt; data) {
         root-&gt;rightChild-&gt;rightChild = splay(root-&gt;rightChild-&gt;rightChild,
data);
         root = leftRotate(root);
      }
      return (root-&gt;rightChild == NULL)? root: leftRotate(root);
   }
}
struct node* insert(struct node *root, int k){
   if (root == NULL) return newNode(k);
   root = splay(root, k);
   if (root-&gt;data == k) return root;
   struct node *newnode = newNode(k);
   if (root-&gt;data &gt; k) {
      newnode-&gt;rightChild = root;
      newnode-&gt;leftChild = root-&gt;leftChild;
      root-&gt;leftChild = NULL;
   } else {
      newnode-&gt;leftChild = root;
      newnode-&gt;rightChild = root-&gt;rightChild;
      root-&gt;rightChild = NULL;
   }
   return newnode;
}
struct node* deletenode(struct node* root, int data){
   struct node* temp;
   if (root == NULL)
      return NULL;
   root = splay(root, data);
   if (data != root-&gt;data)
      return root;
   if (!root-&gt;leftChild) {
      temp = root;
      root = root-&gt;rightChild;
   } else {
      temp = root;
      root = splay(root-&gt;leftChild, data);
      root-&gt;rightChild = temp-&gt;rightChild;
   }
   free(temp);

   return root;
}
int height(struct node* node)
{
    if (node == NULL)
        return 0;
    else {
         
        // Compute the height of each subtree
        int lheight = height(node-&gt;leftChild);
        int rheight = height(node-&gt;rightChild);
 
        // Use the larger one
        if (lheight &gt; rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}
void printCurrentLevel(struct node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf(&quot;%d &quot;, root-&gt;data);
    else if (level &gt; 1) {
        printCurrentLevel(root-&gt;leftChild, level - 1);
        printCurrentLevel(root-&gt;rightChild, level - 1);
    }
}
void printLevelOrder(struct node* root)
{
    int h = height(root);
    int i;
    for (i = 1; i &lt;= h; i++){
        printCurrentLevel(root, i);
        printf(&quot;\n&quot;);
    }
}

int main(){
   struct node* root = newNode(34);
   root = insert(root,15);
   root = insert(root,40);
   root = insert(root,12);
   root = insert(root,14);
   root = insert(root,59);
   printf(&quot;The Splay tree is \n&quot;);

   printLevelOrder(root);
   root = deletenode(root, 40);
   printf(&quot;\nThe Splay tree after deletion is \n&quot;);
   printLevelOrder(root);
   return 0;
}

//TRIES

#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
// The number of children for each node
// We will construct a N-ary tree and make it
// a Trie
// Since we have 26 english letters, we need
// 26 children per node
#define N 26
typedef struct TrieNode TrieNode;
struct TrieNode {
    // The Trie Node Structure
    // Each node has N children, starting from the root
    // and a flag to check if it&#39;s a leaf node
    char data; // Storing for printing purposes only
    TrieNode* children[N];
    int is_leaf;
};
TrieNode* make_trienode(char data) {
    // Allocate memory for a TrieNode
    TrieNode* node = (TrieNode*) calloc (1, sizeof(TrieNode));
    for (int i=0; i&lt;N; i++)
        node-&gt;children[i] = NULL;
    node-&gt;is_leaf = 0;
    node-&gt;data = data;
    return node;
}

void free_trienode(TrieNode* node) {
    // Free the trienode sequence
    for(int i=0; i&lt;N; i++) {
        if (node-&gt;children[i] != NULL) {
            free_trienode(node-&gt;children[i]);
        }
        else {
            continue;
        }
    }
    free(node);
}
TrieNode* insert_trie(TrieNode* root, char* word) {
    // Inserts the word onto the Trie
    // ASSUMPTION: The word only has lower case characters
    TrieNode* temp = root;
    for (int i=0; word[i] != &#39;\0&#39;; i++) {
        // Get the relative position in the alphabet list
        int idx = (int) word[i] - &#39;a&#39;;
        if (temp-&gt;children[idx] == NULL) {
            // If the corresponding child doesn&#39;t exist,
            // simply create that child!
            temp-&gt;children[idx] = make_trienode(word[i]);
        }
        else {
            // Do nothing. The node already exists
        }
        // Go down a level, to the child referenced by idx
        // since we have a prefix match
        temp = temp-&gt;children[idx];
    }
    // At the end of the word, mark this node as the leaf node
    temp-&gt;is_leaf = 1;
    return root;
}
int search_trie(TrieNode* root, char* word)
{
    // Searches for word in the Trie
    TrieNode* temp = root;
    for(int i=0; word[i]!=&#39;\0&#39;; i++)
    {
        int position = word[i] - &#39;a&#39;;
        if (temp-&gt;children[position] == NULL)

            return 0;
        temp = temp-&gt;children[position];
    }
    if (temp != NULL &amp;&amp; temp-&gt;is_leaf == 1)
        return 1;
    return 0;
}
void print_trie(TrieNode* root) {
    // Prints the nodes of the trie
    if (!root)
        return;
    TrieNode* temp = root;
    printf(&quot;%c -&gt; &quot;, temp-&gt;data);
    for (int i=0; i&lt;N; i++) {
        print_trie(temp-&gt;children[i]);
    }
}
void print_search(TrieNode* root, char* word) {
    printf(&quot;Searching for %s: &quot;, word);
    if (search_trie(root, word) == 0)
        printf(&quot;Not Found\n&quot;);
    else
        printf(&quot;Found!\n&quot;);
}
int main() {
    // Driver program for the Trie Data Structure Operations
    TrieNode* root = make_trienode(&#39;\0&#39;);
    root = insert_trie(root, &quot;hello&quot;);
    root = insert_trie(root, &quot;hi&quot;);
    root = insert_trie(root, &quot;teabag&quot;);
    root = insert_trie(root, &quot;teacan&quot;);
    print_search(root, &quot;tea&quot;);
    print_search(root, &quot;teabag&quot;);
    print_search(root, &quot;teacan&quot;);
    print_search(root, &quot;hi&quot;);
    print_search(root, &quot;hey&quot;);
    print_search(root, &quot;hello&quot;);
    print_trie(root);
    free_trienode(root);
    return 0;
}