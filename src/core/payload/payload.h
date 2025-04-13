#ifndef _MY_PAYLOAD_H_
#define _MY_PAYLOAD_H_

#include "../../utils/linkedlist/linkedlist.h"
#include "../../utils/string/fc_string.h"
#include "../cookie_jar/cookie_jar.h"
#include "../curl/curl_header.h"

#define __AJAX_STR_         "JSESSIONID"
#define PAYLOAD_USERN       "session_key="
#define PAYLOAD_PASSW       "&session_password="
#define PAYLOAD_SESSI       "&JSESSIONID="
#define PAYLOAD_BASE_LEN    42

char*       get_csrf_token(node_t* head);
char*       set_auth_payload(char* username, char* password, char* csrf_token);
// payload_t*  create_payload_struct(char* user, char* password, char* csrf_token);
char*       concat_string(int argc, ...);

#endif
