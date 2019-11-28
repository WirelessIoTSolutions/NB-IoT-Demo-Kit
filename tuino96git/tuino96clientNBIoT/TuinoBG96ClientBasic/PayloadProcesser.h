/**
 * @file PayloadProcesser.h
 * @description Functions for putting together and checking
 *              send and receive buffers
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
#ifndef CLIENTUDP_PAYLOADPROCESSER_H
#define CLIENTUDP_PAYLOADPROCESSER_H

#include <Arduino.h>

void setIMSI(String imsi);
void SetupBufForRegister(char *sendBuf, String imsi);
void SetupBufForSendMsg(char *sendBuf, char *Payload);
int checkRegisterAcknoledge(char *recvBuf);
int checkSendRecvAcknoledge(char *recvBuf);

#endif //CLIENTUDP_PAYLOADPROCESSER_H
