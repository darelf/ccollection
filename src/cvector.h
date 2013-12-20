#ifndef CVECTOR_H__
#define CVECTOR_H__

#define CV_DEFAULT_SIZE 15

#include <string.h>

typedef struct cvector_ {
  void ** data;
  size_t size;
  size_t count;
} cvector;

cvector * cv_create_default();
cvector * cv_create(size_t);
void cv_add(cvector *, void *);
void cv_insert(cvector *, size_t, void *);
void * cv_get(cvector *, size_t);
void cv_remove(cvector *, size_t);
void cv_free(cvector *);

#endif
