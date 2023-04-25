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
#include <String.h>
// lib for ble
#include <NimBLEDevice.h>

// libs for DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

// include Renesas lib to control GPAK from I2C
#include "Silego.h"
#include "macros/SLG46826.h"    // Include macros for SLG46531

// lib to control micro-servos using angle references
#include "Servo.h"

//lib with my helping utilities
#include "utils.h"

// config i2c pins
#define I2C_SCL 18
#define I2C_SDA 19

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
bool deviceConnected = false;
bool oldDeviceConnected = false;
bool buttonWerePressed = false;
uint8_t txValue = 0;

// Create an instance of Silego class called
// "silego" with device address 0x08
Silego silego(0x08, I2C_SDA, I2C_SCL);

//Create an instance of Servo class
Servo myServo(4);

//Create an instance of Utils class
Utils utils(1);


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
    std::string rxValue = pCharacteristic->getValue();

    if (rxValue.length() > 0)
    {
      printf("Received Value: ");
      printf("%s\n", rxValue.c_str());
      myServo.setDegStrServo(rxValue, 0);
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
      if (currentMillis - previousMillis >= 3000)
      {
        printf("Client notifying...\n");
        pTxCharacteristic->setValue(&txValue, 2);
        pTxCharacteristic->notify();
        txValue = readTemperature(0);
        Serial.println(txValue);
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


// FreeRTOS task for other peripherial
void perifTask(void *parameter) {
  for (;;)
  {
    if (buttonWerePressed) {
      buttonWerePressed = false;
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("button pressed");
      utils.parseCommand("My first command");
      myServo.setDegServo(rand() % 0x7f, 0); // not string here
      // myServo.setDegStrServo("73", 0);
    }
  digitalWrite(LED_BUILTIN, LOW);
  vTaskDelay(50 / portTICK_PERIOD_MS); // Delay between loops to reset watchdog timer
  }
  vTaskDelete(NULL);
}


// Arduino init function
void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // ext button
  attachInterrupt(BUTTON, bint, FALLING); // button interrupt
  digitalWrite(LED_BUILTIN, LOW);

  // Start up the Dallas DS18B20 library
  DSsensors.begin();
  // set Servo to zero
  myServo.setDegServo(0, 0);

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
