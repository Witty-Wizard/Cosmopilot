#include "functions.h"
#include "variables.h"
#include <AsyncUDP.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

void startWiFi() {
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}

void startmDNS() {
  if (!MDNS.begin("esp32")) {
    Serial.println("Error setting up MDNS responder!");
    return;
  }
  Serial.println("mDNS responder started");

  int n = MDNS.queryService("elrs", "udp");

  if (n == 0) {
    Serial.println("No services found");
  } else {
    Serial.printf("%d service(s) found:\n", n);
    for (int i = 0; i < n; ++i) {
      Serial.print("Service name: ");
      Serial.println(MDNS.hostname(i));
      Serial.print("IP Address: ");
      Serial.println(MDNS.IP(i));
      Serial.print("Port: ");
      Serial.println(MDNS.port(i));
    }
  }
}

void stopJoystick(IPAddress ip) {
  HTTPClient http;

  String url = "http://" + ip.toString() + "/udpcontrol?action=joystick_end";
  http.begin(url);

  http.addHeader("Content-Type", "application/json");

  String payload = "";

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code (End): " + String(httpResponseCode));
    Serial.println("Response (End): " + response);
  } else {
    Serial.println("Error on sending POST (End): " + String(httpResponseCode));
  }

  http.end();
}

void startJoystick(IPAddress ip, int channels) {
  stopJoystick(ip);
  HTTPClient http;

  String url = "http://" + ip.toString() +
               "/udpcontrol?action=joystick_begin&interval=10000&channels=8";
  http.begin(url);

  http.addHeader("Content-Type", "application/json");

  String payload = "";

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println("Response: " + response);
  } else {
    Serial.println("Error on sending POST: " + String(httpResponseCode));
  }

  http.end();
}

void startAsyncUDPServer(uint16_t port) {
  if (udp.listen(port)) {
    Serial.print("Async UDP server started");

    udp.onPacket(handleUDPPacket);
  } else {
    Serial.println("Failed to start Async UDP server.");
  }
}

Packet *createPacket(size_t size) {
  Packet *pkt = (Packet *)malloc(size);
  return pkt;
}

void handleUDPPacket(AsyncUDPPacket packet) {
  uint8_t *data = packet.data();
  xQueueSend(udpQueue, data, portMAX_DELAY);
}