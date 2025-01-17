#include "wifiUpdateParameters.h"
#include <WiFi.h>
#include <WebServer.h>
#include "variablesAndParameters.h"
#include "wifi_cred.h"


// Set up a web server on port 80
WebServer server(80);

// Handler to read constant value
void handleRead() {
   String message = "{";
   message += "\"slider1\": " + String(KpA) + ",";
   message += "\"slider2\": " + String(KdA) + ",";
   message += "\"slider3\": " + String(KpA);
   message += "}";
  server.send(200, "text/plain", message);
}

// Handler to write mutable value
void handleWrite() {
  if (server.hasArg("slider1")) {
    KpA = server.arg("slider1").toInt();
    server.send(200, "text/plain", "Mutable Value Set to: " + String(KpA));
  }
  else if (server.hasArg("slider2")) {
    KdA = server.arg("slider2").toInt();
    server.send(200, "text/plain", "Mutable Value Set to: " + String(KdA));
  } else if (server.hasArg("slider3")) {
    KiA = server.arg("slider3").toInt();
    server.send(200, "text/plain", "Mutable Value Set to: " + String(KiA));
  } else {
    server.send(400, "text/plain", "Missing 'value' parameter");
  }
}

void wifiSetup() {
  // Initialize serial monitor and Wi-Fi connection
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  // Wait until connected to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Define routes and handlers for HTTP requests
  server.on("/read", handleRead);   // Endpoint to read constant value
  server.on("/write", handleWrite); // Endpoint to write mutable value

  // Start the server
  server.begin();
}

void wifiLoop() {
  // Handle incoming client requests
  server.handleClient();
}
