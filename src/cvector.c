#include <stdlib.h>

#include "cvector.h"

cvector * cv_create(size_t num) {
  cvector * v = calloc(1, sizeof(cvector));
  v->size = num;
  v->count = 0;
  v->data = calloc(v->size, sizeof(void *) * v->size);;
  return v;
}

cvector * cv_create_default() {
  return cv_create(CV_DEFAULT_SIZE);
}

void cv_add(cvector * v, void * d) {
  if (!d) return;
  if (v->size == v->count) {
    //You already used the last slot... What do we do now!?!
    v->size = v->size * 2; //Maybe "double the size" a little simplistic?
    // Note that realloc doesn't initialize the new memory, however,
    // since we only read up to count items, and items are always compacted
    // we don't have to worry about those memory locations.
    v->data = realloc(v->data, sizeof(void *) * v->size);
  }
  //Now actually put the data in
  v->data[v->count] = d;
  v->count++;
}

/* This will overwrite any data in position idx.
 */
void cv_insert(cvector * v, size_t idx, void * d) {
  if ( idx >= v->size ) {
    //don't do anything if they give an invalid index...
    return;
  }
  v->data[idx] = d;
}

void * cv_get(cvector * v, size_t idx) {
  if ( idx >= v->size ) {
    //invalid index...
    return NULL;
  }
  // if NULL is at this location, will return NULL... obviously
  return v->data[idx];
}

void cv_remove(cvector * v, size_t idx) {
  if (idx >= v->count) {
    //invalid index...
    return;
  }
  // v->data[idx] = NULL; // I think this is unnecessary
  
  /* We're going to go through the vector and remove this entry.
   * Since we can only remove one item at a time, we can edit the array
   * in place, starting at the deleted item and shifting everything down
   * Obviously this takes more time the earlier in the array the index is.
   */
  int i;
  for ( i = idx; i < v->count - 1; i++) {
    v->data[i] = v->data[i+1];
  }
  v->data[v->count-1] = NULL;
  v->count--;
  /* Maybe add something to reduce the memory allocation if the
   * size of the vector has fallen past a threshold?
   */
  if (v->count < (v->size / 2)) {
    v->size = (v->size / 2);
    v->data = realloc(v->data, sizeof(void *) * v->size);
  }
}

void cv_free(cvector * v) {
  free(v->data);
  free(v);
}
