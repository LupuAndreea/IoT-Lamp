

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <curl/curl.h>
#include <signal.h>
#include <jsoncpp/json/json.h>
#include <list>
#include <algorithm>
#include <arpa/inet.h>
#include <list>
#include <sys/shm.h>
#include <sys/mman.h>
#include <typeinfo>
#define SHMSIZE 27

#include "fusion.h"

using namespace std;


int main() {

    int readBufferid;


    temporar = (char *)mmap(NULL, sizeof *temporar, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	

    if (fork() == 0)
    {  

        cout << "This child process" << endl;
      
     
        start_server();
    }
    else
    {
        cout << "This is parent process" << endl;   
        communicationWithHttp();
    }
    
	

	return 0;
   
       
    
} 

