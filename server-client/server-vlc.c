// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address);  
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	}

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons(PORT); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	
	
	//char vlc[4]={'v','l','c','\0'} , vlcv[14]={'v','l','c',' ','-','-','v','e','r','s','i','o','n','\0'};
	char *vlc="vlc\n", *vlcv="vlc --version\n";
	char *ok="valid command", *nok="not valid command";
	
	while(1)
	{
		
		int n;
		char buffer[256];
		bzero(buffer,256);
		n = read(new_socket,buffer,255);
		if (n < 0) 
			printf("ERROR reading from socket");
		else
			{
				// printf("B %s\n",buffer);
				// printf("%ld\n",strlen(buffer));
				// printf("V %s\n",vlc);
				// printf("%ld\n",strlen(vlc));		
				// printf("%d\n",strcmp(buffer,vlc));		
			}
		if(!strcmp(buffer,vlc))
		{
			send(new_socket,ok,strlen(ok),0);
			printf("OK vlc opening\n");
			system(buffer);
		}
		else if(!strcmp(buffer,vlcv))
		{
			send(new_socket,ok,strlen(ok),0);
			printf("OK vlc version\n");
			system(buffer);
		}
		else
		{
			send(new_socket,nok,strlen(nok),0);
			printf("NOK Message sent\n");
			break;
		}
	}
	return 0; 
} 
