#include <SoftwareSerial.h> 
#include <SparkFunESP8266WiFi.h>
#include "ESP8266WifiConnection.h"

// constructor
ESP8266WifiConnection::ESP8266WifiConnection(String mySSID, String myPSK){
  this->mySSID = mySSID;
  this->myPSK = myPSK;

  serialTrigger(F("Press any key to begin."));

  // verifies communication with the WiFi shield, and sets it up.
  initializeESP8266();

  // connects to the defined WiFi network.
  connectESP8266();

  // prints the Shield's local IP and the network it's connected to.
  displayConnectInfo();
}

void ESP8266WifiConnection::initializeESP8266() {
  // esp8266.begin() verifies that the ESP8266 is operational
  // and sets it up for the rest of the sketch.
  // It returns either true or false -- indicating whether
  // communication was successul or not.
  int test = esp8266.begin();
  if (test != true)
  {
    Serial.println(F("Error talking to ESP8266."));
    ESP8266WifiConnection::error(test);
  }
  Serial.println(F("ESP8266 Shield Present"));
}

void ESP8266WifiConnection::connectESP8266() {
  // The ESP8266 can be set to one of three modes:
  //  1 - ESP8266_MODE_STA - Station only
  //  2 - ESP8266_MODE_AP - Access point only
  //  3 - ESP8266_MODE_STAAP - Station/AP combo
  // Use esp8266.getMode() to check which mode it's in:
  int retVal = esp8266.getMode();
  if (retVal != ESP8266_MODE_STA)
  { // If it's not in station mode.
    // Use esp8266.setMode([mode]) to set it to a specified
    // mode.
    retVal = esp8266.setMode(ESP8266_MODE_STA);
    if (retVal < 0)
    {
      Serial.println(F("Error setting mode."));
      ESP8266WifiConnection::error(retVal);
    }
  }
  Serial.println(F("Mode set to station"));

  // 1 indicates device is already connected. 0 indicates disconnected. 
  // Negative values are communication errors
  retVal = esp8266.status();
  if (retVal <= 0)
  {
    Serial.print(F("Connecting to "));
    Serial.println(mySSID);
    
    // On success connect() returns a value >0
    // On fail, the function will either return:
    //  -1: TIMEOUT - The library has a set 30s timeout
    //  -3: FAIL - Couldn't connect to network.
    retVal = esp8266.connect(mySSID.c_str(), myPSK.c_str());
    
    if (retVal < 0)
    {
      Serial.println(F("Error connecting"));
      ESP8266WifiConnection::error(retVal);
    }
  }
}


void ESP8266WifiConnection::displayConnectInfo() {
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);
  // esp8266.getAP() can be used to check which AP the
  // ESP8266 is connected to. It returns an error code.
  // The connected AP is returned by reference as a parameter.
  int retVal = esp8266.getAP(connectedSSID);
  if (retVal > 0)
  {
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }

  // esp8266.localIP returns an IPAddress variable with the ESP8266's current local IP address.
  IPAddress myIP = esp8266.localIP();
  Serial.print(F("My IP: ")); Serial.println(myIP);
}

void ESP8266WifiConnection::error(int error) {
  Serial.print(F("Error: ")); Serial.println(error);
  //Serial.println(F("Looping forever."));
  //for (;;)
  //  ;
}

// serialTrigger prints a message, then waits for something
// to come in from the serial port.
void ESP8266WifiConnection::serialTrigger(String message) {
  Serial.println();
  Serial.println(message);
  Serial.println();
  while (!Serial.available())
    ;
  while (Serial.available())
    Serial.read();
}
