/*
  Bluetooth ESP32 bridge to control GPAK through I2C
*/

#include <Arduino.h>

// lib for ble
#include <NimBLEDevice.h>

// libs for DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

//lib with my helping utilities
#include "services.h"

using namespace std;

#define BUTTON 32 //dont use IO02 - this is LED_BUILTIN

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// board variables
unsigned long previousMillis = 0;
OneWire oneWire(21);
DallasTemperature DSsensors(&oneWire);

// ble variables
BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
BLECharacteristic *pReadedReg;
bool deviceConnected = false;
bool oldDeviceConnected = false;
bool buttonWerePressed = false;
uint8_t txValue = 0;

//Create an instance of program services class
Services myServices(1);


#ifndef BleServerCallbacks_h
#define BleServerCallbacks_h

class BleServerCallbacks : public BLEServerCallbacks
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

#ifndef CharacteristicCallbacks_h
#define CharacteristicCallbacks_h

class CharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    string rxValue = pCharacteristic->getValue();

    if (rxValue.length() > 0)
    {
      printf("******* Received Value from BLE: ");
      // printf("%s\n", rxValue.c_str());
      myServices.executeCommand(rxValue);
    }
  }
};

#endif

int readTemperature(int dsIndex)
{
  DSsensors.requestTemperatures(); // Send the command to get temperatures

  return DSsensors.getTempCByIndex(dsIndex);
}


// button hardware interrupt
void IRAM_ATTR bint() {
  buttonWerePressed = true;
}

// bluetooth FreeRTOS task
void bleTask(void *parameter)
{
  for (;;)
  {
    if (deviceConnected)
    {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= 10000)
      {
        printf("******* Client notifying - temperature\n");
        pTxCharacteristic->setValue(&txValue, 2);
        pTxCharacteristic->notify();
        txValue = readTemperature(0);
        Serial.println(txValue);
        myServices.blink();
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


// FreeRTOS task for other peripherial
void perifTask(void *parameter) {
  for (;;)
  {
    if (buttonWerePressed) {
      Serial.println("******* Button pressed");
      int random = rand();
      myServices.executeCommand("servo: 0," + to_string(random % 0x7f));
      // myServices.executeCommand("virtual: " + to_string(random % 0xff));
      txValue = myServices.executeCommand("regr: " + to_string(VIRTUAL_INPUTS));
      printf("%s\n", to_string(txValue).c_str());
      pTxCharacteristic->setValue(&txValue, 2);
      pTxCharacteristic->notify();
      myServices.blink();
      buttonWerePressed = false;
    }
  vTaskDelay(50 / portTICK_PERIOD_MS); // Delay between loops to reset watchdog timer
  }
  vTaskDelete(NULL);
}


// Arduino init function
void setup()
{
  Serial.begin(9600);

  //onboard LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  // ext button
  pinMode(BUTTON, INPUT_PULLUP); 
  attachInterrupt(BUTTON, bint, FALLING); // button interrupt

  // Start up the Dallas DS18B20 library
  DSsensors.begin();

  // Create the BLE Device
  BLEDevice::init("Ble Bridge");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new BleServerCallbacks());

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

  pRxCharacteristic->setCallbacks(new CharacteristicCallbacks());

  // Start the service
  pService->start();

  //start BLE loop - FreeRTOS task
  xTaskCreate(bleTask, "BLE server task", 5000, NULL, 1, NULL);

  //start peripherial loop - FreeRTOS task
  xTaskCreate(perifTask, "Peripherial Task", 5000, NULL, 0, NULL);

  // Start advertising
  pServer->getAdvertising()->start();
  printf("Waiting a client connection...\n");
};

void loop()
{
}
