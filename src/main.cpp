#include "functions.h"
#include "variables.h"
#include <Arduino.h>
#include <AsyncUDP.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

void setup() {
  pkt = createPacket(0x01, 8);
  udpQueue = xQueueCreate(10, sizeof(pkt));
  Serial.begin(115200);
  startWiFi();
  startmDNS();
  startJoystick(MDNS.IP(0));
  startAsyncUDPServer(MDNS.IP(0), MDNS.port(0));
}

void loop() {
  if (xQueueReceive(udpQueue, pkt, portMAX_DELAY)) {
    Serial.println(pkt->header);
  }
}