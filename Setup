#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>       
#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <SPI.h>
#include <FS.h>
#include <SD.h>


void setup()
{
    Serial.begin(115200);
    setupTempSensor();
    setupTDS();
    setupSDCard();
    setupGNSS();
}

void loop()
{
    loopTempSensor();
    loopTDS();
    loopGNSS();
    loopSDCard();
}
