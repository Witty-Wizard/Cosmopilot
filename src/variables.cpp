#include "variables.h"

const char *ssid = "ExpressLRS TX";
const char *password = "expresslrs";
Packet pkt = {0};
QueueHandle_t udpQueue;
AsyncUDP udp;