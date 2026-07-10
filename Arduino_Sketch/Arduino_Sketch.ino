#include <Servo.h>

const int LED_PINs[] = {50, 51, 52, 53};
Servo myServo;

String input = "";

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(LED_PINs[i], OUTPUT);
    digitalWrite(LED_PINs[i], LOW);
  }

  myServo.attach(22);        // Change to your servo pin if different
  myServo.write(90);        // Start at middle position

  Serial.begin(9600);
  Serial.println("Ready.");
  Serial.println("Format: <servo> <leds>");
  Serial.println("Examples:");
  Serial.println("  512 5     → servo 512, LEDs binary 0101");
  Serial.println("  0 15      → servo 0,   all LEDs on");
  Serial.println("  1023 0    → servo 1023, LEDs off");
  Serial.println("  300 0xA   → servo 300, LEDs 1010");
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();

    if (c == '\n' || c == '\r') {
      input.trim();
      
      if (input.length() > 0) {
        parseCommand(input);
      }
      
      input = "";
    } 
    else {
      input += c;
    }
  }
}

// ==================== COMMAND PARSER ====================
void parseCommand(String cmd) {
  int servoVal = 0;
  int ledMask = 0;

  // Split on space or comma
  int spaceIndex = cmd.indexOf(' ');
  int commaIndex = cmd.indexOf(',');

  if (spaceIndex > 0) {
    String s1 = cmd.substring(0, spaceIndex);
    String s2 = cmd.substring(spaceIndex + 1);
    
    servoVal = parseNumber(s1);
    ledMask  = parseNumber(s2);
  } 
  else if (commaIndex > 0) {
    String s1 = cmd.substring(0, commaIndex);
    String s2 = cmd.substring(commaIndex + 1);
    
    servoVal = parseNumber(s1);
    ledMask  = parseNumber(s2);
  } 
  else {
    // Single value → treat as servo only
    servoVal = parseNumber(cmd);
  }

  // Clamp values
  servoVal = constrain(servoVal, 0, 1023);
  ledMask  = constrain(ledMask, 0, 15);

  // Apply to hardware
  myServo.writeMicroseconds(map(servoVal, 0, 1023, 500, 2500)); // Better resolution than write()
  // myServo.write(map(servoVal, 0, 1023, 0, 180));   // Alternative if you prefer degrees

  for (int i = 0; i < 4; i++) {
    digitalWrite(LED_PINs[i], (ledMask >> i) & 0x01);
  }

  // Feedback
  Serial.print("Servo: ");
  Serial.print(servoVal);
  Serial.print(" | LEDs: 0x");
  Serial.print(ledMask, HEX);
  Serial.print(" (");
  Serial.print(ledMask, BIN);
  Serial.println(")");
}

// Helper to parse decimal or hex
int parseNumber(String str) {
  str.trim();
  if (str.startsWith("0x") || str.startsWith("0X")) {
    return strtol(str.c_str(), NULL, 16);
  } else if (str.startsWith("0b") || str.startsWith("0B")) {
    return strtol(str.c_str() + 2, NULL, 2);
  } else {
    char *endptr;
    long val = strtol(str.c_str(), &endptr, 16);
    if (*endptr == '\0') return val;           // was valid hex
    return strtol(str.c_str(), NULL, 10);      // try decimal
  }
}