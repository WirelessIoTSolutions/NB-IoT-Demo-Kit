/**
 * @file Parser.h
 * @description Functions for parsing protocol specific data 
 *              into the buffers and from the buffers
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
#ifndef CLIENTUDP_PARSER_H
#define CLIENTUDP_PARSER_H

#include <Arduino.h>

void SetProtocolVersion(char *sendBuf, short ProtocolVersion);
void SetProtocolCommand(char *sendBuf, short ProtocolCommand);
void SetSharedsecret(char *sendBuf, String Sharedsecret);
void SetIMSI(char *sendBuf, String IMSI);
void SetPayload(char *sendBuf, String Payload);
void SetPayload(char *sendBuf, char* Payload);
char getProtocolVersion(char *recvBuf);
char getProtocolCommand(char *recvBuf);
String getSharedsecret(char *recvBuf);
String getClientProcessPayload(char *recvBuf);
int getLength(char *buf);
void appendBackchanneldata(char* backchannelBuffer, char* recvBuffer);

#endif //CLIENTUDP_PARSER_H
