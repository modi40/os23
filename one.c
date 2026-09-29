#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void bubble_sort(int arr[], int n) {
int i, j, t;
for(i = 0; i < n - 1; i++) {
for(j = 0; j < n - i - 1; j++) {
if(arr[j] > arr[j + 1]) {
t = arr[j];
arr[j] = arr[j + 1];
arr[j + 1] = t;
}
}
}
}
void insertion_sort(int arr[], int n) {
int i, j, key;
for(i = 1; i < n; i++) {
key = arr[i];
j = i - 1;
while(j >= 0 && arr[j] > key) {
arr[j + 1] = arr[j];
j--;
}
arr[j + 1] = key;
}
}
int main() {
int n, i;
printf("Enter number of integers: ");
if(scanf("%d", &n) != 1) return 0;
int arr[100];
printf("Enter %d integers: ", n);
for(i = 0; i < n; i++) scanf("%d", &arr[i]);
pid_t pid = fork();
if(pid < 0) {
perror("Fork failed");
exit(1);
}
if(pid == 0) {
insertion_sort(arr, n);
printf("Child Process (PID: %d) - Sorted using Insertion Sort:\n", getpid());
for(i = 0; i < n; i++) printf("%d ", arr[i]);
printf("\n");
exit(0);
} else {
wait(NULL);
bubble_sort(arr, n);
printf("Parent Process (PID: %d) - Sorted using Bubble Sort:\n", getpid());
for(i = 0; i < n; i++) printf("%d ", arr[i]);
printf("\n");
}
return 0;
}
