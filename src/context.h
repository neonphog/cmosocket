#ifndef _CMO_CONTEXT_H
#define _CMO_CONTEXT_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 */
typedef struct _cmo_ctx {
  void *(*alloc)(void *usr, size_t size);
  void *alloc_usr;
  void (*free)(void *usr, void *ptr);
  void *free_usr;
  int32_t last_err;
  size_t last_err_str_len;
  char *last_err_str;
} _cmo_ctx;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _CMO_CONTEXT_H */
