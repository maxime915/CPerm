#include <stdbool.h>
#include <stdlib.h>

// SECTION macros
#define DEBUG fprintf(stderr, "This is line %d of file %s (function %s)\n",\
                      __LINE__, __FILE__, __func__)

/**
 * PermStack - generate each permuation one by one using Heap's algortihm
 * source: http://www.cs.princeton.edu/~rs/talks/perms.pdf
 * and: https://en.wikipedia.org/wiki/Heap%27s_algorithm
 */

typedef int* TYPE;

typedef struct perm_stack_t PermStack;

// Create and destroy a new PermStack
PermStack *PScreate(TYPE *array, size_t length);
void PSfree(PermStack *p);

// get a permutation (first one is the original array)
TYPE *PSPop(PermStack *p);

// get an array (of size fact(length)) containing all permutations
TYPE **PSGetAllPerms(PermStack *p);

//
bool PSIsFinished(PermStack *p);

// restart the permutation (NOTE: do not actually go back to the given permutation)
void PSReastart(PermStack *p);
