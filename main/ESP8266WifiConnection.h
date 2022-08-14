#ifndef MY_ESP8266WifiConnection_H
#define MY_ESP8266WifiConnection_H

#include <Arduino.h>

class ESP8266WifiConnection {
  private:
    String ssid;
    String password;

    void error(int errorCode);
    void serialTrigger(String message);

  public:
    ESP8266WifiConnection(String ssid, String password);
    void initializeESP8266();
    void connectESP8266(); 
    void displayConnectInfo();
};

#endif
