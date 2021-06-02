#include "serverWeb.h"



using namespace std;

int main(int argc, char *argv[])
{
	sigset_t signals;

	Port port(8081);



	Address addr(Ipv4::any(), port);

	SmartLampEndpoint stats(addr);


    //int thr = 2;

	stats.init();
	stats.start();

	
	int signal = 0;
    int status = sigwait(&signals, &signal);
    if (status == 0)
    {
        std::cout << "received signal " << signal << std::endl;
    }
    else
    {
        std::cerr << "sigwait returns " << status << std::endl;
    }
  

    cout<<"server waiting for client command"<<endl;


}