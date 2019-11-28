/**
 * @file TuinoBG96ClientWithSensors.ino
 * @description Example Client on how to use the Relay-Service 
 *              based on NBIoT with the Tuino96
 * @author htemizel
 * ATTENTION: Need a subscription to Nb-IoT relay service and client library on IoT device to work
 * @copyright (C) 2019 WIOTS GmbH - all rights reserved.
 * 
 *
 * Find out more about WIOTS:
 * Company:     https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
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

/*FREQUENCY BAND BASED ON YOUR OPERATOR (look into bg96.h)*/
#define NBIOT_BAND      BG96_LTE_BAND_B8
//#define NBIOT_BAND      BG96_LTE_BAND_B20

/* ENDPOINT WHERE YOU WANT TO SEND DATA */
#define UDP_IP_ADDRESS  <"...">
#define UDP_PORT        <Port>

//client class instance for relay-service communication
VSNBPClient relayServiceClient;

// setup function to set all configurations needed for the application
void setup() {
  
  Serial.begin(9600);
  
  //init function for the BG96 MODULE
  int ret = BG96_init();
  if ( ret ==  BG96_OK )
    Serial.println("BG96_init() OK!");
  else if ( ret ==  BG96_KO ){
    Serial.println("Error while initializing BG96 Modem!");
    abort();
  }

  //the SIM cards IMSI inside the device
  char IMSI[32] = {'\0'};
  //procedure to get the SIM Cards IMSI 
  ret = BG96_getIMSI(IMSI,sizeof(IMSI));
  relayServiceClient.setIMSI(IMSI);
  if (ret == BG96_OK)
    Serial.println("BG96_getIMSI OK : " + String(IMSI));
  else if (ret == BG96_KO){
    Serial.println("Could not read IMSI. SIM Card inserted?");
    abort();
  }

  //function to set the necessary NBIoT parameters
  ret = BG96_setNBIoTConfigs(OPERATOR_APN, NBIOT_BAND);
  if (ret == BG96_OK)
    Serial.println("BG96_setNBIoTConfigs() OK!");
  else if (ret == BG96_KO){
    Serial.println("Could not set NBIoT configurations, check the freq. Band and APN link!");
    abort();
  }
}

//the buffer that will be filled and send to the Relay-Service
char sensorDataBuf[BUFLEN] = "Test";
//intervall of the loop in ms
int loopIntervall = 30000;

void loop() {
  
  //checking the NBIoT connection and UDP Socket to make a reconnection/reopen attempt if needed
  BG96_checkNBIoTConnectionProperties(OPERATOR_CODE, UDP_IP_ADDRESS, UDP_PORT);

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
  //delay for the main loop
  delay(loopIntervall);
}
