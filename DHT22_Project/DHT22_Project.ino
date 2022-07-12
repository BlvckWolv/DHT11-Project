/*
 *  DHT-22 TEMPERATURE SENSOR
 *  DATE: 6/29/22
*/

// OLED Library by Adafruit
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED Size
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT-22 Library by Adafruit
#include "DHT.h"

// Set DHT-22 Pin 2
#define DHTPIN 2

// Sensor type
#define DHTTYPE DHT22

// Initialize DHT22 Sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  // Start Serial and set baud to 9600
  Serial.begin(9600);
  Serial.println(F("DHT22 Initialized"));


  // DHT begin
  dht.begin();  

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  
  // Clear OLED Buffer and wait 1 seconds
  delay(1000);
  display.setTextColor(WHITE, BLACK);
  display.clearDisplay();
  
  // Welcome message
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("Made with");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.println("love.");
  display.display();
  delay(3000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20,20);
  display.println("By Chris");
  display.display();
  delay(3000);
  display.clearDisplay();
  
}


void loop() {
  // Pause 2 seconds before loop starts
  delay(2000);

  int h = dht.readHumidity();

  int t = dht.readTemperature();

  int f = dht.readTemperature(true);

  // Error checking
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("DHT-22 Error"));
    return;
  }

  // Clear buffer before displaying
  display.clearDisplay();

  // Symbols
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(100,5);
  display.println("F");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(100,40);
  display.println("%");

  
 // Temperature Static
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.println("Temp: ");
  
  // Temperature Value
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(72, 5);
  display.println(f);

  // Humidity Static
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 40);
  display.println("Humi: ");

  // Humidity Value
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(72, 40);
  display.println(h);

  // Display all values above
  display.display();
  
}
