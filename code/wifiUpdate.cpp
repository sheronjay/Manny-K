#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoOTA.h>
#include "variablesAndParameters.h"
#include "wifi_cred.h"
#include "wifiUpdate.h"

WebServer server(80); // Create a web server on port 80

// Global variable to store a mutable value
int mutableValue = 0;

// Handler to read constant value
void handleRead()
{
    String message = "{";
    message += "\"slider1\": " + String(KpA) + ",";
    message += "\"slider2\": " + String(KdA) + ",";
    message += "\"slider3\": " + String(KpA);
    message += "}";
    server.send(200, "text/plain", message);
}

// Handler to write mutable value
void handleWrite()
{
    if (server.hasArg("slider1"))
    {
        KpA = server.arg("slider1").toFloat();
        server.send(200, "text/plain", "Mutable Value Set to: " + String(KpA));
    }
    else if (server.hasArg("slider2"))
    {
        KdA = server.arg("slider2").toFloat();
        server.send(200, "text/plain", "Mutable Value Set to: " + String(KdA));
    }
    else if (server.hasArg("slider3"))
    {
        KiA = server.arg("slider3").toFloat();
        server.send(200, "text/plain", "Mutable Value Set to: " + String(KiA));
    }
    else
    {
        server.send(400, "text/plain", "Missing 'value' parameter");
    }
}

void handleSerial()
{
    static String serialOutput = ""; // Buffer to store serial output
    if (Serial.available())
    {
        char c = Serial.read();
        serialOutput += c; // Append serial data to buffer
        if (serialOutput.length() > 1024)
        {
            serialOutput.remove(0, serialOutput.length() - 1024); // Limit buffer size
        }
    }

    String html = "<html><body>";
    html += "<h1>ESP32 Serial Monitor</h1>";
    html += "<pre>" + serialOutput + "</pre>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

// Function to initialize Wi-Fi
void setupWiFi()
{
    Serial.print("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi. IP: " + WiFi.localIP().toString());
}

// Function to initialize OTA
void setupOTA()
{
    ArduinoOTA.setPassword("mannyk");

    ArduinoOTA.onStart([]()
                       {
        String type = ArduinoOTA.getCommand() == U_FLASH ? "sketch" : "filesystem";
        Serial.println("Start updating " + type); });

    ArduinoOTA.onEnd([]()
                     { Serial.println("\nUpdate Complete"); });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });

    ArduinoOTA.onError([](ota_error_t error)
                       {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Authentication Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

    ArduinoOTA.begin();
    Serial.println("OTA Ready");
}

void wifiSetup()
{
    setupWiFi(); // Initialize Wi-Fi
    setupOTA();  // Initialize OTA

    // Define HTTP server endpoints
    server.on("/read", handleRead);   // Endpoint to read the mutable value
    server.on("/write", handleWrite); // Endpoint to write a new value
    server.on("/", handleSerial);     // Define a route for the root URL

    // Start the HTTP server
    server.begin();
    Serial.println("HTTP server started");
}

void wifiLoop(void *parameter)
{
    for (;;)
    {                                         // Infinite loop
        ArduinoOTA.handle();                  // Handle OTA requests
        server.handleClient();                // Handle HTTP server requests
        vTaskDelay(100 / portTICK_PERIOD_MS); // Non-blocking delay
    }
}