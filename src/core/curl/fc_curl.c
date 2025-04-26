#include "../../../include/uri_struct.h"
#include <stdlib.h>
#include "../error_handler/error_handler.h"


int     perform_get_request(char* domain,  char* get, int protocol_type);
/*
################ init_fc_curl #################
# This function initializes a 'fc_curl' request based on the given URI and user argument.
# @return {uri_s_t} Initialized uri_s_t structure
*/
uri_s_t init_fc_curl(uri_s_t  uri, char* user_arg)
{
    int protocol_type = 0;
    uri.type_uri = 0;
    if (is_not_url(user_arg))
    {
        /* placeHolder to handle URI */
        return uri;
    }
    else
    {
        if ((protocol_type = get_protocol_from_url(user_arg)))
        {
            uri.type_uri = URL;
            uri.uri_union.url = fc_url_parser(user_arg);
            uri.uri_union.url->protocol = protocol_type;
            return uri;
        }
        else
        {
            /* placeHolder to handle unknow protocols */
            return uri;
        }
    }
    return uri;
}

/*
################ fc_curl #################
# This function performs a curl-like request using the provided uri_s_t structure.
# @return {int} Status of the request (EXIT_FAILURE or the result of perform_get_request)
*/
int fc_curl(uri_s_t  uri)
{
    int exit_status = EXIT_FAILURE;
    if (uri.type_uri == 0)
    {
        return EXIT_FAILURE;
    }
    if (uri.type_uri == URL)
    {
        url_p_s_t* url_s = uri.uri_union.url;
        exit_status = perform_get_request(url_s->domain, url_s->req, url_s->protocol);
        return exit_status;
    }
    return EXIT_FAILURE;
}



/*
################ clean_fc_curl #################
# This function cleans up resources associated with the provided uri_s_t structure.
# @return {int} Status of the cleanup (EXIT_FAILURE or EXIT_SUCCESS)
*/
int clean_fc_curl(uri_s_t  uri)
{
    if (uri.type_uri == 0)
    {
        return EXIT_FAILURE;
    }
    else if (uri.type_uri == URL)
    {
        url_p_s_t* url_s = uri.uri_union.url;
        free_url_struct(url_s);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
