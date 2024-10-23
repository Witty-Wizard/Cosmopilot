#pragma once

#ifndef VARIABLES_H
#define VARIABLES_H
#include <AsyncUDP.h>

typedef struct {
  uint8_t header;
  uint8_t channel;
  uint16_t data[];
} Packet;

extern const char *ssid;
extern const char *password;
extern Packet *pkt;
extern AsyncUDP udp;
extern QueueHandle_t udpQueue;
#endif