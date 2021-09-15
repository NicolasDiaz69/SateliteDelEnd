// Receiver Code for Arduino x E32 LoRa 
#include <SoftwareSerial.h>
#include "EBYTE.h"

#define PIN_M0 D4
#define PIN_M1 D5
#define PIN_AX D6

String str_read = "";

SoftwareSerial ESerial(D2, D3);
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {
 
  pinMode(PIN_M0, OUTPUT);
  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_AX, INPUT);

  Serial.begin(9600);

  ESerial.begin(9600);
  Serial.println("Starting Reader");

  Transceiver.init();
  Transceiver.SetMode(MODE_PROGRAM);
  Transceiver.SetTransmitPower(OPT_TP20);
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
  Serial.println("Setup end");
}

void loop() {
  while (ESerial.available()) {
    str_read = ESerial.readStringUntil('\n');
  }
  if (str_read!=""){
    Serial.println(str_read);
    str_read = "";
  }

}
