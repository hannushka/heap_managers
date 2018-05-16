#include "malloc.c"

struct person_t
{
  int age;
  int height;
  int weight;
  char c;
};

typedef struct person_t person_t;

int main(){

  printf("%lld\n", MAX_SIZE);

  printf("Begin malloc tests...\n");

  printf("Allocating a\n");
  int *a = malloc(34*1024);
  printf("Memory: %p\n\n", a);

  print_blocks_list();

  printf("Allocating b\n");
  int *b = malloc(66*1024);
  printf("Memory: %p\n\n", b);

  print_blocks_list();

  printf("Allocating c\n");
  // TODO Fix when this happens!!
  person_t* c = malloc(sizeof *c);
  // c->age = 10;
  // c->height = 175;
  // c->weight = 75;
  // c->c = 'a';
  // int *c = malloc(35*1024);
  printf("Memory: %p\n\n", c);

  print_blocks_list();

  printf("Allocating d\n");
  int *d = malloc(67*1024);
  printf("Memory: %p\n\n", d);

  print_blocks_list();

  printf("Freeing b\n");
  free(b);

  print_blocks_list();

  printf("Freeing d\n");
  free(d);

  print_blocks_list();

  printf("Freeing a\n");
  free(a);

  print_blocks_list();

  printf("Freeing c\n");
  free(c);

  print_blocks_list();

  // printf("Allocating e\n");
  // int *e = malloc(100*1024);
  // printf("Memory: %p\n\n", b);
  //
  // print_blocks_list();

  // int* n = malloc(sizeof(int));
  // *n = 456;
	// fprintf(stderr, "%s %p\n", "Pointer N", (void*)n);
	// fprintf(stderr, "N is %d\n", *n);
  //
	// // print_list();
	// // fprintf(stderr, "END\n");
  //
	// int* m = malloc(sizeof(int));
  // *m = 100;
	// fprintf(stderr, "%s %p\n", "Pointer M", (void*)m);
	// fprintf(stderr, "M is %d\n", *m);
  //
	// // print_list();
	// // fprintf(stderr, "END\n");
  //
	// int* o = malloc(sizeof(int));
  // *o = 3244;
	// fprintf(stderr, "%s %p\n", "Pointer O", (void*)o);
	// fprintf(stderr, "O is %d\n", *o);
  //
	// //print_list();
	// //fprintf(stderr, "END\n");
  //
	// free(o);
  //
	// // print_list();
	// // fprintf(stderr, "END\n");
  //
	// free(m);
  //
  //
	// free(n);
  //
	// // print_list();
	// // fprintf(stderr, "END\n");


}
