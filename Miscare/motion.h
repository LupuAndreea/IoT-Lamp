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

#define PORT 8081

using namespace std;



class Motion{
private:
    bool status;
    float range; //distanta=range
	int TRIG;
	int ECHO;
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


    void preluare_date_json(Json::Value json)
    {
        
        cout << "Nu contez" << endl;

    }
    void scriere_fisier()
        {
            ofstream out("MiscareOutput.txt");
            if(out.is_open())
            {
                out<<" "<<status<<" "<<range;
                out.close();
            }
            else cout<<"Eroare la deschiderea fisierului de iesire";
        }

    void set_status(Json::Value json)
    {
        if (json["movement_status"] != null )
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

    //intensitate = range
    void set_range(Json::Value json)
    {
        Json::FastWriter fastWriter;
        if (json["movement_range"] != null)
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

int sock = 0;
int verificare_citire_mesaj;
struct sockaddr_in serv_addr;

char * buffer_de_citire = NULL;
char * buffer_de_scriere = NULL;

int conectare_la_server(){

	buffer_de_scriere = new char[1024];
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

	delete buffer_de_citire;
	delete buffer_de_scriere;
}


#endif