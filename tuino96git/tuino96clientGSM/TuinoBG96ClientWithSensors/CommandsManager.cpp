/**
 * @file CommandsManager.cpp
 * @description Interprets and executes the commands
 *              received from the Relay-Service via Backchannel
 * @author htemizel
 * ATTENTION: Need a subscription to Nb-IoT relay service and client library on IoT device to work
 * @copyright (C) 2019 WIOTS GmbH - all rights reserved.
 * @licence proprietary licence - WIOTS grants all users of the WIOTS relay service 
 * the right to use this software for evaluation and testing. It is not allowed to use this software 
 * with any other service than the WIOTS relay service of copy or use this software into other 
 * projects than related to the WIOTS relay service.
 *
 * Find out more about WIOTS:
 * Company: https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
 */
#include "CommandsManager.h"
#include <Arduino.h>


CommandsManager::CommandsManager(SeeedOLED oled, LED led1) {
  this->oled = oled;
  this->led1 = led1;
  this->interval = 30000;
}

void CommandsManager::handleBackchannelCommands(const JsonArray& array){
  for(int i=0; i<array.size(); i++){
    checkCommands(array[i]);   
  }
}


void CommandsManager::checkCommands(const JsonObject& obj){
  if(obj.containsKey("command")){
    executeCommands(obj);
  }
}

void CommandsManager::executeCommands(const JsonObject& obj){
  
  if(obj.get<String>("command") == "interval"){
    if((obj.get<int>("value"))>= 15000){
      this->interval = (obj.get<int>("value"));
      Serial.println("Value Interval");
      Serial.println(this->interval);
    }
  }
  
  if(obj.get<String>("command") == "oled"){
      this->oled.clearLine(7);
      this->oled.printOLED((obj.get<String>("value")), 7, 0);
  }

  if(obj.get<String>("command") == "led"){
    if((obj.get<String>("value"))== "on"){
      Serial.println("Switching LED On");
      led1.ledOn();
    }else if((obj.get<String>("value")) == "off"){
      Serial.println("Switching LED Off");
      led1.ledOff();
    }
  }
  
}

int CommandsManager::getRemoteLoopInterval(){
  return this->interval;
}

/*
if(obj.get<int>("value") == "1"){
      Serial.println("LED on");
    }else if(obj.get<String>("value") == "0"){
      Serial.println("LED off");
    }
*/
