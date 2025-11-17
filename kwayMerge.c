#include <stdio.h>

int main() {
    int k, n;

    printf("Enter the number of arrays (k): ");
    scanf("%d", &k);

    printf("Enter the number of elements in each array (n): ");
    scanf("%d", &n);

    int arr[50][50];
    int pos[50] = {0};
    int merged[500];
    int total = k * n;
    int idx = 0;

    // Input arrays
    for (int i = 0; i < k; i++) {
        printf("Enter %d sorted elements for array %d: ", n, i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    for (int count = 0; count < total; count++) {
        int minArr = -1;

        // Find the first non-exhausted array to initialize minArr
        for (int i = 0; i < k; i++) {
            if (pos[i] < n) {
                minArr = i;
                break;
            }
        }

        // Compare remaining arrays to find actual minimum
        for (int i = 0; i < k; i++) {
            if (pos[i] < n && arr[i][pos[i]] < arr[minArr][pos[minArr]]) {
                minArr = i;
            }
        }

        merged[idx++] = arr[minArr][pos[minArr]];
        pos[minArr]++;
    }

    // Output merged array
    printf("\nMerged and Sorted Array:\n");
    for (int i = 0; i < total; i++) {
        printf("%d ", merged[i]);
    }

    return 0;
}