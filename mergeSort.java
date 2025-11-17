import java.util.Scanner;

class sort {
    public void merge(int [] array, int start, int mid, int end) {
        int n1 = mid - start + 1;
        int n2 = end - mid;

        int left[] = new int[n1];
        int right[] = new int[n2];

        for(int i = 0; i < n1; i++) {
            left[i] = array[start + i];
        }
        for(int j = 0; j < n2; j++) {
            right[j] = array[mid + 1 + j];
        }

        int i = 0, j = 0, k = start;
        while(i < n1 && j < n2) {
            if(left[i] <= right[j]) {
                array[k++] = left[i++];
            } else {
                array[k++] = right[j++];
            }
        }
            
        while(i < n1) {
            array[k++] = left[i++];
        }
        while(j < n2) {
            array[k++] = right[j++];
        }
    }

    void sortArray(int [] array, int start, int end) {
        if(start < end) {
            int mid = (start + end) / 2;
            sortArray(array, start, mid);
            sortArray(array, mid + 1, end);
            merge(array, start, mid, end);
        }
    }
}

class mergeSort {
    public static void main(String [] args){
        System.out.println("Enter the array length");
        Scanner sc = new Scanner(System.in);
        int length = sc.nextInt();
        int array [] = new int [length];
        System.out.println("Enter the array elements");

        for(int range = 0; range < length; range++) {
            array[range] = sc.nextInt();
        }

        sort obj = new sort();
        obj.sortArray(array, 0, length - 1);

        for(int index = 0; index < length; index++) {
            System.out.println(array[index]);
        }
    }
}