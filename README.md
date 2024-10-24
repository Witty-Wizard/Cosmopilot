<p align="center">
  <img src="https://img.shields.io/github/v/release/Witty-Wizard/UDP-Reciever" alt="GitHub Release">
  <img src="https://img.shields.io/github/license/Witty-Wizard/UDP-Reciever" alt="GitHub License">
  <img src="https://img.shields.io/github/stars/Witty-Wizard/UDP-Reciever?style=flat" alt="GitHub Repo stars">
  <img alt="GitHub Issues or Pull Requests" src="https://img.shields.io/github/issues/Witty-Wizard/UDP-Reciever">
  <img alt="GitHub forks" src="https://img.shields.io/github/forks/Witty-Wizard/UDP-Reciever?style=flat">
</p>

# UDP Joystick Control
This project uses an ESP32 to read the Joystick Control data sent via UDP. The system identifies the device using mDNS, starts a UDP Server, and receive the joystick control frames.

## Code Explanation
Libraries Used
- **Async UDP:** Provides asynchronous UDP support, this process runs on `Core 1` of ESP32 in parallel with `Core 0` so this is non-blocking in nature.
- **ESPmDNS:** For mDNS discovery to find the IP address of the transmitting device on the local network.
- **HttpClient:** For making HTTP request to the transmitting device to start or stop the joystick service.
- **WiFi:** To connect ESP32 to local WiFi network
- **FreeRTOS:** For managing queues,i.e., transferring data from `Core 1` to `Core 0`
> [!IMPORTANT]  
> - ESP32 has 2 cores `Core 0` and `Core 1`, `Core 0` runs the code in the `setup()` and `loop()` functions, `Core 1` is dedicated for Networking related Tasks, like `Wifi` and `Bluetooth` Callbacks.
> - There should be minimum processing in the `Core 1` and it should be only used to receive the data and then sent it to `Core 0` for further processing.
> - For sending data form `Core 1` to `Core 0` one should never use direct variables addressing as the two cores run asynchronously and this can result in random bits flipping. To send data between core one must use `queues`.

## Functions Used
- `startWiFi()`: Initializes the WiFi connection.
- `startmDNS()`: Sets up mDNS to discover the device and find its IP and port.
- `startJoystick(IP)`: Asks the Joystick Device to begin communication.
- `startAsyncUDPServer(port)`: Starts listening on the UDP port.

## Code Walkthrough
1. Setup
   - The `Serial` connection starts at 115200 baud for debugging.
   - A FreeRTOS queue `udpQueue` is created to handle incoming UDP joystick packets (`pkt`).
   - WiFi and mDNS are started using the `startWiFi()` and `startmDNS()` functions.
   - The joystick control service begins using `startJoystick()` with the IP found through mDNS.
   - The UDP server starts with `startAsyncUDPServer()` on the port obtained from mDNS.

2. Loop
   - Inside the loop(), the code waits to receive packets from the UDP queue using xQueueReceive().
   - When a packet arrives, the channel data is read from and copied to a `struct` called `Packet`.

## For more details, you can refer to: 
- The ExpressLRS pull request that inspired this implementation: https://github.com/ExpressLRS/ExpressLRS/pull/2444
- Espresiff [documentation](https://docs.espressif.com/projects/esp-idf/en/v4.2.3/esp32/api-reference/system/freertos.html), on how to use `queues` and `FreeRTOS`.
- This [article](https://www.cloudflare.com/en-gb/learning/ddos/glossary/user-datagram-protocol-udp/) on `UDP` Protocol
