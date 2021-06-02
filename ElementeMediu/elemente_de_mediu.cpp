#include <iostream>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <string.h>
#include <fstream>
#include <jsoncpp/json/json.h>

#define PORT 8081

using namespace std;
  
int sock = 0;
int verificare_citire_mesaj;
struct sockaddr_in serv_addr; 

char * buffer_de_citire = NULL;
char * buffer_de_scriere = NULL;
char * buffer_json = NULL;

class EnvironmentInformation {

    float humidity;
    float temperature;
    bool  status_olfactive;
    bool status_pollution;

    Json::Value json;
    Json::FastWriter fastWriter;

   

public:
    void read_from_file(){
    	
            ifstream in("EnvironmentInformation.txt");
            if(in.is_open())
            {
                in>>humidity>>temperature>>status_olfactive>>status_pollution;
                in.close();
            }
            else cout<<"Eroare la deschiderea fisierului de intrare"<<endl;

           // cout << humidity << temperature << status_olfactive << status_pollution;
    }

    void data_to_json()
    {
        json["humidity"] = humidity;
        json["temperature"] = temperature;
        json["status_olfactive"] = status_olfactive;
        json["status_pollution"] = status_pollution;

       // cout << json;
        
    }

    void jsonToChar()
    { 
        

        string aux;
        aux = fastWriter.write(json);

        buffer_json = new char[aux.length()];
        strcpy(buffer_json,aux.c_str());
        cout << "Datele pentru mediu: " << buffer_json;
    }



};

int conectare_la_server(){
	
	buffer_de_scriere = new char[(sizeof"Hello from client!")];
	strcpy(buffer_de_scriere ,"Hello from client!");
	
	buffer_de_citire = new char [1024];
	
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
    
    send(sock , buffer_de_scriere, strlen(buffer_de_scriere) , 0 ); 
    printf("Am trimis mesaj catre server!\n"); 
    verificare_citire_mesaj = read( sock , buffer_de_scriere, 1024); 
    printf("%s\n", buffer_de_scriere ); 
    
    EnvironmentInformation env;

    env.read_from_file();
    env.data_to_json();
    env.jsonToChar();

    send(sock , buffer_json, strlen(buffer_json) , 0 ); 
    printf("Am trimis json-ul!\n");


	delete buffer_de_citire;
	delete buffer_de_scriere;
} 

int main() 
{   
	
    conectare_la_server();
    return 0; 
} 
