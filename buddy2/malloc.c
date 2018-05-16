// Buddy version 2
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h> // Is this available?

#include "malloc.h"

#define debug 0

// Variables ------------------------------------------------

void* start = NULL; /* A pointer to where the memory starts */

// Functions ------------------------------------------------

void *malloc(size_t size)
{
  if (size <= 0 || size > MAX_SIZE) {
    return NULL;
  }

  if (start == NULL) {
    init_memory_pool();
  }

  // Figure out what size block is needed
  int block_size = nearest_block_size_required(size + LIST_T_SIZE);
  int n = log(block_size) / log(2); // Log2

  // TODO Can I take away this?
  // if (n < MIN_SIZE_N) {
  //   printf("NULL\n");
  //   return NULL;
  // }

#if debug
printf("Block size required: %d, n: %d\n", block_size, n);
#endif

  list_t* free_block = get_free_block(n);

  if (free_block == NULL) {
    return NULL;
  }

#if debug
printf("Free block: %p\n", free_block);
#endif

  if (free_block != NULL) {
    free_block->free = 0;
  }

  return &free_block[1]; // TODO: free_block->data / &free_block[1] ?
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
  // Implement the free function
  if (ptr == NULL) {
        return;
  }

  list_t* block = (list_t*)((char*)ptr - LIST_T_SIZE);
  block->free = 1;

  #if debug
  printf("Free block %p\n", block);
  #endif
  
  merge_up(block);
}

// Helper functions ------------------------------------------------

void init_memory_pool() {
  /* TODO Maybe I need to allocate size for the list_t aswell?
          All the list_t's too?
  */

  list_t *block = sbrk(MAX_SIZE); // Allocate more memory so that the structs will fit

  // Create the start block
  block->size = N;
  block->free = 1;
  block->pred = NULL;
  block->succ = NULL;

  start = block;

  #if debug
  printf("Init block from sbrk is %p\n", block);
  printf("Block, size: %zu, free: %d\n", block->size, block->free);
  printf("SUCCESSFUL INIT\n");
  #endif
}

list_t* get_free_block(int n) {
  list_t* free_block = find_block_of_size(n);

  int higher_n = n;
  while (free_block == NULL) {
    higher_n++;
    if (higher_n > N) {
      printf("NO MEMORY\n");
      return NULL; // There is no free memory available
    }
    free_block = find_block_of_size(higher_n);
  }

  #if debug
  printf("Nearest free block is %d but need size %d. It has pointer %p\n", higher_n, n, free_block);
  #endif

  while (free_block->size != n) {
    free_block = split_block(free_block);
  }

  return free_block;
}

list_t* find_block_of_size(int n) {
  list_t* current_block = start;

  while (current_block != NULL) {
    if (current_block->size == n && current_block->free) {
      return current_block;
    }
    current_block = current_block->succ;
  }

  return NULL;
}

list_t* split_block(list_t* block) {
  #if debug
  printf("---------Splitting----------\n");
  #endif

  size_t half_size = block->size - 1;
  int block_size = pow(2, block->size);

  #if debug
  printf("New size: %zu, Block size: %d, Current block: %p\n", half_size, block_size, block);
  #endif

  list_t* left = block;
  left->free = 1;
  left->size = half_size;
  left->pred = block->pred;

  list_t* right = (list_t*) ((char*) left + (1LL << half_size)); // TODO Why does this work? Does it?
  right->free = 1;
  right->size = half_size;
  right->pred = left;
  right->succ = block->succ;

  left->succ = right;

  if (right->succ != NULL) {
    right->succ->pred = right; // TODO Make sure that this happens everywhere and doesn't get lost
  }

  if (block == start) {
    start = left;
  }

  #if debug
  printf("---------Done splitting----------\n");
  #endif

  return left;
}

list_t* merge_blocks(list_t* left, list_t* right) {
  #if debug
  printf("Merging block %p and %p\n", left, right);
  #endif

  list_t* merged_block = left;

  merged_block->free = 1;
  merged_block->size = right->size + 1;
  merged_block->succ = right->succ;
  merged_block->pred = left->pred;

  if (right->succ != NULL) {
    right->succ->pred = merged_block;
  }

  if (left->pred != NULL) {
    left->pred->succ = merged_block;
  }

  return merged_block;
}

void merge_up(list_t* block) {
  list_t* buddy_left = block->pred;
  list_t* buddy_right = block->succ;

  #if debug
  printf("Left %p Right %p\n", buddy_left, buddy_right);
  #endif

  // TODO The wrong predecessor!

  if (buddy_left != NULL && buddy_left->free && buddy_left->size == block->size) {
    #if debug
    printf("MERGE WITH LEFT\n");
    #endif
    merge_up(merge_blocks(buddy_left, block));
  } else if (buddy_right != NULL && buddy_right->free && buddy_right->size == block->size) {
    #if debug
    printf("MERGE WITH RIGHT\n");
    #endif
    merge_up(merge_blocks(block, buddy_right));
  } else {
    return;
  }

  // TODO Maybe not needed since the pointer will be the same anyways?

  // if (start == block) {
  //   printf("Switching start block to: pointer %p, size %zu, free %d\n", new_block, new_block->size, new_block->free);
  //   start = new_block;
  // }
}

int nearest_block_size_required(size_t size) {
  int required_size = 1; // TODO Something goes wrong when small memory is allocated. How to solve this?

  while (size > required_size) {
    required_size *= 2;
  }
  return required_size;
}

void print_free_list() {
  list_t* current = start;
  printf("--------- Memory --------\n");
  while (current != NULL) {
    printf("Slot size: %zu, Available: %d, Pointer: %p\n", current->size, current->free, current);
    current = current->succ;
  }
  printf("-------------------------\n");
}
