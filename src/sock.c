#include "cmosocket.h"

#include "sock.h"

#include <string.h>
#include <stdio.h>

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
