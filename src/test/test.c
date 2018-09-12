#include <stdio.h>

#include "cmosocket.h"

void test_con_in(void *usr, const char *session_id) {
  printf("test_con_in: %s\n", session_id);
}

void test_bind(void *usr) {
  printf("test_bind\n");
}

void test_con_out(void *usr) {
  printf("test_con_out\n");
}

int main() {
  cmo_ctx ctx;
  cmo_sock s;

  ctx = cmo_ctx_alloc();

  s = cmo_sock_alloc(ctx, 0, 0, &test_con_in, 0);

  cmo_sock_poll(s, 20);

  cmo_sock_bind(s, "hello-bind", &test_bind, 0);
  cmo_sock_connect(s, "hello-connect", &test_bind, 0);

  cmo_sock_free(s);

  cmo_ctx_free(ctx);

  return 0;
}
