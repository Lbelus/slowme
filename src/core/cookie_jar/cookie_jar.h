#ifndef __MYCOOKIEJAR_H
#define __MYCOOKIEJAR_H

// #include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../curl/ssl_header.h"
#include "../parser/parser.h"

#ifndef NODE_S
#define NODE_S
struct node 
{
    void* token;
    struct node* head;
    struct node* next;
};
typedef struct node node_t;
#endif

#ifndef _COOKIE_S_
#define _COOKIE_S_
struct cookie_s
{
    char* domain;
    char* subdomain_bool;
    char* path;
    char* secure_bool;
    char* date;
    char* cookie_name;
    char* cookie_value;
};
typedef struct cookie_s cookie_t;
#endif

#ifndef _CMD_PTR_S_
#define _CMD_PTR_S_
struct cmd_ptr_s
{
    char* cmd;
    void (*func_ptr) (cookie_t*, char*);
};
typedef struct cmd_ptr_s cmd_ptr_t;
#endif

#define __DOMAIN_STR_A_    "Domain="
#define __DOMAIN_STR_B_    "domain="
#define __PATH_STR_        "Path="
#define __EXPIRES_STR_     "Expires="
#define __TRUE_STR_        "TRUE"
#define __FALSE_STR_       "FALSE"
#define __COOKIE_STR_      "Set-Cookie:"
#define __SECURE_STR_      " Secure"
#define __HTTPONLY_STR_    " HttpOnly"
#define __HTTP_TOKEN_      "#HttpOnly_"
#define __HTTP_TOKEN_LEN_  10
#define __ZERO_STR_        "0"


// int         find_ch(char* str, char ch);
// char**      my_strtok(char* str, char ch);
// char*       itoa(long long value, char* result, int base);

// void        set_cookie_name_value(cookie_t* cookie_jar, char* token);
// void        set_cookie_domain(cookie_t* cookie_jar, char* token);
// void        set_cookie_path(cookie_t* cookie_jar, char* token);
// void        set_cookie_secure(cookie_t* cookie_jar, char* token);
// // int         convert_date_to_second(char* date_str, char* epoch_str);
// void        set_cookie_date(cookie_t* cookie_jar, char* token);
// void        set_http_only(cookie_t* cookie_jar, char* token);

node_t*     fill_cookie_jar(ssl_s_t* ssl_data);
cookie_t*   add_cookie(char** tokens);
void        free_cookie(cookie_t* cookie);
void        execute_cmd(cookie_t* cookie_jar, char* token);
char*       set_cookies_str(node_t* head);

#endif
