#include "./fc_string.h"   

void fc_bzero(void *generic_ptr, size_t n)
{ // void* p ; generic pointer type. can be converted to any type without "explicit" cast,  // size_t is for array indexing and loop counting
    
    if (generic_ptr == NULL)
    {
        return; // stop if the generic_ptr is NULL
    }
    char *arr = generic_ptr; // generic pointers cannot be dereferenced, must convert to a pointer before using it. 
    size_t i;
    for (i = 0; i < n; ++i)
    {
        arr[i] = '\0';
    }
}

void* fc_memcpy(void* dest, void* src, int len)
{
    int index = 0;
    char *arr_d = dest;
    char *arr_s = src;
    while (index < len)
    {
        arr_d[index] = arr_s[index];
        index +=1;
    }
    return dest;
}


void* fc_memset(void* ptr, char ch, int len)
{
    int index = 0;
    char* ptr_a = ptr;
    while (index < len)
    {
        ptr_a[index] = ch;
        index += 1;
    }
    return ptr_a;
}

char* fc_strcat(char* str_dest, char* str_src)
{
    int dest_len = fc_strlen(str_dest);
    int index = 0;
    while (str_src[index] != '\0')
    {
        str_dest[dest_len + index] = str_src[index];
        index += 1;
    }
    str_dest[dest_len + index] = '\0';
    return str_dest;
}

char* fc_strchr(char* str, char ch)
{
    int len = fc_strlen(str);
    int index = 0;
    while (str[index] != ch && str[index] != '\0')
    {
        index += 1;
        if (index == len)
        {
            return NULL;
        }
    }
    return &str[index];
}

int fc_strcmp(char* str1, char* str2)
{
    int index = 0;
    char ch1 = str1[index], ch2 = str2[index];
    while (ch1 == ch2)
    {
        ch1 = str1[index];
        ch2 = str2[index];
        if (ch1 == '\0')
        {
            return ch1 - ch2;
        }
        index += 1;
    }
    return ch1 - ch2;
}


char* fc_strcpy(char* str_dest, char* str_src)
{
    int len = fc_strlen(str_src);
    int index = 0;
    while (index < len)
    {
        str_dest[index] = str_src[index];
        index += 1;
    }
    str_dest[index] = '\0';
    return str_dest;
}

char* fc_strdup(char* str)
{
    int len = fc_strlen(str);
    if (len == 0)
    {
        return NULL;
    }
    char* new_str = malloc(sizeof(char) * (len + 1));
    if (new_str == NULL)
    {
        return NULL;
    }
    fc_memcpy(new_str, str, len);
    new_str[len] = '\0';
    return new_str;
}


int fc_strlen(char* str)
{
    int len = 0;
    if (str == NULL)
    {
        return len;
    }
    while (str[len] != '\0')
    {  
        len += 1;
    }
    return len;
}

int fc_strncmp(char* str1, char* str2, int len)
{
    int index = 0;
    char ch1 = str1[index], ch2 = str2[index];
    while (ch1 == ch2 && index < len)
    {
        ch1 = str1[index];
        ch2 = str2[index];
        if (ch1 == '\0')
        {
            return ch1 - ch2;
        }
        index += 1;
    }
    return ch1 - ch2;
}

char* fc_strstr(char *str, char *substr)
{
    char* ptr_a;
    char* ptr_b;
    while (*str != '\0')
    {
        ptr_a = str;
        ptr_b = substr;
    while (*ptr_a != '\0' && 
        *ptr_b != '\0' && 
        *ptr_a == *ptr_b)
    {
        ptr_a++;
        ptr_b++;
    }
    if (*ptr_b == '\0')
    {
      return (char *) str;
    }
    str++;
  }
  return NULL;
}

int find_ch(char* str, char ch)
{
    int index = 0;
    while (str[index] != ch && str[index] != '\0')
    {
      index += 1;
    }
    return index;
}


char** fc_strtok(char* str, char ch)
{
    char** tokens = malloc(sizeof(char*) * MAX_INPUT_TOKENS);
    char* start = str;
    char* end;
    int index = 0;
    int pos = 0;
    while ((end = fc_strchr(start, ch)) != NULL)
    {
        pos = find_ch(start, ch);
        start[pos] = '\0';
        tokens[index] = start;
        index += 1;
        start = end + 1;
    }
    tokens[index] = start;
    index += 1;
    tokens[index] = NULL;
    return tokens;
}


