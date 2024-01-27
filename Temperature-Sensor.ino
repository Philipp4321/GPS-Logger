#define SENSOR_PIN  27

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

float tempC;

float getCTemperatur(void)
{
    return tempC;
}

void setupTempSensor(void)
{
    DS18B20.begin();
}

void loopTempSensor(void)
{
    DS18B20.requestTemperatures();
    tempC = DS18B20.getTempCByIndex(0);
    Serial.print("Temperatur: ");
    Serial.print(tempC);
    Serial.print("°C  ");
    delay(1000); 
}
