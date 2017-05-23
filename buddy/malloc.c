//Buddy system version

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define N 1024 //Memory size

//Data structures

typedef struct list_t list_t;

struct list_t {
	size_t  size; //size including list_t
	list_t* next; //next available block.
	int free;
	char    data[]; //C99 flexible array.
};

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
}

void *calloc(size_t nitems, size_t size)
{
}

void *realloc(void *ptr, size_t size)
{
}

void free(void *ptr)
{
	/*If buddy also free => merge the blocks and recurse until no free buddy
	add the resulting block to list
	Else add block to list*/
}
