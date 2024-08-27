#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <WebServer.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

const char* ssid = "Khushi wifi_4G";
const char* password = "0117678100674";

WebServer server(80);
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define trigPin 2
#define echoPin 4
#define MAX_DISTANCE 200
#define HR_SENSOR_PIN 32

TinyGPSPlus gps;
SoftwareSerial GPS_SERIAL(16, 17); // RX, TX

Adafruit_BMP085 bmp;

String sensorData;
bool alertSent = false;

// Dummy latitude and longitude
float dummyLatitude = 28.6110;
float dummyLongitude = 77.0379;
int pulseSensorValue;
const int pulseSensorPin = 32;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  if (!bmp.begin()) {
    Serial.println("Could not find BMP085 sensor, check wiring!");
    while (1) {}
  }

  GPS_SERIAL.begin(9600);

  server.on("/", HTTP_GET, handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  while (GPS_SERIAL.available() > 0) {
    if (gps.encode(GPS_SERIAL.read())) {
      
    }
  }

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float distance = getDistance();
  float hr = readHeartRate();
  float latitude = gps.location.isValid() ? gps.location.lat() : dummyLatitude;
  float longitude = gps.location.isValid() ? gps.location.lng() : dummyLongitude;
  float pressure = bmp.readPressure();

  StaticJsonDocument<256> doc;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["distance"] = distance;
  doc["hr"] = hr;
  doc["latitude"] = latitude;
  doc["longitude"] = longitude;
  doc["pressure"] = pressure;

  sensorData = "";
  serializeJson(doc, sensorData);

  if (pressure > 101500 && !alertSent) {
    sendAlert();
    alertSent = true;
  }

  delay(1000);
}

void handleRoot() {
  String data = "<!DOCTYPE html>";
  data += "<html><head>";
  data += "<style>";
  data += "body { background: linear-gradient(to bottom right, black, red); }";
  data += "div.sensor { width: 45%; margin: 10px; padding: 10px; float: left; border: 1px solid black; ";
  data += "background: linear-gradient(to bottom right, blue, black); color: white; text-align: center; }";
  data += "p.value { font-size: 20px; font-weight: bold; margin: 0; }";
  data += ".map { height: 400px; }";
  data += "</style></head><body>";
  data += "<h1 style=\"color: white;\">Real-Time Sensor Data</h1>";

  DynamicJsonDocument jsonDoc(256);
  deserializeJson(jsonDoc, sensorData);
  
  data += "<div class=\"sensor\"><p class=\"value\">Temperature</p>";
  data += "<p class=\"value\">" + String(jsonDoc["temperature"].as<float>()) + " °C</p></div>";

  data += "<div class=\"sensor\"><p class=\"value\">Humidity</p>";
  data += "<p class=\"value\">" + String(jsonDoc["humidity"].as<float>()) + " %</p></div>";

  data += "<div class=\"sensor\"><p class=\"value\">Distance</p>";
  data += "<p class=\"value\">" + String(jsonDoc["distance"].as<float>()) + " cm</p></div>";

  data += "<div class=\"sensor\"><p class=\"value\">Heart Rate</p>";
  data += "<p class=\"value\">" + String(jsonDoc["hr"].as<float>()) + " bpm</p></div>";

  data += "<div class=\"map\">";
  data += "<iframe id=\"mapFrame\" src=\"https://www.google.com/maps/embed?pb=!1m14!1m12!1m3!1d48970.57525928261!2d" + String(jsonDoc["longitude"].as<float>()) + "!3d" + String(jsonDoc["latitude"].as<float>()) + "!3m2!1i1024!2i768!4f13.1!5e0!3m2!1sen!2sus!4v1648050052447!5m2!1sen!2sus\" width=\"100%\" height=\"100%\" style=\"border:0;\" allowfullscreen=\"\" loading=\"lazy\" referrerpolicy=\"no-referrer-when-downgrade\"></iframe>";
  data += "</div>";

  // Button to trigger Python code
  data += "<form action=\"/triggerPython\" method=\"get\">";
  data += "<input type=\"submit\" value=\"Trigger Python Code\">";
  data += "</form>";

  data += "<script>";
  data += "function updateMap() {";
  data += "var frame = document.getElementById('mapFrame');";
  data += "frame.src = 'https://www.google.com/maps/embed?pb=!1m14!1m12!1m3!1d48970.57525928261!2d' + " + String(jsonDoc["longitude"].as<float>()) + " + '!3d' + " + String(jsonDoc["latitude"].as<float>()) + " + '!3m2!1i1024!2i768!4f13.1!5e0!3m2!1sen!2sus!4v1648050052447!5m2!1sen!2sus';";
  data += "}";
  data += "</script>";

  data += "</body></html>";

  server.send(200, "text/html", data);
}

void sendAlert() {
  Serial.println("Alert: Pressure threshold exceeded!");
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

float readHeartRate() {
  pulseSensorValue = analogRead(HR_SENSOR_PIN);
  // Serial.print("Pulse Sensor Value: ");
  // Serial.println(pulseSensorValue);
  return pulseSensorValue; // Return dummy value
}
