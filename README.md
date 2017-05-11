# heap_managers
1. The task is to implement two versions of malloc/calloc/realloc and free.
2. One should be a linked-list implementation and the other an implementation of the buddy system.
3. You need to use sbrk to allocate memory from the kernel on Linux for the list version and increment the heap size in suitable steps. For the buddy system, you are allowed to allocate a sufficiently large block at once.
4. At a free, you must merge adjacent unallocated blocks in the list version and buddies in the buddy version.
5. Your implementations should work with gawk. Use any version.
6. Download gawk and type configure and make check.
7. Then edit the Makefile to use your malloc implementation. To edit the Makefile, look for places where version is used and add your file in the same way.
8. Then type make check again.
9. Repeat for your other malloc implementation.

#AWK tutorial:

https://www.math.utah.edu/docs/info/gawk_3.html#SEC13
