#include <fc_curl.h>



int main(void)
{
    uri_s_t uri = {0};
    uri = init_fc_curl(uri, "https://www.google.com");
    // url_p_s_t* url_s = uri.uri_union.url;
    fc_curl(uri);
    clean_fc_curl(uri);

    return EXIT_SUCCESS;
}
