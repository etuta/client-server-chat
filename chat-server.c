/*
 * chat-server.c
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BACKLOG 10
#define BUF_SIZE 4096
#define MAX_CLIENTS 100

int thread_conn_fds[MAX_CLIENTS];


void *server_handler (void *fd)
{

  int conn_fd = *((int*)fd);

  printf ("server_handler %d\n", conn_fd);
  char buf[BUF_SIZE];
  size_t bytes_received;
  /* receive and echo data until the other end closes the connection */
  while((bytes_received = recv(conn_fd, buf, BUF_SIZE, 0)) > 0) {
    printf("Server received %s\n", buf);
    fflush(stdout);

    /* send it back */
    /*
    send(conn_fd, buf, bytes_received, 0);
    */
    int i;
    for (i=0; i<MAX_CLIENTS; ++i) {
        if (thread_conn_fds[i] != -1) {
          	printf("Server sending %s to %d\n", buf, thread_conn_fds[i]);
    		send(thread_conn_fds[i], buf, bytes_received, 0);
        }
    }


  }
  printf("\n");

  close(conn_fd);
}

int main(int argc, char *argv[])
{
	char *listen_port;
    int listen_fd, conn_fd;
    struct addrinfo hints, *res;
    int rc;
    struct sockaddr_in remote_sa;
    struct sockaddr_in cliaddr, servaddr;
    uint16_t remote_port;
    socklen_t addrlen;
    socklen_t clilen;
    char *remote_ip;
    char buf[BUF_SIZE];
    int bytes_received;
    pthread_t threads[MAX_CLIENTS];
  	int i;

    for (i=0; i<MAX_CLIENTS; ++i)
      thread_conn_fds[i] = -1;


    listen_port = argv[1];

    /* create a socket */
    listen_fd = socket(PF_INET, SOCK_STREAM, 0);

    if (listen_fd == -1){
        perror("Could not create socket \n");
    }

    /* bind it to a port */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if((rc = getaddrinfo(NULL, listen_port, &hints, &res)) != 0) {
        printf("getaddrinfo failed: %s\n", gai_strerror(rc));
        exit(1);
    }

    bind(listen_fd, res->ai_addr, res->ai_addrlen);

    /* start listening */
    listen(listen_fd, BACKLOG);

    /* infinite loop of accepting new connections and handling them */
    int client_count = 0;
    while(1) {
     /*while((conn_fd = accept (listen_fd, (struct sockaddr_in *) &cliaddr, &clilen)))
     pthread_t server_thread;
     new_sock = malloc(1);
     *new_sock = conn_fd;
     pthread_create (&server_thread, NULL, server_handler, (void*) new_sock);*/

        /* accept a new connection (will block until one appears) */
        addrlen = sizeof(remote_sa);
        conn_fd = accept(listen_fd, (struct sockaddr *) &remote_sa, &addrlen);
		  /* announce our communication partner */
        remote_ip = inet_ntoa(remote_sa.sin_addr);
        remote_port = ntohs(remote_sa.sin_port);
        thread_conn_fds[client_count] = conn_fd;

        printf("new connection from %s:%d\n", remote_ip, remote_port);

      	pthread_create(&threads[client_count], NULL, &server_handler, (void*) &conn_fd);

        ++client_count;
    }
}
