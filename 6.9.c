#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void bubbleSort(int arr[], int n, int descending) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (descending) {
                if (arr[j] < arr[j + 1]) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            } else {
                
                if (arr[j] > arr[j + 1]) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    int n = atoi(argv[1]);
    int descending = 0; 
    
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            descending = 1;
            break;
        }
    }
    
    if (n <= 0) {
        return 1;
    }
    
    int *numbers = (int*)malloc(n * sizeof(int));
    if (numbers == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    
    bubbleSort(numbers, n, descending);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    free(numbers);
    
    return 0;
}