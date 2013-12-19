#include <stdio.h>
#include "cvector.h"
#include "chashtable.h"

int main(void) {
  cvector * v = cv_create();
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
  
  printf("Before removing items:\n");
  int i;
  for ( i = 0; i < v->count; i++) {
    printf("%s\n", cv_get(v, i));
  }
  cv_remove(v, 2);
  cv_remove(v, 5);
  
  printf("After removing items:\n");
  for ( i = 0; i < v->count; i++) {
    printf("%s\n", cv_get(v, i));
  }
  
  cv_free(v);
  
  printf("\nTesting HashTable\n");
  
  hashtable * ht = ch_create(50);
  
  ch_set(ht, "John", "Mar");
  ch_set(ht, "Jahn", "Say What?");
  ch_set(ht, "Another", "Yet another entry");
  printf("Showing value for key 'John': %s\n", ch_get(ht, "John"));
  printf("Showing value for key 'Jahn': %s\n", ch_get(ht, "Jahn"));
  
  ch_free(ht);
  
  return 0;
}
