# SmartLamp

![Demo](https://user-images.githubusercontent.com/48756694/120623799-b78c4c00-c468-11eb-99aa-c60c6a856d65.mp4)

Raportul de analiză se găsește [aici](https://github.com/LupuAndreea/IoT-Lamp/blob/main/Raport_Final_Smart_Lamp.pdf)

Offline Demo [aici](https://youtu.be/0RtRmJab8Y4) și [MakeDemo](https://github.com/LupuAndreea/IoT-Lamp/blob/main/MakeDemoApp.md)

## **Cerințe de sistem**


  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**În scopul realizării proiectului am folosit numeroase librării. Dintre acestea, [Jsoncpp ](https://github.com/open-source-parsers/jsoncpp), [Pistache](https://github.com/pistacheio/pistache) şi [Curl](https://curl.se/) au trebuit să fie instalate. Datorită faptului că _Pistache_ nu suportă _Windows_, sistemul de operare utilizat este `Ubuntu`.** :smirk:
  
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; **De asemenea, este necesar un compilator C++, iar noi am ales `g++`.**
 
 ## **Librării**
 
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  Pe parcursul creării proiectului am folosit librăriile standard pentru citire, scriere, librării pentru manipularea şirurilor de caractere sau lucrul cu variabile de tip bool şi multe altele. Dintre aceste se diferenţiază cele pe care a trebuit să le instalăm:

  1. **#include <jsoncpp/json/json.h>** face posibilă manipularea valorilor `JSON` de care am avut nevoie în vederea transmiterii datelor
  2. **Pistache** este utilizat pentru:
     - crearea unui `server HTTP` cu mai multe fire de execuţie destinat creării, definirii şi solicitării `API-urilor`
     - a trimite cereri către funcţiile C++ printr-un `router HTTP`

     În cadrul proiectului am folosit următoarele: 
       * #include <pistache/net.h>
       * #include <pistache/http.h>
       * #include <pistache/peer.h>
       * #include <pistache/http_headers.h>
       * #include <pistache/cookie.h>
       * #include <pistache/router.h>
       * #include <pistache/endpoint.h>
       * #include <pistache/common.h>
   
  3. **#include <curl/curl.h>** ajută la transferarea datelor de la server sau către server, utilizând protocoalele `HTTP` şi `MQTT`
  4. **#include <boost/lexical_cast.hpp>** face posibilă conversia din valori numerice în şiruri de caractere şi invers

 
 ## **Paşi de instalare**
 1. ***JSON***
   -  Se rulează în terminal comanda sudo `apt-get install libjsoncpp-dev`. Numeroase detalii despre JSON se  găsesc aici: [JSON](https://www.json.org/json-en.html)

 2. ***Pistache***
   -  Pentru a instala Pistache pe Ubuntu, am introdus în terminal comenzile 
  
      * `sudo add-apt-repository ppa:pistache+team/unstable`
      * `sudo apt update`
      * `sudo apt install libpistache-dev`
      
      Mai multe informaţii despre instalarea Pistache se găsesc aici: [pistacheio/pistache: A high-performance REST Toolkit written in C++ (github.com)](https://github.com/pistacheio/pistache)


 3. ***Curl***
   - Prin prisma faptului că librăria `curl` este disponibilă în Ubuntu 20.04, primul pas către instalare este rularea comenzii sudo apt update, urmată de `sudo apt install curl`.
     Despre curl, dar şi o trimitere către o carte dedicată acestui subiect găsim aici: [curl](https://curl.se/).

 4. ***#include <boost/lexical_cast.hpp>***
    Se rulează în terminal comanda `sudo apt-get install libboost-all-dev`.
    
 ## **Paşi de rulare**
 
  1. ***JSON***
     Se rulează în terminal numele fişierului urmat de compiler flag  `g++ -o server serverWeb.cpp –ljsoncpp`.
  Apoi, în terminal este rulată comanda `./server`.
  
  2. ***Pistache***
     În cadrul proiectului nostru, pentru am utilizat Pistache în comenzi scrise în terminal, precum: `g++ -o led led.cpp -ljsoncpp`.
     
  3. ***Curl***
        Pentru a rula curl, se utilizează o comandă de tipul curl urmat de url-ul dorit. Spre exemplu, curl    `http://localhost:8080/command/1`.


Linkul către [Trello](https://trello.com/b/TnOty7z8/to-do-list)
