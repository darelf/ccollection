#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cvector.h"
#include "chashtable.h"

// qsort compatible compare function
int compare(const void * a, const void * b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

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
  
  printf("Looking for a key that isn't there...\n");
  assert( ch_get(ht, "Missing Key") == NULL );
  
  // Let's store a number value...
  double dv = 0;
  sscanf("123456789.0", "%lf", &dv);
  ch_set(ht, "Value", &dv);
  // You have to know what the table is storing...
  printf("Showing value for key 'Value': %.3lf\n", *(double *)ch_get(ht, "Value"));
  
  // Let's get a list of keys...
  printf("Getting the list of keys for the hastable:\n");
  
  cvector * keys = ch_keys(ht);
  qsort(keys->data, keys->count, sizeof(char *), compare);
  for ( i = 0; i < keys->count; i++ ) {
    printf("%s\n", (char *)cv_get(keys, i));
  }
  // The caller has to free the vector...
  cv_free(keys);
  
  ch_free(ht);
  
  return 0;
}
