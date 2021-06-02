#ifndef FUSION_H
#define FUSION_H

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <curl/curl.h>
#include <signal.h>
#include <jsoncpp/json/json.h>
#include <list>
#include <algorithm>
#include <arpa/inet.h>
#include <list>
#include <sys/shm.h>
#include <sys/mman.h>
#include <typeinfo>
#define SHMSIZE 27

//g++ -o fusion fusion.cpp -ljsoncpp -lcurl


#define PORT 8080

using namespace std;

std::list<int> listaClienti;

void print(std::list<int> const &list)
{
    for (auto const &i: list) {
        std::cout << i << std::endl;
    }
}

int  server_fd, ret;
int comunication;
int verification;

struct sockaddr_in address;
int opt = 1; 
    
   
int addrlen = sizeof(address); 
char * buffer_de_citire = NULL; 
char * buffer_de_scriere = NULL; 
char * buffer_json = NULL;
static string  readBuffer;
static char * temporar;


string listOfOuput [] = {"all_info","all_env","temperature","humidity","location"};

std::list<string> outputList (listOfOuput,listOfOuput + sizeof(listOfOuput)/sizeof(string));

    

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

class UrlCommunication
{
    Json::Value json;
    Json::FastWriter fastWriter;
    CURLcode res;
 
	

public:

	

        void communicationWithServer(char command)
        {

		  CURL *curl;  
          char b = '1';
          if (typeid(command).name() == typeid(b).name())
          cout << "Comanda este de ip char" << endl;

		  curl = curl_easy_init();
   		  char mesaj[] = "http://localhost:8081/command/";

            
          int len = strlen(mesaj);
          mesaj[len] = command;
          mesaj[len+1] = '\0';

            

		  if(curl) 
		  {
		    curl_easy_setopt(curl, CURLOPT_URL, mesaj);
		    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		    res = curl_easy_perform(curl);
		    curl_easy_cleanup(curl);

		   }

            bzero(temporar, sizeof(temporar));
            cout << "Sunt in fusion" << endl;

            strcpy(temporar,readBuffer.c_str());

	    }

    void jsonToChar(string modul)
    { 
    	

        string aux;
        aux = fastWriter.write(json[modul]);
        buffer_json = new char[aux.length()];
        strcpy(buffer_json,aux.c_str());
        cout << "Datele pentru led: " << buffer_json;
    }
    

};


int start_server(){
	
	
    int sockfd, ret;
     struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in newAddr;

    socklen_t addr_size;

    char buffer[1024];
    pid_t childpid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Server Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
        printf("[-]Error in binding.\n");
        exit(1);
    }
    printf("[+]Bind to port %d\n", PORT);

    if(listen(sockfd, 10) == 0){
        printf("[+]Listening....\n");
    }else{
        printf("[-]Error in binding.\n");
    }


    while(1){
        newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
        if(newSocket < 0){
            exit(1);
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        if((childpid = fork()) == 0){
            close(sockfd);

            while(1){
                recv(newSocket, buffer, 1024, 0);
                if(strcmp(buffer, ":exit") == 0){
                    printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    break;
                }else{
                    printf("Client: %s\n", buffer);
                   

                    send(newSocket, temporar, strlen(temporar), 0);
                }
            }
        }

    }

    close(newSocket);   

    return 0; 
}

void communicationWithHttp(){

    char stringCommand;

    UrlCommunication url; 

    while(1)
    {   
        cout << "Insert command: " ;
        cin >> stringCommand;
        bzero(temporar, sizeof(temporar));
        url.communicationWithServer(stringCommand);
    }
  

}

#endif
