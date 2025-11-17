#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data;
    int priority;
} Element;

Element pq[MAX];
int size = 0;

// Insert at the end (unordered)
void insert(int val, int prio) {
    if (size == MAX) {
        printf("Queue Overflow\n");
        return;
    }
    pq[size].data = val;
    pq[size].priority = prio;
    size++;
    printf("Inserted: %d (Priority: %d)\n", val, prio);
}

// Delete element with highest priority (smallest priority value)
void delete() {
    if (size == 0) {
        printf("Queue Underflow\n");
        return;
    }
    int i, minIndex = 0;
    for (i = 1; i < size; i++) {
        if (pq[i].priority < pq[minIndex].priority)
            minIndex = i;
    }
    printf("Deleted: %d (Priority: %d)\n", pq[minIndex].data, pq[minIndex].priority);
    pq[minIndex] = pq[size - 1];
    size--;
}

// Display the priority queue
void display() {
    if (size == 0) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Priority Queue (Unordered):\n");
    for (int i = 0; i < size; i++)
        printf("Data: %d  Priority: %d\n", pq[i].data, pq[i].priority);
}

int main() {
    int choice, val, prio;
    while (1) {
        printf("\n1. Insert\n2. Delete (highest priority)\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data and priority: ");
                scanf("%d %d", &val, &prio);
                insert(val, prio);
                break;
            case 2:
                delete();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}