#ifndef __FC_SSL_HEADER_
#define __FC_SSL_HEADER_

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <netinet/in.h>
#include <netdb.h>

#define __PORT__ "80"

#ifndef SSL_STRUCT
#define SSL_STRUCT
struct ssl_struct
{
    const SSL_METHOD    *method;
    SSL_CTX             *ctx;
    SSL                 *ssl;
};
typedef struct ssl_struct ssl_s_t;
#endif

// ssl_s_t*    init_open_ssl();
// int         create_ssl_context(ssl_s_t* ssl_data);
// int         create_ssl_connection(ssl_s_t* ssl_data);
// int         tsl_handshake(ssl_s_t* ssl_data);
// int         perform_context_and_connection(ssl_s_t* ssl_data);
// int         https_get_request(char* domain, char* get);
// int         cleanup_ssl(ssl_s_t* ssl_data, int sockfd);

#endif
