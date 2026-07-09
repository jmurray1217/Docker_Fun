const int LED_PIN = LED_BUILTIN;

String input = "";

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);
  Serial.println("Ready. Send 'On' or 'Off'.");
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();

    // End of command
    if (c == '\n' || c == '\r') {
      input.trim();

      if (input.equalsIgnoreCase("On")) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED ON");
      }
      else if (input.equalsIgnoreCase("Off")) {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED OFF");
      }
      else if (input.length() > 0) {
        Serial.print("Unknown command: ");
        Serial.println(input);
      }

      input = "";
    }
    else {
      input += c;
    }
  }
}