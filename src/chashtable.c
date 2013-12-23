#include <string.h>
#include "chashtable.h"

/* from wikipedia entry on jenkins hash
 */
static uint32_t jenkins_hash(void * k, size_t len) {
  uint32_t hash, i;
  char * key = (char *)k;
  for (hash = i = 0; i < len; ++i) {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}

/* Use a compare function, so it can be replaced by the user
 * The default is the strcmp() function
 */
static int default_compare(void * a, void * b) {
  return strcmp((char *)a, (char *)b);
}

hashtable * ch_create() {
  return ch_create_full(DEFAULT_BUCKETS, default_compare);
}

hashtable * ch_create_full(size_t num_buckets, hashtable_compare comp) {
  hashtable * h = calloc(1, sizeof(hashtable));
  
  h->buckets = cv_create(num_buckets);
  h->buckets->count = num_buckets;
  h->size = num_buckets;
  h->hash = jenkins_hash;
  h->compare = comp;
  
  return h;
}

void ch_free(hashtable * h) {
  int i,j;
  if (h) {
    if (h->buckets) {
      for (i = 0; i < h->size; i++) {
        cvector * bucket = cv_get(h->buckets, i);
        if (bucket) {
          for (j = 0; j < bucket->count; j++) {
            free(cv_get(bucket, j));
          }
          cv_free(bucket);
        }
      }
      cv_free(h->buckets);
    }
    free(h);
  }
}

static inline hashnode * ch_node_create(int hash, void * key, void * data) {
  hashnode * node = calloc(1, sizeof(hashnode));
  
  node->key = key;
  node->data = data;
  node->hash = hash;
  
  return node;
}

static inline cvector * ch_find_bucket(hashtable * h, void * key, int create, uint32_t * hash_out) {
  uint32_t hash = h->hash(key, strlen(key));
  int bucket_num = hash % h->size;
  *hash_out = hash;
  
  cvector * bucket = cv_get(h->buckets, bucket_num);
  
  if (!bucket && create) {
    bucket = cv_create_default();
    cv_insert(h->buckets,bucket_num,bucket);
  }
  
  return bucket;
}

void ch_set(hashtable * h, void * key, void * value) {
  uint32_t hash = 0;
  cvector * bucket = ch_find_bucket(h, key, 1, &hash);
  hashnode * node = ch_node_create(hash, key, value);
  cv_add(bucket, node);
}

static inline int ch_get_node(hashtable * h, uint32_t hash, cvector * bucket, void * key) {
  int i = 0;
  for (i = 0; i < bucket->count; i++) {
    hashnode * node = cv_get(bucket, i);
    if (node->hash == hash && h->compare(node->key, key) == 0) {
      return i;
    }
  }
  return -1;
}

void * ch_get(hashtable * h, void * key) {
  uint32_t hash = 0;
  cvector * bucket = ch_find_bucket(h, key, 0, &hash);
  if (!bucket) return NULL;
  
  int i = ch_get_node(h, hash, bucket, key);
  if (i == -1) return NULL;
  hashnode * node = cv_get(bucket, i);
  if (!node) return NULL; // This really shouldn't happen
  
  return node->data;
}

void * ch_remove(hashtable * h, void * key) {
  uint32_t hash = 0;
  cvector * bucket = ch_find_bucket(h, key, 0, &hash);
  if (!bucket) return NULL;
  int i = ch_get_node(h, hash, bucket, key);
  if (i == -1) return NULL;
  hashnode * node = cv_get(bucket, i);
  void * data = node->data;
  cv_remove(bucket, i);
  free(node);
  return data;
}

// Caller is responsible for freeing the vector
cvector * ch_keys(hashtable * h) {
  cvector * keys = cv_create_default();
  int i, j;
  for (i = 0; i < h->buckets->count; i++) {
    cvector * bucket = cv_get(h->buckets, i);
    if (bucket) {
      for (j = 0; j < bucket->count; j++) {
        hashnode * node = cv_get(bucket, j);
        cv_add(keys, node->key);
      }
    }
  }
  return keys;
}
