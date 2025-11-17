#include<stdio.h>
#include<stdlib.h>

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[left] > arr[largest]) {
        largest = left;
    } 
    
    if(left < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if(largest != i) {
        swap(&arr[i], &arr[largest]);
        heapifyDown(arr, n, largest);
    }
}

void buildHeap(int arr[], int n) {
    int nonLeafIdx = (n / 2) - 1;

    for(int i = nonLeafIdx; i >= 0; i--) {
        heapifyDown(arr, n, i);
    }
}

int main() {
    int heap[100];
    int count;
    printf("Enter the number of elements you want to add");
    scanf("%d", &count);
    int c = count;

    printf("Enter the array elements");
    for(int i = 0; i < c; i++) {
        scanf("%d", &heap[i]);
    }
    
    count--;
    for(int i = 0; i < c; i++) {
        buildHeap(heap, count);
        swap(&heap[0], &heap[count]);
        count--;
    }

    printf("Array elements after sorting are");
    for(int i = 0; i < c; i++) {
        printf("%d", heap[i]);
    }
}