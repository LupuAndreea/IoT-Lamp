#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <new>
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <typeinfo>
#include <jsoncpp/json/json.h>

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

	int clientSocket, ret;
    struct sockaddr_in serverAddr;
  //  char buffer[1024];
      // char * buffer;

      // string buffer_string = string(buffer);


      //  Json::Value json;	
      //  Json::Reader buffer_reader;
       
      //  buffer_reader.parse( buffer, json);

      //  char * auxiliar;
      //  auxiliar = (char*) json;

       char buffer[1024]; 

       Json::Value config; 

      //  memset(buffer,0,sizeof(buffer)); 
      // // memcpy(buffer,"zhaosi",strlen("zhaosi")); 

      //   config["name"] = buffer;



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
        
       memset(buffer,0,sizeof(buffer)); 
      // memcpy(buffer,"zhaosi",strlen("zhaosi")); 

        config["name"] = buffer;

        send(clientSocket, buffer, strlen(buffer), 0);

        if(strcmp(buffer, ":exit") == 0){
            close(clientSocket);
            printf("[-]Disconnected from server.\n");
            exit(1);
        }

        if(recv(clientSocket, auxiliar, 1024, 0) < 0){
            printf("[-]Error in receiving data.\n");
        }else{
            printf("Server: \t%s\n", json);
        }
    }
    
}

int main() {

    Info info;
    info.scriere_fisier();
    conectare_la_server();
    return 0;
}
