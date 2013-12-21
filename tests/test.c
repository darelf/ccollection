#include <stdio.h>
#include <assert.h>
#include "cvector.h"
#include "chashtable.h"

int main(void) {
  cvector * v = cv_create_default();
  cv_add(v, "one");
  cv_add(v, "two");
  cv_add(v, "three");
  cv_add(v, "four");
  cv_add(v, "five");
  cv_add(v, "six");
  cv_add(v, "seven");
  cv_add(v, "eight");
  cv_add(v, "nine");
  cv_add(v, "ten");
  cv_add(v, "one");
  cv_add(v, "two");
  cv_add(v, "three");
  cv_add(v, "four");
  cv_add(v, "five");
  cv_add(v, "six");
  cv_add(v, "seven");
  cv_add(v, "eight");
  cv_add(v, "nine");
  cv_add(v, "ten");
  
  // add nothing... nothing happens
  cv_add(v, NULL);
  
  // If you allocate it yourself you have to free it yourself
  char * buf = calloc(1, 10);
  strncpy(buf, "TEST", 4);
  cv_add(v, buf);
  
  assert( v->size == 32 );
  printf("Before removing items (size of %lu):\n", v->size);
  int i;
  for ( i = 0; i < v->count; i++) {
    printf("%s\n", (char *)cv_get(v, i));
  }
  cv_remove(v, 2);
  cv_remove(v, 5);
  cv_remove(v, 5);
  cv_remove(v, 5);
  cv_remove(v, 5);
  cv_remove(v, 5);
  cv_remove(v, 5);
  
  assert( v->size == 16 );
  printf("After removing items (size of %lu):\n", v->size);
  for ( i = 0; i < v->count; i++) {
    printf("%s\n", (char *)cv_get(v, i));
  }
  
  cv_free(v);
  // See above
  free(buf);
  
  printf("\nTesting HashTable\n");
  
  // Let's use the default bucket size
  hashtable * ht = ch_create();
  assert( ht->size == 64 );
  
  ch_set(ht, "John", "Mar");
  ch_set(ht, "Jahn", "Say What?");
  ch_set(ht, "Another", "Yet another entry");
  
  assert( strcmp(ch_get(ht, "John"), "Mar") == 0 );
  assert( strcmp(ch_get(ht, "Another"), "Yet another entry") == 0 );
  
  printf("Showing value for key 'John': %s\n", (char *)ch_get(ht, "John"));
  printf("Showing value for key 'Jahn': %s\n", (char *)ch_get(ht, "Jahn"));
  
  ch_free(ht);
  
  return 0;
}
