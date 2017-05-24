//Buddy system version

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>

#define N 10 //Memory size (index)
#define MIN_SIZE 1; //1K is minimum block size
#define LIST_T_SIZE sizeof(list_t)
#define MAX_SIZE (1L << N)

//Data structures
typedef struct list_t list_t;

struct list_t
{
  unsigned free:1;     /* one if free. */
  size_t   size;       /* size including list_t */
  list_t*  succ;       /* successor block in list. */
  list_t*  pred;       /* predecessor block in list. */
  char     data[];
};

list_t* free_list[N];
unsigned int init = 1;

/*Keep a linked list (n) for each possible memory size 2^n == memory size.
All empty except for the largest memory size which has a block*/

void init_blocks()
{
  list_t* block = sbrk(0);
	void* req = sbrk(MAX_SIZE);
	if (req == (void*) -1) {
		return;
	}
  block->size = N;
  block->free = 1;
	block->pred = NULL;
	block->succ = NULL;

  free_list[N-1] = block;
}

size_t rounded_size(size_t size)
{
  size_t rounded_size = MIN_SIZE;
  while (rounded_size < MAX_SIZE && rounded_size < size) {
    rounded_size *= 2;
  }
  return rounded_size;
}

//Recursive method
list_t* recursive_alloc(size_t index, size_t start, size_t size)
{
  list_t* avail = free_list[index];
  //Remove from the freelist
  free_list[index] = free_list[index]->succ;

  if (index > N-1)
  {
    return NULL;
  }

  //If the block has the same size as the expected size
  if (index == start) {
    avail->free = 0;
    if (avail->succ != NULL) {
      avail->succ->pred = NULL;
      avail->succ = NULL;
    }

    return avail;
  }

  if (avail->succ != NULL) {
    avail->succ->pred = NULL;
  }

	//Split into two blocks
	unsigned int new_size = (avail->size)/2;

	list_t* first_half = avail;
	list_t* second_half = avail + new_size;

	first_half->free = 1;
	first_half->size = new_size;
	first_half->pred = NULL;
	first_half->succ = second_half;

	second_half->free = 1;
	second_half->size = new_size;
	second_half->pred = first_half;
	second_half->succ = NULL;

	//Add the element with half the size to the list
	free_list[index-1] = first_half;

  return recursive_alloc(index-1, start, new_size);
}

list_t* allocate_memory(size_t index, size_t size)
{
  size_t start_index = index;
  list_t* avail = free_list[index];
	while (avail == NULL && index < N) {
		index++;
	  avail = free_list[index];
	}

  if (!avail) {
    return NULL;
  }

  return recursive_alloc(index, start_index, size);
}

void *malloc(size_t size)
{
	/*Round size up to power of two = y
	Check if available block of resulting size by taking the log base 2 of y
	In C you can write = log(x)/log(2)
	to get the free list number.
	Otherwise check upwards in sizes, splitting each in two
	If no space return null*/
  if (size <= 0 || size > MAX_SIZE)
    return NULL;

  if (init) {
    init_blocks();
    init = 0;
  }

  size_t r_size = rounded_size(size);
  size_t index = log(r_size)/log(2);
  list_t* block = allocate_memory(index - 1, r_size);

	return (void*) block;
}

void *calloc(size_t nitems, size_t size)
{
	void *memory = malloc(nitems * size);

	if(memory != NULL)
		memset(memory, 0, nitems * size);
	return memory;
}

void *realloc(void *ptr, size_t size)
{
	void *new_memory = malloc(size);

	if (new_memory != NULL) {
		memmove(new_memory, ptr, size);
		free(ptr);
	}
	return new_memory;
}

void free(void *ptr)
{
	/*If buddy also free => merge the blocks and recurse until no free buddy
	add the resulting block to list
	Else add block to list*/

  if (ptr == NULL) {
        return;
  }

  list_t* block_ptr = (list_t*)ptr-1;
	block_ptr->free = 1;

}
