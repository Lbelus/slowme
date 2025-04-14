#ifndef __PARSER_HEADERFILE_
#define __PARSER_HEADERFILE_

#include <openssl/ssl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "../../../include/uri_struct.h"
#include "../../utils/string/fc_string.h"

#define MAX_INPUT_TOKENS  1000
#define PROTOCOL_SEP      "://"
#define _HTTPS__          "https://"
#define _HTTPS_LEN_       8
#define _HTTP__           "http://"
#define _HTTP_LEN_        7
#define PATH_SEP          '/'


void    log_host_error(char* domain);

char* set_var(char* src, int len);
// char* create_get_request(char* path, char* domain, int total_str_len);
url_p_s_t* my_url_parser(char* url);
void free_url_struct(url_p_s_t* url_s);
protocol_enum get_protocol_from_url(char* url);

int token_array_size(char** resp_tokens);
char* set_response_code(char* response);

char* init_my_readline();
char* my_readline(int fd);
char* my_SSL_readline(SSL* ssl);
void flush_buffer();

#endif
