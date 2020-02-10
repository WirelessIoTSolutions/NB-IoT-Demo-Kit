/**
 * @file VSNBPClient.h
 * @description Implementing the protocol commands
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
#ifndef VSNBPCLIENT_h_
#define VSNBPCLIENT_h_

#include <Arduino.h>
#include <stdarg.h>
#include "PayloadProcesser.h"


/* @def Error code for overall success*/
#define FAILED 0
/* @def Error code for overall success*/
#define SUCCESS 1
/* @def Error code for being unable to send data to the apn*/
#define SERVER_NOT_REACHABLE -1
/* @def Error code for getting no acknowledge after successfully sending data*/
#define NO_ACKNOLEDGE -1
/* @def Maximum amount of retries before restarting the Tuino1 via software*/
#define MAX_RETRIES 5
/* @def Error code for overall success*/
#define RETRY_INTERVALL 7000
/* @def Error code for overall success*/
#define SEND_DELAY 5000
/* @def maximum buffer length*/
#define BUFLEN 1200

class VSNBPClient {

  private:
  String IMSI;
  int registerStatus;
  /* buffers for sending and receiving data*/
  char sendBuf[BUFLEN];
  char recvBuf[BUFLEN];
  char backchannelBuffer[BUFLEN];
  
  public:
  VSNBPClient();
  void setIMSI(String IMSI);
  int RegisterProcedure();
  int SendRegister();
  int ReceiveRegisterAck();
  int ReceiveSendMsgAck();
  int SendMsg(char* sensorDataBuf);
  int SendMsgProcedure(char* sensorDataBuf);
  void CheckBackchannelPayload();
  int ContainsBackchannelPayload(char* searchStr);
  String GetBackchannelPayload();

};

#endif
