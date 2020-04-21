#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
	int sock = 0; 
	struct sockaddr_in serv_addr; 

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	 
	//Parsing
	char *nok="not valid command";
	while(1)
	{
		int n;
		char buffer[256];
		
		//Recieve
		printf("Please enter the command: ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		n = write(sock,buffer,strlen(buffer));
		if (n < 0) 
			printf("ERROR writing to socket");
		else
			printf("Message sent\n");

		//Send	
		bzero(buffer,256);
		n = read(sock,buffer,255);
		if (n < 0) 
			printf("ERROR reading from socket");
		else
			printf("%s\n",buffer);

		if(!strcmp(buffer,nok))
		{
			printf("Invalid Command, Terminating\n");
			break;
		}
	}

	return 0; 
} 
