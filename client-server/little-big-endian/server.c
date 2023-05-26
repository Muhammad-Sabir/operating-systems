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

int main(int argc, char *argv[]) {
	int sockfd, newsockfd, portno;
	short s1;
	socklen_t clilen;

	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
	if(argc < 2) {
		fprintf(stderr, "Error, no port number provided.");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0) {
		error("Error while opening port");
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = portno;
	
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("Error while binding.");
	}
	
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	
	if(newsockfd < 0) {
		error("Error while accepting.");
	}
	
	if((n = read(newsockfd, &s1, sizeof(short))) < 0) {
		error("Error while reading from socket.");
	}
	
	printf("Received (from client - Big Endian): %d \n", s1);
	s1 = ntohs(s1);
	printf("Received (from client - Little Endian): %d \n", s1);
	
	s1 += 500;
	printf("\n\n %d \n\n", s1);
	s1 = htons(s1);
	printf("\n\n %d \n\n", s1);
	
	if((n = write(newsockfd, &s1, sizeof(short))) < 0) {
		error("Error while writing to socket.");
	}
	
	
	close(newsockfd);
}
