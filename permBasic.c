#include "permBasic.h"

void swap(int arr[], int i, int j) {
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void printAllPermutationREC(int arr[], int k, int length) {
    if (k >= length)
        return;
    if (k == length - 1)
        printArray(arr, length);

    for (int i = k; i < length; i++) {
        int *copy = copyOfArray(arr, length);
        swap(copy, k, i);
        printAllPermutationREC(copy, k + 1, length);
        free(copy);
    }
}

void printAllPermutation(int arr[], int length) {
    if (length < 1)
        return;

    if (length == 1) {
        fprintf(stdout, "{%d}\n", arr[0]);
        return;
    }

    printAllPermutationREC(arr, 0, length);
}

void printArray(int arr[], int length) {
    printf("{");
    for (int i = 0; i < length - 1; i++)
        printf("%d, ", arr[i]);
    printf("%d };\n", arr[length - 1]);
}

int *copyOfArray(int arr[], int length) {
    int *c = (int *)malloc(length * sizeof(int));
    if (c == NULL)
        exit(1);
    for (int i = 0; i < length; i++)
        c[i] = arr[i];
    return c;
}
