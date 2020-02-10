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
 * Company: https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
 */
#include <ArduinoJson.h> //Use stable Version 5
#include "Wire.h"

#include "tuino096.h"
#include "bg96.h"
#include "VSNBPClient.h"

#include "Ultrasonic.h"
#include "rotaryAngleSensor.h"
#include "lightSensor.h"
#include "SeeedOLED.h"
#include "DHT.h"
#include "led.h"

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
#define UDP_IP_ADDRESS  "XXX.XXX.XXX.XXX"
#define UDP_PORT         XXXXX

//the instances of the sensor classes
//analog PINS: A0, A1, A2...
//digital PINS: 0, 1, 2, 3...
Ultrasonic ultrasonic(4);
DHT dht(7, DHT22);
LightSensor li1(A3);
SeeedOLED oled;
LED led1(6);

//client class instance for relay-service communication
VSNBPClient relayServiceClient;

// setup function to set all configurations needed for the application
void setup() {
  //setup I2C
  Wire.begin();
  Serial.begin(9600);

  //configure the OLED display(I2C)
  oled.setupOLED();
  //configure temp&humi sensor(I2C)
  dht.begin();
  
  //init function for the BG96 MODULE
  int ret = BG96_init();
  if ( ret ==  BG96_OK ){
    Serial.println("DEBUG - BG96 MODEM Initialization Success!\n");
    oled.printOLED("BG96 init OK!", 0, 0);
  }else if ( ret ==  BG96_KO ){
    Serial.println("DEBUG - Error while initializing BG96 Modem!\n");
    oled.printOLED("BG96 init Fail", 0, 0);
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
    oled.printOLED("BG96 IMSI OK!", 1, 0);
  }else if (ret == BG96_KO){
    Serial.println("DEBUG - Could not read IMSI. SIM Card inserted?\n");
    oled.printOLED("BG96 IMSI Fail", 1, 0);
    abort();
  }

  //function to set the necessary NBIoT parameters
  ret = BG96_setNBIoTConfigs(OPERATOR_APN, NBIOT_BAND);
  if (ret == BG96_OK){
    Serial.println("DEBUG - NB-IoT Config Set!\n");
    oled.printOLED("NBIoT set OK!", 2, 0);
  }else if (ret == BG96_KO){
    Serial.println("DEBUG - Could not set NBIoT configurations, check the freq. Band and APN link!\n");
    oled.printOLED("NBIoT set Fail", 2, 0);
    abort();
  }

  //function to enable the BG96's GPS functionality
  ret = BG96_gpsOn();
  if (ret == BG96_OK){
    Serial.println("DEBUG - GPS Config Set!");
    oled.printOLED("BG96 GPS OK!", 3, 0);
  }else if (ret == BG96_KO){
    Serial.println("ERROR - Could not activate GPS Module!");
    oled.printOLED("BG96 GPS Fail", 3, 0);
    abort();
  }
  
  //function to enable NMEA to periodically read GPS data
  ret = BG96_enableNMEA();
  if (ret == BG96_OK){
    Serial.println("NMEA-Format for GPS set!");
    oled.printOLED("BG96 NMEA OK!", 4, 0);
  }else if (ret == BG96_KO){
    Serial.println("Could not enable NMEA for the GPS Module!");
    oled.printOLED("BG96 NMEA Fail", 4, 0);
    abort();
  }

  oled.printMM1Logo();
}

//the buffer that will be filled and send to the Relay-Service
char sensorDataBuf[BUFLEN] = {'\0'};

//creating a JSON object 
StaticJsonBuffer<300> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

//intervall of the loop in ms
int loopIntervall = 30000;

void loop() {
  
  //checking the NBIoT connection and UDP Socket to make a reconnection/reopen attempt if needed
  BG96_checkNBIoTConnectionProperties(OPERATOR_CODE, UDP_IP_ADDRESS, UDP_PORT);

  //__________Reading_Sensor_data___________
  //aquiring sensor data(Humidity) and printing it to the oled display
  float humidity = dht.readHumidity();
  //aquiring sensor data(Centimeters) and printing it to the oled display
  float temperature = dht.readTemperature();
  //aquiring sensor data(Centimeters) and printing it to the oled display
  long centimeters = ultrasonic.MeasureInCentimeters();
  //aquiring sensor data(lum) and printing it to the oled display
  int lum = li1.getLightAmountiinLumen();
  //aquiring sensor data(lux) and printing it to the oled display
  float lux = li1.getLightAmountiinLux();

  //_______Printing_Sensor_data_to_OLED_______
  oled.clearDisplay();
  printSensordata("Humid", 0, humidity);
  printSensordata("Temp", 1, temperature);
  printSensordata("Cm", 2, centimeters);
  printSensordata("Lumen", 3, lum);
  printSensordata("Lux", 4, lux);

  //string to store the connection status
  String connectionStatus;
  //checking the attachement status to print it to the OLED screen
  if(BG96_deviceIsConnected(OPERATOR_CODE) == BG96_OK){
    oled.printOLED("Net: Connected", 5, 0);
    connectionStatus = "Connected";
  }else{
    oled.printOLED("Net:Disconnected", 5, 0);
    connectionStatus = "Disconnected";
  }

  //string to store the connection type
  String connectionType;
  //checking the NBIoT connection status to print it to the OLED screen
  if(BG96_isConnectedToNBIoT(OPERATOR_CODE) == BG96_OK){
    oled.printOLED("NType:  Cat-NB1", 6, 0);
    connectionType = "Cat-NB1";
  }else if(BG96_isConnectedToGSM(OPERATOR_CODE) == BG96_OK){
    oled.printOLED("NType:  EDGE", 6, 0);
    connectionType = "EDGE";
  }

  //int to store the rsrp value
  int rsrp;
  if(BG96_QCSQ(&rsrp) == BG96_OK){
    root["rsrp"] = rsrp;
  }

  //putting the sensor data into the JSON object
  root["connectStat"] = connectionStatus;
  root["connectType"] = connectionType;
  root["humidity"] = humidity;
  root["temp"] = temperature;
  root["distance"] = centimeters;
  root["lightlum"] = lum;
  root["lightlux"] = lux;

  //putting CE-LEVEL  into the JSON object only if there is CE-LEVEL available
  char ceLevel[2] = {'\0'};
  if(BG96_getCeLevel(ceLevel) == BG96_OK){
    root["celevel"] = ceLevel;
  }

  //rssi and bit error rate ints
  int rssi = 0;
  int ber = 0;
  //checking signalQuality and putting it into the JSON 
  if(BG96_signalQuality(&rssi,&ber) == BG96_OK){
    rssi = (-113) + rssi + rssi;
    root["rssi"] = rssi;
    root["ber"] = ber;
  }
  
  //putting GPS data into the JSON object only if there is GPS data available
  char latituteBuffer[14] = {'\0'};
  char longituteBuffer[15] = {'\0'};
  if(BG96_getCoordinates(latituteBuffer, longituteBuffer) == BG96_OK){
    float latitute = BG96_convertNMEALatituteToDecDeg(latituteBuffer);
    root["latitude"] = latitute;
    float longitute = BG96_convertNMEALongituteToDecDeg(longituteBuffer);
    root["longitude"] = longitute;
  }

  //printing the JSON object to the char buffer in order to send it via NBIoT
  root.printTo(sensorDataBuf);

  oled.printOLED("Send Data", 7, 0);
  //sending the buffer via NBIoT using the protocols SendMsgProcedure when device is registered
  if(relayServiceClient.SendMsgProcedure(sensorDataBuf) == SUCCESS)
    oled.printOLED(" OK!", 7, 10);
  else
    oled.printOLED(" FAIL", 7, 10);

  //relayServiceClient.ContainsBackchannelPayload("Test");
   
  //delay for the main loop
  Serial.println("Main Loop End, starting again in " + String(loopIntervall/1000) + " seconds.\n");
  delay(loopIntervall);
}



//functions to make the oled print for the sensordata shorter(actually not needed, just for convenience)
void printSensordata(String dataName, int line, float value){
  oled.printOLED(("%s: ",dataName), line, 0);
  oled.printOLED(String(value), line, 8);
}
void printSensordata(String dataName, int line, long value){
  oled.printOLED(("%s: ",dataName), line, 0);
  oled.printOLED(String(value), line, 8);
}
void printSensordata(String dataName, int line, int value){
  oled.printOLED(("%s: ",dataName), line, 0);
  oled.printOLED(String(value), line, 8);
}
