#ifndef MY_TEMP_H
#define MY_TEMP_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DallasTemperature.h>

class Temperature {
  private:
    float firstC = 0;
    float firstF = 0;
    float secondC = 0;
    float secondF = 0; 
    int count = 0;
    bool reprint = false;
    LiquidCrystal& lcd;
    DallasTemperature& sensors;

  public:
    Temperature(LiquidCrystal& lcd, DallasTemperature& sensors);
    void temperatureDisplay();
    void setFirstTemp(); 
    void setSecondTemp();
    void updateTemperature();
    void printToLCD();
};

#endif
