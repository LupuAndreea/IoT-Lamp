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

char buffer[1024];

int sock = 0;
int verificare_citire_mesaj;
struct sockaddr_in serv_addr;


class Sunet{
private:
    bool notifications;
    bool status_sound;
    string sound_type;
    int volume;

    Json::Value json;

public:

    Sunet()
        {
            ifstream in("SunetInput.txt");
            if(in.is_open())
            {
                in>>notifications>>status_sound>>volume>>sound_type;
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
            
        json = json["sound"];
        cout << json;
    }

    void procesare_json(){

        this->stringToJson();
        this->set_notifications();
        this->set_status();
        this->set_soundType();
        this->set_volume();
        this->scriere_fisier();
    }

    void scriere_fisier()
        {
            ofstream out("SunetOutput.txt");
            if(out.is_open())
            {
                out << "Notification: " <<  notifications << endl;
                out << "Status sound: " << status_sound << endl;
                out << "Volum " << volume << endl;
                out << "Sount Type" << sound_type << endl;
                out.close();
            }
            else cout<<"Eroare la deschiderea fisierului de iesire";
        }

    void set_notifications()
    {
        if(json["notifications"] != "null")
        {
            if (json["notifications"] == true)
            {
                notifications = true;
            }

            else
            {
                notifications = false;
            }

        }
    }

    void set_status()
    {
        if(json["status_sound"] != "null" )
        {
            if (json["status_sound"] == true)
            {
                status_sound = true;
            }

            else
            {
                status_sound = false;
            }

        }
    }

    void set_soundType()
    {
        if(json["sound_type"] != "null")
        {
            Json::FastWriter fastWriter;
            sound_type = fastWriter.write(json["sound_type"]);
        }
    }

    void set_volume()
    {
        if(json["volume"] != "null" )
        {
            Json::FastWriter fastWriter;
            string volume = fastWriter.write(json["volume"]);

            stringstream geek(volume);

            geek >> volume;

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



int conectare_la_server(){

    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    Sunet s;
    

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
            s.procesare_json();
        }
    }
}


#endif
