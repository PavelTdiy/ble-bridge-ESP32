// /*
//     Video: https://www.youtube.com/watch?v=oCMOYS71NIU
//     Sourse: https://github.com/h2zero/esp-nimble-cpp/blob/05ac9deaead7e05865fd7aaca5f9f8747d00a99a/examples/basic/BLE_uart/main/main.cpp

//    The program of creating the BLE server is:
//    1. Create a BLE Server
//    2. Create a BLE Service
//    3. Create a BLE Characteristic on the Service
//    4. Create a BLE Descriptor on the characteristic
//    5. Start the service.
//    6. Start advertising.

//    In this example rxValue is the data received (only accessible inside that function).
//    And txValue is the data to be sent, in this example just a byte incremented every second.
// */

#include <Arduino.h>
#include <NimBLEDevice.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// board variables
unsigned long previousMillis = 0;

// ble variables
BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;

#ifndef MyServerCallbacks_h
#define MyServerCallbacks_h

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    printf("Client connected\n");
    deviceConnected = true;
  }

  void onDisconnect(BLEServer *pServer, int reason)
  {
    deviceConnected = false;
    printf("Client disconnected\n");
  }

  /***************** New - Security handled here ********************
  ****** Note: these are the same return values as defaults ********/
  uint32_t onPassKeyRequest()
  {
    printf("Server PassKeyRequest\n");
    return 123456;
  }

  bool onConfirmPIN(uint32_t pass_key)
  {
    printf("The passkey YES/NO number: %d\n", pass_key);
    return true;
  }

  void onAuthenticationComplete()
  {
    printf("Starting BLE work!\n");
  }
};
#endif

#ifndef MyCallbacks_h
#define MyCallbacks_h

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string rxValue = pCharacteristic->getValue();

    if (rxValue.length() > 0)
    {
      printf("*********\n");
      printf("Received Value: ");
      for (int i = 0; i < rxValue.length(); i++)
        printf("%d", rxValue[i]);

      printf("\n*********\n");
    }
  }
};

#endif

void connectedTask(void *parameter)
{
  for (;;)
  {
    if (deviceConnected)
    {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= 2000)
      {
        pTxCharacteristic->setValue(&txValue, 1);
        pTxCharacteristic->notify();
        printf("Client notified\n");
        txValue++;
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        previousMillis = currentMillis;
      }
    }

    // disconnecting
    if (!deviceConnected && oldDeviceConnected)
    {
      pServer->startAdvertising(); // restart advertising
      printf("start advertising\n");
      oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected)
    {
      // do stuff here on connecting
      oldDeviceConnected = deviceConnected;
    }

    vTaskDelay(10 / portTICK_PERIOD_MS); // Delay between loops to reset watchdog timer
  }

  vTaskDelete(NULL);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Create the BLE Device
  BLEDevice::init("Ble Bridge");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID_TX,
      /******* Enum Type NIMBLE_PROPERTY now *******
          BLECharacteristic::PROPERTY_NOTIFY
          );
      **********************************************/
      NIMBLE_PROPERTY::NOTIFY);

  /***************************************************
   NOTE: DO NOT create a 2902 descriptor
   it will be created automatically if notifications
   or indications are enabled on a characteristic.

   pCharacteristic->addDescriptor(new BLE2902());
  ****************************************************/

  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID_RX,
      /******* Enum Type NIMBLE_PROPERTY now *******
              BLECharacteristic::PROPERTY_WRITE
              );
      *********************************************/
      NIMBLE_PROPERTY::WRITE);

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  xTaskCreate(connectedTask, "connectedTask", 5000, NULL, 1, NULL);

  // Start advertising
  pServer->getAdvertising()->start();
  printf("Waiting a client connection to notify...\n");
};

void loop()
{
}
