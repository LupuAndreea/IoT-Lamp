h


#ifndef MOTION_H
#define MOTION_H
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <typeinfo>
#include <jsoncpp/json/json.h>
#include <boost/lexical_cast.hpp>
#include <sstream>

#define PORT 8080

using namespace std;

//multi-line comment ctr+/ 
char buffer[1024];

int sock = 0;
int verificare_citire_mesaj;
struct sockaddr_in serv_addr;
Json::Reader reader;

class Movement{
private:
    bool status;
    float range; 
    //int TRIG;
    //int ECHO;

    Json::Value json;

public:
    Motion()
        {
            ifstream in("MiscareInput.txt");
            if(in.is_open())
            {
                in>>status>>range;
                in.close();
            }
            else cout<<"Eroare la deschiderea fisierului de intrare"<<endl;
        }
 void stringToJson()
    {

        //string res1 = to_string(res);
        Json::Reader reader;
        string temp = string(buffer);
        cout << buffer<<endl;

        bool parsingSuccessful = reader.parse( temp.c_str(), json);

        if ( !parsingSuccessful )
        {

            cout << "Error parsing the string" << endl;
        }
            
        json = json["movement"];
        cout << json;
    }


    void procesare_json()
    {
        
        this->stringToJson();
        this->set_status();
        this->set_range();

    }
    void scriere_fisier()
        {
            ofstream out("MiscareOutput.txt");
            if(out.is_open())
            {
                out<<" Movement status: "<<status<<"endl;
	  out<<"Range: "<<range<<endl;
                out.close();
            }
            else cout<<"Eroare la deschiderea fisierului de iesire";
        }

    void set_status()
    {
        if (json["movement_status"] != "null")
        {
         if (json["movement_status"] == true)
         { 
            status = true;
         }

         else 
         {  
            status = false;
         }

         cout << "status: "<< status;
        }

    }

    void set_range()
    {
        Json::FastWriter fastWriter;
        if (json["movement_range"] != "null")
        {
        std::string string_range = fastWriter.write(json["movement_range"]);

        stringstream geek(string_range);

        geek >> range;
        } 
    }


    bool get_status()
    {
        return status;
    }
    int get_range()
    {
        return range;
    }
};

//char * buffer_de_citire = NULL;
//char * buffer_de_scriere = NULL;

int conectare_la_server(){

	int clientSocket, ret;
    struct sockaddr_in serverAddr;
    Movement l;
    

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0){
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Client Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    while(1){
        printf("Client: \t");
        scanf("%s", &buffer[0]);
        send(clientSocket, buffer, strlen(buffer), 0);

        if(strcmp(buffer, ":exit") == 0){
            close(clientSocket);
            printf("[-]Disconnected from server.\n");
            exit(1);
        }

        if(recv(clientSocket, buffer, 1024, 0) < 0){
            printf("[-]Error in receiving data.\n");
        }
        else{
            //printf("Server: \t%s\n", buffer);
            cout << "Message received succesfully"<< endl; 
            l.procesare_json();
        }
    }
}



#endif