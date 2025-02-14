# ESP32 OUI Sniffer

This project uses a Seedstudio Xiao esp32-C3 and a Heltec Lora V3 to send BLE OUI detections over the LoRa mesh network of your choice.

## Background

Provide some background information about the project. Explain what the project does, why it is useful, and any other relevant details.

## Requirements

- Seedstudio Xiao esp32-C3
- Heltec Lora V3
- Meshtastic framework (if applicable)

## Setup

If using Meshtastic framework, you must set your serial settings to:
- TextMessage
- 115200 baud
- Pins: Rx 19 and Tx 20 on the Heltec board

All of this can be done in the Meshtastic app.

## OUI Filtering

On Line 73, replace the placeholder OUI (00:11:22) with the OUI(s) of your desired device(s). 

## Usage

Power the device via the Xiao esp32 usb-c port. 

## Contributing

If you would like to contribute, please fork the repository and use a feature branch. Pull requests are welcome.

