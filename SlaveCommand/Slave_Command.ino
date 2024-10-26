#include <AccelStepper.h>

// Define pin connections for the stepper motor
const int dirPin = 8;   // Direction pin
const int stepPin = 9;  // Step pin

// Create an instance of the AccelStepper
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);

// Variable to hold the received command
String receivedCommand = "";

// Motor control variables
bool motorOn = false;   // Motor ON/OFF flag
float motorSpeed = 1000; // Default motor speed (steps per second)

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize the stepper motor
  myStepper.setMaxSpeed(6000);  // Set max speed (adjust as needed)
  myStepper.setAcceleration(1000);  // Set acceleration (adjust as needed)

  // Instructions for motor control
  Serial.println("Type 'ON' to start the motor, 'OFF' to stop the motor.");
  Serial.println("Type 'CW' for clockwise direction and 'CCW' for counterclockwise direction.");
  Serial.println("Type a speed value to set the motor speed.");
}

void loop() {
  // Check for serial input from the user
  if (Serial.available() > 0) {
    receivedCommand = Serial.readStringUntil('\n');  // Read input until newline
    receivedCommand.trim();
    receivedCommand.toUpperCase();  // Convert input to uppercase

    // Handle motor commands
    if (receivedCommand == "ON") {
      motorOn = true;
      myStepper.setSpeed(motorSpeed); // Set speed for continuous rotation
      Serial.println("Motor is ON.");
    } else if (receivedCommand == "OFF") {
      motorOn = false;
      myStepper.stop();  // Stop the motor
      Serial.println("Motor is OFF.");
    }
    // Handle speed input
    else if (receivedCommand.toFloat() > 0) {
      motorSpeed = receivedCommand.toFloat();
      if (motorOn) {
        myStepper.setSpeed(motorSpeed); // Update speed if motor is on
      }
      Serial.print("Motor speed set to: ");
      Serial.println(motorSpeed);
    }
    // Handle direction input
    else if (receivedCommand == "CW") {  // Clockwise
      myStepper.setSpeed(abs(motorSpeed)); // Ensure speed is positive for CW
      Serial.println("Direction set to clockwise.");
    } else if (receivedCommand == "CCW") {  // Counterclockwise
      myStepper.setSpeed(-abs(motorSpeed)); // Ensure speed is negative for CCW
      Serial.println("Direction set to counterclockwise.");
    } else {
      Serial.println("Invalid input. Enter 'ON', 'OFF', 'CW', or 'CCW'.");
    }
  }

  // Run the motor continuously if it is turned on
  if (motorOn) {
    myStepper.runSpeed();  // Runs the motor continuously at set speed
  }
}
