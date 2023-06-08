#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
	perror(msg);
	exit(1);
}

// ss dst 127.0.0.1 -p (to view connections)
// ps -aux | grep server2
int main(int argc, char *argv[]) {
	int sockfd, portno, n;
	short s1;

	struct sockaddr_in serv_addr, cli_addr;
	struct hostent *server;
	
	if(argc < 3) {
		fprintf(stderr, "Usage: '%s hostname port'. \n", argv[0]);
		exit(0);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	portno = atoi(argv[2]);
	
	if(sockfd < 0) {
		error("Error while opening port");
	}
	
	server = gethostbyname(argv[1]);
	
	if(server == NULL) {
		fprintf(stderr, "Error, no such host found.");
		exit(0);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = portno;
	
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("Error while connecting.");
	}
	
	s1 = 25;
	s1 = htons(s1);
	
	if((n = write(sockfd, &s1, sizeof(short))) < 0) {
		error("Error writing to socket.");
	}
	
	if((n = read(sockfd, &s1, sizeof(short))) < 0) {
		error("Error while reading from socket.");
	}
			
	printf("Received (from server - Big Endian): %d \n", s1);
	s1 = ntohs(s1);
	printf("Received (from server - Little Endian): %d \n", s1);
}

