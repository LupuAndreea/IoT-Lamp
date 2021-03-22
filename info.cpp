#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <new>
#include <stdio.h>
#include <stdbool.h>
#include <winsock2.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <typeinfo>

#define PORT 8080

using namespace std;

class Info {
    private:
        string locatie;
        string data;
        string timp;
        string calendar;
    public:
        Info() {
            /*time_t now = time(0);
            tm *ltm = localtime(&now);
            string zi = (char*)ltm->tm_mday;
            string luna = (char*)(1 + ltm->tm_mon);
            string an = (char*)(1900 + ltm->tm_year);
            data = zi + "/" + luna + "/" + an;
            string ora = (char*)(5 + ltm->tm_hour);
            string minute = (char*)(30 + ltm->tm_min);
            string secunde = (char*)ltm->tm_sec;
            timp = ora + ":" + minute + ":" + secunde;*/
            ifstream in("input.txt");
            if(in.is_open()) {
                in>>locatie>>data>>timp>>calendar;
                in.close();
            }
            else
                cout<<"Eroare la citire";
        }
        void scriere_fisier()
        {
            ofstream out("output.txt");
            if(out.is_open()) {
                out<<"Locatie: "<<locatie<<endl<<"Data: "<<data<<endl<<"Ora: "<<timp<<endl<<"Date importante: "<<calendar<<endl;
                out.close();
            }
            else
                cout<<"Eroare la scriere";
        }
        string get_locatie() {
            return locatie;
        }
        void set_locatie(string l) {
            locatie = l;
        }
        string get_data() {
            return data;
        }
        void set_data(string d) {
            data = d;
        }
        string get_timp() {
            return timp;
        }
        void set_timp(string t) {
            timp = t;
        }
        string get_calendar() {
            return calendar;
        }
        void set_calendar(string c) {
            calendar = c;
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

int main() {
    Info info;
    info.scriere_fisier();
    conectare_la_server();
    return 0;
}
