#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include "Temperature.h"

// constant for temperature

int outlet = 13;


// initialize libraries
#define ONE_WIRE_BUS 26
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);



const int rs = 19, en = 23, d4 = 27, d5 = 16, d6 = 17, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


Temperature temp(lcd, sensors);


//#include <stdlib.h> // for malloc and free
//void* operator new(size_t size) { return malloc(size); } 
//void operator delete(void* ptr) { free(ptr); }

// const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;





// temperature vars
//float firstC = 0;
//float firstF = 0;
//float secondC = 0;
//float secondF = 0; 
//int count = 0;
//bool reprint = false;

// ph vars
//const int analogInPin = 36;
//int sensorValue = 0;
//unsigned long int avgValue;
//float b;
//int buf[10], temp;

//outlet vars
float temporary = 74.00;
//Temperature* temp;



void setup(void) {
  Serial.begin(115200);
  sensors.begin();

  lcd.begin(16, 2);
  lcd.display();

  pinMode(13, OUTPUT);
  
//  temp = new Temperature();
}

void loop(void) {
  // Display and update temperature as needed
  temp.temperatureDisplay();
}

//void temperatureDisplay() {
//  count++;
//  if (count == 1 || reprint) {
//    printToLCD();
//  }
//  setFirstTemp();
//  delay(1000);
//  setSecondTemp();
//  updateTemperature();
//}
//
//void printToLCD() {
//  lcd.print("F: " + String(firstF));
//  lcd.setCursor(0, 1);
//  lcd.print("C: " + String(firstC));
//}
//
//
//void setFirstTemp() {
//  sensors.requestTemperatures();
//  firstC = sensors.getTempCByIndex(0);
//  firstF = sensors.toFahrenheit(firstC);
//}
//
//void setSecondTemp() {
//  sensors.requestTemperatures();
//  secondC = sensors.getTempCByIndex(0);
//  secondF = sensors.toFahrenheit(secondC);
//}
//
//void updateTemperature() {
//  if (firstF != secondF) {
//    lcd.clear();
//    reprint = true;
//  } else {
//    reprint = false;
//  }
//}

//void ATORelay() {
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
