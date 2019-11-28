"""
@file        http_client.py
@description Class to enable the use of a request client to simulate a user
             that wants to send payload back to its NBIoT device
@author      htemizel
Find out more about WIOTS:
Company:     https://wireless-iot-solutions.com/wp/
"""
import requests
import json
import base64

"""
@brief Class to send payload to the relay-service for the NBIoT backchannel
"""
class HTTP_Client:

    def __init__(self, url):
        self.base_url = url
        self.connect_status()
        self.token = ""

    """
    @brief Function that checks if the remote station is available
    """
    def connect_status(self):
        print("connect_status: Server reachable?")
        response = requests.get(self.base_url, timeout=4.0)
        return self.check_response(response)

    """
    @brief Function to request a login at the relay-service to enable sending payload to a specific NBIoT device
    @param the username for the login
    @param the password for the login
    """
    def request_login(self, username, password):
        print("requesting login: ")
        header = {'content-type': 'application/json'}
        login_payload = {'username': username, 'password': password}
        response = requests.post(self.base_url + "/api/login", headers=header,  timeout=4.0, data=json.dumps(login_payload))
        self.token = response.json()['token']
        return self.check_response(response)

    """
    @brief Function to send a message to the relay-service that contains the payload for the specific NBIoT device
    @param data for the NBIoT device
    @param IMSI of the specific NBIoT device
    """
    def sendMSG(self, data, imsi):
        header = {"Authorization": "Bearer " + self.token}
        response = requests.post(self.base_url + "/api/device/%s/message" %imsi, headers=header, json={"message": data})
        print(response.json())

    """
    @brief Function that checks the response of the relay-service
    @param response from the relay-service
    """
    def check_response(self, response):
        print("response code: " + str(response.status_code))
        #print("response content: " + str(response.content))

        if (response.status_code == requests.codes.ok) is True:
            print("Success response!\n")
            return True
        else:
            print("Bad Response!\n")
            return False

