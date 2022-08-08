#ifndef MY_ESP8266WifiConnection_H
#define MY_ESP8266WifiConnection_H

#include <Arduino.h>

class ESP8266WifiConnection {
  private:
    String mySSID;
    String myPSK;

  public:
    ESP8266WifiConnection(String mySSID, String myPSK);
    void initializeESP8266();
    void connectESP8266(); 
    void displayConnectInfo();
    void error(int errorCode);
    void serialTrigger(String message);
};

#endif
