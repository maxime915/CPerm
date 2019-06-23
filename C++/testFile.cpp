#include "permStack.hpp"
#include <cstddef>

#include <iostream>

using namespace std;

void printArray(int *arr, unsigned l) {
    cout << "array of size " << l << " : {";
    for (unsigned i = 0; i < l - 1; i++)
        cout << arr[i] << ", ";
    cout << arr[l - 1] << "}" << endl;
}

int main(int argc, char const *argv[]) {
    unsigned l = 4;
    int arr[] = {1, 2, 3, 4};
    PermStack<int> p(arr, l);
    int **t = p.getAllPerms();
    unsigned count = p.countPermutations();
    for (unsigned i = 0; i < count; i++) {
        printArray(t[i], l);
        delete t[i];
    }
    delete t;
    return 0;
}
