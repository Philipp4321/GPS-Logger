#define RXD2 16
#define TXD2 17
HardwareSerial gnss_uart(1);

TinyGPSPlus gps;
TaskHandle_t Task1;
const int TIME_HOUR_OFFSET = 2;
const unsigned int MAX_TIMEDATE_STRING = 28;
void loopGNSS(void* pvParameters);

void getTimeDateString(char* timeBuffer, unsigned int max_length)
{
    if (gps.time.isValid() && gps.date.isValid())
    {
        snprintf(timeBuffer, max_length, "%02d:%02d:%02d %02d.%02d.%04d",
        gps.time.hour() + TIME_HOUR_OFFSET,
        gps.time.minute(),
        gps.time.second(),
        gps.date.day(),
        gps.date.month(),
        gps.date.year());
    }
}

void getTimeDateFileName(char* timeBuffer, unsigned int max_length)
{
    if (gps.location.isValid() && gps.time.isValid() && gps.date.isValid())
    {
        snprintf(timeBuffer, max_length, "/GPSLOG-%02d%02d%02d-%02d%02d%02d.txt",
        gps.date.year() - 2000,
        gps.date.month(),
        gps.date.day(),
        gps.time.hour() + TIME_HOUR_OFFSET,
        gps.time.minute(),
        gps.time.second());

    }
    else
    {
        Serial.printf("WARNUNG: Keine valide GPS Position, keine Daten werden gespeichert\n");
        timeBuffer[0] = '\0';
    }

}

void printGNSS()
{
    char timeStrBuffer[MAX_TIMEDATE_STRING];
    if (gps.location.isValid() == 1)
    {
        Serial.print("sat: "); Serial.println(gps.satellites.value());
        Serial.print("spd: "); Serial.println(gps.speed.kmph());
        Serial.print("lat: "); Serial.println(gps.location.lat());
        Serial.print("lon: "); Serial.println(gps.location.lng());
        Serial.print("alt: "); Serial.println(gps.altitude.meters());
        getTimeDateString(timeStrBuffer, MAX_TIMEDATE_STRING);
        Serial.println(timeStrBuffer);
    }
}

void setupGNSS()
{
    gnss_uart.begin(9600, SERIAL_8N1, RXD2, TXD2);
#if 0
    //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    loopGNSS,   /* Task function. */
                    "LoopGNSS",     /* name of task. */
                    30000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */ 
#endif                    
}

void loopGNSS(void)
{
    boolean newData = false;
    for (unsigned long start = millis(); millis() - start < 1000;)
    {
        while (gnss_uart.available())
        {
            if (gps.encode(gnss_uart.read()))
            {
                newData = true;
            }
        }
    }

    if (newData == true)
    {
        newData = false;
        printGNSS();
        Serial.println("Neue GNSS Daten");
    }
    else
    {
        Serial.println("Keine validen GNSS Daten");
    }
}

unsigned int getNumSat(void)
{
    return gps.satellites.value();
}

unsigned int getGPSValid(void)
{
    return gps.location.isValid();
}

double getGNSSLat(void)
{
    return gps.location.lat();
}

double getGNSSLon(void)
{
    return gps.location.lng();
}

double getGNSSAlt(void)
{
    return gps.altitude.meters();
}

double getGNSSSpeed(void)
{
    return gps.speed.mps();
}
