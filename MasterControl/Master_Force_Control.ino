#include <HX711.h>
#include <SoftwareSerial.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;
HX711 scale;

// Create a SoftwareSerial instance for communication with the slave
SoftwareSerial slaveSerial(10, 11);  // RX, TX

// Variable to hold the command from Serial Monitor
String inputCommand = "";  

void setup() {
  // Start serial communication for the Serial Monitor (115200)
  Serial.begin(115200);
  // Start software serial for slave communication (9600)
  slaveSerial.begin(9600);

  // Initialize the load cell
  Serial.println("Initializing the scale...");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(-43748.73911);  // Calibration value
  scale.tare();  // Zero the scale
}

void loop() {
  // Check for input from the Serial Monitor
  if (Serial.available() > 0) {
    inputCommand = Serial.readStringUntil('\n');  // Read the command
    inputCommand.trim();  // Remove any extra spaces or newline characters

    // Send the command to the slave Arduino
    slaveSerial.println(inputCommand);  // Forward the input to the slave
    Serial.print("Command sent to slave: ");
    Serial.println(inputCommand);
  }

  // Optional: Read force data for debugging
  float forceValue = scale.get_units(10);
  Serial.print("Force: ");
  Serial.println(forceValue);

  // Optional delay to avoid flooding the Serial Monitor
  delay(500);
}
