#define _XOPEN_SOURCE
#include "./cookie_jar.h"
// #include <main_header.h>
// #include "../curl/ssl_header.h"
// #include "../parser/parser.h"
// #include "../../utils/linkedlist/linkedlist.h"

#include <string.h>



cmd_ptr_t cmd_ptr_map[] = {
    {__DOMAIN_STR_A_,       set_cookie_domain},
    {__DOMAIN_STR_B_,       set_cookie_domain},
    {__PATH_STR_,           set_cookie_path},
    {__EXPIRES_STR_,        set_cookie_date},
    {__SECURE_STR_,         set_cookie_secure},
    {__HTTPONLY_STR_,       set_http_only},
    {NULL, NULL}
};


node_t* cookie_splicer(node_t** head, char* str)
{
    char**      tokens   = NULL;
    cookie_t*   cookie   = NULL;
    node_t*     tmp      = NULL;
    printf("str: |%s|\n", str);
    tokens = my_strtok(&str[12], ';');
    cookie = add_cookie(tokens);
    tmp = create_node(cookie);
	insert_at_head(head, tmp);
    free(tokens);
}


node_t* fill_cookie_jar(ssl_s_t* ssl_data)
{
	char*       str      = NULL;
    node_t*     head     = NULL;
    int         pos      = 0;
    init_my_readline();
	while ((str = my_SSL_readline(ssl_data->ssl)) != NULL)
	{
        if (my_strstr(str, __COOKIE_STR_) != NULL)
        {
            pos = find_ch(str, '\r');
            str[pos] = '\0';
            cookie_splicer(&head, str);
        }
        free(str);
	}
    // print_llist(head);
	flush_buffer();
	free(str);
	return head;
}

cookie_t* add_cookie(char** tokens)
{
    cookie_t* cookie = malloc(sizeof(cookie_t));
    memset(cookie, '\0', sizeof(cookie_t));
    int index = 0;
    set_cookie_name_value(cookie, tokens[index]);
    index += 1;
    while (tokens[index] != NULL)
    {
        printf("token is :|%s|\n", tokens[index]);
        execute_cmd(cookie, tokens[index]);
        index += 1;
    }
    if (cookie->date == NULL)
    {
        cookie->date = my_strdup(__ZERO_STR_);
    }
    return cookie;
}

void free_cookie(cookie_t* cookie)
{
    if (cookie)
    {
        free(cookie->domain);
        free(cookie->subdomain_bool);
        free(cookie->path);
        free(cookie->secure_bool);
        free(cookie->cookie_name);
        free(cookie->cookie_value);
        free(cookie->date);
        free(cookie);
    }
}


void execute_cmd(cookie_t* cookie_jar, char* token)
{
    cmd_ptr_t* cf_ptr = cmd_ptr_map;
    while (cf_ptr->cmd != NULL)
    {
        if (strstr(token, cf_ptr->cmd) != NULL)
        {
            cf_ptr->func_ptr(cookie_jar, token);
            break;
        }
        cf_ptr++;
    }
}

int cookies_len(node_t* head)
{
    int len   = 0;
    int index = 0;
    node_t* iterator = head;
    cookie_t* cookie = NULL;
    while (iterator->next != NULL)
    {
        cookie = iterator->token;
        len += my_strlen(cookie->cookie_name);
        len += my_strlen(cookie->cookie_value);
        len += 3; // extra char '=' & '; ' per cookie
        index += 1;
        iterator = iterator->next;
    }
    return len;
}

char* set_cookies_str(node_t* head)
{
    char* cookies_str = NULL;
    int len = cookies_len(head);
    cookies_str = (char*)malloc(sizeof(char)* len + 1);
    cookies_str[0] = '\0';
    node_t* iterator = head;
    cookie_t* cookie = NULL;
    while (iterator->next != NULL)
    {
        cookie = iterator->token;
        my_strcat(cookies_str, cookie->cookie_name);
        my_strcat(cookies_str, "=");
        my_strcat(cookies_str, cookie->cookie_value);
        my_strcat(cookies_str, "; ");
        iterator = iterator->next;
    }
    return cookies_str;
}



// -----------------------------------------------------------------
void set_cookie_name_value(cookie_t* cookie_jar, char* token)
{
    int pos = find_ch(token, '=');
    token[pos] = '\0';
    cookie_jar->cookie_name  = my_strdup(token);
    cookie_jar->cookie_value = my_strdup(&token[pos + 1]);
}

void set_cookie_domain(cookie_t* cookie_jar, char* token)
{
    int pos = find_ch(token, '=') + 1;
    cookie_jar->domain = my_strdup(&token[pos]);
    if (token[pos] == '.')
    {
        cookie_jar->subdomain_bool = my_strdup(__TRUE_STR_); // Netscape set subdomain to true as default, not sure what to do :/
    }
    else
    {
        cookie_jar->subdomain_bool = my_strdup(__FALSE_STR_);
    }
}

void set_http_only(cookie_t* cookie_jar, char* token)
{
    char* new_str = NULL;
    int len = my_strlen(cookie_jar->domain) + 1 + __HTTP_TOKEN_LEN_;
    new_str = malloc(len);
    my_strcpy(new_str, __HTTP_TOKEN_);
    my_strcat(new_str, cookie_jar->domain);
    free(cookie_jar->domain);
    cookie_jar->domain = new_str;
}

void set_cookie_path(cookie_t* cookie_jar, char* token)
{
    int pos = find_ch(token, '=') + 1;
    cookie_jar->path = my_strdup(&token[pos]);
}

void set_cookie_secure(cookie_t* cookie_jar, char* token)
{
    if (my_strcmp(token, __SECURE_STR_) == 0)
    {
        cookie_jar->secure_bool = my_strdup(__TRUE_STR_); // yuck;
    }
    else
    {
        cookie_jar->secure_bool = my_strdup(__FALSE_STR_);
    }
}

int convert_date_to_second(char* date_str, char* epoch_str)
{
    struct tm tm;
    time_t epoch_time;
    long epoch_seconds;
    char* ret = NULL;
    printf("date is: %s\n", date_str);

    memset(&tm, 0, sizeof(struct tm));
    ret = strptime(date_str, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    if (ret == NULL)
    {
        ret = strptime(date_str, "%a, %d-%b-%Y %H:%M:%S %Z", &tm);
    }
    if (ret == NULL)
    {
        printf("Failed to parse date\n");
        return EXIT_FAILURE;
    }
    epoch_time = mktime(&tm);
    epoch_seconds = (long)epoch_time;
    itoa(epoch_seconds, epoch_str, 10);
    return EXIT_SUCCESS;
}

void set_cookie_date(cookie_t* cookie_jar, char* token)
{
    int pos = find_ch(token, '=') + 1;
    char epoch_str[11] =  {'\0'};
    if (convert_date_to_second(&token[pos], epoch_str))
    {
        cookie_jar->date = my_strdup(__ZERO_STR_);
    }
    else
    {
        cookie_jar->date = my_strdup(epoch_str);
    }
}
