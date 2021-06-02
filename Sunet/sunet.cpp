#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <typeinfo>
#include <arpa/inet.h>
#include <jsoncpp/json/json.h>

#include "sunet.h"

using namespace std;


int main()
{
    conectare_la_server();
    return 0;
}
