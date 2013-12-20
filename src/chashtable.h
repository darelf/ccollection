#ifndef CHASHTABLE_H__
#define CHASHTABLE_H__

#include <stdint.h>
#include <stdlib.h>
#include "cvector.h"

/* We are using a power of two, since apparently hashes work
 * better in that scenario */
#define DEFAULT_BUCKETS 64

typedef uint32_t (*hashtable_hash)(void * key, size_t len);
typedef int (*hashtable_compare)(void * a, void *b);

typedef struct hashtable {
  cvector * buckets;
  size_t size;
  hashtable_hash hash;
  hashtable_compare compare;
} hashtable;

typedef struct hashnode {
  void * key;
  void * data;
  uint32_t hash;
} hashnode;

hashtable * ch_create();
hashtable * ch_create_full(size_t, hashtable_compare);
void ch_free(hashtable *);

void ch_set(hashtable *, void *, void *);
void * ch_get(hashtable *, void *);
void * ch_remove(hashtable *, void *);
void * ch_keys(hashtable *);

#endif
