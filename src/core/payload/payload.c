#include "./payload.h"

char* get_csrf_token(node_t* head)
{
    node_t* iterator    = head;
    cookie_t* cookie    = NULL;
    int len = 0;
    while (iterator != NULL)
    {
        cookie = (cookie_t*)iterator->token;
        if (my_strstr(cookie->cookie_name, __AJAX_STR_))
        {   
            return cookie->cookie_value;
        }
        iterator = iterator->next;
    }
    return NULL;
}

// // PAYLOAD="session_key=$USERNAME&session_password=$PASSWORD&JSESSIONID=$CSRF_TOKEN"

char* crop_csrf_token(char* csrf_token)
{
    int index       = 1;
    int pos         = 0;
    int len         = 0; 
    char* cpy_str   = NULL;
    len             = my_strlen(csrf_token) - 1;
    cpy_str         = (char*)malloc(sizeof(char) * len);
    while (index < len)
    {
        cpy_str[pos] = csrf_token[index];
        pos += 1;
        index += 1;
    }
    cpy_str[pos] = '\0';
    return cpy_str;
}

char* set_auth_payload(char* username, char* password, char* csrf_token)
{
    char* new_token     = NULL;
    char* payload_str   = NULL;
    new_token   = crop_csrf_token(csrf_token);
    payload_str = concat_string(6,
    PAYLOAD_USERN,
    username,
    PAYLOAD_PASSW,
    password,
    PAYLOAD_SESSI,
    new_token
    );
    free(new_token);
    return payload_str;
}

