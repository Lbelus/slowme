#include "./curl_api.h"

node_t* login(char* username, char* password, char* user_agent_designation, char* url)
{
    node_t* cookie_jar = NULL;
    user_agent_t* user_agent = pick_user_agent(user_agent_designation);
    cookie_jar = get_session_cookie(user_agent, url);
    char* csrf_token = get_csrf_token(cookie_jar);
    char* payload = set_auth_payload(username, password, csrf_token);
    char* cookies_str = set_cookies_str(cookie_jar);
    free_llist(cookie_jar);
    printf("cookies: %s\n", cookies_str);
    printf("payload %s\n", payload);
    cookie_jar = get_auth_cookie(user_agent, cookies_str, payload, url);
    free(cookies_str);
    printf("\ngot cookie_jar\n");
    // free_user_agent(user_agent);
    // free(payload);
    return cookie_jar;
}

url_p_s_t* set_parsed_url_struct(char* url)
{
    uri_s_t uri;
    uri = init_my_curl(uri, url);
    url_p_s_t* url_s = uri.uri_union.url;
    return url_s;
}

node_t* get_session_cookie(user_agent_t* user_agent, char* url)
{
    node_t* cookie_jar = NULL;
    url_p_s_t* url_s = set_parsed_url_struct(url);
    char* user_a_str = msg_user_agent(user_agent->value, user_agent->designation); // refactor here string should be stored on user agent struct
  	url_s->req = create_user_a_get_request_(url_s->path, url_s->domain, user_a_str);
    cookie_jar = get_cookie(url_s);
    return cookie_jar;
}

node_t* get_auth_cookie(user_agent_t* user_agent, char* cookies, char* payload, char* url)
{
    node_t* cookie_jar = NULL;
    url_p_s_t* url_s = set_parsed_url_struct(url);
    printf("host:%s, path:%s\n", url_s->path, url_s->domain);
    char* host_path     = msg_path_host(POST_MSG_P1,url_s->path, url_s->domain);
    char* user_a_str    = msg_user_agent(user_agent->value, user_agent->designation); // refactor here string should be stored on user agent struct
    char* payload_str   = msg_payload(cookies, payload);
    url_s->req          = create_auth_request(host_path, user_a_str, payload_str);
    printf("\n\n\nrequest:\n%s\n\n\n", url_s->req);
    cookie_jar = get_cookie(url_s);
    return cookie_jar;
}

node_t* get_cookie(url_p_s_t*  url_s)
{
    node_t* cookie_jar = NULL;
    cookie_jar = req_cookie(url_s->domain, url_s->req);
    free_url_struct(url_s);
    return cookie_jar;
}
