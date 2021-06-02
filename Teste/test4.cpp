#include <iostream>
#include <string.h>
#include <jsoncpp/json/json.h>
#include <CUnit/CUnit.h>
#include <fstream>


using namespace std;

Json::FastWriter fastWriter;
string notifications;
string status_sound;

int readFromFile(){

	ifstream in("SunetOutput.txt");
    if(in.is_open())
    {
        in>>notifications>>status_sound;
        in.close();
        return 1;
    }
	return 0;

}

int main (){
	Json::Value json;

	readFromFile();
	ifstream commandFile("commands.json");
	commandFile>>json;

	cout << json["input-buffers"]["1"] << endl;
    cout << notifications << endl;

	int resultat_1 = 1;
	if (json["input-buffers"]["1"]["notifications"] != notifications)
    {
    	resultat_1 = 0;
    	cout << "Testul a crapat la setarea notifications! ---> KO" << endl;
    }
    else
    {
    	cout << "Verificarea corecta a notifications ---> OK" << endl;
    }


    int resultat_2 = 1;
	if (json["input-buffers"]["1"]["status_sound"] != status_sound)
    {
    	resultat_1 = 0;
    	cout << "Testul a crapat la setarea status_sound! ---> KO" << endl;
    }
    else
    {
    	cout << "Verificarea corecta a status_sound ---> OK" << endl;
    }


    int rezultat_global = resultat_1 && resultat_2;

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