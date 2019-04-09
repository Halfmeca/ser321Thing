#include <string>
#include <json/json.h>


using namespace std;






class Message{
public:

	string header , subject , plainText , target , date , sender;
	Message(string messageHeader , string messageSubject , string messagePlainText , string messageTarget
						, string messageDate , string messageSender);
	 Message();
	~Message();

	void setValues(string messageHeader , string messageSubject , string messagePlainText , string messageTarget
						, string messageDate , string messageSender);
	void setValues(Json::Value& msgJson);
	Json::Value toJson();
};
