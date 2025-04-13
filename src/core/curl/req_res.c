#include <main_header.h>
#include "./ssl_header.h"
#include "../cookie_jar/cookie_jar.h"
#include "../../../include/uri_struct.h"
#include "../../utils/linkedlist/linkedlist.h"
#include "../error_handler/error_handler.h"



//HTTP

/*
################ send_get_req #################
# Sends a GET request to a socket identified by the sockfd parameter.
# The function also checks for errors, and if an error occurs, it prints out the error message and the error code.
# @return {int} Returns EXIT_SUCCESS if the request is sent successfully, otherwise returns EXIT_FAILURE.
*/
int send_get_req(char* get, int sockfd)
{
  	int len = my_strlen(get);
  	int err_code;
  	err_code = send(sockfd, get, len, 0);
  	if (err_code == -1)
  	{
    	perror(ESENDREQUEST);
    	printf("errcode: %d", errno);
    	return EXIT_FAILURE;
  	}
  	return EXIT_SUCCESS;
}

// /*
// ################ r_socket_w_out #################
// # Reads data from a socket, identified by the sockfd parameter, and writes the read data to the standard output.
// # Once all the data is read, the socket is closed.
// # @return {void}
// */
node_t* set_http_responser_header(int sockfd)
{
	char* 	str  = NULL;
	node_t* head = NULL;
	node_t* tmp  = NULL;
	int index = 0;
	printf("start response header:\n\n\n");
    while ((str = my_readline(sockfd)) != NULL // optimization => "\r" search should be implemented at readline level
	&& my_strcmp(str, "\r") != 0)
    {
		printf("%s\n", str);
		// tmp = create_node(str);
		// insert_at_head(&head, tmp);
		index += 1;
		free(str);
	}
	printf("encountered a \\r end of known header\n\n\n");
	flush_buffer();
	free(str);
	return head;
}

int r_socket_w_out(int sockfd)
{
	node_t* head = NULL;
	node_t* tmp  = NULL;
	char* 	str  = NULL;
    char 	buffer[ANSWER_BUFFER_SIZE];
	int 	size_read = 0;
	init_my_readline();
	head = set_http_responser_header(sockfd);
	my_memset(buffer, 0, ANSWER_BUFFER_SIZE); 
 	while (size_read = read(sockfd, buffer, ANSWER_BUFFER_SIZE))
 	{
    	write(STDOUT_FILENO, buffer, size_read);
    	my_memset(buffer, 0, ANSWER_BUFFER_SIZE);
   	}
	// free_llist(head);
  	close(sockfd);
	return EXIT_SUCCESS;
}

// /*
// ################ connect_to_server #################
// # Connects a socket, identified by the sockfd parameter, to a server defined by the servinfo parameter.
// # If the connection fails, the function prints an error message, frees the servinfo structure, and closes the socket.
// # @return {int} Returns EXIT_SUCCESS if the socket is connected successfully, otherwise returns EXIT_FAILURE.
// */
int connect_to_server(int sockfd, struct addrinfo* servinfo)
{
	if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		perror("Error: could not connect socket");
    	freeaddrinfo(servinfo);
    	close(sockfd);
    	return EXIT_FAILURE;
  	}
  	return EXIT_SUCCESS;
}

// /*
// ################ perform_get_request #################
// # Performs a GET request on the specified domain with the provided GET request string.
// # The response from the server is printed to the standard output.
// # @return {int} Returns 0 after successfully executing the function.
// */
int http_request(char* domain,  char* get)
{
	int sockfd;
  	int err_code;
  	struct addrinfo hints, *servinfo;
  	my_memset(&hints, 0, sizeof hints);
  	hints.ai_family = AF_INET;
  	hints.ai_socktype = SOCK_STREAM;
  	err_code = getaddrinfo(domain, __PORT__, &hints, &servinfo);
  	if (check_error_code(err_code, domain))
  	{
    	return EXIT_FAILURE;
  	}
  	sockfd = socket(AF_INET, SOCK_STREAM, 0);
  	connect_to_server(sockfd, servinfo);
  	freeaddrinfo(servinfo);
  	if (send_get_req(get, sockfd))
  	{
    	return EXIT_FAILURE;
  	}
  	r_socket_w_out(sockfd);
  	return EXIT_SUCCESS;
}

/*----------------------------------------------------*/
//HTTPS

ssl_s_t* init_open_ssl()
{
	SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
	ssl_s_t* ssl_data = malloc(sizeof(ssl_s_t));
	return ssl_data; 
}

int create_ssl_context(ssl_s_t* ssl_data)
{
    ssl_data->method = TLS_client_method();
    ssl_data->ctx = SSL_CTX_new(ssl_data->method);

    if (ssl_data->ctx == NULL)
	{
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }
	return EXIT_SUCCESS;
}

int create_ssl_connection(ssl_s_t* ssl_data)
{
    ssl_data->ssl = SSL_new(ssl_data->ctx);
    if (ssl_data->ssl == NULL) {
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }
	return EXIT_SUCCESS;
}

int perform_context_and_connection(ssl_s_t* ssl_data)
{
	if (create_ssl_context(ssl_data))
	{
		return EXIT_FAILURE;
	}
	if (create_ssl_connection(ssl_data))
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int tsl_handshake(ssl_s_t* ssl_data)
{
	if (SSL_connect(ssl_data->ssl) <= 0)
	{
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }
	else
	{
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl_data->ssl));
    }
	return EXIT_SUCCESS;
}

int create_socket(char *hostname, int port)
{
    int sockfd;
    struct sockaddr_in addr;
    struct hostent *host;
    host = gethostbyname(hostname);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
	{
        perror("Socket creation failed");
        return -1;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long *)(host->h_addr);
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
        perror("Socket connection failed");
        close(sockfd);
        return -1;
    }
    return sockfd;
}

int cleanup_ssl(ssl_s_t* ssl_data, int sockfd)
{

	SSL_free(ssl_data->ssl);
    close(sockfd);
    SSL_CTX_free(ssl_data->ctx);
	free(ssl_data);
}

int write_https_req(ssl_s_t* ssl_data, char* get)
{
	if (SSL_write(ssl_data->ssl, get, my_strlen(get)) <= 0)
	{
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }
	return EXIT_SUCCESS;
}

int read_https_res(ssl_s_t* ssl_data)
{
	int bytes = 0;
	char buffer[1024];
    while ((bytes = SSL_read(ssl_data->ssl, buffer, sizeof(buffer) - 1)) > 0)
	{
        buffer[bytes] = '\0';
        printf("%s\n", buffer);
    }
	return EXIT_SUCCESS;
}

int https_w_req_r_res(ssl_s_t* ssl_data, char* get)
{
	if (write_https_req(ssl_data, get))
	{
		return EXIT_FAILURE;
	}
	read_https_res(ssl_data);
	return EXIT_SUCCESS;
}

int https_request(char* domain, char* get)
{
	ssl_s_t* ssl_data = init_open_ssl();
	if (perform_context_and_connection(ssl_data))
	{
		return EXIT_FAILURE;
	}
	int sockfd = create_socket(domain, 443);
    SSL_set_fd(ssl_data->ssl, sockfd);
	tsl_handshake(ssl_data);
	https_w_req_r_res(ssl_data, get);
	cleanup_ssl(ssl_data, sockfd);
	return EXIT_SUCCESS;
}

node_t* req_cookie(char* domain, char* get)
{
	node_t* head = NULL;
	ssl_s_t* ssl_data = init_open_ssl();
	if (perform_context_and_connection(ssl_data))
	{
		return NULL;
	}
	int sockfd = create_socket(domain, 443);
    SSL_set_fd(ssl_data->ssl, sockfd);
	tsl_handshake(ssl_data);
	write_https_req(ssl_data, get);
	head = fill_cookie_jar(ssl_data);
	cleanup_ssl(ssl_data, sockfd);
	return head;
}

int perform_get_request(char* domain,  char* get, int protocol_type)
{
	int exit_status = EXIT_FAILURE;
	if (protocol_type == PROTOCOL_HTTP)
	{
		exit_status = http_request(domain, get);
	}
	else if (protocol_type == PROTOCOL_HTTPS)
	{
		exit_status = https_request(domain, get);
	}
	return exit_status;
}
