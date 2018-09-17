#include "cmo_vector.h"

#include <string.h>
#include <stdio.h>

cmo_vector *cmo_vector_alloc(_cmo_ctx *_ctx) {
  cmo_vector *v = _ctx->alloc(_ctx->alloc_usr, sizeof(cmo_vector));
  v->_ctx = _ctx;
  return v;
}

void cmo_vector_free(cmo_vector *v) {
  v->_ctx->free(v->_ctx->free_usr, v);
}
