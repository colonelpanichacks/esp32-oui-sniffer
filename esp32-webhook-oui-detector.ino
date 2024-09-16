
#include <NimBLEDevice.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <vector>
#include <algorithm>

// Define the number of LEDs and the data pin for ESP32 (if using an external LED)
#define LED_PIN 2  // GPIO2 is the onboard LED pin for many ESP32 boards

// Struct to hold information about each detected device
struct DeviceInfo {
    std::string macAddress;
    int rssi;
    unsigned long firstSeen;
};

// Vector to store the list of detected devices
std::vector<DeviceInfo> devices;

// Function to blink LED three times
void blinkLED() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
    }
}

// Function to trigger webhook
void triggerWebhook(const char* url) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(url);
        http.GET();
        http.end();
    }
}

// Callback function for Bluetooth scan
class MyAdvertisedDeviceCallbacks: public NimBLEAdvertisedDeviceCallbacks {
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
        std::string mac = advertisedDevice->getAddress().toString();
        int rssi = advertisedDevice->getRSSI();

        if (mac.rfind("00:11:22", 0) == 0) {  // Check if MAC starts with "00:11:22"
            DeviceInfo newDevice = {mac, rssi, millis()};
            devices.push_back(newDevice);

            blinkLED();  // Blink LED when a filtered OUI is discovered

            // Replace with your actual webhook URL
            triggerWebhook("http://your-webhook-url.com");
        }
    }
};

void setup() {
    Serial.begin(115200);
    WiFi.begin("your-SSID", "your-PASSWORD");  // Connect to WiFi

    pinMode(LED_PIN, OUTPUT);  // Set LED pin as output

    NimBLEDevice::init("");
    NimBLEScan* pScan = NimBLEDevice::getScan();
    pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pScan->setActiveScan(true);
    pScan->start(0, nullptr, false);
}

void loop() {
    // Do nothing. The scanning is handled in the background.
}
