
#include <algorithm>

#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/peer.h>
#include <pistache/http_headers.h>
#include <pistache/cookie.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>


#include <signal.h>

using namespace std;
using namespace Pistache;

void printCookies(const Http::Request& req) {
    auto cookies = req.cookies();
    std::cout << "Cookies: [" << std::endl;
    const std::string indent(4, ' ');
    for (const auto& c: cookies) {
        std::cout << indent << c.name << " = " << c.value << std::endl;
    }
    std::cout << "]" << std::endl;
}

 namespace Generic {

    void handleReady(const Rest::Request& request, Http::ResponseWriter response) {
      // Read the request data
    cout << "Received a request from IP address " << request.address().host() << '\n';

    // Send a reply
    response.send(Http::Code::Ok, "Hello world!");
    }

}

class SmartLampEndpoint
{
	Json::Value json;

private:

   	std::shared_ptr<Http::Endpoint> httpEndpoint;
    	Rest::Router router;


	void getCommand(const Rest::Request& request, Http::ResponseWriter response)
	{
		std::string returnString = "No Command available!";
		auto commandString = request.param(":commandName").as<std::string>();
		int commandInt = stoi(commandString);

		switch(commandInt)
		{
			case 1:
				
				cout << "Sunt aici " << endl;
				response.send(Http::Code::Ok, json);
				break;
				
			case 2:
				cout << "" <<endl;	
		}
   

	    /*
		if(commandString == "Standard command")
		{
			cout<<"Standard command was called"<<endl;

		cout<<"AICI!"<<endl;
		cout<< typeid(commandInt).name()<<endl;


		}
		*/
	
	}


      	void setupRoutes() {
		using namespace Rest;
		// Defining various endpoints
		// Generally say that when http://localhost:9080/ready is called, the handleReady function should be called. 
		Routes::Get(router, "/ready", Routes::bind(&Generic::handleReady));
		Routes::Get(router, "/auth", Routes::bind(&SmartLampEndpoint::doAuth, this));
		Routes::Get(router,"/command/:commandName", Routes::bind(&SmartLampEndpoint::getCommand,this));
		// Routes::Post(router, "/settings/:settingName/:value", Routes::bind(&MicrowaveEndpoint::setSetting, this));
		//Routes::Get(router, "/settings/:settingName/", Routes::bind(&MicrowaveEndpoint::getSetting, this));
        }


	void doAuth(const Rest::Request& request, Http::ResponseWriter response) {
		// Function that prints cookies
		printCookies(request);
		// In the response object, it adds a cookie regarding the communications language.
		response.cookies()
		    .add(Http::Cookie("lang", "en-US"));
		// Send the response
		response.send(Http::Code::Ok);
	}
	
public:

	explicit SmartLampEndpoint(Address addr)
        : httpEndpoint(std::make_shared<Http::Endpoint>(addr))
    	{ 
    		ifstream commandFile("commands.json");
		commandFile >> json;
    	}

    	 void init() {
        	auto opts = Http::Endpoint::options();
        	httpEndpoint->init(opts);
		 
        	// Server routes are loaded up
       		 setupRoutes();
    	}

    	 void start() {
        	httpEndpoint->setHandler(router.handler());
        	httpEndpoint->serveThreaded();
   	}

   	 // When signaled server shuts down
   	 void stop(){
        	httpEndpoint->shutdown();
   	}

};


int main(int argc, char *argv[])
{
 sigset_t signals;
 Port port(8080);
 Address addr(Ipv4::any(), port);
 SmartLampEndpoint stats(addr);

 SmartLamp smL;

 stats.init();
 stats.start();

 //cout<<"Heeelllooo!"<<endl;


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

cout << "server waiting for client command" << endl;

//stats.


}
