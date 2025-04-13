#include "./parser.h"
/*
################ set_var #################
# Allocates memory for a new string and copies a given number of characters from the source string into the new string.
# @param src {char*} Source string.
# @param len {int} The length of the string to copy from the source string.
# @return {char*} Returns a pointer to the newly allocated string.
*/
char* set_var(char* src, int len)
{
  	char* new_str = malloc(sizeof(char)*len + 1);
  	my_bzero(new_str, len + 1);
  	my_memcpy(new_str, src, len);
  	return new_str;
}

int diff_len(char* str1, char* str2)
{
	int len_a 	= 0;
	int len_b 	= 0;
	int result 	= 0; 
	len_a = my_strlen(str1);
	len_b = my_strlen(str2);
	result = len_a - len_b;
	return result;
}

/*
################ set_parse_struct #################
# Sets the domain, path, and GET request for a given URL parsing structure.
# The domain and path are determined from the source string, and the GET request is created from the domain and path.
# @param url {url_p_s_t*} Pointer to the URL parsing structure.
# @param domain {char*} Pointer to the start of the domain in the source string.
# @param path {char*} Pointer to the start of the path in the source string.
# @return {void}
*/
void set_parse_struct(url_p_s_t* url_s, char* domain, char* path)
{
	int len_dom = diff_len(domain, path);
  	int len_path = my_strlen(path) + 1;
  	url_s->domain = set_var(domain, len_dom);
	// url_s->domain[len_dom]= '\0';
	if (path == NULL)  // dirty patch starts
	{
		url_s->path = set_var("/\0", 1);	
	}
	else
	{
		url_s->path = set_var(path, len_path);
		// url_s->path[len_path] = '\0';
	} // dirty patch ends
  	// url_s->req = create_get_request(url_s->path, url_s->domain);
}

/*
################ get_protocol_from_url #################
# This function determines the protocol used in a given URL.
# @return {protocol_enum} Identified protocol from the URL
*/
protocol_enum get_protocol_from_url(char* url)
{
    if (my_strncmp(url, _HTTP__, _HTTP_LEN_) == 0)
	{
        return PROTOCOL_HTTP;
    } 
	else if (my_strncmp(url, _HTTPS__, _HTTPS_LEN_) == 0)
	{
        return PROTOCOL_HTTPS;
    } 
	else
	{
        return PROTOCOL_UNKNOWN;
    }
}

/*
################ my_urL_parser #################
# Parses a URL into its domain and path components, and then creates a GET request.
# @return {url_p_s_t*} A pointer to the parsed URL structure, which contains the domain, path, and GET request.
*/
url_p_s_t* my_url_parser(char* url)
{
  	url_p_s_t* url_s = malloc(sizeof(url_p_s_t));
  	char* ptr_doma = NULL;
  	char* ptr_path = NULL;
  	ptr_doma  = my_strstr(url, PROTOCOL_SEP);
	if (ptr_doma == NULL)
	{
		log_host_error(url);
		free(url_s);
		return NULL;
	}
  	ptr_path = my_strchr(&ptr_doma[3], PATH_SEP);
  	set_parse_struct(url_s, &ptr_doma[3], ptr_path);  
  	// if (url_s->req == NULL)
  	// {
    // 	return NULL;
  	// }
  	return url_s;
}
/*
################ free_url_struct #################
# Frees the allocated memory of the given URL parsing structure.
# @param url {url_p_s_t*} Pointer to the URL parsing structure to be freed.
# @return {void}
*/
void free_url_struct(url_p_s_t* url)
{
  	free(url->domain);
  	free(url->path);
  	free(url->req);
  	free(url);
}
