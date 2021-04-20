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
#define PORT 8080

using namespace std;

class Sunet{
private:
    bool status;
    int volum;
    string tip;
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
    void set_status(bool status)
    {
        status = status;
    }
    void set_volum(int volum)
    {
        volum = volum;
    }
    void set_tip(string tip)
    {
        tip = tip;
    }
    bool get_status()
    {
        return status;
    }
    int get_volum()
    {
        return volum;
    }
    string get_tip()
    {
        return tip;
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
