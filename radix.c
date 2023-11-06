#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define max(a, b) ((a) &gt; (b) ? (a) : (b))
struct Node
{
    int val;
    struct Node *next;
};
int findMax(int a[], int n)
{
    int m = INT_MIN;
    for (int i = 0; i &lt; n; i++)
    {
        m = max(a[i], m);
    }
    return m;
}
int countDigits(int x)
{
    int c = 0;
    while (x &gt; 0)
    {
        x /= 10;
        c++;
    }
    return c;
}
void Insert(struct Node **b, int value, int idx)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp-&gt;val = value;
    temp-&gt;next = NULL;
    if (b[idx] == NULL)

    {
        b[idx] = temp;
    }
    else
    {
        struct Node *p = b[idx];
        while (p-&gt;next != NULL)
        {
            p = p-&gt;next;
        }
        p-&gt;next = temp;
    }
}
int Delete(struct Node **b, int idx)
{
    struct Node *p = b[idx];
    b[idx] = b[idx]-&gt;next;
    int x = p-&gt;val;
    free(p);
    return x;
}
void radixSort(int a[], int n)
{
    int m = findMax(a, n);
    int nPass = countDigits(m);
    struct Node **posBin = (struct Node **)malloc(sizeof(struct Node) * 10);
    struct Node **negBin = (struct Node **)malloc(sizeof(struct Node) * 10);
   
    for (int i = 0; i &lt; 10; i++) posBin[i] = NULL;
    for (int i = 0; i &lt; 10; i++) negBin[i] = NULL;
   
    for (int i = 0; i &lt; nPass; i++)
    {
        for (int j = 0; j &lt; n; j++)
        {
            int binIdx;
            if (a[j] &gt;= 0) {
                binIdx = (int)(a[j] / pow(10, i)) % 10;
                Insert(posBin, a[j], binIdx);
            } else {
                binIdx = abs((int)(a[j] / pow(10, i)) % 10);
                Insert(negBin, a[j], binIdx);
            }
        }

        int j = 0;
        for (int i = 0; i &lt; 10; i++) {
            while (negBin[i] != NULL) {
                a[j++] = Delete(negBin, i);
            }
        }
       
        for (int i = 0; i &lt; 10; i++) {
            while (posBin[i] != NULL) {
                a[j++] = Delete(posBin, i);
            }
        }
    }
    free(posBin);
    free(negBin);
}
int main()
{
    int a[] = {11, 13, -7, 12, 16, 9, 24, 5, 10, 3, -25, -18, -3}, n = 13;
    radixSort(a, n);
    for (int i = 0; i &lt; n; i++)
        printf(&quot;%d &quot;, a[i]);
    printf(&quot;\n&quot;);
    return 0;
}

Output:

Q3)
Code:
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
struct Node {
    int row, col, value;
    struct Node* next;
};
void displaySparseMatrix(struct Node* head) {
    struct Node* current = head;

   
    while (current != NULL) {
        printf(&quot;Row: %d, Column: %d, Value: %d\n&quot;, current-&gt;row+1, current-
&gt;col+1, current-&gt;value);
        current = current-&gt;next;
    }
}
void insertSorted(struct Node** head, int row, int col, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode-&gt;row = row;
    newNode-&gt;col = col;
    newNode-&gt;value = value;
   
    if (*head == NULL || row &lt; (*head)-&gt;row || (row == (*head)-&gt;row &amp;&amp; col &lt;
(*head)-&gt;col)) {
        newNode-&gt;next = *head;
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current-&gt;next != NULL &amp;&amp; (row &gt; current-&gt;next-&gt;row || (row ==
current-&gt;next-&gt;row &amp;&amp; col &gt; current-&gt;next-&gt;col))) {
            current = current-&gt;next;
        }
        newNode-&gt;next = current-&gt;next;
        current-&gt;next = newNode;
    }
}
int main() {
    int numRows = 3, numCols = 4;
    int m[numRows][numCols];
    m[0][0] = 0; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
    m[1][0] = 1; m[1][1] = 5; m[1][2] = 0; m[1][3] = 0;
    m[2][0] = 0; m[2][1] = 0; m[2][2] = 0; m[2][3] = 8;
   
    struct Node* head = NULL;
   
    for (int i = 0; i &lt; numRows; i++) {
        for (int j = 0; j &lt; numCols; j++) {
            if (m[i][j] != 0) {
                insertSorted(&amp;head, i, j, m[i][j]);
            }
        }
    }
   
    printf(&quot;Linked List Representation of Sparse Matrix:\n&quot;);
    displaySparseMatrix(head);

   
    while (head != NULL) {
        struct Node* temp = head;
        head = head-&gt;next;
        free(temp);
    }
   
    return 0;