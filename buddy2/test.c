#include <stdio.h>
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
  *a = 50;

  printf("Allocating b\n");
  char *b = malloc(66*1024);
  *b = 'A';

  printf("Allocating c\n");
  person_t* c = malloc(sizeof *c);
  c->age = 26;
  c->height = 175;
  c->weight = 75;
  c->c = 'a';

  printf("Allocating d\n");
  int *d = malloc(67*1024);
  *d = 1992;

  printf("Memory: %p Value: %d\n\n", a, *a);
  printf("Memory: %p Value: %c\n\n", b, *b);
  printf("Memory: %p Value: (age) %d (height) %d (weight) %d (c) %c\n\n", c, c->age, c->height, c->weight, c->c);
  printf("Memory: %p Value: %d\n\n", d, *d);

  print_free_list();

  printf("Freeing b\n");
  free(b);

  printf("Freeing d\n");
  free(d);

  printf("Freeing c\n");
  free(c);

  printf("Freeing a\n");
  free(a);

  print_free_list();

  printf("Allocating f\n");

  person_t* f = malloc(sizeof *f);
  f->age = 65;
  f->height = 175;
  f->weight = 70;
  f->c = 'g';

  printf("Allocating g\n");

  person_t* g = malloc(sizeof *g);
  g->age = 58;
  g->height = 165;
  g->weight = 55;
  g->c = 'e';

  printf("Freeing f\n");
  free(f);

  print_free_list();

  printf("-----------Stress test begin----------\n");

  for (size_t times = 1; times <= 10; times++) {
    int loops = 10 * times;
    unsigned long* places[loops];

    for (int i = 0; i < loops; i++) {
      unsigned long *pointer = malloc(loops * 3); // TODO Something goes wrong when allocating small memory sizes. Overwrite happens?
      print_free_list();
      *pointer = i;
      places[i] = pointer;
    }

    printf("FREE!!!!\n");

    for (int i = 0; i < loops; i++) {
      // printf("Freeing %p\n", places[i]);
      free(places[i]);
      print_free_list();
    }
  }

  printf("-----------Stress test done----------\n");
  print_free_list();

  printf("g is age: %d (58) height: %d (165) weight: %d (55) c: %c (e) pointer: %p\n", g->age, g->height, g->weight, g->c, g);
  printf("Size of g %lu\n", sizeof(*g));
}
