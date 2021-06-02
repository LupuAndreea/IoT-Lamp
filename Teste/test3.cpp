#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <CUnit/CUnit.h>
#include <fstream>

using namespace std;

string status;
string intensitate;
string culoare;
string timer;
string status_timer;


Json::FastWriter fastWriter;


int readFromFile(){

	ifstream in("LedOutput.txt");
    if(in.is_open())
    {
        in>>status>>intensitate>>culoare>>timer>>status_timer;
        in.close();
    }
	return 0;

}

int main (){
	Json::Value json;

	readFromFile();
	ifstream commandFile("commands.json");
	commandFile>>json;

	cout << json["input-buffers"]["1"] << endl;

	int resultat_1 = 1;
	if (json["input-buffers"]["1"]["status_led"] != status)
    {
    	resultat_1 = 0;
    	cout << "Testul a crapat la setarea statusului! ---> KO" << endl;
    }
    else
    {
    	cout << "Verificarea corecta a statusului ---> OK" << endl;
    }


    int resultat_2 = 1;
	if (json["input-buffers"]["1"]["color"] != culoare)
    {
    	resultat_1 = 0;
    	cout << "Testul a crapat la setarea culorii! ---> KO" << endl;
    }
    else
    {
    	cout << "Verificarea corecta a culorii ---> OK" << endl;
    }

    int resultat_3 = 1;

    if(json["input-buffers"]["1"]["intensity"] != intensitate )
    {
    	resultat_3 = 0;
    	cout << "Testul a crapat la setarea intensitatii! ---> KO" << endl;
    }
    else
    {
    	cout << "Verificarea corecta a culorii ---> OK" << endl;
    }

    int resultat_4 = 1;
	if (json["input-buffers"]["1"]["status_timer"] != status_timer)
    {
    	resultat_4 = 0;
    	cout << "Testul a crapat la status_timer ! ---> KO" << endl;
    }
    else
    {
    	cout << "Verificarea corecta a status_timer---> OK" << endl;
    }

    int resultat_5 = 1;
	if (json["input-buffers"]["1"]["timer"] != timer)
    {
    	resultat_5 = 0;
    	cout << "Testul a crapat la setarea stimer! ---> KO" << endl;
    }
    else
    {
    	cout << "Verificarea corecta a timerului ---> OK" << endl;
    }

    int rezultat_global = resultat_1 && resultat_2 && resultat_3 && resultat_4 && resultat_5;

    if ( rezultat_global == 0)
    {
    	cout << "Testul nu a mers cum trebuie ---> KO global " << endl;
    }
    else 
    {
    	cout << "Testul a fost finalizat cu succes ---> OK global " << endl;
    }
	return 0;
}