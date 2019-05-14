/**
 * @file bg96.cpp
 * @description Functions to abstract the at_client's serial communication 
 * @author Gimasi
 * @reworker htemizel
 * @licence MIT licence
 *
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 */
#include "tuino096.h"
#include "at_client.h"
#include "bg96.h"

#define DEBUG_BG96 1

void _log(String data )
{
  #ifdef DEBUG_BG96
    Serial.println(data);
  #endif
}

void _BG96Reset()
{
 
  // Reset 
  digitalWrite(PIN_BG96_RESET,LOW);
  delay(200);
  digitalWrite(PIN_BG96_RESET,HIGH);
  delay(500);
  digitalWrite(PIN_BG96_RESET,LOW);
}

void _BG96PowerCycle()
{

  // 
  digitalWrite(PIN_BG96_PWRKEY,LOW);
  delay(500);
  digitalWrite(PIN_BG96_PWRKEY,HIGH);
  delay(500);
  digitalWrite(PIN_BG96_PWRKEY,LOW);
}


void _GPIOInit()
{
 
    pinMode(BG96_RESET,OUTPUT);
    pinMode(PIN_BG96_PWRKEY,OUTPUT);
    
    digitalWrite(BG96_RESET,LOW);
    digitalWrite(PIN_BG96_PWRKEY,LOW);   
}


void _strip_all_newlines(char *data )
{
  
  String _temp= String(data);

  _temp.replace("\n","");
  _temp.replace("\r","");
  
  _temp.toCharArray(data,_temp.length()+1);

}

/*
 *  Public Functions
 */


uint8_t BG96_init() 
{

    // Init AT Interface
    at_serial_init(&Serial2, 115200);
    //at_serial_initGPS(&Serial1, 115200);

   _log("BG96 Init");
   
    // Check if module is ON
    at_send_command("AT");
    if ( at_read_for_response_single("OK",BG96_DEFAULT_TIMEOUT) == 0 )
    {
      // it Is ON
      _log("BG96 Is ON");
      _BG96PowerCycle();
      delay(1000);
    }
 
    _BG96PowerCycle();
    delay(500);
   
    _BG96Reset();
    if ( at_read_for_response_single("RDY",BG96_BOOT_TIMEOUT) != 0 )
    {
      return BG96_KO;
    }

    _log("BG96 Boot OK !!!");

    at_send_command("ATE0");

    if ( at_read_for_response_single("OK",BG96_DEFAULT_TIMEOUT) != 0 )
    {
      return BG96_KO;
    }

    _log("BG96 AT OK !!!");

     // Delay for SIM reading
     delay(2000);
     
     return BG96_OK;
}

uint8_t BG96_getIMEI(char *data, uint8_t max_size)
{
  
  at_send_command("AT+GSN");

  if ( at_read_dual_and_copy_to_buffer(data, "OK","ERROR", max_size,  BG96_DEFAULT_TIMEOUT) != AT_COMMAND_SUCCESS )
    return BG96_KO;
  
   _strip_all_newlines( data );
   
  return BG96_OK;
}

uint8_t BG96_getIMSI(char *data, uint8_t max_size)
{
  
  at_send_command("AT+CIMI");
  
  if ( at_read_IMSI_and_copy_to_buffer(data, "OK","ERROR", max_size,  BG96_DEFAULT_TIMEOUT) != AT_COMMAND_SUCCESS )
    return BG96_KO;

  _strip_all_newlines( data );
  
  
  return BG96_OK;
}

void BG96_checkGSMConnectionProperties(char *operator_code, char *ip, uint16_t port)
{ 
  int retries = 0;
  while(BG96_deviceIsConnected(operator_code) != 0){
    BG96_setOperator(operator_code,"0");
    if(retries > 7)
      Serial.println("Please check SIM Card and restart the Application!");
    retries++;
  }
  if(BG96_isSocketOpen(ip,port) != 0){
    BG96_SocketClose();
    BG96_SocketOpen(ip,port);
  }

}

void BG96_checkNBIoTConnectionProperties(char *operator_code, char *ip, uint16_t port)
{  
  int retries = 0;
  while(BG96_deviceIsConnected(operator_code) != 0 || BG96_checkNBIoTFallback(operator_code) == 0){
    BG96_setOperator(operator_code);
    if(retries > 7)
      Serial.println("Please check SIM Card and restart the Application!");
    retries++;
  }
  if(BG96_isSocketOpen(ip,port) != 0){
    BG96_SocketClose();
    BG96_SocketOpen(ip,port);
  }

}

uint8_t BG96_deviceIsConnected(char *operator_code)
{

  char tmp_string[128];
  sprintf(tmp_string,"1,2,\"%s\"",operator_code);
  
  at_send_command("AT+COPS?");
  
  if ( at_read_for_response_single(tmp_string,BG96_BOOT_TIMEOUT) == 0 )
  {
    return BG96_OK;
  }
  return BG96_KO;
}

uint8_t BG96_checkNBIoTFallback(char *operator_code)
{

  char tmp_string[128];
  sprintf(tmp_string,"\"CAT-NB1\",\"%s\"",operator_code);
  
  at_send_command("AT+QNWINFO");
  
  if ( at_read_for_response_single(tmp_string,BG96_BOOT_TIMEOUT) == 0 )
  {
    return BG96_KO;
  }

  char tmp_string2[128];
  sprintf(tmp_string2,"\"EDGE\",\"%s\"",operator_code);
  
  at_send_command("AT+QNWINFO");
  
  if ( at_read_for_response_single(tmp_string2,BG96_BOOT_TIMEOUT) == 0 )
  {
    return BG96_OK;
  }

  Serial.println("Neither connected to NBIoT nor GSM");
  return BG96_KO;
}

uint8_t BG96_isConnectedToGSM(char *operator_code)
{
  char tmp_string2[128];
  sprintf(tmp_string2,"\"EDGE\",\"%s\"",operator_code);
  
  at_send_command("AT+QNWINFO");
  
  if ( at_read_for_response_single(tmp_string2,BG96_BOOT_TIMEOUT) == 0 )
  {
    return BG96_OK;
  }

  Serial.println("Not connected to GSM");
  return BG96_KO;
}

uint8_t BG96_isConnectedToNBIoT(char *operator_code)
{
  char tmp_string2[128];
  sprintf(tmp_string2,"\"CAT-NB1\",\"%s\"",operator_code);
  
  at_send_command("AT+QNWINFO");
  
  if ( at_read_for_response_single(tmp_string2,BG96_BOOT_TIMEOUT) == 0 )
  {
    return BG96_OK;
  }

  Serial.println("Not connected to NBIoT");
  return BG96_KO;
}

uint8_t BG96_setGSMConfigs(char *apn)
{
  char cgdcont[128];
  char temp_string[128];

  at_send_command("AT+QCFG=\"nwscanseq\",01");
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    

  at_send_command("AT+QCFG=\"nwscanmode\",1");
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    

  sprintf(temp_string,"AT+QCFG=\"band\",F,0,0");
 
  at_send_command(temp_string);
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;  
    
  sprintf(cgdcont,"AT+CGDCONT=1,\"IP\",\"%s\"",apn);

  at_send_command(cgdcont);
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    


  sprintf(cgdcont,"AT+QICSGP=1,1,\"%s\",\"\",\"\",1",apn);
  at_send_command(cgdcont);
  
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;   
    
  return BG96_OK;
}

uint8_t BG96_setNBIoTConfigs(char *apn, char *band)
{
  char temp_string[128];

  at_send_command("AT+QCFG=\"nwscanseq\",0301");
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    
  
  at_send_command("AT+QCFG=\"nwscanmode\",0");
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    
  
  at_send_command("AT+QCFG=\"iotopmode\",1");
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    

  sprintf(temp_string,"AT+QCFG=\"band\",F,0,%s",band);
 
  at_send_command(temp_string);
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    

  sprintf(temp_string,"AT+QICSGP=1,1,\"%s\",\"\",\"\",1",apn);
  at_send_command(temp_string);
  
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;   
    
  return BG96_OK;
}

uint8_t BG96_setCatM1(char *apn, char *band)
{
  char temp_string[128];

  at_send_command("AT+QCFG=\"nwscanseq\",02,1");
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    

 at_send_command("AT+QCFG=\"nwscanmode\",3,1");
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    
 
  at_send_command("AT+QCFG=\"iotopmode\",0,1");
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    

  sprintf(temp_string,"AT+QCFG=\"band\",0,0,%s",band);
 
  at_send_command(temp_string);
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    

  sprintf(temp_string,"AT+QICSGP=1,1,\"%s\",\"\",\"\",1",apn);
  at_send_command(temp_string);
  
  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;   
    
  return BG96_OK;
}


uint8_t BG96_attach()
{

  at_send_command("AT+CGATT=1");

  if ( read_for_responses_dual("OK","ERROR",BG96_LONG_TIMEOUT) != 0 )
    return  BG96_KO;    
 
  return BG96_OK;
}

uint8_t BG96_setOperator(char *operator_code)
{
  char tmp_string[128];

  sprintf(tmp_string,"AT+COPS=1,2,\"%s\"",operator_code);

  at_send_command(tmp_string);
  if ( read_for_responses_dual("OK","ERROR",BG96_LONG_TIMEOUT) != 0 )
    return  BG96_KO;
 
  return BG96_OK;
}

uint8_t BG96_setOperator(char *operator_code, char* act)
{
  char tmp_string[128];

  sprintf(tmp_string,"AT+COPS=1,2,\"%s\",%s",operator_code, act);

  at_send_command(tmp_string);
  if ( read_for_responses_dual("OK","ERROR",BG96_LONG_TIMEOUT) != 0 )
    return  BG96_KO;
 
  return BG96_OK;
}

uint8_t BG96_isNetworkAttached(int *attach_status, bool mode)
{
  char data[16];
  int network_status;

  if ( mode )
    at_send_command("AT+CREG?");
  else
    at_send_command("AT+CEREG?");
  
  memset(data,0,sizeof(data));
   
  if ( at_copy_serial_to_buffer(data, ',', 16,  BG96_DEFAULT_TIMEOUT) != AT_COMMAND_SUCCESS )
    return BG96_KO;

  memset(data,0,sizeof(data));
  
  if ( at_copy_serial_to_buffer(data, '\r', 16,  BG96_DEFAULT_TIMEOUT) != AT_COMMAND_SUCCESS )
    return BG96_KO;

  *attach_status = atoi(data);

  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;   

  return BG96_OK;
}


uint8_t BG96_signalQuality(int *rssi, int *ber )
{
  char data[16];
  char *pch;
  
  at_send_command("AT+CSQ");

  memset(data,0,sizeof(data));
  if ( at_copy_serial_to_buffer(data, ':', 16,  BG96_DEFAULT_TIMEOUT) != AT_COMMAND_SUCCESS )
    return BG96_KO;

  memset(data,0,sizeof(data));
  if ( at_copy_serial_to_buffer(data, '\r', 16,  BG96_DEFAULT_TIMEOUT) != AT_COMMAND_SUCCESS )
    return BG96_KO;
    
  _strip_all_newlines( data );

  // we have 2 items
  pch = strtok (data,",");
  
  if (pch!=NULL)
  {
    *rssi = atoi( pch );
    pch = strtok (NULL,",");

    if ( pch != NULL )
    {
      *ber = atoi( pch );

      return BG96_OK;
    }
  }

   return  BG96_KO; 
}

/*
uint8_t BG96_SocketOpen(char *ip, uint16_t port)
{

  at_send_command("AT+QIOPEN=1,0,\"UDP\",\"195.201.137.136\",8000,0,1\r");

  if ( at_read_for_response_single("+QIOPEN: 0,0",10000) != 0 )
        return  BG96_KO;   
 
  return BG96_OK;
}
*/


uint8_t BG96_SocketOpen(char *ip, uint16_t port)
{
  char tmp_string[128];

  sprintf(tmp_string,"AT+QIOPEN=1,0,\"UDP\",\"%s\",%d,0,0\r", ip, port);
  
  at_send_command(tmp_string);

  if ( at_read_for_response_single("+QIOPEN: 0,0",10000) != 0 )
        return  BG96_KO;   
 
  return BG96_OK;
}

uint8_t BG96_isSocketOpen(char *ip, uint16_t port)
{
  char tmp_string[128];
  sprintf(tmp_string,"0,\"UDP\",\"%s\",%d", ip, port);

  at_send_command("AT+QISTATE?");

  if ( at_read_for_response_single(tmp_string,10000) == 0 )
        return  BG96_OK;   
 
  return BG96_KO;
}


uint8_t BG96_SocketClose(void)
{

  at_send_command("AT+QICLOSE=0");

  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    
 
  return BG96_OK;
}

uint8_t BG96_gpsOn(void)
{

  at_send_command("AT+QGPS=1");

  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    
 
  return BG96_OK;
}

uint8_t BG96_enableNMEA(void)
{

  at_send_command("AT+QGPSCFG=\"nmeasrc\",1");

  if ( read_for_responses_dual("OK","ERROR",BG96_DEFAULT_TIMEOUT) != 0 )
    return  BG96_KO;    
 
  return BG96_OK;
}

uint8_t BG96_getCoordinates(char *latitute, char *longitute)
{
  char temp[128] = { '\0' };
  char temp2[128] = { '\0' };
  //memset(temp, '\0', 250);
  
  at_send_command("AT+QGPSGNMEA=\"RMC\"");
  
  if ( at_read_dual_and_copy_to_buffer(temp,"*","GPRMC,,V,,", 128,  BG96_DEFAULT_TIMEOUT) != AT_COMMAND_SUCCESS ){
    Serial.println("UART: No Coordinates available yet!");
    return BG96_KO;
  } 

  Serial.println("UART: GPS Coordinates available!");
  /*
  Serial.println("temp:");
  Serial.println("+++++++++++++++++++++++++++++++++++++");
  Serial.println(temp);
  Serial.println("++++++++++++++++++++++++++++++++++++++");
  */
  
  char *tmp = strstr (temp,"+QGPSGNMEA: ");
  strncpy(temp2, tmp,  90);

  /*
  Serial.println("GPS NMEA over UART");
  Serial.println("+++++++++++++++++++++++++++++++++++++");
  Serial.println(temp2);
  Serial.println("++++++++++++++++++++++++++++++++++++++");
  */
  
  char *pch = strstr (temp2,",A,");
  pch = pch + 3;

  int i = 0;
  char latituteType = 'X';
  char c = ',';
  while(/**pch != c &&*/ i < 13){
    latitute[i] = *pch;
    i++;
    pch++;
  }

  /*
  Serial.println("Latitute");
  Serial.println("------------------------------------");
  Serial.println(latitute);
  Serial.println("------------------------------------");
  delay(200);
  */
  
  pch = pch + 1;

  int j = 0;
  char longituteType = 'X';
  char d = ',';
  while(/**pch != d &&*/ j < 14){
    longitute[j] = *pch;
    j++;
    pch++;
  }

  /*
  Serial.println("Longitute");
  Serial.println("------------------------------------");
  Serial.println(longitute);
  Serial.println("------------------------------------");
  delay(200);
  */
  return BG96_OK;
}

uint8_t BG96_RXData(char *data, uint8_t max_size)
{
  char temp[max_size];
  memset(temp, '\0', max_size);
  //delay(1000);
  at_send_command("AT+QIRD=0");

  //delay(1000);
  if ( at_read_dual_and_copy_to_buffer(temp, "OK","ERROR", max_size,  BG96_DEFAULT_TIMEOUT) != AT_COMMAND_SUCCESS ){
    Serial.println("UART Error at RXData");
    return BG96_KO;
  }

  Serial.print("UART Payload Received: ");
  Serial.println(temp);
  
  char *pch = strstr (temp,"+QIRD:");
  pch = pch + 7;

  int i = 0;
  char recvBytes[4] = {'\0'};
  char c = '\r';
  while(*pch != c){
    recvBytes[i] = *pch;
    i++;
    pch++;
  }

  int recvSize = atoi(recvBytes);
  Serial.print("\nRX Payload size over UART: ");
  Serial.println(recvSize);

  pch += 2;

  for(int i=0; i<recvSize; i++){
    data[i] = *pch;
    //Serial.println(data[i]);
    //Serial.println(i);
    pch++;
  }

  
  //Serial.print("RX Payload content over UART: ");
  //Serial.print("Size: ");
  //Serial.println(strlen(data));
  
  
  
  for(int i = 0; i < strlen(data); i++){
    //Serial.println(data[i]);
    //Serial.println(i);
  }
  //Serial.println();
  
  //Serial.print("TEMP got over UART: ");
  //Serial.println(temp);

  int analyse = data[0];
  int analyse2 = data[1];
  
  if(analyse == 0 && analyse2 == 0){
    Serial.println("Nothing received over UART at RXData");
    return BG96_KO;
  }else{
    return BG96_OK;
  }
}

uint8_t BG96_TXData(char *data, int data_len)
{
   char tx_string[128];
   sprintf(tx_string,"AT+QISEND=0,%d",data_len);  
   at_send_command(tx_string);
   
   if ( at_read_for_response_single(">",BG96_DEFAULT_TIMEOUT) != 0 ){
    Serial.print("UART Error at TXData");
    return  BG96_KO; 
   }
 
  _log("Sending Data to Socket");

  for (int i=0; i<data_len; i++) 
  {
    at_send_char(data[i]);
    delay(1);
  }
  
  if ( read_for_responses_dual("SEND OK","SEND FAIL",BG96_DEFAULT_TIMEOUT) != 0 ){
    Serial.print("UART Error at TXData");
    return  BG96_KO;
  }else{
    Serial.print("UART TXData Send!\n");
    return BG96_OK;
  }
}

float BG96_convertNMEALatituteToDecDeg(char* latitute){
  char decDeg1[3] = {'\0'}; 
  decDeg1[0] = latitute[0];
  decDeg1[1] = latitute[1];
  decDeg1[2] = '\0';

  float dec;
  dec = (float)atof(decDeg1);

  char decDeg2[10] = {'\0'}; 
  decDeg2[0] = latitute[2];
  decDeg2[1] = latitute[3];
  decDeg2[2] = latitute[4];
  decDeg2[3] = latitute[5];
  decDeg2[4] = latitute[6];
  decDeg2[5] = latitute[7];
  decDeg2[6] = latitute[8];
  decDeg2[7] = latitute[9];
  decDeg2[8] = latitute[10];
  decDeg2[9] = '\0';

  float deg;
  deg = (float)atof(decDeg2);
  deg = deg/60.0;
  dec = dec + deg;
  if(latitute[12] == 'S')
    dec = dec * (-1);

  return dec;
}


float BG96_convertNMEALongituteToDecDeg(char* longitute){
  char decDeg1[4] = {'\0'}; 
  decDeg1[0] = longitute[0];
  decDeg1[1] = longitute[1];
  decDeg1[2] = longitute[2];
  decDeg1[3] = '\0';
  float dec;
  dec = (float)atof(decDeg1);

  char decDeg2[10] = {'\0'}; 
  decDeg2[0] = longitute[3];
  decDeg2[1] = longitute[4];
  decDeg2[2] = longitute[5];
  decDeg2[3] = longitute[6];
  decDeg2[4] = longitute[7];
  decDeg2[5] = longitute[8];
  decDeg2[6] = longitute[9];
  decDeg2[7] = longitute[10];
  decDeg2[8] = longitute[11];
  decDeg2[9] = '\0';
  float deg;
  deg = (float)atof(decDeg2); 
  deg = deg/60.0;
  dec = dec + deg;
  
  if(longitute[13] == 'W')
    dec = dec * (-1);

  return dec;
}
