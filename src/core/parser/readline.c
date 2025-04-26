#include "./parser.h"

int READLINE_READ_SIZE = 256;
char* rl_buff;

char* init_fc_readline()
{
    rl_buff = malloc(sizeof(char) * READLINE_READ_SIZE);
    fc_memset(rl_buff, '\0',READLINE_READ_SIZE);
    return rl_buff;
}

int fc_realloc_rl(int size)
{
    int size_buff = 0;
    size_buff = fc_strlen(rl_buff) + 1;
    char tmp_buff[size_buff];
    int total_size = size + size_buff;
    fc_strcpy(tmp_buff, rl_buff);
    free(rl_buff);
    rl_buff = malloc(total_size + 1);
    fc_strcpy(rl_buff, tmp_buff);
    rl_buff[size_buff] = '\0';
    return size + size_buff;
}

int seek_newline(int size)
{
    int len = 0;
    while (rl_buff[len] != '\n' && rl_buff[len] != '\0' && len < size - 1 )
    {
        len += 1;
    }
    return len;
}

bool is_newline(int size)
{
    int len = 0;
    while (rl_buff[len] != '\n' && len < size - 1)
    {
        len += 1;
    }
    if (len == size -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}


char* fc_readline(int fd)
{
    if (fd == -1)
    {
        free(rl_buff);
        rl_buff = NULL;
        return rl_buff;
    }

    char* new = NULL;
    char tmp_buff[READLINE_READ_SIZE];
    char tmp;
    int cursor = 0; 
    int len = 0;
    int size = 0;
    int index = 0;
    int jndex = 0;
    int byte_count = 0;

    size = fc_strlen(rl_buff) + 1;
    cursor = seek_newline(size);
    // fill buff
    while (is_newline(size) == false 
        && (byte_count = read(fd, tmp_buff, READLINE_READ_SIZE - 1)))
    {
        tmp_buff[byte_count] = '\0';
        fc_realloc_rl(byte_count);
        fc_strcat(rl_buff, tmp_buff);
        size = fc_strlen(rl_buff) + 1;
        cursor = seek_newline(size);
    }
    new = malloc(sizeof(char)*cursor +1);
    //copy line
    while (index < cursor )
    {
        new[index] = rl_buff[index];
        index += 1;
    }

    new[index] = '\0';
    index += 1;
    len = size - 1;

    // reset variables to complete buffer flush;
    if (index == size)
    {
        index = 1;
        len = 0;
    }
    // partial or complete buffer flush;
    while (size - index)
    {
        tmp = rl_buff[index];
        rl_buff[jndex] = tmp;
        if (index > len)
        {
            rl_buff[jndex] = '\0';
        }
        index += 1;
        jndex += 1;
    }
    //enter exit state once buffer has been flushed 
    if (cursor == 0 && byte_count == 0 && rl_buff[0] == '\0')
    {
        if (size == 1)
        {
            free(new);
            free(rl_buff);
            rl_buff = NULL;
            return rl_buff;
        }
    }
    return new;
}


char* fc_SSL_readline(SSL* ssl)
{
    if (ssl == NULL)
    {
        free(rl_buff);
        rl_buff = NULL;
        return rl_buff;
    }

    char* new = NULL;
    char tmp_buff[READLINE_READ_SIZE];
    char tmp;
    int cursor = 0; 
    int len = 0;
    int size = 0;
    int index = 0;
    int jndex = 0;
    int byte_count = 0;

    size = fc_strlen(rl_buff) + 1;
    cursor = seek_newline(size);
    // fill buff
    while (is_newline(size) == false 
        && (byte_count = SSL_read(ssl, tmp_buff, READLINE_READ_SIZE - 1)))
    {
        if (byte_count == -1)
        {
            return NULL;
        }

        printf("byte count is:%i\n", byte_count);
        tmp_buff[byte_count] = '\0';
        fc_realloc_rl(byte_count);
        fc_strcat(rl_buff, tmp_buff);
        size = fc_strlen(rl_buff) + 1;
        cursor = seek_newline(size);
    }
    new = malloc(sizeof(char)*cursor + 1);
    //copy line
    while (index < cursor)
    {
        new[index] = rl_buff[index];
        index += 1;
    }

    new[index] = '\0';
    index += 1;
    len = size - 1;

    // reset variables to complete buffer flush;
    if (index == size)
    {
        index = 1;
        len = 0;
    }
    // partial or complete buffer flush; 
    while (size - index)
    {
        tmp = rl_buff[index];
        rl_buff[jndex] = tmp;
        if (index > len)
        {
            rl_buff[jndex] = '\0';
        }
        index += 1;
        jndex += 1;
    }
    //enter exit state once buffer has been flushed 
    if (cursor == 0 && byte_count == 0 && rl_buff[0] == '\0')
    {
        if (size == 1)
        {
            free(new);
            free(rl_buff);
            rl_buff = NULL;
            return rl_buff;
        }
    }
    return new;
}



void flush_buffer()
{
    int len = fc_strlen(rl_buff);
    write(STDOUT_FILENO, rl_buff, len);
    free(rl_buff);
    // flushall();
    // fc_bzero(rl_buff, READLINE_READ_SIZE);
}
