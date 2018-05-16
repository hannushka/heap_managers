///Linked-list version

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct list_t list_t;

struct list_t {
	size_t  size; //size including list_t
	list_t* next; //next available block.
	unsigned int free; //if available or not
};

#define LIST_T_SIZE sizeof(list_t)
void *start = NULL;

list_t *create_block(list_t* last, size_t size)
{
	list_t *block = sbrk(size + LIST_T_SIZE);

	if (last) {
		last->next = block;
	}

	block->size = size;
	block->next = NULL;
	block->free = 0;
	return block;
}

list_t *find_free_block(list_t** last, size_t size)
{
	list_t* current = start;
	while (current && !(current->free && current->size >= size)) {
		*last = current;
		current = current->next;
	}
	return current;
}

void *malloc(size_t size)
{
	list_t* block;
	if (size <= 0) {
		return NULL;
	}
	if (!start) {
		block = create_block(NULL, size);

		if (!block) {
			return NULL;
		}
		start = block;
	} else {
		list_t* last = start;
		block = find_free_block(&last, size);
		if (!block) {
			block = create_block(last, size);
			if (!block) {
				return NULL;
			}
		} else {
			block->free = 0;
		}
	}
	return (block+1);
}

void *calloc(size_t nitems, size_t size)
{
	void *memory = malloc(nitems * size);

	if(memory != NULL) {
		memset(memory, 0, nitems * size);
	}
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
	if (ptr == NULL) {
		return;
	}
	list_t* block_ptr = (list_t*)ptr-1;
	block_ptr->free = 1;
}
