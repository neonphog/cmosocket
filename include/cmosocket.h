#ifndef CMOSOCKET_H
#define CMOSOCKET_H

#define CMO_OK (0)
#define CMO_ERR_GENERIC (-1)

#include <stdint.h>
#include <stdlib.h>

/* will need this for different export visibility decorators */
#define _CMO_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

/**
 */
typedef void *cmo_ctx;

/**
 */
_CMO_EXPORT cmo_ctx cmo_ctx_alloc(void);

/**
 */
_CMO_EXPORT cmo_ctx cmo_ctx_alloc_custom(
    /* allocator (e.g. &malloc) */
    void *(*alloc)(void *usr, size_t size),
    void *alloc_usr,
    /* de-allocator (e.g. &free) */
    void (*free)(void *usr, void *ptr),
    void *free_usr);

/**
 */
_CMO_EXPORT void cmo_ctx_free(cmo_ctx ctx);

/**
 * @return CMO_OK or CMO_ERR_?
 */
_CMO_EXPORT int32_t cmo_ctx_last_err(cmo_ctx ctx);

/**
 * @return if CMO_ERR_? - returns error text
 */
_CMO_EXPORT const char *cmo_ctx_last_err_str(cmo_ctx ctx);

/**
 */
typedef void *cmo_sock;

/**
 */
_CMO_EXPORT cmo_sock cmo_sock_alloc(
    cmo_ctx ctx,
    /* check ctx last_err */
    void (*poll_err)(void *usr),
    void *poll_err_usr,
    /* incoming connection */
    void (*con_in)(void *usr, const char *session_id),
    void *con_in_usr);

/**
 */
_CMO_EXPORT void cmo_sock_free(cmo_sock s);

/**
 */
_CMO_EXPORT void cmo_sock_poll(cmo_sock s, int32_t ms);

/**
 */
_CMO_EXPORT void cmo_sock_bind(
    cmo_sock s, const char *multiaddr,
    void (*bind_complete)(void *usr),
    void *bind_usr);

/**
 */
_CMO_EXPORT void cmo_sock_connect(
    cmo_sock s, const char *multiaddr,
    void (*con_complete)(void *usr),
    void *con_usr);

/**
 */
/*
_CMO_EXPORT void cmo_sock_proto_first(
    cmo_sock s, const char *name, const char *ver,
    void (*preauth_req)(void *usr, ...

_CMO_EXPORT void cmo_sock_proto_small(

_CMO_EXPORT void cmo_sock_proto_notify_reliable(

_CMO_EXPORT void cmo_sock_proto_notify_unreliable(
*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#undef _CMO_EXPORT

#endif /* CMOSOCKET_H */
