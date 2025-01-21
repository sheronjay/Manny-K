#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoOTA.h>
#include "wifi_cred.h"
#include "wifiUpdate.h"

WebServer server(80); // Create a web server on port 80

// Global variable to store a mutable value
int mutableValue = 0;

// Function to handle the "/read" endpoint
void handleRead()
{
    server.send(200, "text/plain", String(mutableValue));
}

// Function to handle the "/write" endpoint
void handleWrite()
{
    if (server.hasArg("value"))
    {
        mutableValue = server.arg("value").toInt();
        server.send(200, "text/plain", "Value updated to: " + String(mutableValue));
    }
    else
    {
        server.send(400, "text/plain", "Missing 'value' parameter");
    }
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
    ArduinoOTA.setPassword("ass");

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
    Serial.begin(115200);

    setupWiFi(); // Initialize Wi-Fi
    setupOTA();  // Initialize OTA

    // Define HTTP server endpoints
    server.on("/read", handleRead);   // Endpoint to read the mutable value
    server.on("/write", handleWrite); // Endpoint to write a new value

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