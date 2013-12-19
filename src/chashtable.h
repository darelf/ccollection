#ifndef CHASHTABLE_H__
#define CHASHTABLE_H__

#include <stdint.h>
#include <stdlib.h>
#include "cvector.h"

/* We are using a power of two, since apparently hashes work
 * better in that scenario */
#define DEFAULT_BUCKETS 64

typedef uint32_t (*hashtable_hash)(char * key, size_t len);

typedef struct hashtable {
  void ** buckets;
  size_t size;
  hashtable_hash hash;
} hashtable;

typedef struct hashnode {
  char * key;
  void * data;
  uint32_t hash;
} hashnode;

hashtable * ch_create();
void ch_free(hashtable *);

void ch_set(hashtable *, char *, void *);
void * ch_get(hashtable *, char *);
void * ch_remove(hashtable *, char *);

#endif
