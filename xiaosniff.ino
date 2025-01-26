#define NIMBLE_DEBUG_DISABLED // Disable NimBLE logs (at compile time)

#include <NimBLEDevice.h>
#include <esp_log.h>
#include <vector>
#include <algorithm>

// Struct to hold discovered device info
struct DeviceInfo {
    std::string macAddress;
    int rssi;
    unsigned long firstSeen;
    unsigned long lastSeen;
};

// Track devices to avoid duplicates and for redetection
std::vector<DeviceInfo> devices;

// BLE Advertised Device Callback
class MyAdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) override {
        // Extract MAC address and RSSI
        std::string mac = advertisedDevice->getAddress().toString();
        int rssi = advertisedDevice->getRSSI();
        unsigned long currentMillis = millis();

        // Log detected device to USB Serial
        Serial.print("Detected device: ");
        Serial.print(mac.c_str());
        Serial.print(" RSSI: ");
        Serial.println(rssi);

        // OUI Filtering: Place your OUI here "00:11:22" 
        if (mac.rfind("00:11:22", 0) == 0) {
            Serial.println("OUI match found!");

            // Check if the device is already known
            bool known = false;
            for (auto& dev : devices) {
                if (dev.macAddress == mac) {
                    known = true;

                    // Debugging to check time since last seen
                    Serial.print("Device already known. Time since last seen: ");
                    Serial.print(currentMillis - dev.lastSeen);
                    Serial.println(" ms");

                    // If redetected after 30 seconds, send redetection message
                    if (currentMillis - dev.lastSeen > 30000) {
                        Serial1.print("Redetection: Device ");
                        Serial1.println(mac.c_str());
                        Serial1.flush(); // Ensure UART buffer is sent
                        Serial.println("Redetection message sent to Serial1.");
                    }

                    // Update the lastSeen timestamp
                    dev.lastSeen = currentMillis;
                    break;
                }
            }

            // If new, add to list and send alert
            if (!known) {
                DeviceInfo newDev = { mac, rssi, currentMillis, currentMillis };
                devices.push_back(newDev);

                // Send detection message to Serial1
                Serial1.print("Device detected: ");
                Serial1.println(mac.c_str());
                Serial1.flush(); // Ensure UART buffer is sent
                Serial.println("Sent message to Serial1.");
            }
        }
    }
};

void setup() {
    // Short delay for boot stability
    delay(2000);

    // Silence all ESP-IDF logs
    esp_log_level_set("*", ESP_LOG_NONE);

    // Initialize USB Serial
    Serial.begin(115200);
    Serial.println("USB Serial started.");

    // Initialize Serial1 for UART (TX: D6, RX: D7)
    Serial1.begin(115200, SERIAL_8N1, D7, D6); // TX = GPIO6, RX = GPIO7
    Serial.println("Serial1 started.");

    // Initialize NimBLE
    NimBLEDevice::init("");
    Serial.println("NimBLE initialized.");

    // 5-second pause before starting BLE scan
    Serial.println("Pausing for 5 seconds before starting BLE scan...");
    delay(5000);

    // Start BLE Scanning
    NimBLEScan* pScan = NimBLEDevice::getScan();
    pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pScan->setActiveScan(true); // Enable active scanning for detailed data
    pScan->start(0, nullptr, false); // Start continuous scanning

    Serial.println("BLE scan started (continuous).");
}

void loop() {
    // Nothing to process in the loop; BLE scanning runs in the background
}
