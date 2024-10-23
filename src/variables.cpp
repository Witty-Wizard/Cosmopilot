#include "variables.h"

const char *ssid = "ssid";
const char *password = "password";
Packet pkt = {0};
QueueHandle_t udpQueue;
AsyncUDP udp;