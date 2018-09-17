#ifndef _CMO_SOCK_H
#define _CMO_SOCK_H

#include "context.h"

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 */
typedef struct _cmo_sock {
  _cmo_ctx *_ctx;
  void (*poll_err)(void *usr);
  void *poll_err_usr;
  void (*con_in)(void *usr, const char *session_id);
  void *con_in_usr;
} _cmo_sock;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _CMO_SOCK_H */
