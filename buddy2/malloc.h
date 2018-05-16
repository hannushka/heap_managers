#define N (22) //Memory size (index) 2^N
#define MIN_SIZE 128 //Minimum block size
#define MIN_SIZE_N 7
#define LIST_T_SIZE sizeof(list_t)
#define MAX_SIZE (1LL << N) // 2 MB

// Data structures ------------------------------------------------
typedef struct list_t list_t;

struct list_t
{
  unsigned free:1;     /* one if free. */
  size_t   size;       /* size including list_t */ //Use char or size_t?
  list_t*  succ;       /* successor block in list. */
  list_t*  pred;       /* predecessor block in list. */
  char     data[];     /* the block data */ // TODO Is this needed?
};

// Declaration of functions

void *malloc(size_t size);

void free(void *ptr);

void *calloc(size_t nelem, size_t elsize);

void *realloc(void *ptr, size_t size);

// Helper functions

void init_memory_pool();

list_t* split_block(list_t* block); // Returns the left split block

list_t* get_free_block(int n);

list_t* find_block_of_size(int n);

list_t* merge_blocks(list_t* left, list_t* right);

void merge_up(list_t* block);

/* Questions:
    * Do I have to care about the space list_t takes?
    * Can I implement calloc and realloc like I have?
    * sbrk can't seem to allocate more than N=22, how can I solve this? -- Maybe I can...
*/
