# CPerm

Generate all permutation of a random array in C.

## permBasic

Naive approach to get all permutation of an array, only print them but could easily be modified to do something else

## permStack

Implementation using Heap's algorithm see [some slide from princeton CS](http://www.cs.princeton.edu/~rs/talks/perms.pdf) and [wikipedia](https://en.wikipedia.org/wiki/Heap%27s_algorithm). Interface based on a stack-like object: each permutation can be given at any given time.

### Interface

* The structure works on a generic type called `TYPE` defined in the header file, it's by default set to `int *` but you way change it as you wish
* The function `PScreate` create a new `permStack` using an array (will be copied) and `PSfree` destroy it
* The function `PSPop` returns a new permutation if it's not finished (see `PSIsFinished`) i.e. if all permutation were not yet given
* The function `PSGetAllPerms` returns a list of all possible permutation (NB: may be very memory intensive for large array) (NB: this function can be called wheter the structure is declared finished or not)
* The function `PSIsFinished` returns `true` if a new permutation can be given
* The function `PSRestart` must be used on a finished structure for this structure to be able to pop again (NB: the order after a restart is not the same as the intial order, it seems to be reversed but further investigations may help to understand why)