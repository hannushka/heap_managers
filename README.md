# heap_managers
The task is to implement two versions of malloc/calloc/realloc and free.

One should be a linked-list implementation and the other an implementation of the buddy system.

You need to use sbrk to allocate memory from the kernel on Linux for the list version and increment the heap size in suitable steps. For the buddy system, you are allowed to allocate a sufficiently large block at once.

At a free, you must merge adjacent unallocated blocks in the list version and buddies in the buddy version.

Your implementations should work with gawk. Use any version.
Download gawk and type configure and make check.

Then edit the Makefile to use your malloc implementation. To edit the Makefile, look for places where version is used and add your file in the same way.

Then type make check again.

Repeat for your other malloc implementation. 
