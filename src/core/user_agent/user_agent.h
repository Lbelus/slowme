#ifndef __USER_AGENT_HEADER_
#define __USER_AGENT_HEADER_

#include <fcntl.h>
#include <stdlib.h>
#include "../../utils/string/fc_string.h"
#include "../parser/parser.h"
#include "../cookie_jar/cookie_jar.h"

#ifndef _USER_AGENT_STRUCT_
#define _USER_AGENT_STRUCT_
struct user_agent_s
{
    char* designation;
    char* value;
};
typedef struct user_agent_s user_agent_t; 
#endif


// void free_llist(node_t* head);
user_agent_t*   pick_user_agent(char* designation);
user_agent_t*   set_user_agent(char* designation, char* value);
int             free_user_agent(user_agent_t* user_agent);


#endif
