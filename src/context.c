#include "cmosocket.h"

#include "context.h"

#include <string.h>
#include <stdio.h>

void *_cmo_def_alloc(void *usr, size_t size) {
  return malloc(size);
}

void _cmo_def_free(void *usr, void *ptr) {
  free(ptr);
}

cmo_ctx cmo_ctx_alloc(void) {
  return cmo_ctx_alloc_custom(&_cmo_def_alloc, 0, &_cmo_def_free, 0);
}

cmo_ctx cmo_ctx_alloc_custom(
    void *(*alloc)(void *usr, size_t size),
    void *alloc_usr,
    void (*free)(void *usr, void *ptr),
    void *free_usr) {
  _cmo_ctx *_ctx = alloc(alloc_usr, sizeof(_cmo_ctx));
  _ctx->alloc = alloc;
  _ctx->alloc_usr = alloc_usr;
  _ctx->free = free;
  _ctx->free_usr = free_usr;
  _ctx->last_err = 0;
  _ctx->last_err_str_len = 1024;
  _ctx->last_err_str = alloc(alloc_usr, _ctx->last_err_str_len);
  _ctx->last_err_str[0] = '\0';
  return _ctx;
}

void cmo_ctx_free(cmo_ctx ctx) {
  _cmo_ctx *_ctx = (_cmo_ctx *) ctx;
  _ctx->free(_ctx->free_usr, _ctx->last_err_str);
  _ctx->free(_ctx->free_usr, _ctx);
}

int32_t cmo_ctx_last_err(cmo_ctx ctx) {
  _cmo_ctx *_ctx = (_cmo_ctx *) ctx;
  return _ctx->last_err;
}

const char *cmo_ctx_last_err_str(cmo_ctx ctx) {
  _cmo_ctx *_ctx = (_cmo_ctx *) ctx;
  return _ctx->last_err_str;
}
