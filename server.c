#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>

// https://rosettacode.org/wiki/Hello_world/Web_server#C

char response[] = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"Hello world!\r\n";

char buffer[1024];
int bytes = 0;
char *p;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    err(1, "Pass port number as first argument");
  }
  int port = (int)strtol(argv[1], &p, 10);
  int one = 1, client_fd;
  struct sockaddr_in svr_addr, cli_addr;
  socklen_t sin_len = sizeof(cli_addr);

  if (argc < 2 || *p != '\0' || port > 65536 || port == 0) {
    err(1, "Invalid port number");
  }
  
  fprintf(stderr, "Port: %d\n", port);

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    err(1, "can't open socket");
 
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
 
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = INADDR_ANY;
  svr_addr.sin_port = htons(port);
 
  if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
    close(sock);
    err(1, "Can't bind");
  }
 
  listen(sock, 5);

  fprintf(stderr, "Server listening.\n");

  while (1) {
    client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);
    printf("Got connection.\n");
 
    // wait for the client to send the HTTP header
    //memset(buffer, 0, sizeof(buffer));
    do {
      bytes = recv(client_fd, buffer, 1024, 0);
      // printf("%s", buffer);
    } while (bytes==1024);
    printf("Read header.\n");

    if (client_fd == -1) {
      perror("Can't accept connection.");
      continue;
    }
 
    write(client_fd, response, sizeof(response) - 1); /*-1:'\0'*/
    close(client_fd);
    printf("Done.\n");
  }
}
