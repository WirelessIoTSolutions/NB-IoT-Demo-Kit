"""
@file        run.py
@description simulation of a user
             that wants to send payload back to its NBIoT device
@author      htemizel
Find out more about mm1 Technology:
Company:     http://mm1-technology.de/
"""
import http_client
from http_client import HTTP_Client
from constants import test_username as user, test_password as pw, base_url as url, imsi
import sys
if __name__=="__main__":
    arg = sys.argv[1]
    print("\nSending String"+arg+"\n")
    #client object to login and send Payload to the relay-service and to the device
    client = HTTP_Client(url)
    #the login to the relay service
    client.request_login(user, pw)
    #the payload for the NBIoT device with the specific IMSI
    client.sendMSG(str(arg), imsi)
