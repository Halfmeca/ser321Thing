#include "MessageGui.cpp"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Check_Browser.H>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <stdlib.h>
using namespace std;
string host;
string name;
/**
 * Copyright (c) 2019 Tim Lindquist,
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose: C++ FLTK client UI for Message management.
 * This class extends the Gui component class MessageGui and demonstrates
 * sample control functions that respond to button clicks drop-down selects.
 * This software is meant to run on Linux and MacOS using g++.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering,
 *                       IAFSE, ASU at the Polytechnic campus
 * @file    samplemain.cpp
 * @date    January, 2019
 **/
class SampleStudentClient : public MessageGui {

   /** ClickedX is one of the callbacks for GUI controls.
    * Callbacks need to be static functions. But, static functions
    * cannot directly access instance data. This program uses "userdata"
    * to get around that by passing the instance to the callback
    * function. The callback then accesses whatever GUI control object
    * that it needs for implementing its functionality.
    */
   static void ClickedX(Fl_Widget * w, void * userdata) {
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      exit(1);
   }

   static void ClickedGet(Fl_Widget * w, void * userdata) {
      // since this is a static method, it does not have access to any instance variables.
      // get access through the userdata argument which is the instance.
      
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
      Fl_Input * dateFI = anInstance->dateFI;
      Fl_Input * subjectFI = anInstance->subjectFI;
      Fl_Input * toFI = anInstance->toFI;
      Fl_Input * fromFI = anInstance->fromFI;
      Fl_Check_Browser * headers = anInstance->headerFCB;
      HttpClient httpclient(host);
      messageserverstub mg(httpclient);



      // clear all existing entries from the list of message headers
      headers->clear();
      
    
      // get the instance's userId string so we know who is sending messages
      Json::Value jsonHeaders = mg.getHeaders(name);
      
      
        for(int ii = 1; ii <jsonHeaders.size(); ii++)
        {
          cout<< ii;
          string aString = jsonHeaders[ii].asString();
          headers->add(aString.c_str());

        }
          // all FLTK controls are loaded via c strings, not c++ string objects.

      // select this first element in the list. the first arg is the index into the
      // list (1st entry) beginning at 1. The second arg is 0 for unchecked and 1 for
      // checked.
      
      
      // fill in the corresponding fields as if we are displaying a real message.
      headers->check_none();
      // add another header
      

      
  }
    static void ClickedSend(Fl_Widget * w, void * userdata) {
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;

      Fl_Check_Browser * headers = anInstance->headerFCB;
      Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
      Fl_Input * dateFI = anInstance->dateFI;
      Fl_Input * subjectFI = anInstance->subjectFI;
      Fl_Input * toFI = anInstance->toFI;
      Fl_Input * fromFI = anInstance->fromFI;
      HttpClient httpclient(host);
      messageserverstub mg(httpclient);


      string fromString = toFI->value();
      string senderString = fromFI->value();
      string subjectString = subjectFI->value();
      string dateString = dateFI->value();
      string headerString = subjectString + " " + dateString;
      string textString = messageFMI->value();
      Message aMessage;
      aMessage.setValues(headerString, subjectString ,textString , fromString , dateString, senderString);
      Json::Value messageJson = aMessage.toJson();
      mg.addMessage(messageJson);
      headers->add(headerString.c_str());

      toFI->value(" ");
      fromFI->value(" ");
      dateFI->value(" ");
      subjectFI->value(" ");
      messageFMI->value(" ");

      mg.saveToJsonFile();

    }

    static void ClickedReply(Fl_Widget * w, void * userdata) {
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;

      Fl_Check_Browser * headers = anInstance->headerFCB;
      Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
      Fl_Input * dateFI = anInstance->dateFI;
      Fl_Input * subjectFI = anInstance->subjectFI;
      Fl_Input * toFI = anInstance->toFI;
      Fl_Input * fromFI = anInstance->fromFI;

      string fromString = toFI->value();
      string senderString = fromFI->value();
      string subjectString = "Re:";
      subjectString.append(subjectFI->value());
      string textString = "\n\n\n\n\n\n-----------------------------------";
      textString.append(messageFMI->value());


      auto aClk = std::chrono::system_clock::now();
      auto aTime = std::chrono::system_clock::to_time_t(aClk);
      std::string aDateStr(ctime(&aTime));
      // the conversion to string adds a new line at the end of the string. Trim it.
      std::string trimmed(trimMe(aDateStr));
      // load the date field with the current time in string form
      //dateFI->value(ctime(&aTime));
      dateFI->value(trimmed.c_str());
      toFI->value(senderString.c_str());
      fromFI->value(fromString.c_str());
      subjectFI->value(subjectString.c_str());
      messageFMI->value(textString.c_str());
      headers->check_none();

  } 



   static void ClickedDelete(Fl_Widget * w, void * userdata) {
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
  
      Fl_Check_Browser * headers = anInstance->headerFCB;
      Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
      Fl_Input * dateFI = anInstance->dateFI;
      Fl_Input * subjectFI = anInstance->subjectFI;
      Fl_Input * toFI = anInstance->toFI;
      Fl_Input * fromFI = anInstance->fromFI;
      HttpClient httpclient(host);
      messageserverstub mg(httpclient);

      int which = headers->value();
      
      if(which>0)
      {
        string aString = headers->text(which);
        
        mg.removeMessage(aString);
        toFI->value(" ");
        fromFI->value(" ");
        dateFI->value(" ");
        subjectFI->value(" ");
        std::string msg(" ");
        headers->clear();
      
      
        // get the instance's userId string so we know who is sending messages
        Json::Value jsonHeaders = mg.getHeaders(name);

        for(int ii = 1; ii <jsonHeaders.size(); ii++)
        {
          cout<< ii;
          string aString = jsonHeaders[ii].asString();
          headers->add(aString.c_str());

        }
        headers->check_none();
        mg.saveToJsonFile();

      }

   }
   
   static std::string& trimMe (std::string& str) {
      // right trim
      while (str.length() > 0 && (str[str.length()-1] == ' ' || str[str.length()-1] == '\t'
                                  || str[str.length()-1] == '\n' ||  str[str.length()-1] == '\r')){
         str.erase(str.length ()-1, 1);
      }
      // left trim
      while (str.length () > 0 && (str[0] == ' ' || str[0] == '\t')){
         str.erase(0, 1);
      }
      return str;
   }

   static void SelectedHeader(Fl_Widget * w, void * userdata) {
      SampleStudentClient* anInstance = (SampleStudentClient*)userdata;
      Fl_Check_Browser * headers = anInstance->headerFCB;
      int howMany = headers->nitems();
      int which = headers->value();
      Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
      Fl_Input * dateFI = anInstance->dateFI;
      Fl_Input * subjectFI = anInstance->subjectFI;
      Fl_Input * toFI = anInstance->toFI;
      Fl_Input * fromFI = anInstance->fromFI;
      string aString = headers->text(which);
      HttpClient httpclient(host);
      messageserverstub mg(httpclient);
      Json::Value messageJson = mg.getMessage(aString);
      Message aMessage;
      aMessage.setValues(messageJson);

      toFI->value((aMessage.target).c_str());
      fromFI->value((aMessage.sender).c_str());
      dateFI->value((aMessage.date).c_str());
      subjectFI->value((aMessage.subject).c_str());
      std::string msg((aMessage.plainText).c_str());
      messageFMI->value(msg.c_str());
      
      // unselect all but the item just selected. Note, first item is item 1 not 0
      for(int i=1; i<howMany+1; i++){
         if(i != which ){
            headers->checked(i,0);

         }
      }


   }

public:
   std::string userId;
   SampleStudentClient(const char * name = 0) : MessageGui(name) {
      getButt->callback(ClickedGet, (void*)this);
      deleteButt->callback(ClickedDelete, (void*)this);
      headerFCB->callback(SelectedHeader, (void*)this);
      replyButt->callback(ClickedReply, (void*)this);
      sendButt->callback(ClickedSend , (void*)this);
      headerFCB->when(FL_WHEN_CHANGED);
      
      callback(ClickedX);

      userId = "Tim.Lindquist";
   }
};

int main(int argc, char*argv[]) {
   
  host = "http://127.0.0.1:8080";
  string hostArg = "localhost";
  string ipArg = "8080";
  name = "Halfmeca";
  if(argc>3){
     hostArg = string(argv[1]);
     ipArg = (argv[2]);
     name = string(argv[3]);
  }

  host = hostArg + ":" + ipArg ;


  

  SampleStudentClient cm(name.c_str());

  return (Fl::run());
}
