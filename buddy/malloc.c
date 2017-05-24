//Buddy system version

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define N 11 //Memory size
#define MIN_SIZE 1; //1K is minimum block size
#define LIST_T_SIZE sizeof(list_t)

long MAX_SIZE = 1L << N;

//Data structures
typedef struct list_t list_t;

struct list_t
{
  unsigned free:1;     /* one if free. */
  size_t   size;       /* size including list_t */
  list_t*  succ;       /* successor block in list. */
  list_t*  pred;       /* predecessor block in list. */
  char     data[];
}

void* list[N];
unsigned int init = 1;

/*Keep a linked list (n) for each possible memory size 2^n == memory size.
All empty except for the largest memory size which has a block*/
void init_blocks()
{
  list_t* block = sbrk(0);
	void* req = sbrk(size + LIST_T_SIZE);
	if (req == (void*) -1) {
		return NULL;
	}
  block->size = MAX_SIZE;
  block->free = 1;

  list[N-1] = (void*)block;
}

size_t round_up(size_t size)
{
  unsigned int rounded_size = 2;
  while (rounded_size < MAX_SIZE && rounded_size > N) {
    rounded_size *= 2;
  }

  return rounded_size;
}

list_t* check_available_block(void* head)
{
  void* tmp = head;
  while (tmp != NULL && !tmp->free)
    tmp = tmp->succ;
  return tmp;
}

list_t* allocate_memory(size_t index, size_t size)
{
  void* block = list[index];
  list_t* avail = check_available_block(block);
  if (!avail) {
    avail = recursive_alloc(index, index);
  }
  return avail;
}

void split (size_t index)
{
  list[index]
  //remove 16K block
  //two new blocks 8K add to list
}

//Recursive method
void* recursive_alloc(size_t index, size_t start)
{
  if (index > N)
    return NULL;
  void* block = list[index];
  list_t* avail = check_available_block(block);
  if (avail) {
    //Free block
    //Split into two blocks
    //Add one to the list
    //Return the other
    return
  } else
    return recursive_alloc(index++, index);
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
  {
    return NULL;
  }

  if (init) {
    init_blocks();
    init = 0;
  }

  size = rounded_size(size);

  size_t index = log(size)/log(2);

  list_t* block = allocate_memory(index, size);

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
