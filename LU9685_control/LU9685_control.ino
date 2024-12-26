#include <Wire.h>

#define LU9685_ADDRESS 0x80 // Replace with your I2C address

void setup() {
  Wire.begin();               // Initialize I2C
  softReset();                // Perform a soft reset
  setPWMFrequency(50);        // Set frequency to 50 Hz for servos
  setServoAngle(0, 90);       // Set channel 0 to 90 degrees
}

void softReset() {
  Wire.beginTransmission(0x00); // All Call address
  Wire.write(0x06);             // Software reset command
  Wire.endTransmission();
}

void setPWMFrequency(int freq) {
  // Calculate prescale value (similar to PCA9685)
  uint8_t prescale = (25000000 / (4096 * freq)) - 1;
  Wire.beginTransmission(LU9685_ADDRESS);
  Wire.write(0xFE);       // PRE_SCALE register
  Wire.write(prescale);   // Write prescale value
  Wire.endTransmission();
}

void setServoAngle(uint8_t channel, int angle) {
  // Convert angle (0-180) to pulse width (0-4095)
  int pulse = map(angle, 0, 180, 0, 4095);
  uint8_t reg = 0x06 + 4 * channel; // Base address for channel 0
  
  Wire.beginTransmission(LU9685_ADDRESS);
  Wire.write(reg);        // Start register for the channel
  Wire.write(pulse & 0xFF); // Low byte
  Wire.write(pulse >> 8);   // High byte
  Wire.endTransmission();
}

void loop() {
  // Example: Sweep servo angles
  for (int angle = 0; angle <= 180; angle += 10) {
    setServoAngle(0, angle);
    delay(500);
  }
}

