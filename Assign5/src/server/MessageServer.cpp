#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <csignal>



#include "messageserverstub.h"
#include "GroupMessage.hpp"

using namespace jsonrpc;
using namespace std;



class MessageServer : public messageserverstub {
   public:
   MessageServer(AbstractServerConnector &connector, int port);  
   virtual bool saveToJsonFile();
   virtual bool resetFromJsonFile();
   virtual bool addMessage(const Json::Value& singleMessage);
   virtual bool removeMessage(const std::string& headerInfo);
   virtual Json::Value getMessage(const std::string& headerInfo);
   virtual Json::Value getHeaders(const std::string& userInfo);

private:
   GroupMessage * messages;
   int portNum;


};


MessageServer::MessageServer(AbstractServerConnector &connector, int port) :
   messageserverstub(connector){

   messages = new GroupMessage();
   messages->initGroupMessage("messages.json");
   portNum = port;
}

bool MessageServer::resetFromJsonFile()
{
   messages = new GroupMessage();
   messages->initGroupMessage("messages.json");
}

bool MessageServer::saveToJsonFile() {
   messages->toJsonFile("messages.json");
   return true;
}

bool MessageServer::addMessage(const Json::Value& singleMessage) {
   
   Json::Value aMessage = singleMessage;
   messages->add(aMessage);
   return true;
}

bool MessageServer::removeMessage(const std::string& headerInfo)
{  
   messages->remove(headerInfo);
   return true;
}

Json::Value MessageServer::getMessage(const std::string& headerInfo)
{
   Json::Value aJsonValue = messages->get(headerInfo);
   return aJsonValue;
}  

Json::Value MessageServer::getHeaders(const std::string& userInfo)
{
   Json::Value jsonHeaders = messages->getHeaders(userInfo);
   return jsonHeaders;

}
void exiting(){
   std::cout << "Server has been terminated. Exiting normally" << endl;
   //ss.StopListening();
}


int main(int argc, char * argv[]) {
   // invoke with ./bin/studentRPCServer 8080
   int port = 8080;
   if(argc > 1){
      port = atoi(argv[1]);
   }
   HttpServer httpserver(port);
   MessageServer ms(httpserver , port);
   
   std::atexit(exiting);
   auto ex = [] (int i) {cout << "server terminating with signal " << i << endl;
                         
                         exit(0);
                         
                        };
   // ^C
   std::signal(SIGINT, ex);
   // abort()
   std::signal(SIGABRT, ex);
   // sent by kill command
   std::signal(SIGTERM, ex);
   // ^Z
   std::signal(SIGTSTP, ex);
   cout << "Message server listening on port " << port
      //<< " press return/enter to quit." << endl;
        << " use ps to get pid. To quit: kill -9 pid " << endl;
   ms.StartListening();
   while(true){
   }
   ms.StopListening();
   return 0;   
}