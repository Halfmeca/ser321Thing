#include "Message.hpp"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>





Message::Message()
{
	header 		= "Null";
	subject 	= "Null";
	plainText 	= "Null";
	target 		= "Null";
	date 		= "Null"; 
	sender 		= "Null";

}


Message::~Message()
{
	header 		= " ";
	subject 	= " ";
	plainText 	= " ";
	target 		= " ";
	date 		= " ";
	sender 		= " ";

}

void Message::setValues(string messageHeader , string messageSubject , string messagePlainText , string messageTarget ,string messageDate , string messageSender)
{
	header 		= messageHeader;
	subject 	= messageSubject;
	plainText 	= messagePlainText;
	target 		= messageTarget;
	date 		= messageDate;
	sender 		= messageSender;
}

Message::Message(string messageHeader , string messageSubject , string messagePlainText , string messageTarget, string messageDate , string messageSender)
{
	header 		= messageHeader;
	subject 	= messageSubject;
	plainText 	= messagePlainText;
	target 		= messageTarget;
	date 		= messageDate;
	sender 		= messageSender;
}

void Message::setValues(Json::Value& msgJson)
{
	string messageHeader 	= "messageHeader";
	string messageSubject 	= "messageSubject";
	string messagePlainText	= "messagePlainText";
	string messageTarget 	= "messageTarget";
	string messageDate		= "messageDate";
	string messageSender	= "messageSender";
   	Json::Value::Members mbr = msgJson.getMemberNames();
   	for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
      Json::Value jsonM = msgJson[*i];
      if(messageHeader.compare(*i)==0){ 
         header = jsonM.asString();
      }
      else if(messageSubject.compare(*i)==0){
         subject = jsonM.asString();
      }
      else if(messagePlainText.compare(*i)==0){
         plainText = jsonM.asString();  
      }
      else if(messageTarget.compare(*i)==0){
         target = jsonM.asString();
      }
      else if(messageDate.compare(*i)==0){
         date = jsonM.asString();  
      }
      else if(messageSender.compare(*i)==0){
         sender = jsonM.asString();  
      }
    }
}

Json::Value Message::toJson()
{
	Json::Value jsonMessage;
	jsonMessage["messageHeader"] 	= header;
	jsonMessage["messageSubject"] 	= subject;
	jsonMessage["messagePlainText"]	= plainText;
	jsonMessage["messageTarget"]	= target;
	jsonMessage["messageDate"]		= date;
	jsonMessage["messageSender"]	= sender;

	return jsonMessage;
}



