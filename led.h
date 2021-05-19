#ifndef LED_H
#define LED_H
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



class Led{
private:
    bool status;
    int intensitate;
    string culoare;
    int timer;
    bool status_timer;
public:
    Led()
        {
            ifstream in("SunetInput.txt");
            if(in.is_open())
            {
                in>>status>>intensitate>>culoare>>timer>>status_timer;
                in.close();
            }
            else cout<<"Eroare la deschiderea fisierului de intrare"<<endl;
        }


    void preluare_date_json(Json::Value json)
    {
        
        cout << "Nu contez" << endl;
      // cout << json["stat"];

    }
    void scriere_fisier()
        {
            ofstream out("SunetOutput.txt");
            if(out.is_open())
            {
                out<<" "<<status<<" "<<intensitate<<" "<<culoare<<" "<<timer<<" "<<status_timer;
                out.close();
            }
            else cout<<"Eroare la deschiderea fisierului de iesire";
        }

    void set_status(Json::Value json)
    {

         if (json["status_led"] == true)
         { 
            status = true;
         }

         else 
         {  
            status = false;
         }

         cout << "status: "<< status;

    }

    void set_intensitate(Json::Value json)
    {
        Json::FastWriter fastWriter;
        std::string string_intensitate = fastWriter.write(json["intensity"]);

        stringstream geek(string_intensitate);

        geek >> intensitate;

       // cout << "Value of string_intensitate: " << string_intensitate;

       // cout << "Value of intensitate: " << intensitate; 
    }


    void set_culoare(Json::Value json)
    {
          
        Json::FastWriter fastWriter;
        culoare = fastWriter.write(json["color"]);

       // cout << "Color: " << culoare;

    }

    void set_timer (Json::Value json)
    {
         
        Json::FastWriter fastWriter;
        std::string string_timer = fastWriter.write(json["timer"]);

        stringstream geek(string_timer);

        geek >> timer;

       // cout << "Value of timer: " << timer; 

    }

    void set_status_timer(Json::Value json)
    {
         if (json["status_timer"] == true)
         { 
            status_timer = true;
         }

         else 
         {  
            status_timer = false;
         }

        // cout << "status_timer: "<< status_timer;
    }

    bool get_status()
    {
        return status;
    }
    int get_intensitate()
    {
        return intensitate;
    }
    string get_culoare()
    {
        return culoare;
    }
    int get_timer()
    {
        return timer;
    }
    bool get_status_timer()
    {
        return status_timer;
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