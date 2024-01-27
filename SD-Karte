extern float getCTemperatur(void);
extern float getTDSVolt(void);
extern float getTDSppm(void);
extern unsigned int getNumSat(void);
extern unsigned int getGPSValid(void);
extern double getGNSSLat(void);
extern double getGNSSLon(void);
extern double getGNSSAlt(void);
extern double getGNSSSpeed(void);

const int MAX_FILE_LENGTH = 40;
char fileBuf[MAX_FILE_LENGTH];

void readFile(const char* path)
{
    Serial.printf("Lese Datei: %s\n", path);

    File file = SD.open(path);
    if (!file)
    {
        Serial.printf("Öffnen der Datei fehlgeschlagen %s fürs lesen", path);
        return;
    }

    Serial.printf("Von Datei gelesen: %s:", path);
    while (file.available())
    {
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(const char* path, const char* message)
{
    Serial.printf("Schreibe Datei: %s\n", path);

    File file = SD.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.printf("Öffnen der Datei fehlgeschlagen %s fürs lesen\n", path);
        return;
    }
    if (file.print("Temperatur [°C];TDS [V];TDS [ppm];Satelliten [num];fix [Y|N];Breitengrad [rad];Längengrad [rad];Höhe [m];Geschwindigkeit [m/s]\n"))
    {
        file.print(message);
    }
    else
    {
        Serial.println("Schreiben fehlgeschlagen");
    }
    file.close();
}

void appendFile(const char* path, const char* message)
{
    File file = SD.open(path, FILE_APPEND);
    if (!file)
    {
        writeFile(path, message);
    }
    else
    {
        if (!file.print(message))
        {
            Serial.printf("ERROR: Anhängen an Datei: %s fehlgeschlagen\n", path);

        }
        file.close();
    }
}

void deleteFile(const char* path)
{
    Serial.printf("Lösche Datei: %s\n", path);
    if (SD.remove(path))
    {
        Serial.println("Datei gelöscht");
    }
    else
    {
        Serial.printf("ERROR: Löchen der Datei %s fehlgeschlagen", path);
    }
}


void setupSDCard()
{
    fileBuf[0] = '\0';

    if (!SD.begin(5))
    {
        Serial.println("Einsetzen der Karte fehlgeschlagen");
        return;
    }
    uint8_t cardType = SD.cardType();

    switch (cardType)
    {
    CARD_NONE:
    Serial.println("Keine SD Karte eingesetzt");
    break;
MMC:
    Serial.println("MMC Karte eingesetzt");
    break;
SDSC:
    Serial.println("SDSC Karte eingesetzt");
    break;
SDHC:
    Serial.println("SDHC Karte eingesetzt");
    break;
UNKNOWN:
    default:
      Serial.println("SD Kartentyp unbekannt");
break;
  }

  Serial.printf("SD Karten Größe: %lluMB\n", SD.cardSize() / (1024 * 1024));
Serial.printf("Gesamter Speicherplatz: %lluMB\n", SD.totalBytes() / (1024 * 1024));
Serial.printf("Benutzer Speicherplatz: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void loopSDCard()
{
    if (strlen(fileBuf) > 10)
    {
        const unsigned int MAX_BUFFER = 100;
        char buffer[MAX_BUFFER];
        snprintf(buffer, MAX_BUFFER, "%02d%02d%02d;%02d%02d%02d;%02.1f;%02.2f;%04.2f;%02d;%c;%2.6f;%2.6f;%03.0f;%02.2f\n",
          gps.date.year() - 2000,
          gps.date.month(),
          gps.date.day(),
          gps.time.hour() + TIME_HOUR_OFFSET,
          gps.time.minute(),
          gps.time.second(),
          getCTemperatur(),
          getTDSVolt(), getTDSppm(),
          getNumSat(),
          (getGPSValid() == 1) ? 'Y' : 'N',
          getGNSSLat(), getGNSSLon(),
          getGNSSAlt(), getGNSSSpeed());
        appendFile(fileBuf, buffer);
    }
    else
    {
        getTimeDateFileName(fileBuf, MAX_FILE_LENGTH);
    }
}
