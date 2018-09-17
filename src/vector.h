#ifndef _CMO_VECTOR_H
#define _CMO_VECTOR_H

#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 */
typedef struct cmo_vector {
  _cmo_ctx *_ctx;
  void * * data;
  int32_t size;
  int32_t start_idx;
  int32_t end_idx; /* actually points to one past end */
} cmo_vector;

/**
 */
cmo_vector *cmo_vector_alloc(_cmo_ctx *_ctx);

/**
 */
void cmo_vector_realloc(cmo_vector *v, int32_t size);

/**
 */
void cmo_vector_free(cmo_vector *v);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _CMO_VECTOR_H */
