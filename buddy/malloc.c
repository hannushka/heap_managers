//Buddy system version

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define N 1024 //Memory size
#define BLOCK_SIZE (1L << 32)

//Data structures
typedef struct list_t list_t;

struct list_t
{
  unsigned free:1; /* one if free. */
  size_t   size; //size including list_t
  list_t*  succ;       /* successor block in list. */
  list_t*  pred;       /* predecessor block in list. */
  char     data[];
}

void *global_head = NULL;

void allocate_block()
{

}

/*Keep a linked list (n) for each possible memory size 2^n == memory size.
All empty except for the largest memory size which has a block*/
void* list[N];

void *malloc(size_t size)
{
	/*Round size up to power of two = y
	Check if available block of resulting size by taking the log base 2 of y
	In C you can write = log(x)/log(2)
	to get the free list number.
	Otherwise check upwards in sizes, splitting each in two
	If no space return null*/
  if (global_head == NULL) {
    allocate_block(BLOCK_SIZE);
  }
}

void *calloc(size_t nitems, size_t size)
{
  void *memory = malloc(nitems * size);

	if(memory != NULL)
	{
		memset(memory, 0, nitems * size);
	}

	return *memory;
}

void *realloc(void *ptr, size_t size)
{
  void *new_memory = malloc(size);

	if(new_memory != NULL)
	{
		memmove(new_memory, ptr, size_t __len, size);
		free(ptr);
	}
	return new_memory;
}

void free(void *ptr)
{
	/*If buddy also free => merge the blocks and recurse until no free buddy
	add the resulting block to list
	Else add block to list*/
}
