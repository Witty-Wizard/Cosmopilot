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
  Serial.begin(115200);
  udpQueue = xQueueCreate(10, sizeof(pkt));
  startWiFi();
  startmDNS();
  startJoystick(MDNS.IP(0));
  startAsyncUDPServer(MDNS.port(0));
}

void loop() {
  if (xQueueReceive(udpQueue, &pkt, portMAX_DELAY)) {
    Serial.print(pkt.channel[0]);
    Serial.print("\t");
    Serial.print(pkt.channel[1]);
    Serial.print("\n");
  }
}