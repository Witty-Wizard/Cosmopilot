#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "variables.h"
#include <AsyncUDP.h>
#include <ESPmDNS.h>

void startWiFi();
void startmDNS();
void startJoystick(IPAddress ip);
void startAsyncUDPServer(IPAddress ip, uint16_t port);
void handleUDPPacket(AsyncUDPPacket packet);
Packet *createPacket(uint8_t headerValue, uint8_t channelValue);

#endif