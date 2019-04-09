#include "GroupMessage.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <json/json.h>


using namespace std;
	
	GroupMessage::GroupMessage(){}




	void GroupMessage::initGroupMessage(string jsonFileName)
	{


		Json::Reader reader;
		Json::Value root;
		std :: ifstream json(jsonFileName.c_str() , std::ifstream::binary);
		bool parseSuccess = reader.parse(json,root,false);
		if(parseSuccess)
		{
			Json::Value::Members mbr = root.getMemberNames();
			for(vector<string>::const_iterator i = mbr.begin() ; i != mbr.end() ; i++)
			{
				Json::Value jsonMessage = root[*i];
				string nameStr = "name";
				if(nameStr.compare(*i) == 0)
				{
					name = jsonMessage.asString();
				}
				else 
				{
					string messageHeader 	= jsonMessage["messageHeader"].asString();
					string messageSubject 	= jsonMessage["messageSubject"].asString();
					string messagePlainText	= jsonMessage["messagePlainText"].asString();
					string messageTarget 	= jsonMessage["messageTarget"].asString();
					string messageDate		= jsonMessage["messageDate"].asString();
					string messageSender	= jsonMessage["messageSender"].asString();

					Message * aMessage = new Message(messageHeader , messageSubject , messagePlainText , messageTarget
						, messageDate , messageSender);

					messages[messageHeader] = *aMessage;

				}

			}

		}

	}


	void GroupMessage::toJsonFile(string jsonFileName)
	{	
		
		Json::Value jsonLib;
		jsonLib["name"] = name;
		for(std::map<string , Message>::iterator i = messages.begin() ; i != messages.end() ; i++)
		{
			string key = i->first;
			Json::Value jsonMessage;
			Message msg = messages[key];
			
			jsonMessage["messageHeader"] 	= msg.header;
			jsonMessage["messageSubject"] 	= msg.subject;
			jsonMessage["messagePlainText"]	= msg.plainText;
			jsonMessage["messageTarget"]	= msg.target;
			jsonMessage["messageDate"]		= msg.date;
			jsonMessage["messageSender"]	= msg.sender;
			jsonLib[key] = jsonMessage;

		}
		Json::StyledStreamWriter ssw(" ");
		std::ofstream jsonOutFile(jsonFileName.c_str(), std::ofstream::binary);
   		ssw.write(jsonOutFile, jsonLib);
	}


	GroupMessage::~GroupMessage()
	{

		messages.clear();
	}

	void GroupMessage::add(Message msg)
	{
		messages[msg.header] = msg;

	}
	void GroupMessage::add(Json::Value& msgJson)
	{
		Message msg;
		msg.setValues(msgJson);
		messages[msg.header] = msg;

	}

	void GroupMessage::remove(Message msg)
	{
		messages.erase(msg.header);
	}

	void GroupMessage::remove(string header)
	{
		messages.erase(header);
	}

	Json::Value GroupMessage::get(string msgHeader)
	{
		Message aMessage = messages[msgHeader];
		return aMessage.toJson();

	}

	Json::Value GroupMessage::getHeaders(string userName)
	{
		Json::Value ret(Json::arrayValue);
		vector<string> aVector;
		aVector.push_back("temp");
		for(map<string, Message>:: iterator it = messages.begin() ; it != messages.end() ; ++it)
		{
			if((it->second).target == userName)
			{
				aVector.push_back(it->first);
			}
		}

		for(std::vector<string>::iterator it = aVector.begin(); it!=aVector.end();++it) {
      		ret.append(Json::Value(*it));
   		}


		return ret;
	}


 