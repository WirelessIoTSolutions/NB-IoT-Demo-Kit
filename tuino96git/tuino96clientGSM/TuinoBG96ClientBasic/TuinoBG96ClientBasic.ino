/**
 * @file TuinoBG96ClientWithSensors.ino
 * @description Example Client on how to use the Relay-Service 
 *              based on GSM with the Tuino96
 * @author htemizel
 * ATTENTION: Need a subscription to Nb-IoT relay service and client library on IoT device to work
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * 
 *
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 */
#include "tuino096.h"
#include "bg96.h"
#include "VSNBPClient.h"
#include "at_client.h"

/* APN LINK BASED ON YOUR OPERATOR (look into bg96.h)*/
#define OPERATOR_APN    ONCE_APN_LINK
//#define OPERATOR_APN    TELEKOM_APN_LINK
//#define OPERATOR_APN    TELEFONICA_APN_LINK
//#define OPERATOR_APN    VODAFONE_APN_LINK

/* OPERATOR CODE BASED ON YOUR OPERATOR (look into bg96.h)*/
#define OPERATOR_CODE   ONCE
//#define OPERATOR_CODE   TELEKOM
//#define OPERATOR_CODE   VODAFONE
//#define OPERATOR_CODE   TELEFONICA

/* ENDPOINT WHERE YOU WANT TO SEND DATA */
#define UDP_IP_ADDRESS  "XXX.XXX.XXX.XXX"
#define UDP_PORT         XXXXX

//class instance to send data 
VSNBPClient relayServiceClient;

// setup function to set all configurations needed for the application
void setup() {
  
  Serial.begin(9600);
  
  //init function for the BG96 MODULE
  int ret = BG96_init();
  if ( ret ==  BG96_OK )
    Serial.println("DEBUG - BG96 MODEM Initialization Success!\n");
  else if ( ret ==  BG96_KO ){
    Serial.println("DEBUG - Error while initializing BG96 Modem!\n");
    abort();
  }
  
  //the SIM cards IMSI inside the device
  char IMSI[32] = {'\0'};
  //procedure to get the SIM Cards IMSI 
  ret = BG96_getIMSI(IMSI,sizeof(IMSI));
  relayServiceClient.setIMSI(IMSI);
  if (ret == BG96_OK){
    Serial.print("DEBUG - IMSI Read Correctly! -> ");
    Serial.print(IMSI);Serial.println("\n");
  }else if (ret == BG96_KO){
    Serial.println("DEBUG - Could not read IMSI. SIM Card inserted?\n");
    abort();
  }

  //function to set the necessary NBIoT parameters
  ret = BG96_setGSMConfigs(OPERATOR_APN);
  if (ret == BG96_OK)
    Serial.println("DEBUG - GSM Config Set!\n");
  else if (ret == BG96_KO){
    Serial.println("DEBUG - Could not set GSM configurations, check the freq. Band and APN link!\n");
    abort();
  }

}

//the buffer that will be filled and send to the Relay-Service
char sensorDataBuf[BUFLEN] = "Test";
//intervall of the loop in ms
int loopIntervall = 30000;

void loop() {
  
  //checking the GSM connection and UDP Socket to make a reconnection/reopen attempt if needed
  BG96_checkGSMConnectionProperties(OPERATOR_CODE, UDP_IP_ADDRESS, UDP_PORT);

  /***********************************************
   * 
   * Put your code in here to aqauire sensor data 
   * 
   ***********************************************/

  //sending the buffer via NBIoT using the protocols SendMsgProcedure when device is registered
  relayServiceClient.SendMsgProcedure(sensorDataBuf);

  /***********************************************
   * 
   * search for strings in the response of the relay service 
   * with the 
   * relayServiceClient.ContainsBackchannelPayload("test") - function
   * 
   ***********************************************/

   relayServiceClient.ContainsBackchannelPayload("Test");
   
   //delay for the main loop
   Serial.println("Main Loop End, starting again in " + String(loopIntervall/1000) + " seconds.\n");
   delay(loopIntervall);
}
