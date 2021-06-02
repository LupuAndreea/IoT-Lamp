#ifndef SERVERWEB_H
#define SERVERWEB_H


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
#include <list>


//g++ -o server serverWeb.cpp -lpistache -ljsoncpp

#include <signal.h>

using namespace std;
using namespace Pistache;

 
void print(std::list<std::string> const &list, int iterator)
{
    
    for (auto const &i: list) {
      
             std::cout << iterator << std::endl;

       
    }
}


string listOfOuput [] = {"all_info","all_env","temperature","humidity","location"};

std::list<string> outputList (listOfOuput,listOfOuput + sizeof(listOfOuput)/sizeof(string));

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

Json::Value json;

class SmartLampEndpoint
{
	

	Json::FastWriter fastWriter;

	string chestie = "eu sunt temporar";
    
    std::string output;
	
public:

	explicit SmartLampEndpoint(Address addr)
        : httpEndpoint(std::make_shared<Http::Endpoint>(addr))
    { 
    	ifstream commandFile("commands.json");
		commandFile>>json;
	  

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

  private:

   	std::shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;


	void getCommand(const Rest::Request& request, Http::ResponseWriter response)
	{

		std::string returnString = "No Command available!";
		auto commandString = request.param(":commandName").as<std::string>();
		int commandInt = stoi(commandString);

	
		if (commandInt >= 1 && commandInt <= 5) 
		{   
			output = fastWriter.write(json["input-buffers"][commandString]);
			cout<<"Am trimis comanda "<<json["input-buffers"][commandString]["name"] << endl;
			response.send(Http::Code::Ok, output);
		}
	
	}
     
     void setCommand(const Rest::Request& request, Http::ResponseWriter response)
     {

        string returnString= request.param(":commandOutput").as<std::string>(); 

        bool found = (std::find(outputList.begin(), outputList.end(), returnString) != outputList.end());
        
        //string message = (found) ? returnString : "No Command available!";


        string message = "{request: temperature}";

        cout << " Return string: " << returnString << endl;

        cout << message << endl;

        response.send(Http::Code::Ok, message);


     }

      void setupRoutes() {
        using namespace Rest;
        // Defining various endpoints
        // Generally say that when http://localhost:9080/ready is called, the handleReady function should be called. 
        Routes::Get(router, "/ready", Routes::bind(&Generic::handleReady));
        Routes::Get(router, "/auth", Routes::bind(&SmartLampEndpoint::doAuth, this));
        Routes::Get(router,"/command/:commandName", Routes::bind(&SmartLampEndpoint::getCommand,this));
        Routes::Get(router,"/request/:commandOutput",Routes::bind(&SmartLampEndpoint::setCommand,this));
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


};



#endif
