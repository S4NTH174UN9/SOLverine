#ifndef LU9685_H
#define LU9685_H

#include <Wire.h>

#define DEFAULT_PWM_SPEED 50
#define DEFAULT_ADDRESS 0x80

uint8_t PWM_SPEED = DEFAULT_PWM_SPEED;
uint8_t ADDRESS = DEFAULT_ADDRESS;

// Function to write to a register
void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// Initialization function for LU9685
void LU9685_init(uint8_t SPEED = DEFAULT_PWM_SPEED, uint8_t address = DEFAULT_ADDRESS) {
  if (SPEED < 30 || SPEED > 400) {
    SPEED = DEFAULT_PWM_SPEED;  // Clamp SPEED to the default if out of range
  }
  if (address > 0x80) {
    address = DEFAULT_ADDRESS;  // Clamp address to default if out of range
  }

  PWM_SPEED = SPEED;
  ADDRESS = address;

  Wire.begin();
  // Set initial PWM speed and configuration
  writeRegister(0xFB, 0xFB);  //reset the controller
}

// Function to control a single servo
void servoWrite(uint8_t servo, uint8_t degree) {
  if (servo < 0 || servo > 20) {
    return;  // Invalid servo channel, do nothing
  }
  if (degree < 0 || degree > 180) {
    return;  // Invalid degree, do nothing
  }

  writeRegister(servo, degree);
}

// Function to control all servos
void allServo(char address, char *degrees, uint8_t length) {
  Wire.beginTransmission(address);
  Wire.write(0xFD);  // Command to write to all servos

  for (int i = 0; i < length; i++) {
    Wire.write(degrees[i]);
  }

  Wire.endTransmission();
}

// Function to directly control all servos with provided degrees
void DCAS(uint8_t d1 = 0, uint8_t d2 = 0, uint8_t d3 = 0, uint8_t d4 = 0, uint8_t d5 = 0, 
          uint8_t d6 = 0, uint8_t d7 = 0, uint8_t d8 = 0, uint8_t d9 = 0, uint8_t d10 = 0, 
          uint8_t d11 = 0, uint8_t d12 = 0, uint8_t d13 = 0, uint8_t d14 = 0, uint8_t d15 = 0, 
          uint8_t d16 = 0, uint8_t d17 = 0, uint8_t d18 = 0, uint8_t d19 = 0, uint8_t d20 = 0) {
  
          // Ensure values are between 0 and 180
          uint8_t degrees[20] = {d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20};
          for (int i = 0; i < 20; i++) {
            if (degrees[i] > 180) {
              degrees[i] = 180;
            }
          }

          Wire.beginTransmission(ADDRESS);
          Wire.write(0xFD);  // Command to write to all servos simultaneously

          // Write degrees for all 20 servos
          for (int i = 0; i < 20; i++) {
            Wire.write(degrees[i]);
          }

          Wire.endTransmission();
        }

void resetServos(){
  writeRegister(0xFB, 0xFB);
}

#endif
