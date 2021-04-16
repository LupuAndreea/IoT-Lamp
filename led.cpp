#include "led.h"


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
