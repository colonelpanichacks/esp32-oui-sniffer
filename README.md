# Mesh Detect esp32 OUI Sniffer

This project uses a Seedstudio Xiao esp32-C3 and a Heltec Lora V3 to send BLE OUI detections over the LoRa mesh network of your choice.

## Background

This build allows a user to scan for a specific oui or group of ouis via ble. If a specified device is detected, a message is sent to the Heltec Lora V3 board and distributed over a Lora mesh network such as Meshtastic. 

## Requirements

- Seedstudio Xiao esp32-C3
- Heltec Lora V3
- Meshtastic framework (if applicable)

## Setup

If using Meshtastic framework, you must set your Heltec device serial settings to:
- TextMessage
- 115200 baud
- Pins: Rx 19 and Tx 20 on the Heltec board

## OUI Filtering

On Line 73, replace the placeholder OUI (00:11:22) with the OUI(s) of your desired device(s). 

## Usage

Flash Meshtastic firmware to Heltec board. Flash Xiao board with meshdetect.ino. Power the device via the Xiao esp32 usb-c port. 

## Contributing

If you would like to contribute, please fork the repository and use a feature branch. Pull requests are welcome.

## Order a PCB for this project on my Tindie store 
<a href="https://www.tindie.com/stores/colonel_panic/?ref=offsite_badges&utm_source=sellers_colonel_panic&utm_medium=badges&utm_campaign=badge_large"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>
