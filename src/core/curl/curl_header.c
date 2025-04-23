#include "./curl_header.h"
#include "../user_agent/user_agent.h"


char* itoa(long long value, char* result, int base);

char* concat_string(int argc, ...)
{
    int len = 0;
    int index = 0;
    char* result = NULL;
	va_list ap;
    va_start(ap, argc);
    while (index < argc)
    {
        len += my_strlen(va_arg(ap, char*));
        index += 1;
    }
    result = (char*)malloc(sizeof(char)* len + 1);
	result[0] = '\0';
    va_start(ap, argc);
    index = 0;
    while (index < argc)
    {
        my_strcat(result, va_arg(ap, char*));
        index += 1;
    }
    return result;
}

char* create_get_request(char* path, char* domain)
{
	if (is_request_complete(path, domain))
	{
		return NULL;
	}
	char* new_req = concat_string(6, 
		GET_MSG_P1,
		path,
		REQ_MSG_P2,
		domain,
		REQ_MSG_P3
		);
	return new_req;
}


char* create_user_a_get_request_(char* path, char* domain, char* user_agent_data)
{
	if (is_request_complete(path, domain))
	{
		return NULL;
	}
	char* new_req = concat_string(7, 
		GET_MSG_P1,
		path,
		REQ_MSG_P2,
		domain,
		user_agent_data,
		REQ_MSG_P3
		);
		free(user_agent_data);
	return new_req;
}

char* msg_path_host(char* type_req, char* path, char* domain)
{
	if (is_request_complete(path, domain))
	{
		return NULL;
	}
	char* msg = NULL;
	msg = concat_string(4, 
		type_req,
		path,
		REQ_MSG_P2,
		domain
	);
	return msg;
}

char* msg_user_agent(char* x_li_user_agent, char* user_agent)
{
	char* msg = NULL;
	msg = concat_string(7,
		X_LI_USER_AGENT_STR,
		x_li_user_agent,
		USER_AGENT,
		user_agent,
		X_USER_LANGUAGE,
		X_USER_LOCALE,
		ACCEPT_LANGUAGE
	);
	return msg;
}

void get_content_len(char* payload, char* content_len)
{
	int len = my_strlen(payload);
	itoa(len, content_len, 10);
}

char* msg_payload(char* cookies, char* payload)
{
	char content_len[7] = {'\0'};
	get_content_len(payload, content_len);
	char* msg = NULL;
	msg = concat_string(7,
		CONTENT_TYPE,
		CONTENT_LENGTH,
		content_len,
		COOKIE,
		cookies,
		REQ_MSG_P3,
		payload
	);
	return msg;
}


char* msg_cookie(char* cookies, char* csrf_token)
{
	char* new_token = crop_csrf_token(csrf_token);
	char* msg = NULL;
	msg = concat_string(6,
		ACCEPT_TYPE,
		CSRF_HEADER,
		new_token,
		COOKIE,
		cookies,
		REQ_MSG_P3
	);
	free(new_token);
	return msg;
}


char* create_auth_request(char* msg_p1, char* msg_p2, char* msg_p3)
{
	char* new_req = concat_string(3, 
		msg_p1,
		msg_p2,
		msg_p3
	);
	free(msg_p1);
	free(msg_p2);
	free(msg_p3);
	return new_req;
}
