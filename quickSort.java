import java.util.Scanner;

class sort {
    
    int partition (int [] array, int lower, int upper) {
        int pivot = array[upper];
        // System.out.println("lower" + lower);
        int i = (lower - 1);
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

    void quickSort (int [] array, int lower, int upper) {
        if (lower < upper) {
            int pivot = partition(array, lower, upper);
            quickSort(array, lower, pivot - 1);
            quickSort(array, pivot + 1, upper);
        }
    }

    void displayArray(int[] array) {
        for (int i : array) {
            System.out.print(i + " ");
        }
        System.out.println();
    }

    void sortArray(int[] array) {
        quickSort(array, 0, array.length - 1);
        System.out.println("Sorted array:");
        displayArray(array);
    }

}

public class quickSort {
    public static void main(String args []) {
        System.out.println("Enter the length of the array");
        Scanner sc = new Scanner(System.in);
        int length = sc.nextInt();
        System.out.println("Enter the array elements");
        int arrary [] = new int[length];
        
        for(int i = 0; i < length; i++) {
            arrary[i] = sc.nextInt();
        }

        sort sorter = new sort();
        sorter.sortArray(arrary);
    }
}