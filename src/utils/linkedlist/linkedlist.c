// #include <main_header.h>
#include "./linkedlist.h"
#include "../../core/cookie_jar/cookie_jar.h"


node_t* create_node(void* token)
{
    node_t* new_node = malloc(sizeof(node_t));
    new_node->token = token;
    new_node->next = NULL;
    new_node->head = NULL;
    return new_node;
}

void insert_at_head(node_t** head, node_t* node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
}

void print_llist(node_t* head)
{
    node_t* iterator = head;
    cookie_t* cookie = NULL;
    printf("printing the llist:\n");
    while (iterator != NULL)
    {
        cookie = (cookie_t*)iterator->token;
        printf("%s\t", cookie->domain);
        printf("%s\t", cookie->subdomain_bool);
        printf("%s\t", cookie->path);
        printf("%s\t", cookie->secure_bool);
        if (cookie->date)
        {
            printf("%s\t", cookie->date);
        }
        printf("%s\t", cookie->cookie_name);
        printf("%s\t", cookie->cookie_value);
        printf("\n");
        iterator = iterator->next;
    }
    printf("NULL\n");
}

void free_llist(node_t* head)
{
    node_t* tmp = NULL;
    cookie_t* cookie = NULL;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        cookie = (cookie_t*)tmp->token;
        free_cookie(cookie);
        free(tmp);
    }
}
