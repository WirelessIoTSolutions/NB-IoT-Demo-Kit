/**
 * @file CommandsManager.h
 * @description Interprets and executes the commands
 *              received from the Relay-Service via Backchannel
 * @author htemizel
 * ATTENTION: Need a subscription to Nb-IoT relay service and client library on IoT device to work
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * @licence proprietary licence - mm1 Technology grants all users of the mm1 Technology relay service 
 * the right to use this software for evaluation and testing. It is not allowed to use this software 
 * with any other service than the mm1 Technology relay service of copy or use this software into other 
 * projects than related to the mm1 Technology relay service.
 *
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 */
#ifndef COMMANDSMANAGER_h_
#define COMMANDSMANAGER_h_

#include <ArduinoJson.h>
#include "SeeedOLED.h"
#include "led.h"

class CommandsManager {

  private:
  SeeedOLED oled;
  LED led1;
  int interval;
  
  public:
  CommandsManager(SeeedOLED oled, LED led1);
  void setOled(SeeedOLED oled);
  void handleBackchannelCommands(const JsonArray& array);
  void checkCommands(const JsonObject& obj);
  void executeCommands(const JsonObject& obj);
  int getRemoteLoopInterval();

};

#endif
