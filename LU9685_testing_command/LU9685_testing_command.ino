#include "LU9685.h"

void setup() {
  Serial.begin(57600);
  LU9685_init(50, 0x80);
  Serial.println("Send commands in the format: sX = angle (0-180), where X is 1 to 20");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    // Check if the command matches the expected format
    if (command.startsWith("s") && command.indexOf(" = ") != -1) {
      int separatorIndex = command.indexOf(" = "); // Find the separator index
      String servoStr = command.substring(1, separatorIndex); // Extract servo number (after 's')
      String angleStr = command.substring(separatorIndex + 3); // Extract angle part

      int servoIndex = servoStr.toInt() - 1; // Convert to zero-based index
      int angle = angleStr.toInt();         // Convert angle to an integer

      if (servoStr.toInt() == 0){
        resetServos();
        Serial.println("Servo controller have been reset");
      }
      // Validate the servo index and angle range
      else if (servoIndex >= 0 && servoIndex < 20 && angle >= 0 && angle <= 180) {
        servoWrite(servoIndex, angle); // Set the servo position
        Serial.print("Servo");
        Serial.print(servoIndex + 1); // Convert back to one-based index for display
        Serial.print(" set to: ");
        Serial.println(angle);
      } else {
        Serial.println("Error: Invalid servo number (1-20) or angle (0-180).");
      }
    } else {
      Serial.println("Invalid command. Use format: sX = angle (X: 1-20, angle: 0-180)");
    }
  }
}
