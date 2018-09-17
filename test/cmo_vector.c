#include <criterion/criterion.h>

#include "cmosocket.h"
#include "cmo_vector.h"

Test(cmo_vector_suite, it_can_alloc_and_free) {
  cmo_ctx ctx = cmo_ctx_alloc();

  cmo_vector *v = cmo_vector_alloc(ctx);

  cmo_vector_free(v);

  cmo_ctx_free(ctx);
}
