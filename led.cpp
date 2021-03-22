#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <winsock2.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <typeinfo>

#define PORT 8080

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
    void set_status(bool status)
    {
        status = status;
    }
    void set_intensitate(int intensitate)
    {
        intensitate = intensitate;
    }
    void set_culoare(string culoare)
    {
        culoare = culoare;
    }
    void set_timer (int timer)
    {
        timer = timer;
    }
    void set_status_timer(bool status_timer)
    {
        status_timer = status_timer;
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

int main()
{
    Led l;
    l.scriere_fisier();
    //citire_fisier();


    /*cout<<status<<"  "<<volum<<" "<<tip<<endl;
    cout<<typeid(status).name();*/
    conectare_la_server();
    return 0;
}
