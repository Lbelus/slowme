#include <my_user_agent.h>

user_agent_t* pick_user_agent(char* designation)
{
    user_agent_t*   user_agent  = NULL;
    char*           str         = NULL;
    int             pos         = 0;
	int             fd          = 0;
    fd = open("./user_agents/user_agents.txt", O_RDONLY, 400);
    init_my_readline();
	while ((str = my_readline(fd)) != NULL)
	{
        if (my_strstr(str, designation) != NULL)
        {
            pos = find_ch(str, '=');
            str[pos] = '\0';
            user_agent = set_user_agent(designation, &str[pos + 1]);
            fd = -1;
        }
        free(str);
	}
	flush_buffer();
	return user_agent;
}

user_agent_t* set_user_agent(char* designation, char* value)
{
    user_agent_t* user_agent = NULL;
    user_agent = malloc(sizeof(user_agent_t));
    user_agent->designation = my_strdup(designation);
    user_agent->value = my_strdup(value);
    return user_agent;
}

int free_user_agent(user_agent_t* user_agent)
{
    free(user_agent->designation);
    free(user_agent->value);
    free(user_agent);
    return EXIT_SUCCESS;
}
