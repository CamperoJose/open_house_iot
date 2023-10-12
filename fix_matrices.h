#define N 8

void reverseOddRows(int arr[][N], int n) {
    for (int i = 0; i < n; i++) {
        if (i % 2 == 1) {
            int start = 0;
            int end = n - 1;
            while (start < end) {
                int temp = arr[i][start];
                arr[i][start] = arr[i][end];
                arr[i][end] = temp;
                start++;
                end--;
            }
        }
    }
}
