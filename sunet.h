#ifndef SUNET_H
#define SUNET_H
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

class Sunet{
private:
    bool notifications;
    bool status_sound;
    string sound_type;
    int volume;

public:

    Sunet()
        {
            ifstream in("SunetInput.txt");
            if(in.is_open())
            {
                in>>status>>volum>>tip;
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
                out<<" "<<status<<" "<<volum<<" "<<tip;
                out.close();
            }
            else cout<<"Eroare la deschiderea fisierului de iesire";
        }

    void set_notifications(Json::Value json)
    {
        if(json["notifications"] != null)
        {
            if (json["notifications"] == true)
            {
                notifications = true;
            }

            else
            {
                notifications = false;
            }

            cout << "Notifications: "<< notifications;
        }
    }

    void set_status(Json::Value json)
    {
        if(json["status_sound"] != null)
        {
            if (json["status_sound"] == true)
            {
                status_sound = true;
            }

            else
            {
                status_sound = false;
            }

            cout << "Status_sound: "<< status_sound;
        }
    }

    void set_soundType(Json::Value json)
    {
        if(json["sound_type"] != null)
        {
            Json::FastWriter fastWriter;
            sound_type = fastWriter.write(json["sound_type"]);
             // cout << "Sound type: " << sound_type;
        }
    }

    void set_volume(Json::Value json)
    {
        if(json["volume"] != null)
        {
            Json::FastWriter fastWriter;
            string volume = fastWriter.write(json["volume"]);

            stringstream geek(volume);

            geek >> volume;

            // cout << "Volume: " << volume;
        }
    }

    bool get_notifications()
    {
        return notifications;
    }

    bool get_status()
    {
        return status_sound;
    }

    string get_soundType()
    {
        return sound_type;
    }

    int get_volume()
    {
        return volume;
    }

};

int sock = 0;
int verificare_citire_mesaj;
struct sockaddr_in serv_addr;

char * buffer_de_citire = NULL;
char * buffer_de_scriere = NULL;

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

	delete buffer_de_citire;
	delete buffer_de_scriere;
}

#endif
