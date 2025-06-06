#include "./parser.h"

/*
################ token_array_size #################
# This function calculates the number of tokens in an array of char* 
# @return {int} Size of token array
*/

int token_array_size(char** resp_tokens)
{
    int index = 0;
    while (resp_tokens[index] != NULL)
    {
        index += 1;
    }
    return index - 1;
}

/*
################ set_response_code #################
# This function extracts the response code from a given response string.
# @return {char*} Extracted response code
*/
char* set_response_code(char* response)
{
    int len = fc_strlen(response);
    char* str_cpy = malloc(sizeof(char) * len + 1);
    fc_bzero(str_cpy, len + 1);
    fc_memcpy(str_cpy, &response[7], len + 1);
    char** tokens = fc_strtok(str_cpy, '\n');
    int len_code = fc_strlen(&tokens[1][2]);
    char* result = malloc(sizeof(char) * len_code + 1);
    fc_memcpy(result, &tokens[1][2], len_code + 1);
    free(tokens);
    free(str_cpy);
    return result;
}
