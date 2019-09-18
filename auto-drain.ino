int water_sensor = 2;
int led = 13;
unsigned long uptime = 0;
unsigned long max_uptime = 160;
unsigned long cooldown = 160;

void setup() {
  pinMode(water_sensor, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.begin(57600);
}

void loop() {
  if (digitalRead(water_sensor) == LOW) {
    Serial.print("Water detected.");
    if (uptime < max_uptime) {
      // water was detected recently
      digitalWrite(led, HIGH);
      uptime++;
      Serial.print("Timeout in ");
      Serial.print(max_uptime - uptime + 1);
      Serial.print("\n");
      delay(1000);
    }
    else {
      // water is probably false positive
      Serial.print("Timeout exceeded. Probably false positive reading. Cooling down...");
      digitalWrite(led, LOW);
      for (unsigned long t = cooldown; t > 0; t--) {
        delay(1000);
        Serial.print(t);
        Serial.print("..");
      }
      Serial.print("\n");
      uptime = 0;
    }
  }
  else {
    Serial.print("Water NOT detected.\n");
    digitalWrite(led, LOW);
    uptime = 0;
  }
}
