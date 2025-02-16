<div style="background-color: black; color: limegreen; padding: 15px; font-family: monospace;">

# Mesh Detect 
Esp32 OUI Sniffer

This project uses a Seedstudio Xiao esp32-C3 and a Heltec Lora V3 to send BLE OUI detections over the LoRa mesh network of your choice.  
This build allows a user to scan for a specific OUI or group of OUIs via BLE. If a specified device is detected, a message is sent to the Heltec Lora V3 board and distributed over a LoRa mesh network such as Meshtastic.  

## Requirements

- Seedstudio Xiao esp32-C3  
- Heltec Lora V3  
- Meshtastic framework (if applicable)  
- Nimble 1.4.3 BLE library in Arduino IDE  

## Setup

If using the Meshtastic framework, you must set your Heltec device serial settings to:  
- **TextMessage**  
- **115200 baud**  
- **Pins:** Rx 19 and Tx 20 on the Heltec board  

<img src="https://raw.githubusercontent.com/colonelpanichacks/esp32-oui-sniffer/Xiao-esp32-c3-serial/serial.jpg" alt="Serial Connection" width="400">

## OUI Filtering

On **Line 74** of `meshdetect.ino`, replace the placeholder OUI (`00:11:22`) with the OUI(s) of your desired device(s).  

## Usage

1. **Flash** Meshtastic firmware to Heltec board.  
2. **Flash** Xiao board with `meshdetect.ino`.  
3. **Power** the device via the Xiao ESP32 USB-C port.  

## Contributing

If you would like to contribute, please **fork** the repository and use a **feature branch**. Pull requests are welcome.  

## Order a PCB for this project on my Tindie store  
<a href="https://www.tindie.com/stores/colonel_panic/?ref=offsite_badges&utm_source=sellers_colonel_panic&utm_medium=badges&utm_campaign=badge_large">
    <img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104">
</a>

</div>
