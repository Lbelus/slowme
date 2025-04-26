#include "core/curl/curl_api.h"

int main(void)
{
    uri_s_t uri;
    uri = init_my_curl(uri, "https://google.com");
    url_p_s_t* url_s = uri.uri_union.url;
    my_curl(uri);
    clean_my_curl(uri);

    return EXIT_SUCCESS;
}
