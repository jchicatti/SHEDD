#include <TFT.h>


#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

const int dipPins[3] = {2, 3, 4}; // DIP switch inputs
const int relayPin = 7;          // Output to relay
const int buttonPin = 8;         // Manual power-on button

unsigned long lastPingTime = 0;
unsigned long pingTimeout = 15000; // 15 seconds
unsigned long uptimeStart = 0;
bool isServerOn = false;
bool forceShutdown = false;

void setup() {
  Serial.begin(9600);
  rtc.begin();

  for (int i = 0; i < 3; i++) {
    pinMode(dipPins[i], INPUT_PULLUP);
  }

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  pinMode(buttonPin, INPUT_PULLUP);
  uptimeStart = millis();
}

int getMode() {
  return (!digitalRead(dipPins[2]) << 2) | (!digitalRead(dipPins[1]) << 1) | (!digitalRead(dipPins[0]));
}

void loop() {
  DateTime now = rtc.now();

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input == "PING") {
      lastPingTime = millis();
    }
  }

  unsigned long currentTime = millis();

  // Check for timeout (assume OS failure)
  if (currentTime - lastPingTime > pingTimeout && isServerOn && !forceShutdown) {
    digitalWrite(relayPin, HIGH);
    delay(1000);
    digitalWrite(relayPin, LOW);
    isServerOn = false;
    forceShutdown = false;
    uptimeStart = millis();  // reset uptime counter
  }

  // Manual power-on button
  if (digitalRead(buttonPin) == LOW && !isServerOn) {
    digitalWrite(relayPin, HIGH);
    delay(1000);
    digitalWrite(relayPin, LOW);
    isServerOn = true;
    uptimeStart = millis();
  }

  // Forced shutdown window (1 AM to 4 AM) and running > 20h
  if (isServerOn && (currentTime - uptimeStart > 72000000UL)) { // 20 hours in ms
    if (now.hour() >= 1 && now.hour() < 4) {
      digitalWrite(relayPin, HIGH); // force shutdown
      delay(1000);
      digitalWrite(relayPin, LOW);
      isServerOn = false;
      forceShutdown = true;
    }
  }

  // Reactivate at 4 AM
  if (!isServerOn && forceShutdown && now.hour() == 4 && now.minute() == 0) {
    digitalWrite(relayPin, HIGH);
    delay(1000);
    digitalWrite(relayPin, LOW);
    isServerOn = true;
    uptimeStart = millis();
    forceShutdown = false;
  }

  delay(500);
}
