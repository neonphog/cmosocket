#include "vector.h"

#include <string.h>
#include <stdio.h>

cmo_vector *cmo_vector_alloc(_cmo_ctx *_ctx) {
  cmo_vector *v = _ctx->alloc(_ctx->alloc_usr, sizeof(cmo_vector));
  memset(v, 0, sizeof(cmo_vector));
  v->_ctx = _ctx;

  cmo_vector_realloc(v, 8);

  return v;
}

void cmo_vector_realloc(cmo_vector *v, int32_t size) {
   int32_t i, shift;
   void * * new_data;

   shift = (size - v->size) / 2;

   new_data = (void * *) v->_ctx->alloc(
       v->_ctx->alloc_usr, sizeof(void *) * size);

   for (i = v->start_idx; i < v->end_idx; ++i) {
      new_data[i + shift] = v->data[i];
   }

   v->_ctx->free(v->_ctx->free_usr, v->data);

   v->data = new_data;
   v->size = size;
   v->start_idx += shift;
   v->end_idx += shift;
}

void cmo_vector_free(cmo_vector *v) {
  v->_ctx->free(v->_ctx->free_usr, v);
}
