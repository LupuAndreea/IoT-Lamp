#include <iostream>

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

using namespace std;

int  server_fd;
int comunication;
int verification;

struct sockaddr_in address;
int opt = 1; 
    
   
int addrlen = sizeof(address); 
char * buffer_de_citire = NULL; 
char * buffer_de_scriere = NULL; 
    
    
int start_server(){
	
	buffer_de_scriere = new char[(sizeof"Hello from server!")];
	strcpy(buffer_de_scriere ,"Hello from server!");
	
	buffer_de_citire = new char [1024];
	
	// Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
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
    if ((comunication = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    verification = read( comunication , buffer_de_citire, 1024); 
    printf("Buffer de citire: %s\n",buffer_de_citire ); 
    send(comunication , buffer_de_scriere , strlen(buffer_de_scriere) , 0 ); 
    printf("Buffer de scriere: Hello message sent\n"); 
    return 0; 
}

int main() {

	start_server();
	return 1;
   
       
    
} 

