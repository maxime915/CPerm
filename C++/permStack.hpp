#ifndef __permstack_hpp__
#define __permstack_hpp__

#include <assert.h>
#include <cstddef>

template <typename T>
class PermStack {
private:
    // store a copy of the array
    T *array;
    unsigned length;

    // state of the object
    bool ready;
    bool finished;

    // permutation counters
    unsigned *c;
    unsigned n;

    // get ready
    void beReady();

public:
    // Create a new PermStack
    PermStack(T arr[], unsigned s);
    ~PermStack();

    // get a permutation (first one is the original array)
    T *pop();

    // get an array (of size fact(length)) containing all permutations
    T **getAllPerms();

    // get number of possible permutation (n!)
    unsigned countPermutations();

    // get the length of a popped array (same as the given length)
    unsigned getArraySize();

    // return false if the stack can be popped (call restart to re-use)
    bool isFinished();

    // restart the permutation (NOTE: do not actually go back to the first given permutation)
    void restart();
};

// SECTION maths

static unsigned fact(unsigned i) {
    if (i < 3)
        return i;
    unsigned result = 1, next_result;
    while (i > 1) {
        next_result = i * result;
        assert(next_result / i == result);
        i--;
        result = next_result;
    }
    return result;
}

// SECTION function

template <typename T>
void swap(T *array, unsigned i, unsigned j) {
    T temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}
template <typename T>
T *getCopyOfArray(T *array, unsigned length) {
    T *copy = new T[length];
    for (unsigned i = 0; i < length; i++)
        copy[i] = array[i];
    return copy;
}

// SECTION methods

template <typename T>
PermStack<T>::PermStack(T arr[], unsigned s) {
    array = new T[s];
    length = s;
    for (unsigned i = 0; i < s; i++)
        array[i] = arr[i];

    ready = false;
    finished = false;

    c = new unsigned[s];
    n = 0;
}

template <typename T>
PermStack<T>::~PermStack() {
    delete array;
    delete c;
}

template <typename T>
T *PermStack<T>::pop() {
    if (finished)
        return NULL;

    if (!ready) {
        beReady();
        return getCopyOfArray(array, length);
    }

    // -> the else block in the algorithm
    while (!(c[n] < n)) {
        c[n] = 0;
        n++;
    }

    // -> the if block in the algorithm
    swap(array, (n % 2) == 0 ? 0 : c[n], n);

    // update finished
    if (n == length - 2 && c[length - 1] == length - 1)
        finished = true;

    c[n]++;
    n = 0;

    return getCopyOfArray(array, length);
}

template <typename T>
T **PermStack<T>::getAllPerms() {
    unsigned l = fact(length);
    T **r = new T *[l];

    unsigned c[length];
    for (unsigned i = 0; i < length; i++)
        c[i] = 0;

    // copy of array to prevent change to array
    T *arrayC = getCopyOfArray(array, length);

    unsigned counter = 0;
    r[counter++] = getCopyOfArray(arrayC, length);

    for (unsigned i = 0; i < length;) {
        if (c[i] < i) {
            swap(arrayC, (i % 2) == 0 ? 0 : c[i], i);

            // add permutation
            r[counter++] = getCopyOfArray(arrayC, length);

            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }

    delete arrayC;

    return r;
}

template <typename T>
unsigned PermStack<T>::countPermutations() {
    return fact(length);
}

template <typename T>
unsigned PermStack<T>::getArraySize() {
    return length;
}

template <typename T>
bool PermStack<T>::isFinished() {
    return finished;
}

template <typename T>
void PermStack<T>::restart() {
    finished = false;
    ready = false;
}

// SECTION private methods
template <typename T>
void PermStack<T>::beReady() {
    for (unsigned i = 0; i < length; i++)
        c[i] = 0;
    n = 0;
    ready = true;
    finished = false;
}

#endif // !__permstack_hpp__