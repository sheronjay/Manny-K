#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoWebsockets.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include "wifi_cred.h"
#include "variablesAndParameters.h"

using namespace websockets;

WebsocketsServer webSocket;
WebsocketsClient client;

bool upload = false;

// Function to send messages to Serial and WebSocket
void printSerialAndSend(char *message)
{
    if (Serial)
    {
        Serial.println(message);
    }
    if (client.available())
    {
        client.send(message);
    }
}

// Send JSON data for `read` action
void handleRead()
{
    Serial.println("Sending data to client");
    DynamicJsonDocument doc(1024);
    doc["action"] = "read";

    doc["kpA"] = KpA;
    doc["kiA"] = KiA;
    doc["kdA"] = KdA;
    doc["kpD"] = KpD;
    doc["kdD"] = KdD;
    doc["forward_threshold"] = forward_threshold;
    doc["side_threshold"] = side_threshold;
    doc["maze_width"] = maze_width;
    doc["car_width"] = car_width;
    doc["sensor_left"] = sensor_left;
    doc["sensor_front"] = sensor_front;
    doc["sensor_right"] = sensor_right;
    doc["encoder_counts"] = encoder_counts;
    doc["cell_size"] = cell_size;
    doc["posL"] = posL;
    doc["posR"] = posR;
    doc["upload"] = upload;

    String response;
    serializeJson(doc, response);
    client.send(response);
}

// Handle incoming WebSocket messages
void handleWrite(const WebsocketsMessage &message)
{
    String payload = message.data(); // Extract message content as a String
    Serial.println("Received: " + payload);
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload.c_str()); // Use payload for deserialization

    if (error)
    {
        Serial.println("Failed to parse JSON");
        Serial.println(error.c_str());
        return;
    }

    const char *action = doc["action"];
    Serial.println(action);
    if (strcmp(action, "write") == 0)
    {
        KpA = doc["kpA"] | KpA;
        KiA = doc["kiA"] | KiA;
        KdA = doc["kdA"] | KdA;
        KpD = doc["kpD"] | KpD;
        KdD = doc["kdD"] | KdD;
        forward_threshold = doc["forward_threshold"] | forward_threshold;
        side_threshold = doc["side_threshold"] | side_threshold;
        maze_width = doc["maze_width"] | maze_width;
        car_width = doc["car_width"] | car_width;
        sensor_left = doc["sensor_left"] | sensor_left;
        sensor_front = doc["sensor_front"] | sensor_front;
        sensor_right = doc["sensor_right"] | sensor_right;
        encoder_counts = doc["encoder_counts"] | encoder_counts;
        cell_size = doc["cell_size"] | cell_size;
        posL = doc["posL"] | posL;
        posR = doc["posR"] | posR;
        upload = doc["upload"] | upload;
    }
    else if (strcmp(action, "read") == 0)
    {
        handleRead();
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

    webSocket.listen(80); // Start WebSocket server
    Serial.println("WebSocket server started. Connect to ws://" + WiFi.localIP().toString() + ":80");
}

void wifiLoop(void *parameter)
{
    for (;;)
    {
        // Infinite loop
        if (!client.available() && !upload)
        {
            client = webSocket.accept();
            Serial.println("Client connected");
        }
        else if (!upload)
        {
            client.poll();
            auto message = client.readBlocking();
            handleWrite(message);
            Serial.println("Message received");
        }

        else if (upload)
        {
            if (client.available())
            {
                client.close();
                Serial.println("closed");
            }
            ArduinoOTA.handle(); // Handle OTA requests
        }

        vTaskDelay(100 / portTICK_PERIOD_MS); // Non-blocking delay
    }
}
