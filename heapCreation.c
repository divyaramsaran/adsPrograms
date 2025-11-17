#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify down (used in delete and build heap)
void heapifyDown(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    // Check if left child exists and is greater than root
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    // Check if right child exists and is greater than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapifyDown(arr, n, largest);
    }
}

// Heapify up (used in insert)
void heapifyUp(int arr[], int i) {
    int parent = (i - 1) / 2;
    
    // If current node is greater than parent, swap and continue
    if (i > 0 && arr[i] > arr[parent]) {
        swap(&arr[i], &arr[parent]);
        heapifyUp(arr, parent);
    }
}

// Build heap from an array
void buildHeap(int arr[], int n) {
    // Start from last non-leaf node and heapify all nodes
    int startIdx = (n / 2) - 1;
    
    for (int i = startIdx; i >= 0; i--) {
        heapifyDown(arr, n, i);
    }
}

// Insert element into heap
void insert(int arr[], int *n, int key) {
    if (*n >= MAX_SIZE) {
        printf("Heap overflow! Cannot insert.\n");
        return;
    }
    
    // Insert new element at end
    (*n)++;
    int i = *n - 1;
    arr[i] = key;
    
    // Fix the heap property by bubbling up
    heapifyUp(arr, i);
    
    printf("Inserted %d successfully!\n", key);
}

// Delete root (maximum element) from heap
int deleteRoot(int arr[], int *n) {
    if (*n <= 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    
    if (*n == 1) {
        (*n)--;
        return arr[0];
    }
    
    // Store root and replace with last element
    int root = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    
    // Heapify down from root
    heapifyDown(arr, *n, 0);
    
    return root;
}

// Display heap
void displayHeap(int arr[], int n) {
    if (n == 0) {
        printf("Heap is empty!\n");
        return;
    }
    
    printf("Heap elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int heap[MAX_SIZE];
    int n = 0;
    int choice, value, numElements;
    
    printf("=== Max Heap Implementation ===\n\n");
    
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Create heap from list\n");
        printf("2. Insert element\n");
        printf("3. Delete root (max element)\n");
        printf("4. Display heap (array)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter number of elements: ");
                scanf("%d", &numElements);
                
                if (numElements > MAX_SIZE) {
                    printf("Too many elements! Max allowed: %d\n", MAX_SIZE);
                    break;
                }
                
                printf("Enter %d elements:\n", numElements);
                for (int i = 0; i < numElements; i++) {
                    scanf("%d", &heap[i]);
                }
                n = numElements;
                
                buildHeap(heap, n);
                printf("Heap created successfully!\n");
                displayHeap(heap, n);
                break;
                
            case 2:
                printf("Enter element to insert: ");
                scanf("%d", &value);
                insert(heap, &n, value);
                displayHeap(heap, n);
                break;
                
            case 3:
                value = deleteRoot(heap, &n);
                if (value != -1) {
                    printf("Deleted root element: %d\n", value);
                    displayHeap(heap, n);
                }
                break;
                
            case 4:
                displayHeap(heap, n);
                break;
                
            case 5:
                printf("Exiting program. Goodbye!\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}