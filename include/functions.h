#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "variables.h"
#include <AsyncUDP.h>
#include <ESPmDNS.h>

void startWiFi();
void startmDNS();
void startJoystick(IPAddress ip, int channels = 8);
void startAsyncUDPServer(uint16_t port);
void handleUDPPacket(AsyncUDPPacket packet);
void stopJoystick(IPAddress ip);
Packet *createPacket(uint8_t channelValue = 18);

#endif