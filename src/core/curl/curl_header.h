#ifndef __MY_CURL_HEADER
#define __MY_CURL_HEADER

#include <stdarg.h>

#define GET_MSG_P1        "GET " // 4
#define POST_MSG_P1       "POST " // 5
#define REQ_MSG_P2        " HTTP/1.1\r\nHost: " // 17
#define REQ_MSG_P3        "\r\nConnection: close\r\n\r\n" // 23
#define REQ_MSG_P3_O      "\r\nConnection: keep-alive\r\n\r\n"
#define END_OF_LINE       "\r\n"

#define X_LI_USER_AGENT_STR "\r\nX-Li-User-Agent: "
#define USER_AGENT 			"\r\nUser-Agent: "
#define X_USER_LANGUAGE 	"\r\nX-User-Language: en"
#define X_USER_LOCALE 		"\r\nX-User-Locale: en_US"
#define ACCEPT_LANGUAGE 	"\r\nAccept-Language: en-us"
#define CONTENT_TYPE		"\r\nContent-Type: application/x-www-form-urlencoded"
#define ACCEPT_TYPE         "\r\nAccept: application/json"
#define CONTENT_LENGTH		"\r\nContent-Length: "
#define COOKIE				"\r\nCookie: "
#define CSRF_HEADER         "\r\ncsrf-token: "

int     is_request_complete(char* path, char* domain);
// char* concat_string(int argc, ...);
// char* create_get_request(char* path, char* domain);
char* create_user_a_get_request_(char* path, char* domain, char* user_agent_data);
// char* create_post_data_request(char* path, char* domain, char* payload);
// char* itoa(long long value, char* result, int base);

char* crop_csrf_token(char* csrf_token);

char* msg_path_host(char* type_req, char* path, char* domain);
char* msg_user_agent(char* x_li_user_agent, char* user_agent);
char* msg_payload(char* cookies, char* payload);
char* msg_cookie(char* cookies, char* csrf_token);
char* create_auth_request(char* msg_p1, char* msg_p2, char* msg_p3);

#endif
