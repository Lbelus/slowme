#ifndef __CURL_API_H_
#define __CURL_API_H_

// #include "main_header.h"
#include "../../utils/linkedlist/linkedlist.h"
#include "../user_agent/user_agent.h"
#include "../../../include/uri_struct.h"
#include "../cookie_jar/cookie_jar.h"
#include "../payload/payload.h"

void free_llist(node_t* head);
uri_s_t init_my_curl(uri_s_t  uri, char* user_arg);
int     my_curl(uri_s_t  uri);
int     clean_my_curl(uri_s_t  uri);
int     perform_get_request(char* domain,  char* get, int protocol_type);

node_t* req_cookie(char* domain, char* get);

node_t* login(char* username, char* password, char* user_agent_designation, char* url);
    node_t* get_session_cookie(user_agent_t* user_agent, char* url);
    node_t* get_auth_cookie(user_agent_t* user_agent, char* cookies, char* payload, char* url);
    node_t* get_cookie(url_p_s_t*  url_s);

#endif
