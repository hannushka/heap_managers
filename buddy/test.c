#include "malloc.c"

int main(){
  int* n = malloc(sizeof(int));
  *n = 456;
	fprintf(stderr, "%s %p\n", "Pointer N", (void*)n);
	fprintf(stderr, "N is %d\n", *n);

	int* m = malloc(sizeof(int));
  *m = 100;
	fprintf(stderr, "%s %p\n", "Pointer M", (void*)m);
	fprintf(stderr, "M is %d\n", *m);

	int* o = malloc(sizeof(int));
  *o = 3244;
	fprintf(stderr, "%s %p\n", "Pointer O", (void*)o);
	fprintf(stderr, "O is %d\n", *o);

	free(m);
	free(n);
	free(o);
}
