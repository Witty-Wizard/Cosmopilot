#include "variables.h"

const char *ssid = "ssid";
const char *password = "password";
Packet *pkt = nullptr;
QueueHandle_t udpQueue;
AsyncUDP udp;