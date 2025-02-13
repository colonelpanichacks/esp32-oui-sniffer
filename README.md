This project uses a Seedstudio Xiao esp32-C3 and a Heltec Lora V3 to send BLE oui detections over the lora mesh network of your choice. 

If using Meshtastic framework, you must set your serial settings to Text Message, 115200 baud, and pins must be set to Rx 19 and Tx 20 on the heltec board. All of this can be done in the Meshtactic app. 


On Line 73, replace the placeholder oui (00:11:22) with the oui/ouis of your desired device/devices. 
 e.g. // OUI Filtering: Replace "00:11:22" with your desired OUI
