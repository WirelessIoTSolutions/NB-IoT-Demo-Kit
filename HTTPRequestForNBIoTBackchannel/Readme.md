# HTTP Request Script Guide
The following section provides information about the HTTP Request Script and how to use it for sending back data to the NBIoT Demo Board.

## 1. Setting up the script

In order to be able to send data back to the NBIoT Demo Board you have to open up the constants.py. There are two things to do: 
Fill in the "username" and "password" sections with the account that is connected to the IMSI and the "IMSI" section with the IMSI inside of your NBIoT Demo Board

## 2. Running the script

Run the run.py script in your terminal by calling it with the data you want to send(The demo code for instance wants a JSON array with all the commands for the Demo Board as JSON objects) which looks like this:
	
	python3 run.py '[{"command":"oled", "value":"Hallo"}, {"command":"interval", "value":"25000"}]'
