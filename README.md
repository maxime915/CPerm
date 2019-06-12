# CPerm

Generate all permutation of a random array in C.

## permBasic

Naive approach to get all permutation of an array, only print them but could easily be modified to do something else

## permStack

Implementation using Heap's algorithm see [some slide from princeton CS](http://www.cs.princeton.edu/~rs/talks/perms.pdf) and [wikipedia](https://en.wikipedia.org/wiki/Heap%27s_algorithm). Interface based on a stack-like object: each permutation can be given at any given time. However all permutation are not actually stored to reduce memory usage yet it's possible to get all of them at one.
