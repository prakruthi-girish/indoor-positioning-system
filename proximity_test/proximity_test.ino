#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#define LED 2
String knownBLEAddresses[] = {"7c:9e:bd:ed:b3:3a"};
int RSSI_THRESHOLD = -80;
bool device_found;
int scanTime = 1; //In seconds
BLEScan* pBLEScan;
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
   
};
void setup() {
  Serial.begin(115200); //Enable UART on ESP32
  Serial.println("Scanning..."); // Print Scanning
  pinMode(LED, OUTPUT); //make BUILTIN_LED pin as output
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
 // pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks()); //Init Callback Function
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100); // set Scan interval
  pBLEScan->setWindow(99);  // less or equal setInterval value
}
void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  for (int i = 0; i < foundDevices.getCount(); i++)
  {
    BLEAdvertisedDevice device = foundDevices.getDevice(i);
    int rssi = device.getRSSI();

     if (strcmp(device.getAddress().toString().c_str(), knownBLEAddresses[0].c_str()) == 0)
                        {
          device_found = true;               
                        }
        else {
          device_found = false;
        }
 
    Serial.print("RSSI: ");
    Serial.println(rssi);
    Serial.println(device.toString().c_str());
    if ((rssi > RSSI_THRESHOLD) && (device_found == true))
    { digitalWrite(LED, HIGH);
      break;
    }
    else
     digitalWrite(LED, LOW);
  }
  Serial.println("------------------");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
}
