#include "permStack.h"

#include <stdio.h>

// SECTION maths

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

// SECTION definition

struct perm_stack_t {
    // store the array
    TYPE *array;
    size_t length;

    // state of the object
    bool ready;
    bool finished;

    // permutation counters
    size_t *c;
    size_t n;
};

// SECTION static methods - prototypes

static void swap(TYPE *array, size_t i, size_t j);
static void beReady(PermStack *p);
static TYPE *getCopyOfArray(TYPE *array, size_t length);

// SECTION constructors

PermStack *PScreate(TYPE *array, size_t length) {

    if (length < 1)
        return NULL;

    PermStack *p = (PermStack *)malloc(sizeof(PermStack));

    if (p == NULL)
        return NULL;

    p->ready = false;
    p->finished = false;
    p->c = NULL;
    p->length = length;
    p->array = (TYPE *)malloc(length * sizeof(TYPE));

    if (p->array == NULL) {
        // DEBUG;
        free(p);
        return NULL;
    }

    for (size_t i = 0; i < length; i++) {
        p->array[i] = array[i];
    }

    return p;
}

// SECTION destructor

void PSfree(PermStack *p) {
    if (p == NULL)
        return;

    // don't free each element as they were not allocated in this file
    if (p->array != NULL) {
        // DEBUG;
        free(p->array);
    }

    if (p->c != NULL) {
        // DEBUG;
        free(p->c);
    }

    // DEBUG;
    free(p);
}

// SECTION methods

TYPE *PSPop(PermStack *p) {
    if (p->finished)
        return NULL;

    if (!p->ready) {

        beReady(p);

        if (!p->ready) { // beReady() set p->ready to false in case of failure
            fprintf(stderr, "WARNING: could not get PermStack ready (returning NULL)");
            return NULL;
        }

        // p is now ready, return the copy of the array
        return getCopyOfArray(p->array, p->length);
    }

    // p is ready -> get next perm

    // -> the else block in the algorithm
    while (!(p->c[p->n] < p->n)) {
        p->c[p->n] = 0;
        p->n++;
    }

    // -> the if block in the algorithm
    swap(p->array, (p->n % 2) == 0 ? 0 : p->c[p->n], p->n);

    // update finished
    if (p->n == p->length - 2 && p->c[p->length - 1] == p->length - 1)
        p->finished = true;

    p->c[p->n]++;
    p->n = 0;

    return getCopyOfArray(p->array, p->length);
}

TYPE **PSGetAllPerms(PermStack *p) {
    size_t l = fact(p->length);
    TYPE **r = (TYPE **)malloc(l * sizeof(TYPE *));
    if (r == NULL)
        exit(1);

    size_t *c = (size_t *)calloc(p->length, sizeof(size_t));
    if (c == NULL) {
        free(r);
        return NULL;
    }

    size_t counter = 0;
    r[counter++] = getCopyOfArray(p->array, p->length);

    for (size_t i = 0; i < p->length;) {
        if (c[i] < i) {
            swap(p->array, (i % 2) == 0 ? 0 : c[i], i);

            // add permutation
            r[counter++] = getCopyOfArray(p->array, p->length);

            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }

    return r;
}

bool PSIsFinished(PermStack *p) {
    return p->finished;
}

void PSRestart(PermStack *p) {
    p->finished = false;
    p->ready = false;
}

// SECTION static methods - definition

static void swap(TYPE *array, size_t i, size_t j) {
    TYPE temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

static void beReady(PermStack *p) {
    // prevent memory leaks
    if (p->c != NULL) {
        // DEBUG;
        free(p->c);
        // DEBUG;
    }

    p->c = (size_t *)calloc(p->length, sizeof(size_t));
    p->n = 0;

    // indicate failure
    p->ready = p->c != NULL;
}

static TYPE *getCopyOfArray(TYPE *array, size_t length) {
    TYPE *copy = (TYPE *)malloc(length * sizeof(TYPE));
    if (copy == NULL)
        return NULL;

    for (size_t i = 0; i < length; i++)
        copy[i] = array[i];

    return copy;
}
