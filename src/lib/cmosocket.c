#include "cmosocket.h"

#include <string.h>
#include <stdio.h>

typedef struct _cmo_ctx {
  void *(*alloc)(void *usr, size_t size);
  void *alloc_usr;
  void (*free)(void *usr, void *ptr);
  void *free_usr;
  int32_t last_err;
  size_t last_err_str_len;
  char *last_err_str;
} _cmo_ctx;

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

typedef struct _cmo_sock {
  _cmo_ctx *_ctx;
  void (*poll_err)(void *usr);
  void *poll_err_usr;
  void (*con_in)(void *usr, const char *session_id);
  void *con_in_usr;
} _cmo_sock;

cmo_sock cmo_sock_alloc(
    cmo_ctx ctx,
    void (*poll_err)(void *usr),
    void *poll_err_usr,
    void (*con_in)(void *usr, const char *session_id),
    void *con_in_usr) {
  _cmo_ctx *_ctx = (_cmo_ctx *) ctx;
  _cmo_sock *_s = _ctx->alloc(_ctx->alloc_usr, sizeof(_cmo_sock));
  _s->_ctx = _ctx;
  _s->poll_err = poll_err;
  _s->poll_err_usr = poll_err_usr;
  _s->con_in = con_in;
  _s->con_in_usr = con_in_usr;
  return _s;
}

void cmo_sock_free(cmo_sock s) {
  _cmo_sock *_s = (_cmo_sock *) s;
  _s->_ctx->free(_s->_ctx->free_usr, _s);
}

void cmo_sock_poll(cmo_sock s, int32_t ms) {
  _cmo_sock *_s = (_cmo_sock *) s;
  printf("poling for %d ms\n", ms);
  _s->con_in(_s->con_in_usr, "testing");
}

void cmo_sock_bind(
    cmo_sock s, const char *multiaddr,
    void (*bind_complete)(void *usr),
    void *bind_usr) {
  /* _cmo_sock *_s = (_cmo_sock *) s; */
  printf("binding to %s\n", multiaddr);
  bind_complete(bind_usr);
}

void cmo_sock_connect(
    cmo_sock s, const char *multiaddr,
    void (*con_complete)(void *usr),
    void *con_usr) {
  /* _cmo_sock *_s = (_cmo_sock *) s; */
  printf("connecting to %s\n", multiaddr);
  con_complete(con_usr);
}
