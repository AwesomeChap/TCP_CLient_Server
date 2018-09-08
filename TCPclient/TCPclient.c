#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

void alert(char s[]){
	printf("\n\t\t");

	for(int i=0;i<strlen(s)+4;i++)
		printf("-");
	
	printf("\n\t\t| ");
	printf("%s |\n\t\t",s);
	
	for(int i=0;i<strlen(s)+4;i++)
		printf("-");

	printf("\n\n");
}

int main(){
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in  server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int status = connect(network_socket,(struct sockaddr *)&server_address, sizeof(server_address));
	if(status == -1){
		alert("There was an error asking a connection to the remote socket");
		return 0;
	}

	char response[256];
	recv(network_socket,&response,sizeof(response),0);

	printf("\n\t\tResponse from Server : Data Received\n");
	alert(response);

	close(network_socket);

	return 0; 
}

/*
1. make a socket
2. setup server address
3. connect to server address
4. if status is not -1 then receive the response from server and store it
5. destroy socket
*/