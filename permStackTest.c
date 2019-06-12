#include "permStack.h"
#include <stdio.h>

static size_t fact(size_t i) {
    if (i < 0)
        exit(1);
    if (i < 3)
        return i;
    size_t result = 1, next_result;
    while (i > 1) {
        next_result = i * result;
        if (next_result / i != result)
            exit(1);
        i--;
        result = next_result;
    }
    return result;
}

static void printArray(TYPE *array, size_t length) {
    fprintf(stderr, "{");
    for (size_t i = 0; i < length - 1; i++)
        fprintf(stderr, "%p, ", array[i]);
    fprintf(stderr, "%p};\n", array[length - 1]);
}

int main(int argc, const char *argv[]) {
    size_t length = 3;
    TYPE *array = (TYPE *)malloc(length * sizeof(TYPE));
    for (int i = 0; i < length; i++)
        array[i] = (TYPE)malloc(sizeof(int));

    PermStack *p = PScreate(array, length);

    // Do it one by one

    while (!PSIsFinished(p)) {
        TYPE *copy = PSPop(p);
        if (copy == NULL) {
            fprintf(stderr, "got null output\n");
            continue;
        }
        printArray(copy, length);
        free(copy);
    }

    //  Use restart

    // PSRestart(p);
    // fprintf(stderr, "\nrestarting!\n\n");
    // while (!PSIsFinished(p)) {
    //     TYPE *copy = PSPop(p);
    //     if (copy == NULL) {
    //         fprintf(stderr, "got null output\n");
    //         continue;
    //     }
    //     printArray(copy, length);
    //     free(copy);
    // }

    // get all at once

    // TYPE **list = PSGetAllPerms(p);
    // if (list == NULL) {
    //     fprintf(stderr, "got null pointer\n");
    //     exit(1);
    // }
    // size_t N = fact(length);
    // for (size_t i = 0; i < N; i++) {
    //     fprintf(stderr, "trying for i=%zu / %zu\n", i, N);
    //     printArray(list[i], length);
    //     free(list[i]);
    // }
    // free(list);

    // clear

    PSfree(p);
    for (int i = 0; i < length; i++)
        free(array[i]);
    free(array);
    return 0;
}
