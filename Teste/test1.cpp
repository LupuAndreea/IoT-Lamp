#include <iostream>
#include <string>
#include <curl/curl.h>


using namespace std;
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8081/command/1");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (readBuffer == "{\"led\":{\"color\":\"white\",\"intensity\":80,\"status_led\":true,\"status_timer\":true,\"timer\":60},\"movement\":{\"movement_range\":100,\"movement_status\":true},\"name\":\"Standard command\",\"sound\":{\"notifications\":false,\"status_sound\":false}}")
    {
    	cout << "Testul a fost executat cu succes!" << endl;
    }

    else
    {
    	cout << "A fost identificata o eroare la solicitarfea jsonului" << endl;

    } 
  	}
  return 0;
}