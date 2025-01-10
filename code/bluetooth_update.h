#include <SoftwareSerial.h>
#include <Arduino.h>

// Define HC-05 TX and RX pins
SoftwareSerial bluetooth(10, 11); // RX, TX

// Variables to be updated
int var1 = 0;
float var2 = 0.0;
String var3 = "";

void parseData(String data)
{
  // Split the received data into name and value
  int delimiterIndex = data.indexOf(':');
  if (delimiterIndex == -1)
  {
    Serial.println("Invalid data format.");
    return; // Exit if no delimiter found
  }

  String varName = data.substring(0, delimiterIndex);
  String varValue = data.substring(delimiterIndex + 1);

  // Update variables based on the received name
  if (varName == "var1")
  {
    var1 = varValue.toInt();
  }
  else if (varName == "var2")
  {
    var2 = varValue.toFloat();
  }
  else if (varName == "var3")
  {
    var3 = varValue;
  }
  else
  {
    Serial.println("Unknown variable: " + varName);
  }
}

void setupBluetooth()
{
  // Initialize Serial for debugging
  Serial.begin(9600);

  // Initialize Bluetooth module communication
  bluetooth.begin(9600); // Default baud rate for HC-05
  Serial.println("Bluetooth module is ready...");
}

void loopBluetooth()
{
  if (bluetooth.available())
  {
    String receivedData = bluetooth.readStringUntil('\n'); // Read data until newline
    Serial.println("Received: " + receivedData);
    parseData(receivedData);
  }

  // Debug print variables
  Serial.print("var1: ");
  Serial.print(var1);
  Serial.print(", var2: ");
  Serial.print(var2);
  Serial.print(", var3: ");
  Serial.println(var3);

  delay(500); // Short delay for demonstration purposes
}
