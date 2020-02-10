/**
 * @file Parser.cpp
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
 * Company: https://wireless-iot-solutions.com/wp/
 * GitHub:  https://github.com/WirelessIoTSolutions/
 */
#include "Parser.h"

#define PROTOCOL_VERSION_POSITION 0
#define PROTOCOL_COMMAND_POSITION 1
#define IMSI_POSITION 2
#define SHAREDSECRET_POSITION 2
#define PAYLOAD_POSITION 6
#define BACKCHANNEL_PAYLOAD_POSITION 2

/**
 * @brief Function sets the Protocolversion to the specific Position in sendBuf
 * @param The buffer that will hold the payload that shall be send
 * @param The protocol version that will be put into the sendBufs specific position
 */
void SetProtocolVersion(char *sendBuf, short ProtocolVersion) {
    sendBuf[PROTOCOL_VERSION_POSITION] = ProtocolVersion;
}

/**
 * @brief Function sets the protocol command to the specific Position in sendBuf
 * @param The buffer that will hold the payload that shall be send
 * @param The protocol command that will be put into the sendBufs specific position
 */
void SetProtocolCommand(char *sendBuf, short ProtocolCommand) {
    sendBuf[PROTOCOL_COMMAND_POSITION] = ProtocolCommand;
}

/**
 * @brief Function sets the IMSI to the specific Position in sendBuf
 * @param The buffer that will hold the payload that shall be send
 * @param The IMSI that will be put into the sendBufs specific position
 */
void SetIMSI(char *sendBuf, String IMSI) {
    strcpy((sendBuf+IMSI_POSITION), IMSI.c_str());
}


/**
 * @brief Function sets the SharedSecret to the specific Position in sendBuf
 * @param The buffer that will hold the payload that shall be send
 * @param The SharedSecret that will be put into the sendBufs specific position
 */
void SetSharedsecret(char *sendBuf, String Sharedsecret) {
    strcpy((sendBuf+SHAREDSECRET_POSITION), Sharedsecret.c_str());
}

/**
 * @brief Function sets the sensor payload to the specific Position in sendBuf
 * @param The buffer that will hold the payload that shall be send
 * @param The sensor payload that will be put into the sendBufs specific position
 */
void SetPayload(char *sendBuf, String Payload) {
    strcpy((sendBuf+PAYLOAD_POSITION), Payload.c_str());
}

/**
 * @brief Function sets the sensor payload to the specific Position in sendBuf
 * @param The buffer that will hold the payload that shall be send
 * @param The sensor payload that will be put into the sendBufs specific position
 */
void SetPayload(char *sendBuf, char* Payload) {
    strcpy((sendBuf+PAYLOAD_POSITION), Payload);
}

/**
 * @brief Function parses the protocol version from the specific Position in recvBuf
 * @param The buffer that holds the received payload of UDP Relay Service
 * @returns the protocol version
 */
char getProtocolVersion(char *recvBuf) {
    return recvBuf[PROTOCOL_VERSION_POSITION];
}

/**
 * @brief Function parses the protocol command from the specific Position in recvBuf
 * @param The buffer that holds the received payload of UDP Relay Service
 * @returns the protocol command
 */
char getProtocolCommand(char *recvBuf) {
    return recvBuf[PROTOCOL_COMMAND_POSITION];
}

/**
 * @brief Function parses the SharedSecret from the specific Position in recvBuf
 * @param The buffer that holds the received payload of UDP Relay Service
 * @returns the SharedSecret
 */
String getSharedsecret(char *recvBuf) {
    String dummy(recvBuf);
    return dummy.substring(SHAREDSECRET_POSITION,(SHAREDSECRET_POSITION+4));
}

/**
 * @brief Function parses the client process payload from the specific Position in recvBuf
 * @param The buffer that holds the received payload of UDP Relay Service
 * @returns the client processes payload
 */
String getClientProcessPayload(char *recvBuf) {
    String dummy(recvBuf);
    return dummy.substring(PAYLOAD_POSITION);
}

/**
 * @brief Function measures the length of char buf
 * @param The char buf that will be measured
 * @returns the length of that buf
 */
int getLength(char *buf){
    String dummy(buf);
    return dummy.length();
}

/**
 * @brief Function that parses and appends the relay-services data for the device to "backchannelBuffer"
 * @param backchannelBuffer that is filled with the relay-services data for the device
 * @param recvBuffer that holds all the data received from the relay-service including protocol data 
 */
void appendBackchanneldata(char* backchannelBuffer, char* recvBuffer){
    strcpy(backchannelBuffer+strlen(backchannelBuffer), recvBuffer+BACKCHANNEL_PAYLOAD_POSITION);
}
