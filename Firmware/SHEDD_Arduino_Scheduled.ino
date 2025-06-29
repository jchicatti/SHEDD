
#define RELAY_PIN 8
#define TIMEOUT_INTERVAL 10000  // 10 seconds
#define UPTIME_LIMIT 72000UL    // 20 hours in seconds

unsigned long lastPing = 0;
unsigned long lastMillis = 0;
unsigned long uptimeSeconds = 0;
bool serviceCrashed = false;
String incomingData = "";
int currentHour = 0;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Serial.begin(9600);
  lastPing = millis();
  lastMillis = millis();
}

void loop() {
  // Update uptime counter
  if (millis() - lastMillis >= 1000) {
    uptimeSeconds++;
    lastMillis += 1000;
  }

  // Read incoming serial data
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') {
      processPing(incomingData);
      incomingData = "";
    } else {
      incomingData += c;
    }
  }

  // Timeout watchdog
  if (millis() - lastPing > TIMEOUT_INTERVAL) {
    triggerPhysicalReset();
  }

  // Scheduled reset logic
  if (uptimeSeconds >= UPTIME_LIMIT && currentHour >= 1 && currentHour < 4) {
    triggerScheduledReset();
  }
}

void processPing(String data) {
  // Expected format: "PING|HH:MM"
  if (data.startsWith("PING")) {
    lastPing = millis();
    uptimeSeconds = 0; // Reset uptime on manual reboot or relaunch

    int sep = data.indexOf('|');
    if (sep > 0) {
      String timePart = data.substring(sep + 1);
      int colon = timePart.indexOf(':');
      if (colon > 0) {
        currentHour = timePart.substring(0, colon).toInt();
      }
    }
  }
}

void triggerPhysicalReset() {
  digitalWrite(RELAY_PIN, HIGH);
  delay(500);
  digitalWrite(RELAY_PIN, LOW);
  lastPing = millis();
  uptimeSeconds = 0;
}

void triggerScheduledReset() {
  digitalWrite(RELAY_PIN, HIGH);
  delay(500);
  digitalWrite(RELAY_PIN, LOW);
  lastPing = millis();
  uptimeSeconds = 0;
}
