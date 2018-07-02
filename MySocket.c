#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>


#define PORT 61680 
#define BUF_SIZE 1024
//static const char IP_ADDR[] = "127.0.0.1";

//One should always handle errors. 
//This is bad code style!

int main(int argc, char *argv[]) {

	char *IP_ADDR = argv[1];
	printf("%s\n", IP_ADDR);

	char buffer[BUF_SIZE]; 
	int len, sock_fd; 
	struct sockaddr_in dest;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&dest, 0, sizeof(dest)); 
	dest.sin_family = AF_INET; 
	inet_pton(AF_INET,IP_ADDR,&dest.sin_addr.s_addr); 
	dest.sin_port = htons(PORT);

	connect(sock_fd, (struct sockaddr *)&dest, sizeof(struct sockaddr));

	//create a stream from existing file descriptor for
	//easy fputs and fgets for reading and writing lines 

	FILE* file = fdopen(sock_fd,"r+");

	char message[BUF_SIZE]; sprintf(message,"C-Client listening to %s\n",IP_ADDR); 
	fputs(message,file);

	char exitcode[]="exit\n";

	while(1){

		if(NULL==fgets(buffer,BUF_SIZE,file)) { 
			break; 
		}

		if(0 == strncmp(buffer,exitcode,sizeof(exitcode))){
			break; 
		} 

		fprintf(stdout,"Received data: %s",buffer);

	} 
	close(sock_fd); return 0;

}