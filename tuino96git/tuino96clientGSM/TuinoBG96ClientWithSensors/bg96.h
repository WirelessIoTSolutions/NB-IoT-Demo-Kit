/**
 * @file bg96.h
 * @description Functions to abstract the at_client's serial communication 
 * @author Gimasi
 * @reworker htemizel
 * @licence MIT licence
 *
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 */
#ifndef _GMX_BG96_H_
#define _GMX_BG96_H_

#include <Arduino.h>

#define BG96_OK                      0 
#define BG96_KO                      1


#define BG96_DEFAULT_TIMEOUT          2000
#define BG96_BOOT_TIMEOUT             6000
#define BG96_LONG_TIMEOUT            120000

#define BG96_LTE_BAND_B1                "1"
#define BG96_LTE_BAND_B2                "2"
#define BG96_LTE_BAND_B3                "4"
#define BG96_LTE_BAND_B4                "8"
#define BG96_LTE_BAND_B5                "10"
#define BG96_LTE_BAND_B8                "80"
#define BG96_LTE_BAND_B12               "800"
#define BG96_LTE_BAND_B13               "1000"
#define BG96_LTE_BAND_B18               "20000"
#define BG96_LTE_BAND_B19               "40000"
#define BG96_LTE_BAND_B20               "80000"
#define BG96_LTE_BAND_B26               "2000000"
#define BG96_LTE_BAND_B28               "8000000"
#define BG96_LTE_BAND_B39               "4000000000"
#define BG96_LTE_BAND_ALL               "A0E189F"

#define ONCE_APN_LINK "iot.1nce.net"
#define TELEKOM_APN_LINK "iot.telekom.de"
#define TELEFONICA_APN_LINK "nbiot-sm2m.telefonica.de"
#define VODAFONE_APN_LINK "nb.inetd.gdsp"

#define TELEKOM "26201"
#define ONCE "26201"
#define VODAFONE "26202"
#define TELEFONICA "26203"

uint8_t BG96_init();
uint8_t BG96_getIMEI(char *data, uint8_t max_size);
uint8_t BG96_getIMSI(char *data, uint8_t max_size);

uint8_t BG96_getCeLevel(char *ceLevel);

void BG96_checkNBIoTConnectionProperties(char *operator_code, char *ip, uint16_t port);
void BG96_checkGSMConnectionProperties(char *operator_code, char *ip, uint16_t port);

uint8_t BG96_gpsOn();
uint8_t BG96_enableNMEA(void);
uint8_t BG96_getCoordinates(char *latitute, char *longitute);

uint8_t BG96_deviceIsConnected(char *operator_code);
uint8_t BG96_isSocketOpen(char *ip, uint16_t port);
uint8_t BG96_checkNBIoTFallback(char *operator_code);

uint8_t BG96_isConnectedToNBIoT(char *operator_code);
uint8_t BG96_isConnectedToGSM(char *operator_code);

uint8_t BG96_setOperator(char *code);
uint8_t BG96_setGSMConfigs(char *apn);
uint8_t BG96_setNBIoTConfigs(char *apn, char *band);
uint8_t BG96_setCatM1(char *apn, char *band);

uint8_t BG96_attach();
uint8_t BG96_isNetworkAttached(int *attach_status, bool mode);

uint8_t BG96_RXData(char *data, uint8_t max_size);

uint8_t BG96_TXData(char *data, int data_len);
uint8_t BG96_SocketClose();
uint8_t BG96_SocketOpen(char *ip, uint16_t port);

float BG96_convertNMEALatituteToDecDeg(char* latitute);
float BG96_convertNMEALongituteToDecDeg(char* longitute);

uint8_t BG96_signalQuality(int *rssi, int *ber );


#endif 
