#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

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


class EnvironmentInformation {

    float humidity;
    float temperature;
    bool  status_olfactive;
    bool status_pollution;

    Json::Value json;

public:
    EnvironmentInformation() {
        ifstream in("InputEnvironmentInformation.txt");
            if(in.is_open())
            {
                in>>humidity>>temperature>>status_olfactive>>status_pollution;
                in.close();
            }
            else cout<<"Eroare la deschiderea fisierului de intrare"<<endl;

    }



    void stringToJson()
    {


        Json::Reader reader;
        string temp = string(buffer);
        cout << buffer<<endl;

        bool parsingSuccessful = reader.parse( temp.c_str(), json);

        if ( !parsingSuccessful )
        {

            cout << "Error parsing the string" << endl;
        }

        json = json["information"];
        cout << json;
    }


    void procesare_json()
    {

        this->stringToJson();
        this->set_humidity();
        this->set_temperature();
        this->set_status_olfactive();
        this->set_status_pollution();


    }

    void scriere_fisier()
        {
            ofstream out("OutputEnvironmentInformation.txt");
            if(out.is_open())
            {
                out << "Humidity: " << humidity << endl;
                out << "Temperature " << temperature << endl;
                out << "Olfactive status :  " << status_olfactive << endl;
                out << "Pollution status" << status_pollution << endl;
                out.close();
            }
            else cout<<"Eroare la deschiderea fisierului de iesire";
        }

    void set_humidity() {
        Json::FastWriter fastWriter;
        if(json["humidity"] != "null")
        {
             std::string string_humidity = fastWriter.write(json["humidity"]);

             stringstream geek(string_humidity);

             geek >> humidity;
        }
    }

    void set_temperature() {
        Json::FastWriter fastWriter;
        if(json["temperature"] != "null")
        {
            std::string string_temperature = fastWriter.write(json["temperature"]);

             stringstream geek(string_temperature);

             geek >> temperature;
        }
    }

    void set_status_olfactive() {
        if(json["status_olfactive"] != "null")
        {
            if (json["status_olfactive"] == true)
            {
                status_olfactive = true;
            }
             else
            {
                status_olfactive = false;
            }
        }
    }

    void set_status_pollution() {
        if(json["status_pollution"] != "null")
        {
            if (json["status_pollution"] == true)
            {
                status_pollution = true;
            }
             else
            {
                status_pollution = false;
            }
        }
    }

    float get_humidity()
    {
        return humidity;
    }
    float get_temperature()
    {
        return temperature;
    }
    bool get_status_olfactive()
    {
        return status_olfactive;
    }
    bool get_status_pollution()
    {
        return status_pollution;
    }


int conectare_la_server(){

	int clientSocket, ret;
    struct sockaddr_in serverAddr;
    EnvironmentInformation env;


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

            cout << "Message received succesfully"<< endl;
            env.procesare_json();
        }
    }
}



#endif
