
#include <RTClib.h>
#include <Wire.h>

RTC_DS3231 rtc;

const int relayPin = 8;
const int dipPins[3] = {2, 3, 4};  // DIP switch inputs
const int buttonPin = 7;           // Manual power button
const int debounceDelay = 50;

unsigned long lastPing = 0;
unsigned long uptime = 0;
bool serverRunning = true;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();

  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i = 0; i < 3; i++) pinMode(dipPins[i], INPUT_PULLUP);

  digitalWrite(relayPin, LOW);
}

void loop() {
  DateTime now = rtc.now();
  int hour = now.hour();
  int minute = now.minute();
  unsigned long currentMillis = millis();

  // Read DIP switch value
  int mode = 0;
  for (int i = 0; i < 3; i++) {
    if (!digitalRead(dipPins[i])) mode |= (1 << i); // Active low
  }

  // Mode selector
  switch (mode) {
    case 0: runNormal(now, currentMillis); break;
    case 1: alwaysOn(); break;
    case 2: energySaver(now); break;
    case 3: testRelaunch(); break;
    case 4: testRestart(); break;
    case 5: scheduledReset(now); break;
    default: idleMode(); break;
  }

  if (digitalRead(buttonPin) == LOW) {
    delay(debounceDelay);
    if (digitalRead(buttonPin) == LOW) {
      pressPowerButton();
    }
  }

  delay(1000);
}

void runNormal(DateTime now, unsigned long currentMillis) {
  // Simulate ping timeout
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    if (input == "PING") {
      lastPing = millis();
    }
  }

  if (millis() - lastPing > 15000) {
    if (serverRunning) {
      // No ping -> restart
      pressPowerButton();
      serverRunning = false;
    }
  } else {
    serverRunning = true;
  }

  // Timed restart between 1-4 AM if uptime > 20h
  uptime += 1000;
  if (uptime >= 72000000UL && hour >= 1 && hour < 4) {
    pressPowerButton(); // Turn off
    delay(5000);
    while (rtc.now().hour() < 4) {
      delay(60000); // Wait until 4 AM
    }
    pressPowerButton(); // Turn on
    uptime = 0;
  }
}

void pressPowerButton() {
  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(relayPin, LOW);
}

void alwaysOn() {
  // Do nothing, let PC manage everything
}

void energySaver(DateTime now) {
  if (now.hour() >= 1 && now.hour() < 4) {
    digitalWrite(relayPin, LOW); // Turn off
  } else {
    digitalWrite(relayPin, HIGH); // Turn on
  }
}

void testRelaunch() {
  // Simulate logical relaunch
  Serial.println("RELAUNCH");
}

void testRestart() {
  // Simulate hard restart
  pressPowerButton();
}

void scheduledReset(DateTime now) {
  if (now.hour() >= 1 && now.hour() < 4) {
    pressPowerButton(); // Turn off
    delay(5000);
    while (rtc.now().hour() < 4) {
      delay(60000);
    }
    pressPowerButton(); // Turn on
  }
}

void idleMode() {
  // Low power idle or debug
}
