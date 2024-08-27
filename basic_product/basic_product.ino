#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// WiFi credentials
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// Ultrasonic sensor pins
const int trigPin = 13;
const int echoPin = 12;

// BMP sensor
Adafruit_BMP280 bmp;

// Create a WebServer object
WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print ESP32's IP address
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize BMP sensor
  if (!bmp.begin()) {
    Serial.println("Could not find BMP280 sensor, check wiring!");
    while (1);
  }
  Serial.println("BMP280 sensor found");

  // Initialize ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Route for root / web page
  server.on("/", HTTP_GET, handleRoot);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();

  // Read ultrasonic sensor data
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Read BMP sensor data
  float pressure = bmp.readPressure();

  // Check for alerts
  if (distance < 5) {
    sendAlert("Ultrasonic sensor distance is less than 5cm!");
  }
  if (pressure > 10) {
    sendAlert("BMP sensor detected high pressure!");
  }

  delay(5000); // Adjust delay as needed
}

// Handler for the root page
void handleRoot() {
  server.send(200, "text/plain", "ESP32 IP Address: " + WiFi.localIP().toString());
}

void sendAlert(String message) {
  // This function can be implemented to send alerts to a server or perform any other action
  // For simplicity, I'm just printing the message to the serial monitor
  Serial.println("Alert: " + message);
}
