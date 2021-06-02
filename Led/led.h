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

#define PORT 8080

using namespace std;


//multi-line comment ctr+/ 
char buffer[1024];

int sock = 0;
int verificare_citire_mesaj;
struct sockaddr_in serv_addr;
Json::Reader reader;

class Led{
private:
    bool status;
    int intensitate;
    string culoare;
    int timer;
    bool status_timer;

    Json::Value json;
public:
    Led()
        {
            ifstream in("LedInput.txt");
            if(in.is_open())
            {
                in>>status>>intensitate>>culoare>>timer>>status_timer;
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
            
        json = json["led"];
        cout << json;
    }

    void procesare_json()
    {
        
        this->stringToJson();
        this->set_status();
        this->set_intensitate();
        this->set_culoare();
        this->set_timer();
        this->set_status_timer();

    }
    void scriere_fisier()
        {
            ofstream out("ledOutput.txt");
            if(out.is_open())
            {
                out << "Led status: " << status << endl;
                out << "Intensity " << intensitate << endl;
                out << "Color :  " << culoare << endl;
                out << "Time" << timer << endl;
                out << "Status timer: " << status_timer;
                out.close();
            }
            else cout<<"Eroare la deschiderea fisierului de iesire";
        }

    void set_status()
    {
        if(json["status_led"] != "null"){
             if (json["status_led"] == true)
             { 
                status = true;
             }

             else 
             {  
                status = false;
             }

         }

    }

    void set_intensitate()
    {
        Json::FastWriter fastWriter;
        if(json["intensity"] != "null"){
        std::string string_intensitate = fastWriter.write(json["intensity"]);

        stringstream geek(string_intensitate);

        geek >> intensitate;
        }

    }


    void set_culoare()
    {
        if(json["color"] != "null"){
          
            Json::FastWriter fastWriter;
            culoare = fastWriter.write(json["color"]);
        }

    }

    void set_timer ()
    {
         
        Json::FastWriter fastWriter;
        if(json["timer"] != "null"){
            std::string string_timer = fastWriter.write(json["timer"]);

            stringstream geek(string_timer);

            geek >> timer;
        }

    }

    void set_status_timer()
    {
        if(json["status_timer"] != "null"){
             if (json["status_timer"] == true)
             { 
                status_timer = true;
             }

             else 
             {  
                status_timer = false;
             }
        }
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

int conectare_la_server(){

    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    Led l;
    

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
       //scanf("%s", &buffer[0]);
        sleep(5);
        //buffer = ;
        send(clientSocket,"Solicit update", strlen("Solicit update"), 0);

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