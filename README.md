# Mesh Detect
Esp32 OUI Sniffer

This project uses a Seedstudio Xiao esp32-C3 and a Heltec Lora V3 
to send BLE OUI detections over a LoRa mesh network. 
It scans for a specific OUI or group of OUIs via BLE. 
If a specified device is detected, a message is sent to the Heltec Lora V3 
and distributed over a LoRa mesh network such as Meshtastic.

## Requirements
- Seedstudio Xiao esp32-C3
- Heltec Lora V3
- Meshtastic framework or other lora mesh framework
- Nimble 1.4.3 BLE library in Arduino IDE

## Setup
1. Flash meshdetect.ino to your Xiao board via Arduino IDE.
2. Flash your Heltec board with latest Meshtastic firmware at [flasher.meshtastic.org](https://flasher.meshtastic.org)
3. In Meshtasic app, configure your Heltec device serial module settings:
   - TextMessage
   - 115200 baud
   - Pins: Rx 19 and Tx 20 on the Heltec board

## Serial Connection
<img src="https://raw.githubusercontent.com/colonelpanichacks/esp32-oui-sniffer/Xiao-esp32-c3-serial/serial.jpg" alt="Serial Connection" width="400">

## Usage
1. Flash Meshtastic firmware to Heltec board.
2. Edit **Line 74** in `meshdetect.ino`, replacing `00:11:22` with the OUI(s) of your target devices.
3. Flash Xiao board with `meshdetect.ino`.
4. Power the device via the Xiao ESP32 USB-C port.

## Contributing
Fork the repository and use a feature branch. Pull requests welcome.

## Order a PCB for this project
<a href="https://www.tindie.com/stores/colonel_panic/?ref=offsite_badges&utm_source=sellers_colonel_panic&utm_medium=badges&utm_campaign=badge_large">
    <img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104">
</a>
