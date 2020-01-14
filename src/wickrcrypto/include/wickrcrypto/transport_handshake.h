//
//  transport_handshake.h
//  wickrcrypto
//
//  Created by Tom Leavy on 1/14/20.
//

#ifndef transport_handshake_h
#define transport_handshake_h

#include "identity.h"
#include "stream_key.h"

typedef enum {
    TRANSPORT_HANDSHAKE_STATUS_UNKNOWN,
    TRANSPORT_HANDSHAKE_STATUS_IN_PROGRESS,
    TRANSPORT_HANDSHAKE_STATUS_COMPLETE,
    TRANSPORT_HANDSHAKT_STATUS_FAILED
} wickr_transport_handshake_status;

struct wickr_transport_handshake_res_t;
typedef struct wickr_transport_handshake_res_t wickr_transport_handshake_res_t;

wickr_transport_handshake_res_t *wickr_transport_handshake_res_create(wickr_stream_key_t *local_key,
                                                                      wickr_stream_key_t *remote_key);
wickr_transport_handshake_res_t *wickr_transport_handshake_res_copy(const wickr_transport_handshake_res_t *res);
void wickr_transport_handshake_res_destroy(wickr_transport_handshake_res_t **res);

const wickr_stream_key_t *wickr_transport_handshake_get_local_key(const wickr_transport_handshake_res_t *handshake);
const wickr_stream_key_t *wickr_transport_handshake_get_remote_key(const wickr_transport_handshake_res_t *handshake);

struct wickr_transport_handshake_t;
typedef struct wickr_transport_handshake_t wickr_transport_handshake_t;

typedef void (*wickr_transport_handshake_identity_response)(const wickr_transport_handshake_t *handshake,
                                                            bool is_valid);

typedef void (*wickr_transport_handshake_identity_callback)(const wickr_transport_handshake_t *handshake,
                                                            wickr_identity_chain_t *identity,
                                                            wickr_transport_handshake_identity_response on_complete,
                                                            void *user);

wickr_transport_handshake_t *wickr_transport_handshake_create(wickr_identity_chain_t *local_identity,
                                                              wickr_identity_chain_t *remote_identity,
                                                              wickr_transport_handshake_identity_callback identity_callback);
wickr_transport_handshake_t *wickr_transport_handshake_copy(const wickr_transport_handshake_t *handshake);
void wickr_transport_handshake_destroy(wickr_transport_handshake_t **handshake);

wickr_buffer_t *wickr_transport_handshake_process(wickr_transport_handshake_t *handshake, const wickr_buffer_t *buffer);
wickr_transport_handshake_res_t *wickr_transport_handshake_finalize(const wickr_transport_handshake_t *handshake);

const wickr_transport_handshake_status wickr_transport_handshake_get_status(const wickr_transport_handshake_t *handshake);
const wickr_identity_chain_t *wickr_transport_handshake_get_local_identity(const wickr_transport_handshake_t *handshake);
const wickr_identity_chain_t *wickr_transport_handshake_get_remote_identity(const wickr_transport_handshake_t *handshake);



#endif /* transport_handshake_h */
