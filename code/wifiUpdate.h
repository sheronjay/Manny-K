#pragma once
#include <Print.h>

// void handleRead();

// Handler to write mutable value
// void handleWrite();
void printSerialAndSend(const String message);

void wifiSetup();

// void wifiTask(void *parameter);

void wifiLoop(void *parameter);