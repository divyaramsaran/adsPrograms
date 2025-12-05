#include <stdio.h>

void merge(int array[], int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int left[n1];   // VLA (stack allocation)
    int right[n2];  // VLA

    for (int i = 0; i < n1; i++)
        left[i] = array[start + i];

    for (int j = 0; j < n2; j++)
        right[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = start;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            array[k++] = left[i++];
        } else {
            array[k++] = right[j++];
        }
    }

    while (i < n1) {
        array[k++] = left[i++];
    }

    while (j < n2) {
        array[k++] = right[j++];
    }
}

void sortArray(int array[], int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        sortArray(array, start, mid);
        sortArray(array, mid + 1, end);
        merge(array, start, mid, end);
    }
}

int main() {
    int length;

    printf("Enter the array length:\n");
    scanf("%d", &length);

    int array[length];  // VLA instead of malloc

    printf("Enter the array elements:\n");
    for (int i = 0; i < length; i++) {
        scanf("%d", &array[i]);
    }

    sortArray(array, 0, length - 1);

    for (int i = 0; i < length; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}