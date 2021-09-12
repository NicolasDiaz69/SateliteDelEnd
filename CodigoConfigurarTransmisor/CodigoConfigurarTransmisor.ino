// Transmitter code for Arduino x E32 LoRa
#include <SoftwareSerial.h>
#include "EBYTE.h"

#define PIN_M0 D4
#define PIN_M1 D5
#define PIN_AX D6

float ii = 0.0;

SoftwareSerial ESerial(D2, D3);
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {
  ESerial.begin(9600);
  Serial.begin(115200);
  Serial.println("Iniciando setup");
  Transceiver.init();
  Transceiver.SetMode(MODE_PROGRAM);
  Transceiver.SetTransmitPower(0b00);
  Transceiver.SetUARTBaudRate(UDR_9600);
  Transceiver.SetAirDataRate(ADR_300);
  Transceiver.SetAddressH(0);
  Transceiver.SetAddressL(0);
  Transceiver.SetChannel(13);

  Transceiver.SaveParameters(PERMANENT);
  Transceiver.Reset();

  Transceiver.PrintParameters();
  Transceiver.SetMode(MODE_NORMAL);
  Transceiver.Reset();
  ESerial.flush();
  Serial.println("Setup OK");
}

void loop() {
  ESerial.println(ii);
  smartdelay(2000);
  ii+=0.01;  
}

void smartdelay(unsigned long timeout){
  unsigned long t = millis();
  while (digitalRead(PIN_AX)== LOW){
    if ((millis()-t)>timeout){
      break;
    }
  }
  t = millis();
  while ((millis()-t)<20){};
}
