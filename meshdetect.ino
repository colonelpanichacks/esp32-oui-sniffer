// Disable NimBLE logs (at compile time)
#define NIMBLE_DEBUG_DISABLED

// ================================
// Include Libraries
// ================================
#include <NimBLEDevice.h>
#include <esp_log.h>
#include <vector>
#include <algorithm>

// ================================
// Pin Definitions
// ================================
#define SERIAL1_RX_PIN  D5 // GPIO5
#define SERIAL1_TX_PIN  D4  // GPIO4

// ================================
// Serial Configuration
// ================================
// Initialize Serial Ports
void initializeSerial() {
    // Initialize USB Serial
    Serial.begin(115200);
    // Removed blocking wait
    Serial.println("USB Serial started.");

    // Initialize Serial1 for UART (TX: D5, RX: D4)
    Serial1.begin(115200, SERIAL_8N1, SERIAL1_RX_PIN, SERIAL1_TX_PIN);
    Serial.println("Serial1 started.");
}

// Function to check if USB Serial is connected
bool isSerialConnected() {
    return Serial && Serial.peek() >= 0;
}

// ================================
// Device Information Struct
// ================================
struct DeviceInfo {
    std::string macAddress;
    int rssi;
    unsigned long firstSeen;
    unsigned long lastSeen;
};

// ================================
// Global Variables
// ================================
// Track devices to avoid duplicates and for redetection
std::vector<DeviceInfo> devices;

// ================================
// BLE Advertised Device Callback Class
// ================================
class MyAdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
public:
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) override {
        // Extract MAC address and RSSI
        std::string mac = advertisedDevice->getAddress().toString();
        int rssi = advertisedDevice->getRSSI();
        unsigned long currentMillis = millis();

        // Log detected device to USB Serial if connected
        if (isSerialConnected()) {
            Serial.print("Detected device: ");
            Serial.print(mac.c_str());
            Serial.print(" RSSI: ");
            Serial.println(rssi);
        }

        // OUI Filtering: Replace "00:11:22" with your desired OUI
        if (mac.rfind("00:11:22", 0) == 0) {
            if (isSerialConnected()) {
                Serial.println("OUI match found!");
            }

            // Check if the device is already known
            bool known = false;
            for (auto& dev : devices) {
                if (dev.macAddress == mac) {
                    known = true;

                    // Debugging: Time since last seen
                    if (isSerialConnected()) {
                        Serial.print("Device already known. Time since last seen: ");
                        Serial.print(currentMillis - dev.lastSeen);
                        Serial.println(" ms");
                    }

                    // If redetected after 30 seconds, send redetection message
                    if (currentMillis - dev.lastSeen > 30000) {
                        Serial1.print("Redetection: Device ");
                        Serial1.println(mac.c_str());
                        Serial1.flush(); // Ensure UART buffer is sent
                        if (isSerialConnected()) {
                            Serial.println("Redetection message sent to Serial1.");
                        }
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
                Serial1.print("Device Detected: ");
                Serial1.println(mac.c_str());
                Serial1.flush(); // Ensure UART buffer is sent
                if (isSerialConnected()) {
                    Serial.println("Sent message to Serial1.");
                }
            }
        }
    }
};

// ================================
// Setup Function
// ================================
void setup() {
    // Short delay for boot stability
    delay(2000);

    // Silence all ESP-IDF logs
    esp_log_level_set("*", ESP_LOG_NONE);

    // Initialize Serial Ports
    initializeSerial();

    // Initialize NimBLE
    NimBLEDevice::init("");
    if (isSerialConnected()) {
        Serial.println("NimBLE initialized.");
    }

    // 5-second pause before starting BLE scan
    if (isSerialConnected()) {
        Serial.println("Pausing for 5 seconds before starting BLE scan...");
    }
    delay(5000);

    // Start BLE Scanning
    NimBLEScan* pScan = NimBLEDevice::getScan();
    pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pScan->setActiveScan(true); // Enable active scanning for detailed data
    pScan->start(0, nullptr, false); // Start continuous scanning

    if (isSerialConnected()) {
        Serial.println("BLE scan started (continuous).");
    }
}

// ================================
// Loop Function
// ================================
void loop() {
    // Nothing to process in the loop; BLE scanning runs in the background
}
