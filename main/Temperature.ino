class Temperature {
  private:
    float firstC = 0;
    float firstF = 0;
    float secondC = 0;
    float secondF = 0; 
    int count = 0;
    bool reprint = false;

  public:
    void temperatureDisplay();
    void setFistTemp(); 
    void setSecondTemp();
    void updateTemperature();
}

// constructor
Temperature::Temperature() {
  
}

void Temperature::temperatureDisplay() {
  count++;
  if (count == 1 || reprint) {
    printToLCD();
  }
  setFirstTemp();
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
