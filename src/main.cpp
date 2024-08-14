#include <Arduino.h>
#include <WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Wi-Fi credentials
const char* ssid = "PotatoChipishipss";
const char* password = "paba@1234";

// ThingSpeak credentials
unsigned long myChannelNumber = 2;
const char* myWriteAPIKey = "N16XH9DHRUH89TL2";

// Thermistor and LED pins
const int thermistorPin = 34;
const int yellowLEDPin = 5;
const int redLEDPin = 18;

// Thermistor constants
const float seriesResistor = 10000;
const float nominalResistance = 10000;
const float nominalTemperature = 25.0;
const float bCoefficient = 3950;
const int adcMaxValue = 4095;

// Temperature thresholds
const float minThreshold = 20.0;
const float maxThreshold = 60.0;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(yellowLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ThingSpeak.begin(client);
}

void loop() {
  Serial.print("Ambient Temp: ");
  // Serial.print(ambientTemp);
  Serial.print(12);
  Serial.print(" °C, Humidity: ");
  // Serial.print(humidity);
  Serial.print(23);
  Serial.print(" %, Process Temp: ");
  // Serial.print(processTemp);
  Serial.print(34);
  Serial.println(" °C");

  // Upload data to ThingSpeak
  ThingSpeak.setField(1, 22);
  ThingSpeak.setField(2, 32);
  ThingSpeak.setField(3, 55);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Data uploaded to ThingSpeak successfully");
  } else {
    Serial.println("Failed to upload data to ThingSpeak");
  }

  // Wait for 60 seconds (60000 ms) before sending the next data
  delay(3000);
}
