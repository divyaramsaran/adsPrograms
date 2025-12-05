#include <stdio.h>

/* Partition function (same logic as Java version) */
int partition(int array[], int lower, int upper) {
    int pivot = array[upper];
    int i = lower - 1;

    for (int j = lower; j < upper; j++) {
        if (array[j] < pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[upper];
    array[upper] = temp;

    return i + 1;
}

/* Recursive QuickSort */
void quickSort(int array[], int lower, int upper) {
    if (lower < upper) {
        int pivotIndex = partition(array, lower, upper);
        quickSort(array, lower, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, upper);
    }
}

int main() {
    int length;

    printf("Enter the length of the array:\n");
    scanf("%d", &length);

    int array[length];   // VLA just like previous code

    printf("Enter the array elements:\n");
    for (int i = 0; i < length; i++) {
        scanf("%d", &array[i]);
    }

    quickSort(array, 0, length - 1);

    printf("Sorted array:\n");
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
