#include <stdio.h>
#define MAX 100
int size = 0;
int arr[MAX];
void insert(int val) {
size = size + 1;
int index = size;
arr[index] = val;
while (index &gt; 1) {
int parent = index / 2;
if (arr[parent] &gt; arr[index]) {
int temp = arr[parent];
arr[parent] = arr[index];
arr[index] = temp;
}
index = parent;
}
}
void print() {
for (int index = 1; index &lt;= size; index++) {
printf(&quot;%d &quot;, arr[index]);
}
printf(&quot;\n&quot;);
}
void delete() {
if (size == 0) {
printf(&quot;nothing to delete&quot;);
return;
}
arr[1] = arr[size];
size--;
int i = 1;
while (i &lt; size) {
int lefti = 2 * i;
int righti = 2 * i + 1;
if (lefti &lt; size &amp;&amp; arr[i] &gt; arr[lefti]) {
int temp = arr[lefti];

arr[lefti] = arr[i];
arr[i] = temp;
i = lefti;
} else if (righti &lt; size &amp;&amp; arr[i] &gt; arr[righti]) {
int temp = arr[righti];
arr[righti] = arr[i];
arr[i] = temp;
i = righti;
} else {
return;
}
}
}
void heapify(int arr[], int n, int i) {
int small = i;
int left = 2 * i;
int right = 2 * i + 1;
if (left &lt;= n &amp;&amp; arr[i] &gt; arr[left]) {
small = left;
}
if (right &lt;= n &amp;&amp; arr[small] &gt; arr[right]) {
small = right;
}
if (small != i) {
int temp = arr[small];
arr[small] = arr[i];
arr[i] = temp;
heapify(arr, n, small);
}
}
void heapsort(int arr[], int n) {
int size = n;
while (size &gt; 1) {
int temp = arr[size];
arr[size] = arr[1];
arr[1] = temp;
size--;
heapify(arr, size, 1);
}
}
int main() {
insert(50);
insert(55);
insert(53);
insert(52);

insert(54);
print();
delete();
print();
int input_arr[6] = {-1, 54, 53, 55, 52, 50};
int n = 5;
for (int i = n / 2; i &gt; 0; i--)
heapify(input_arr, n, i);
for (int i = 1; i &lt;= n; i++) {
printf(&quot;%d &quot;, input_arr[i]);
}
heapsort(input_arr, n);
printf(&quot;\nsorted array:\n&quot;);
for (int i = 1; i &lt;= n; i++) {
printf(&quot;%d &quot;, input_arr[i]);
}
return 0;
}