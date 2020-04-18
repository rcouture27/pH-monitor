#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include "Temperature.h"

// ph vars
//const int analogInPin = 36;
//int sensorValue = 0;
//unsigned long int avgValue;
//float b;
//int buf[10], temp;

// initialize libraries
#define ONE_WIRE_BUS 26
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
const int rs = 19, en = 23, d4 = 27, d5 = 16, d6 = 17, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Temperature temp(&lcd, &sensors);

void setup(void) {
  Serial.begin(115200);
  sensors.begin();

  // configure lcd
  lcd.begin(16, 2);
  lcd.display();
}

void loop(void) {
  // Display and update temperature as needed
  temp.temperatureDisplay();
}

//void ATORelay() {
//    put in setup 'pinMode'
//    pinMode(13, OUTPUT);

//    int outlet = 13;
//    if (secondF <= 73){
//      digitalWrite(outlet, HIGH);
//    } else {
//      digitalWrite(outlet, LOW);
//    }
//}

//void phAndRoomTempReading() {
//  // read the input on analog pin 0:
//  int sensorValue = analogRead(36);
//  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
////  float voltage = sensorValue * (5.0 / 1023.0);
////  float voltage = (float) sensorValue / (4096 * 3.3);
//  // print out the value you read:
//  float voltage = (float) sensorValue * (3.3 / 4095);
//  Serial.println(sensorValue);
//  delay(300);
//}
