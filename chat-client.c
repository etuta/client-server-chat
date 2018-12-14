/*
 * chat-client.c
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define BUF_SIZE 4096

// Store the formatted string of time in the output
void format_time(char *output){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    sprintf(output, "%d:%d:%d]", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}



void *receive_from_server (void *fd){
   char buf [BUF_SIZE];

    while (1) {
      int conn_fd = *((int*)fd);
      int n = recv(conn_fd, buf, BUF_SIZE, 0);
      printf("received: %s\n", buf);
      printf("Timestamp: %d\n",(int)time(NULL));
  }
}

int main(int argc, char *argv[])
{
    char *dest_hostname, *dest_port;
    struct addrinfo hints, *res;
    int conn_fd;
    char buf[BUF_SIZE];
    int n;
    int rc;
    pthread_t receiver_thread;

    dest_hostname = argv[1];
    dest_port     = argv[2];

    /* create a socket */
    conn_fd = socket(PF_INET, SOCK_STREAM, 0);

    /* client usually doesn't bind, which lets kernel pick a port number */

    /* but we do need to find the IP address of the server */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if((rc = getaddrinfo(dest_hostname, dest_port, &hints, &res)) != 0) {
        printf("getaddrinfo failed: %s\n", gai_strerror(rc));
        exit(1);
    }

    /* connect to the server */
    if(connect(conn_fd, res->ai_addr, res->ai_addrlen) < 0) {
        perror("connect");
        exit(2);
    }

    printf("Connected\n");
  	pthread_create(&receiver_thread, NULL, &receive_from_server, (void*) &conn_fd);
    /* infinite loop of reading from terminal, sending the data, and printing
     * what we get back */
    while((n = read(0, buf, BUF_SIZE)) > 0) {
        send(conn_fd, buf, n, 0);
        puts(buf);
    }

    close(conn_fd);
}
