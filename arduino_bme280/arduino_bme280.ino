// Modul pro měření teploty, vlhkosti a barometrického tlaku se senzorem BME280

// připojení potřebných knihoven
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
// nastavení adresy senzoru
#define BME280_ADRESA (0x76)
// inicializace senzoru BME z knihovny
Adafruit_BME280 bme;

void setup() {
  // komunikace po sériové lince rychlostí 9600 baud
  Serial.begin(9600);
  // zahájení komunikace se senzorem BME280,
  // v případě chyby je vypsána hláška po sériové lince
  // a zastaven program
  if (!bme.begin(BME280_ADRESA)) {
    //Serial.println("BME280 senzor nenalezen, zkontrolujte zapojeni!");
    Serial.println("X");
    //while (1);
  }
}

void loop() {
    if (!bme.begin(BME280_ADRESA)) {
    //Serial.println("BME280 senzor nenalezen, zkontrolujte zapojeni!");
    Serial.println("X");
    //while (1);
  } else {
  // výpis všech dostupných informací ze senzoru BMP
  // výpis teploty
  //Serial.print("T");
  Serial.print(bme.readTemperature());
  //Serial.println(" stupnu Celsia.");
  // výpis relativní vlhkosti
  Serial.print(";");
  Serial.print(bme.readHumidity());
  //Serial.println(" %");
  // výpis tlaku s přepočtem na hektoPascaly
  Serial.print(";");
  Serial.println(bme.readPressure() / 100.0F);
  //Serial.println(" hPa.");
  // vytištění prázdného řádku a pauza po dobu 20 vteřin
  Serial.println();
  }
  delay(20000);
}