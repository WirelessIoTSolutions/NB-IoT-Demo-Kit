/**
 * @file PayloadProcesser.cpp
 * @description Functions for putting together and checking
 *              send and receive buffers
 * @author htemizel
 * ATTENTION: Need a subscription to Nb-IoT relay service and client library on IoT device to work
 * @copyright (C) 2019 WIOTS GmbH - all rights reserved.
 * @licence proprietary licence - WIOTS grants all users of the WIOTS relay service 
 * the right to use this software for evaluation and testing. It is not allowed to use this software 
 * with any other service than the WIOTS relay service of copy or use this software into other 
 * projects than related to the WIOTS relay service.
 *
 * Find out more about WIOTS:
 * Company:     https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
 */
#include "PayloadProcesser.h"
#include "Parser.h"
#include <string.h>

using namespace std;

// Protocol Version
short ProtocolVersion1 = 1;

// Protocol commands
short Register = 1;
short RegisterAck = 2;
short SendMsg = 3;
short SendRespAck = 4;

// stores current "SharedSecret" between Device and Server
String SharedSecret = "";

// payload of the clients process if it decides to send a message ti the device
String ClientProcessPayload = "";

/**
 * @brief Function that sets the sendBuf up to match the Register pattern
 * @param The buffer that will hold the payload that shall be send
 * @param The current SIM cards imsi inside the device
 */
void SetupBufForRegister(char *sendBuf, String imsi){
    SetProtocolVersion(sendBuf, ProtocolVersion1);
    SetProtocolCommand(sendBuf, Register);
    SetIMSI(sendBuf, imsi);
    Serial.print("Finished Payload for Register: ");
    Serial.println(sendBuf);
}

/**
 * @brief Function that sets the sendBuf up to match the SendMsg pattern
 * @param The buffer that will hold the payload that shall be send
 * @param The buffer that holds the sensor data that will be put into sendBuf
 */
void SetupBufForSendMsg(char *sendBuf, char* Payload){
    SetProtocolVersion(sendBuf, ProtocolVersion1);
    SetProtocolCommand(sendBuf, SendMsg);
    SetSharedsecret(sendBuf, SharedSecret);
    SetPayload(sendBuf, Payload);
    if(getLength(sendBuf)<7){
        Serial.println("Payload is to short to be compatible for SendMsg");
    }
    Serial.print("Finished Payload for SendMsg: ");
    Serial.println(sendBuf);
}

/**
 * @brief Function that checks if the recieved data is RegisterAck and 
 *        if so extracts the SharedSecret
 * @param The buffer that holds the received payload of UDP Relay Service
 * @returns 1 for success, 0 for wrong or no acknowledgement
 */
int checkRegisterAcknoledge(char *recvBuf) {
    if(getProtocolVersion(recvBuf) == ProtocolVersion1){
        if(getProtocolCommand(recvBuf) == RegisterAck) {
            SharedSecret = getSharedsecret(recvBuf);
            Serial.println("Register got Acknoledged");
            Serial.println("Sharedsecret:" + SharedSecret + "\n");
            return 1;
        }else{
            Serial.println("No Acknoledgement for Register\n");
            return 0;
        }
    }else{
        Serial.println("Wrong Protoclversion at Registeracknoledgement\n");
        return 0;
    }
}

/**
 * @brief Function that checks if the recieved data is SendMsgAck and 
 *        if so extracts the extra payload of Clients Process
 * @param The buffer that holds the received payload of UDP Relay Service
 * @returns 1 on success, 0 on wrong/no acknowledgement or wrong SharedSecret
 */
int checkSendRecvAcknoledge(char *recvBuf) {
  if(getProtocolVersion(recvBuf) == ProtocolVersion1){
    if(getProtocolCommand(recvBuf) == SendRespAck){
      Serial.println("SendMsg got acknoledged \n");
      return 1;
    }else{
      Serial.println("Wrong Protoclcomand at SendRespAck\n");
      return 0;
    }
  }else{
    Serial.println("Wrong Protoclversion at SendMsgacknoledgement\n");
    return 0;
  }
}
