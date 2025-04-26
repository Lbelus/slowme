#include "./error_handler.h"
/*
################ check_error_code #################
# This function checks if an error code was received. 
# @param err_code {int} Error code to check.
# @return {int} EXIT_FAILURE if an error occurred, else EXIT_SUCCESS.
*/
int check_error_code(int err_code, char* domain)
{
  if (err_code)
  {
    if(err_code == -2)
    {
      log_host_error(domain);
      return EXIT_FAILURE;
    }
    perror(gai_strerror(err_code));
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/*################ is_request_complete #################
# This function checks if the HTTP GET request parameters are complete. 
# @return {int} EXIT_FAILURE if an error occurred, else EXIT_SUCCESS.
*/
int is_request_complete(char* path, char* domain)
{
    if (path == NULL || domain == NULL)
    {
        perror(EINCOMPLREQ);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*################ is_not_url #################
# if result is NULL write error an error message and exit. 
# @return {int} EXIT_FAILURE if an error occurred, else EXIT_SUCCESS.
*/
int is_not_url(char* uri)
{
  char* result = fc_strstr(uri, PROTOCOL_SEP);
  if (result == NULL)
  {
    write(STDERR_FILENO, ENOTURL, ENOTURL_SIZE);
    return EXIT_FAILURE;
  }
    return EXIT_SUCCESS;
}

/*
################ log_host_error #################
# This function logs an error message for a given domain that could not be resolved.
# @return {void}
*/
void log_host_error(char* domain)
{
  int len = fc_strlen(domain) + ERESOLVEHOST_SIZE + 1;
  char str[len];
  fc_bzero(str, len);
  fc_strcpy(str, ERESOLVEHOST);
  fc_strcat(str, domain);
  write(STDERR_FILENO, str, len);
}
