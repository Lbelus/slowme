#ifndef __CURL_API_H_
#define __CURL_API_H_

#include <main_header.h>
#include <../linkedlist/linkedlist.h>
#include <../user_agent/user_agent.h>
#include <../uri_structs/uri_structs.h>
#include <../cookie_jar/cookie_jar.h>
#include <../payload/payload.h>



node_t* login(char* username, char* password, char* user_agent_designation, char* url);
    node_t* get_session_cookie(user_agent_t* user_agent, char* url);
    node_t* get_auth_cookie(user_agent_t* user_agent, char* cookies, char* payload, char* url);
    node_t* get_cookie(url_p_s_t*  url_s);

#endif
