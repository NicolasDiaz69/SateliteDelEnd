// Transmitter code for Arduino x E32 LoRa
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include "EBYTE.h"

#define PIN_M0 D4
#define PIN_M1 D5
#define PIN_AX D6


// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        D2 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,

boolean stateLed = false;
unsigned long tInitial = 0;
String str_read = "";

SoftwareSerial ESerial(D1, D3);
SoftwareSerial CSerial(D8, D7);

// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {
  
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  
  ESerial.begin(9600);
  Serial.begin(115200);
  CSerial.begin(115200);
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
  while (CSerial.available()) {
    str_read = CSerial.readString();//.readStringUntil('\n');
  }
  if (str_read!=""){
    Serial.println(str_read);
    ESerial.println(str_read);
    str_read = "";
  }
  smartdelay(100);
}

void smartdelay(unsigned long timeout){
  unsigned long t = millis();
  tInitial = millis();
  while (digitalRead(PIN_AX)== LOW || (millis()-t) < timeout){
    if ((millis()-t)>timeout){
      break;
    }
    if((millis()-tInitial) > 8.4)
    {
      Serial.print(stateLed);
      Serial.println("Cambio");
      
      if(!stateLed)
      {
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        pixels.show();   // Send the updated pixel colors to the hardware.
      }
      else
      {
        pixels.setPixelColor(0, pixels.Color(0, 255, 0));
        pixels.show();   // Send the updated pixel colors to the hardware.
      }
      
      stateLed = !stateLed;
      tInitial = millis();
    }
  }
  t = millis();
  while ((millis()-t)<20){};
  
}
