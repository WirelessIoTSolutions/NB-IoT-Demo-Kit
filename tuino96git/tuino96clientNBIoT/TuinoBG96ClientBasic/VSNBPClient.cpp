/**
 * @file VSNBPClient.cpp
 * @description Implementing the protocol commands
 * @author htemizel
 * ATTENTION: Need a subscription to Nb-IoT relay service and client library on IoT device to work
 * @copyright (C) 2019 mm1 Technology GmbH - all rights reserved.
 * @licence proprietary licence - mm1 Technology grants all users of the mm1 Technology relay service 
 * the right to use this software for evaluation and testing. It is not allowed to use this software 
 * with any other service than the mm1 Technology relay service of copy or use this software into other 
 * projects than related to the mm1 Technology relay service.
 *
 * Find out more about WIOTS:
 * Company:     https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
 */
#include <Arduino.h>
#include "PayloadProcesser.h"
#include <math.h>
#include "bg96.h"
#include "Parser.h"
#include "VSNBPClient.h"

/**
 * @brief Function that initiates receive to get the response of relay-service regarding the register attempt 
 */
VSNBPClient::VSNBPClient(){
  this->registerStatus = -1;
  this->IMSI = "";
  memset(this->backchannelBuffer, '\0', BUFLEN);
}

void VSNBPClient::setIMSI(String IMSI){
  this->IMSI = IMSI;
}

/**
 * @brief Function that initiates receive to get the response of relay-service regarding the register attempt 
 */
int VSNBPClient::ReceiveRegisterAck(){
  memset(this->recvBuf, '\0', BUFLEN);
  if(BG96_RXData(this->recvBuf, BUFLEN) == 0){
    if(checkRegisterAcknoledge(this->recvBuf)){
      return SUCCESS;
    }else{
      return NO_ACKNOLEDGE; 
    } 
  }else{
    return NO_ACKNOLEDGE;
  }
}

/**
 * @brief Function that initiates the buffer setup and register process sending
 * @param The current SIM cards imsi inside the device
 */
int VSNBPClient::SendRegister(){
  //Sending Register to Server
  memset(this->sendBuf, '\0', BUFLEN);
  SetupBufForRegister(this->sendBuf, this->IMSI);
  if(BG96_TXData(this->sendBuf, strlen(this->sendBuf)) == 0){
    delay(SEND_DELAY);
    return SUCCESS;
  }else{
    Serial.println("Register not sendable");
    return SERVER_NOT_REACHABLE;
  }
}

/**
 * @brief Function that coordinates the register process to the relay-service
 * @param The current SIM cards imsi inside the device
 */
int VSNBPClient::RegisterProcedure(){
  int sendRetries = 0;
  int recvRetries = 0;

  while(sendRetries < MAX_RETRIES){
    if(SendRegister() == SUCCESS){
      while(recvRetries < MAX_RETRIES){
        if(ReceiveRegisterAck() == SUCCESS){
          return SUCCESS;
        }
        recvRetries++;
        Serial.println("No Acknolegde received at ReceiveRegisterAck, polling again in 6.5s.\n");
        delay(RETRY_INTERVALL);
      }
      return NO_ACKNOLEDGE;
    }
    sendRetries++;
    delay(RETRY_INTERVALL);
  }
  return NO_ACKNOLEDGE;
  
}

/**
 * @brief Function that checks if there is data from the relay-service for the device
 * @param recvBuffer that holds all the data received from the relay-service including protocol data 
 * @param backchannelBuffer that holds the relay-services data for the device
 */
void VSNBPClient::CheckBackchannelPayload(){
  memset(this->backchannelBuffer, '\0', BUFLEN);
  if(strlen(this->recvBuf)>2){
    appendBackchanneldata(this->backchannelBuffer, this->recvBuf);
    Serial.print("Relay-Service Backchannel Payload: ");
    Serial.println(this->backchannelBuffer);
  }else{
    Serial.println("No Backchannel Payload received from Relay Service");
  }
}

/**
 * @brief Function that coordinates the sendMsg process to send sensor data to the relay-service
 * @param backchannelBuffer that holds the relay-services data for the device
 * @param the string to search for inside the buffer
 */
int VSNBPClient::ContainsBackchannelPayload(char* searchStr){
  if((strstr(this->backchannelBuffer, searchStr)) != NULL){
    Serial.print("BackchannelBuffer contains: ");
    Serial.println(searchStr);
    return SUCCESS;
  }else{
    Serial.print("BackchannelBuffer doesn't contain: ");
    Serial.println(searchStr);
    return FAILED;
  }
}

/**
 * @brief Function that initiates receive to get the response of relay-service regarding the register attempt 
 */
int VSNBPClient::ReceiveSendMsgAck(){
  memset(this->recvBuf, '\0', BUFLEN);
  if(BG96_RXData(this->recvBuf, BUFLEN) == 0){
    if(checkSendRecvAcknoledge(this->recvBuf)){
      return SUCCESS;
    }else{
      return NO_ACKNOLEDGE; 
    } 
  }else{
    return NO_ACKNOLEDGE;
  }
}

/**
 * @brief Function that initiates the buffer setup and sendMsg process
 * @param sensorDataBuf that holds the aquired sensor data
 */
int VSNBPClient::SendMsg(char* sensorDataBuf){
  //Sending Register to Server
  memset(this->sendBuf, '\0', BUFLEN);
  SetupBufForSendMsg(this->sendBuf, sensorDataBuf);
  if(BG96_TXData(this->sendBuf, strlen(this->sendBuf)) == 0){
    delay(SEND_DELAY);
    return SUCCESS;
  }else{
    Serial.println("Msg not sendable");
    return SERVER_NOT_REACHABLE;
  }
}

/**
 * @brief Function that coordinates the sendMsg process to send sensor data to the relay-service
 * @param sensorDataBuf that holds the aquired sensor data
 * @param backchannelBuffer to append the relay-services data for the device
 */
int VSNBPClient::SendMsgProcedure(char* sensorDataBuf){
  int sendRetries = 0;
  int recvRetries = 0;
  
  if(this->registerStatus != SUCCESS){
    Serial.println("Registration to the Relay Service needed!");
    this->registerStatus = RegisterProcedure();
  }else{
    Serial.println("Already Registered, no registraion needed!");
  }
  if(this->registerStatus == SUCCESS){
    while(sendRetries < MAX_RETRIES){
      if(SendMsg(sensorDataBuf) == SUCCESS){
        while(recvRetries < MAX_RETRIES){
          if(ReceiveSendMsgAck() == SUCCESS){
            CheckBackchannelPayload();
            return SUCCESS;
          }
          recvRetries++;
          Serial.println("No Acknolegde received at ReceiveSendMsgAck, polling in 6.5s.\n");
          delay(RETRY_INTERVALL);
        }
        this->registerStatus = FAILED;
        return NO_ACKNOLEDGE;
      }
      sendRetries++;
      delay(RETRY_INTERVALL);
    }
    this->registerStatus = FAILED;
    return NO_ACKNOLEDGE;
  }
}

/**
 * @brief function to get the backchannelbuffers content
 * @return returns the backchannnelbuffer as a string
 */
String VSNBPClient::GetBackchannelPayload(){
  return this->backchannelBuffer;
}
