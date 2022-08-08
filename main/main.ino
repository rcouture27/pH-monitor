#include <SparkFunESP8266WiFi.h>
#include <SparkFunESP8266Client.h>
#include <SparkFunESP8266Server.h>


//#include <ArduinoWiFiServer.h>
//#include <BearSSLHelpers.h>
//#include <CertStoreBearSSL.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266WiFiAP.h>
//#include <ESP8266WiFiGeneric.h>
//#include <ESP8266WiFiGratuitous.h>
//#include <ESP8266WiFiMulti.h>
//#include <ESP8266WiFiScan.h>
//#include <ESP8266WiFiSTA.h>
//#include <ESP8266WiFiType.h>

//#include <WiFiClient.h>
//#include <WiFiClientSecure.h>
//#include <WiFiClientSecureBearSSL.h>
////#include <WiFiServer.h>
//#include <WiFiServerSecure.h>
//#include <WiFiServerSecureBearSSL.h>
//#include <WiFiUdp.h>




//#include <LiquidCrystal.h>
//#include "SSD1306Wire.h" 

#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#include "Temperature.h"
#include "ESP8266WifiConnection.h"


#define rx 9                                         //define what pin rx is going to be
#define tx 8                                         //define what pin tx is going to be

int count = 0;

const int buttonPin = 12;
int buttonState = 0;                                  // variable for reading the pushbutton status

/** pH variables */
String inputstring = "";                              // a string to hold incoming data from the PC
String sensorstring = "";                             // a string to hold the data from the Atlas Scientific product
boolean input_string_complete = false;                // have we received all the data from the PC
boolean sensor_string_complete = false;               // have we received all the data from the Atlas Scientific product
float pH; 

/** http vars */
int    HTTP_PORT   = 3000;
String HTTP_METHOD = "GET";
char   HOST_NAME[] = "71.232.236.213"; // hostname of web server:
String PATH_NAME   = "/phs";

/** wifi credentials */
const char mySSID[] = "TP-Link-columbus";
const char myPSK[] = "32-colubus";

//SSD1306Wire display(0x3c, SDA, SCL);                  // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h

/** initialize libraries */
#define ONE_WIRE_BUS 26
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SoftwareSerial myserial(rx, tx);
//HTTPClient http;
//WiFiClient client;
//#include <SparkFunESP8266WiFi.h> // Include the ESP8266 AT library

//const int rs = 19, en = 23, d4 = 27, d5 = 16, d6 = 17, d7 = 25;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//Temperature temp(&lcd, &sensors);



void setup(void) {
  myserial.begin(9600);
  Serial.begin(9600);
  sensors.begin();
  
  // connect to wifi network
  ESP8266WifiConnection wifi("TP-Link-columbus", "32-columbus");

  // configure button
  pinMode(buttonPin, INPUT_PULLUP);



  // configure lcd
//  lcd.begin(16, 2);
//  lcd.display();

  /** configure ph */
  inputstring.reserve(10);                            //set aside some bytes for receiving data from the PC
  sensorstring.reserve(30);                           //set aside some bytes for receiving data from Atlas Scientific product

  testRequest();
}

void loop(void) {
//  temp.temperatureDisplay();                          //  Display and update temperature as needed

  //readPh();
  
/** configure wifiscan */
//  WiFi.mode(WIFI_STA);
//  WiFi.disconnect();

//  wifiScan();
  
  delay(100);

/** configure display */
//  display.init();
//  display.flipScreenVertically();
//  display.setFont(ArialMT_Plain_10);
}

void serialEvent() {                                  // if the hardware serial port_0 receives a char
  inputstring = Serial.readStringUntil(13);           // read the string until we see a <CR>
  input_string_complete = true;                       // set the flag used to tell if we have received a completed string from the PC
}

void readPh() {
  if (input_string_complete == true) {                //if a string from the PC has been received in its entirety
    myserial.print(inputstring);                      //send that string to the Atlas Scientific product
    myserial.print('\r');                             //add a <CR> to the end of the string
    inputstring = "";                                 //clear the string
    input_string_complete = false;                    //reset the flag used to tell if we have received a completed string from the PC
  }

  if (myserial.available() > 0) {                     //if we see that the Atlas Scientific product has sent a character
    char inchar = (char)myserial.read();              //get the char we just received
    sensorstring += inchar;                           //add the char to the var called sensorstring
    if (inchar == '\r') {                             //if the incoming character is a <CR>
      sensor_string_complete = true;                  //set the flag
    }
  }

  if (sensor_string_complete == true) {               //if a string from the Atlas Scientific product has been received in its entirety
    Serial.println(sensorstring + " testing");        //send that string to the PC's serial monitor
    /*                                                //uncomment this section to see how to convert the pH reading from a string to a float 
    if (isdigit(sensorstring[0])) {                   //if the first character in the string is a digit
      pH = sensorstring.toFloat();                    //convert the string to a floating point number so it can be evaluated by the Arduino
      if (pH >= 7.0) {                                //if the pH is greater than or equal to 7.0
        Serial.println("high");                       //print "high" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
      if (pH <= 6.999) {                              //if the pH is less than or equal to 6.999
        Serial.println("low");                        //print "low" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
    }
    */
    sensorstring = "";                                //clear the string
    sensor_string_complete = false;                   //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
  }
}

void testRequest() {
//  http.begin(client, "http://jsonplaceholder.typicode.com/users/1");
//  int httpCode = http.GET();
//  String payload = http.getString();
//  Serial.println(payload);
//  http.end();
}




/************************************************** OTHER **************************************************/


//void loop(void) {
//  buttonState = digitalRead(buttonPin);
//
//  readPh();
//  //temp.temperatureDisplay();                          // Display and update temperature as needed
//
//  //display.clear();
//  
//  if (buttonState == LOW) {
//      // pressed                                 
////      wifiScan();       
//  } else {
//    // Not pressed
//  }
//}


//void wifiScan() {
//   Serial.println("scan start");
//
//    int n = WiFi.scanNetworks();                      // number of networks found
//    Serial.println("scan done");
//    if (n == 0) {
//        Serial.println("no networks found");
//  } else {
//        Serial.print(n);
//        Serial.println(" networks found");
//        int x = 0, y = 15;
//        for (int i = 0; i < n; ++i) {                 // Print SSID and RSSI for each network found   
//            if (i == 0) {
//              display.drawString(x, 0, WiFi.SSID(i));
//            } else if (i == 1) {
//              display.drawString(x, 15, WiFi.SSID(i));
//            } else if (i == 2) {
//              display.drawString(x, 30, WiFi.SSID(i));
//            }
//            display.display();   
//         
//            Serial.print(i + 1);
//            Serial.print(": ");
//
//            Serial.print(WiFi.SSID(i));
//            Serial.print(" (");
//            Serial.print(WiFi.RSSI(i));
//            Serial.print(")");
//            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"Open":"Secure");
//            delay(10);
//        }
//    }
//    Serial.println("");
//
//    // Wait a bit before scanning again
//    delay(5000);
//} 




//void drawFontFaceDemo() {
//    // Font Demo1
//    // create more fonts at http://oleddisplay.squix.ch/
//    display.setTextAlignment(TEXT_ALIGN_LEFT);
//    display.setFont(ArialMT_Plain_10);
//    display.drawString(0, 0, "Hello world");
//    display.setFont(ArialMT_Plain_16);
//    display.drawString(10, 10, "Hello world");
//    display.setFont(ArialMT_Plain_24);
//    display.drawString(0, 40, "Hello world");
//}

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
