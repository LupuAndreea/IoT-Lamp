#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <winsock2.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <typeinfo>

#include <wiringPi.h>

#define PORT 8080

using namespace std;

class Motion{
private:
   	bool status;
    	float distanta;
	
    	int TRIG;
	int ECHO;
public:
    Motion();
    float get_distance(); 
    void scriere_fisier()
        {
            ofstream out("MotionOutput.txt");
            if(out.is_open())
            {
                out<<" "<<status<<" "<<distanta;
                out.close();
            }
            else cout<<"Eroare la deschiderea fisierului de iesire";
        }
    void set_status(bool status){ status = status; }
    bool get_status(){ return status; }   
};

Motion :: Motion( int trigger_pin = 23, int echo_pin = 24){
	// get the pin values
	TRIG = trigger_pin;
	ECHO = echo_pin;

	// set the Sonar pin 
	wiringPiSetupGpio();
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	// stop the trigger pin
	digitalWrite(TRIG, LOW);
	delay(30);

	// Read the modul status
	ifstream in("MotionInput.txt");
	if(in.is_open())
	{
	in>>status;
	in.close();
	}
	else cout<<"Eroare la deschiderea fisierului de intrare"<<endl;

	// in the beginning the distance is 0
	distance = 0
}

float Motion :: get_distance(){
	
	// Start the Trigger
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(20);
	digitalWrite(TRIG, LOW);
	
	// wait for echo to start 
	while(digitalRead(ECHO) == LOW);
	long start_time = micros();
	
	// wait for echo to end
	while(digitalRead(ECHO) == HIGH);
	long end_time = micro();
	
	distance = (end_time - start_time) / 58;
	
	return distance;	
}

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
    Motion m;
    m.scriere_fisier();
    //citire_fisier();


    /*cout<<status<<"  "<<volum<<" "<<tip<<endl;
    cout<<typeid(status).name();*/
    conectare_la_server();
    return 0;
}
