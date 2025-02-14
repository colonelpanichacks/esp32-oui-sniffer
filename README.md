# Mesh Detect esp32-oui-sniffer

This project uses a Seedstudio Xiao esp32-C3 and a Heltec Lora V3 to send BLE OUI detections over the LoRa mesh network of your choice.

## Background

This project allows a user to scan for a specific oui or group of ouis via ble. If a specified device is detected, a message is sent to the Heltec Lora V3 board and distributed over your Lora mesh network such as Meshtastic. 

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

Flash Meshtastic firmware to Heltec board. Flash Xiao board with <<>> . Power the device via the Xiao esp32 usb-c port. 

## Contributing

If you would like to contribute, please fork the repository and use a feature branch. Pull requests are welcome.

