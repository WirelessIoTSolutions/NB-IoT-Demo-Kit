/**
 * @file CommandsManager.h
 * @description Interprets and executes the commands
 *              received from the Relay-Service via Backchannel
 * @author htemizel
 * ATTENTION: Need a subscription to Nb-IoT relay service and client library on IoT device to work
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * @licence MIT licence
 *
 * Find out more about mm1 Technology:
 * Find out more about WIOTS:
 * Company:     https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
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
