#ifndef INFO_H
#define INFO_H

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

class Info {
    private:
        string locatie;
        string data;
        string timp;
        string calendar;
	
	Json::Value json;
	
    public:
        Info() {
            ifstream in("input.txt");
            if(in.is_open()) {
                in>>locatie>>data>>timp>>calendar;
                in.close();
            }
            else

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
	void stringToJson() {
		//string res1 = to_string(res);
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
	void procesare_json() {
		this->stringToJson();
		this->set_locatie();
		this->set_data();
		this->set_timp();
		this->set_calendar();
		this->scriere_fisier();
	}
	void scriere_fisier() {
            ofstream out("SunetOutput.txt");
            if(out.is_open())
            {
                out << "Location: " << location << endl;
                out << "Date: " << date << endl;
                out << "Time: " << time << endl;
                out << "Calendar: " << calendar << endl;
                out.close();
            }
            else cout<<"Eroare la deschiderea fisierului de iesire";
	}
        string get_locatie() {
            return locatie;
        }
        void set_locatie(string locatie) {
		if(json["location"] != "null")
		{
		    if (json["location"] == true)
		    {
			location = true;
		    }

		    else
		    {
			location = false;
		    }

		}
        }
        string get_data() {
            return data;
        }
        void set_data(string data) {
		if(json["date"] != "null")
		{
		    if (json["date"] == true)
		    {
			date = true;
		    }

		    else
		    {
			date = false;
		    }

		}
        }
        string get_timp() {
            return timp;
        }
        void set_timp(string timp) {
		if(json["time"] != "null")
		{
		    if (json["time"] == true)
		    {
			time = true;
		    }

		    else
		    {
			time = false;
		    }

		}
        }
        string get_calendar() {
            return calendar;
        }
        void set_calendar(string calendar) {
		if(json["calendar"] != "null")
		{
		    if (json["calendar"] == true)
		    {
			calendar = true;
		    }

		    else
		    {
			calendar = false;
		    }

		}
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
