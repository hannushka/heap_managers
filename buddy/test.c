#include "malloc.c"

int main(){

  int* n = malloc(sizeof(int));
  *n = 456;
	fprintf(stderr, "%s %p\n", "Pointer N", (void*)n);
	fprintf(stderr, "N is %d\n", *n);

	// print_list();
	// fprintf(stderr, "END\n");

	int* m = malloc(sizeof(int));
  *m = 100;
	fprintf(stderr, "%s %p\n", "Pointer M", (void*)m);
	fprintf(stderr, "M is %d\n", *m);

	// print_list();
	// fprintf(stderr, "END\n");

	int* o = malloc(sizeof(int));
  *o = 3244;
	fprintf(stderr, "%s %p\n", "Pointer O", (void*)o);
	fprintf(stderr, "O is %d\n", *o);

	//print_list();
	//fprintf(stderr, "END\n");

	free(o);

	// print_list();
	// fprintf(stderr, "END\n");

	free(m);


	free(n);

	// print_list();
	// fprintf(stderr, "END\n");
}
