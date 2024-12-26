#include <Wire.h>

void setup() {
  Serial.begin(57600);
  Wire.begin();
  Serial.println("Scanning for I2C devices...");
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at: 0x");
      Serial.println(address, HEX);
    }
  }
}

void loop() {}
