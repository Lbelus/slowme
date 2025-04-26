#ifndef __STRING_HEADER_
#define __STRING_HEADER_

//fc_string.h
// #include <common.h>
#include <stdlib.h>
#include <stddef.h>


#define MAX_INPUT_TOKENS  1000
#define ANSWER_BUFFER_SIZE 4096

int     fc_strlen(char *str);
char*   fc_strcat(char* str_dest, char* str_src);
char*   fc_strcpy(char* str_dest, char* str_src);
char*   fc_strchr(char* str, char ch);   
int     fc_strcmp(char* str1, char* str2);
int     fc_strncmp(char* str1, char* str2, int len);
char*   fc_strdup(char* str);                       
char*   fc_strstr(char* str, char* substr);
void*   fc_memset(void* ptr, char ch, int len);
void*   fc_memcpy(void* dest, void* src, int len);  //fc_strdup
void    fc_bzero(void *generic_ptr, size_t n);
int     find_ch(char* str, char ch);
char**  fc_strtok(char* str, char ch);

#endif
