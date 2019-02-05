#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
  Adafruit_BME280 bme; // I2C

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
  #define OLED_RESET 0  // GPIO0
  Adafruit_SSD1306 OLED(OLED_RESET);

//Sets up the BME280 runs a basic test
void setupBME()  {
    Serial.println(F("BME280 test"));
    bool status;
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    Serial.println(F("BME280 ok"));
}

//Sets up the OLED runs a basic test
void setupOLED()  {
  Serial.println(F("OLed test"));
  bool status;
  status = OLED.begin();
  if (!status) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }
  OLED.clearDisplay();
  OLED.setTextWrap(false);
  OLED.setTextSize(5);
  OLED.setTextColor(1);
  OLED.setCursor(0,0);
  OLED.println("Welcome");
  OLED.display(); //output 'display buffer' to screen  
  OLED.startscrollleft(0x00, 0x0F); //make display scroll 
  delay(1000);
  Serial.println(F("OLed ok"));
}


void OLEDputStringinbuffer(String text,int x, int y) {
  OLED.setTextWrap(false);
  OLED.setTextSize(1);
  OLED.setTextColor(1);
  OLED.setCursor(x,y);
  OLED.print(text);
}

String pressuretext;
String humiditytext;
String temptext;
void readBME280() {
  float temp = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure();
  pressure = pressure / 100.0F;
  pressuretext = String(pressure) + " hPa";
  humiditytext = String(humidity) + " %";
  temptext = String(temp) + " °C";
  Serial.println(temptext);
  Serial.println(humiditytext);
  Serial.println(pressuretext);
}

void setup() {
    Serial.begin(9600);
    setupBME();
    setupOLED();

}

void loop() {
  readBME280();
  OLED.clearDisplay();
  OLED.stopscroll();
  OLED.drawRect(0,0,127,31,1);
  OLEDputStringinbuffer(String(temptext),2,2);
  OLEDputStringinbuffer(String(humiditytext),2,11);
  OLEDputStringinbuffer(String(pressuretext),2,21);
  OLED.display();

  delay(1000);
}