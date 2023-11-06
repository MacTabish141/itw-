#include <stdio.h>
#include <stdlib.h>
struct Node {
    int row, col, value;
    struct Node* next;
};
void insert(struct Node** head, int row, int col, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode-&gt;row = row;
    newNode-&gt;col = col;
    newNode-&gt;value = value;
    newNode-&gt;next = *head;
    *head = newNode;
}
int countLadders(struct Node* head, int threshold) {
    int count = 0;
    while (head != NULL) {
        if (head-&gt;value &gt;= threshold) {
            count++;
        }
        head = head-&gt;next;
    }
    return count;
}
void printLadderCoordinates(struct Node* head, int threshold) {
    printf(&quot;Ladder Coordinates (Value &gt;= %d):\n&quot;, threshold);
    while (head != NULL) {
        if (head-&gt;value &gt;= threshold) {
            printf(&quot;(%d, %d) = %d\n&quot;, head-&gt;row, head-&gt;col, head-&gt;value);
        }
        head = head-&gt;next;
    }
}
int main() {
    int rows, cols, threshold;
    printf(&quot;Enter the number of rows and columns of the matrix: &quot;);
    scanf(&quot;%d %d&quot;, &amp;rows, &amp;cols);
    printf(&quot;Enter the threshold value for ladders: &quot;);

    scanf(&quot;%d&quot;, &amp;threshold);
    struct Node* head = NULL;
    printf(&quot;Enter the matrix elements:\n&quot;);
    for (int i = 0; i &lt; rows; i++) {
        for (int j = 0; j &lt; cols; j++) {
            int value;
            scanf(&quot;%d&quot;, &amp;value);
            if (value != 0) {
                insert(&amp;head, i, j, value);
            }
        }
    }
    int ladderCount = countLadders(head, threshold);
    printf(&quot;Number of ladders: %d\n&quot;, ladderCount);
    if (ladderCount &gt; 0) {
        printLadderCoordinates(head, threshold);
    }
    while (head != NULL) {
        struct Node* temp = head;
        head = head-&gt;next;
        free(temp);
    }
    return 0;
}