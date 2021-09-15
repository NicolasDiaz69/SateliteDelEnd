/*
 * Cyborg CEA cansat V1.0
 * Created for the robotic people competition
 * By Lina / Erick / Nicolas / Juan Andres
 * Coach: IE.Miguel Califa
 * Hardware: Wemos D1 R1 & DHT & BMP180 & SD CARD & E32 915T20D
 * 
 */
 
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <SD.h>
#include <DHT_U.h>
#include <SPI.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <ESP8266WiFi.h>
#include "DHT.h"


#define DHTPIN 2 
#define DHTTYPE    DHT11
#define I2C_ADDRESS 0x77
#define Po 1017
#define chipSelect D8

WiFiClient client;
TinyGPS gps;
SoftwareSerial ss(D4, D3);
SFE_BMP180 bmp180;
DHT_Unified dht(DHTPIN, DHTTYPE);

int satelites,
measurePin = A0,
ledPower = D0,
samplingTime = 280,
deltaTime = 40,
sleepTime = 9680;
float flat, flon,
voMeasured = 0,
calcVoltage = 0,
dustDensity = 0,
pm05=0,
temperatura = 0, 
humedad = 0, 
altitud = 0, 
dust = 0,
latitud = 0,
longitud = 0,
anteriortemperatura = 0,
anteriorhumedad = 0;
boolean heartRate = false;
int HRPin = D0;

unsigned long age;
String informacion = "";
static void smartdelay(unsigned long ms);

// Wi-Fi Settings
const char* ssid = "CEA_Robotica"; // your wireless network name (SSID)
const char* password = "ElectronicsLab2021"; // your Wi-Fi network password


// ThingSpeak Settings
const int channelID = 000000;
String writeAPIKey = "G30XX7RK1V6L6HEL"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";
const int postingInterval = 3.0 * 1000.0; // post data every x seconds

void setup() {
  Serial.begin(115200);
  pinMode(ledPower,OUTPUT);
  pinMode(HRPin, INPUT);
  //Inicializar DHT11.
  dht.begin();
  sensor_t sensor;
  Wire.begin();
  
  //begin() initializes the interface, checks the sensor ID and reads the calibration parameters.  
  if (!bmp180.begin())
  {
    Serial.println("begin() failed. check your BMP180 Interface and I2C Address.");
    while (1);
  } else Serial.println("Inicialice con exito el BMP180");
  
  // SD Card Init
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  } else Serial.println("Inicialice con exito la memoria SD");

  ss.begin(9600);
  
  Serial.println("Inicializacion correcta, procediendo con lectura de señales");


WiFi.begin(ssid, password);

Serial.print ("conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print ("."); 
  }
  
}

void loop() {
  gps.f_get_position(&flat, &flon, &age); // Paso 1, buscar GPS
  temperatura=obtener_temperatura (); // Paso 2, leer temperaturas
  humedad=obtener_humedad (); // Paso 3, leer humedad
  
  altitud=obtener_altitud (); // Paso 4, leer altitud
  dust=get_dust_density ();// Step 5, read dust Density 
  
  satelites = obtener_satelites(); // Paso 5, obtener cantidad de satelites on-line
  latitud = obtener_latitud(); // Paso 6, obtener latitud
  longitud = obtener_longitud(); // Paso 7, obtener longitud
  heartRate = digitalRead(HRPin);

  informacion = String (temperatura) + "," + String (humedad) + "," + String (altitud) + "," + String (satelites) + "," + String (latitud) + "," + String (longitud) + String (dust) + "," + String (heartRate) + ",";
  informacion+= "https://www.google.com/maps/@";
  informacion+= String(latitud) + ",";
  informacion+= String(longitud) + ",";
  informacion+= "16z";


  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  dataFile.println(informacion);
  dataFile.close();

  Serial.println (informacion);
  
  if (client.connect(server, 80)) {
    // Construct API request body
    String body = "&field1=";
           body += String (temperatura);
           body += "&field2=";
           body += String (altitud);
           body += "&field3=";
           body += String (humedad);
           body += "&field4=";
           body += String (latitud);
           body += "&field5=";
           body += String (longitud);
           body += "&field6=";
           body += String (dustDensity);
           body += "&fiel7=";
           body += String (satelites);
           

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);
  }
  client.stop(); 
  
   
 smartdelay(postingInterval);

}
double guardar_sd(String data){
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  dataFile.println(data);
  dataFile.close();
}
double obtener_longitud(){
  //Serial.print("Longitud: ");
  //Serial.println(flon);
  return flon;
}
double obtener_latitud(){
  //Serial.print("Latitud: ");
  //Serial.println(flat);
  return flat;
}
int obtener_satelites(){ 
  satelites = gps.satellites();
  //Serial.print("satelites: ");
  //Serial.println(satelites);
  return satelites;
}
double obtener_temperatura(){ 
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    //Serial.println(F("Error reading temperature!"));
    return anteriortemperatura;
  }
  else {
    //Serial.print(F("Temperature: "));
    //Serial.print(event.temperature);
    //Serial.println(F("°C"));
    anteriortemperatura = event.temperature;
    return event.temperature;
  }
}
double obtener_humedad (){ 
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    //Serial.println(F("Error reading humidity!"));
    return anteriorhumedad;
  }
  else {
    //Serial.print(F("Humidity: "));
    //Serial.print(event.relative_humidity);
    //Serial.println(F("%"));
    anteriorhumedad = event.relative_humidity;
    return event.relative_humidity; 
  }
}
double obtener_altitud()
{
  char status;
  double T, P, alt;
  bool success = false;

  status = bmp180.startTemperature();

  if (status != 0) {
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) {
          alt = bmp180.altitude(P, Po);

          /*
          Serial.print("Altitude: ");
          Serial.print(alt);
          Serial.println(" Meters");
          */
          return abs(alt);
        }
      }
    }
  }
}
double get_dust_density()
{
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin); // read the dust value
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  // 0 - 3.3V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = 5*voMeasured/1024;
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 0.17 * calcVoltage - 0.1;
  // Ecuacion linear de PM 2.5
  pm05=(calcVoltage-0.0356)*120000;
  /*
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
  Serial.print(" - Dust Density(mg/m3): ");
  Serial.println(dustDensity);
  Serial.print(" - PM 0.5(particulas/0.01 pie3): ");
  Serial.println(pm05);
  */
  return abs(dustDensity);
}
static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
