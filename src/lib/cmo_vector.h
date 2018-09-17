#ifndef _CMO_VECTOR_H
#define _CMO_VECTOR_H

#include "_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmo_vector {
  _cmo_ctx *_ctx;
} cmo_vector;

/**
 */
cmo_vector *cmo_vector_alloc(_cmo_ctx *_ctx);

/**
 */
void cmo_vector_free(cmo_vector *v);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

