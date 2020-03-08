#include "Temperature.h"
//#include <LiquidCrystal.h>

// constructor
Temperature::Temperature(LiquidCrystal& lcd, DallasTemperature& sensors){
  this->lcd = lcd;
  this->sensors = sensors;
}

void Temperature::temperatureDisplay() {
  count++;
  if (count == 1 || reprint) {
    Temperature::printToLCD();
  }
  Temperature::setFirstTemp();
  delay(1000);
  setSecondTemp();
  updateTemperature();
}

void Temperature::printToLCD() {
  lcd.print("F: " + String(firstF));
  lcd.setCursor(0, 1);
  lcd.print("C: " + String(firstC));
}


void Temperature::setFirstTemp() {
  sensors.requestTemperatures();
  firstC = sensors.getTempCByIndex(0);
  firstF = sensors.toFahrenheit(firstC);
}

void Temperature::setSecondTemp() {
  sensors.requestTemperatures();
  secondC = sensors.getTempCByIndex(0);
  secondF = sensors.toFahrenheit(secondC);
}

void Temperature::updateTemperature() {
  if (firstF != secondF) {
    lcd.clear();
    reprint = true;
  } else {
    reprint = false;
  }
}
