#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); 
#define SERVOMIN 150
#define SERVOMAX 600

uint8_t servonum = 0;

const char* WIFI_SSID = "Khushi wifi_4G";
const char* WIFI_PASS = "0117678100674";

ESP8266WebServer server(80);

void handleRecognizedText() {
  String receivedText = server.arg("recognized_text");
  
  Serial.print("Received Text: ");
  Serial.println(receivedText);

  for (int i = 0; i < receivedText.length(); i++) {
    char word = receivedText.charAt(i);
    Serial.println(word);
    if (word == 'A' || word == 'a') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMIN);
    } else if (word == 'B' || word == 'b') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMIN);
    } else if (word == 'C' || word == 'c') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMIN);
    }
    // Continue with the rest of the alphabet
      else if (word == 'D' || word == 'd') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMIN);
    } else if (word == 'E' || word == 'e') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMIN);
    }
    // Continue with the rest of the letters
      else if (word == 'F' || word == 'f') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMIN);
    } else if (word == 'G' || word == 'g') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMIN);
    }
    // Add more cases for other letters
    // H to Z
      else if (word == 'H' || word == 'h') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMIN);
    } else if (word == 'I' || word == 'i') {
      pwm.setPWM(0, 0, SERVOMIN);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMIN);
    }
    // Add cases for J to Z
      else if (word == 'J' || word == 'j') {
      pwm.setPWM(0, 0, SERVOMIN);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for J
    } else if (word == 'K' || word == 'k') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for K
    }
    // Continue with the rest of the letters
    // L to Z
      else if (word == 'L' || word == 'l') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for L
    } else if (word == 'M' || word == 'm') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for M
    } else if (word == 'N' || word == 'n') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for N
    } else if (word == 'O' || word == 'o') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for O
    } else if (word == 'P' || word == 'p') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for P
    } else if (word == 'Q' || word == 'q') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for Q
    } else if (word == 'R' || word == 'r') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for R
    } else if (word == 'S' || word == 's') {
      pwm.setPWM(0, 0, SERVOMIN);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for S
    } else if (word == 'T' || word == 't') {
      pwm.setPWM(0, 0, SERVOMIN);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMIN);
      // Set servo positions for T
    } else if (word == 'U' || word == 'u') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMAX);
      // Set servo positions for U
    } else if (word == 'V' || word == 'v') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMAX);
      // Set servo positions for V
    } else if (word == 'W' || word == 'w') {
      pwm.setPWM(0, 0, SERVOMIN);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMAX);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMIN);
      pwm.setPWM(5, 0, SERVOMAX);
      // Set servo positions for W
    } else if (word == 'X' || word == 'x') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMIN);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMAX);
      // Set servo positions for X
    } else if (word == 'Y' || word == 'y') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMAX);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMAX);
      // Set servo positions for Y
    } else if (word == 'Z' || word == 'z') {
      pwm.setPWM(0, 0, SERVOMAX);
      pwm.setPWM(1, 0, SERVOMIN);
      pwm.setPWM(2, 0, SERVOMIN);
      pwm.setPWM(3, 0, SERVOMAX);
      pwm.setPWM(4, 0, SERVOMAX);
      pwm.setPWM(5, 0, SERVOMAX);
    }
    delay(5000);
}
}

  // Here you can add your logic to process the received text
  
  // server.send(200, "text/plain", "Text received successfully!");


void setup() {
  Serial.begin(115200);

  pwm.begin();
  pwm.setPWMFreq(60);

  // Connect to WiFi
  // WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("  /recognized_text");

  // Setup server endpoints
  server.on("/recognized_text", handleRecognizedText);

  // Start server
  server.begin();
  // Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
