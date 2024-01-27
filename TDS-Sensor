// Original source code: https://wiki.keyestudio.com/KS0429_keyestudio_TDS_Meter_V1.0#Test_Code
// Project details: https://RandomNerdTutorials.com/esp32-tds-water-quality-sensor/

#define TdsSensorPin 32
#define VREF 5              
#define SCOUNT  30         

int analogBuffer[SCOUNT];     
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
int copyIndex = 0;

float averageVoltage = 0;
float tdsValue = 0;
extern float getCTemperatur(void);

float getTDSVolt(void)
{
    return averageVoltage;
}

float getTDSppm(void)
{
    return tdsValue;
}

int getMedianNum(int bArray[], int iFilterLen)
{
    int bTab[iFilterLen];
    for (byte i = 0; i < iFilterLen; i++)
        bTab[i] = bArray[i];
    int i, j, bTemp;
    for (j = 0; j < iFilterLen - 1; j++)
    {
        for (i = 0; i < iFilterLen - j - 1; i++)
        {
            if (bTab[i] > bTab[i + 1])
            {
                bTemp = bTab[i];
                bTab[i] = bTab[i + 1];
                bTab[i + 1] = bTemp;
            }
        }
    }
    if ((iFilterLen & 1) > 0)
    {
        bTemp = bTab[(iFilterLen - 1) / 2];
    }
    else
    {
        bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
    }
    return bTemp;
}

void setupTDS()
{
    pinMode(TdsSensorPin, INPUT);
}

void loopTDS()
{
    static unsigned long analogSampleTimepoint = millis();
    if (millis() - analogSampleTimepoint > 40U)
    {   
        analogSampleTimepoint = millis();
        analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);
        analogBufferIndex++;
        if (analogBufferIndex == SCOUNT)
        {
            analogBufferIndex = 0;
        }
    }

    static unsigned long printTimepoint = millis();
    if (millis() - printTimepoint > 800U)
    {
        printTimepoint = millis();
        for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
        {
            analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
            averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 4096.0;
            float compensationCoefficient = 1.0 + 0.02 * (getCTemperatur() - 25.0);
            float compensationVoltage = averageVoltage / compensationCoefficient;
            tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;
        }
        Serial.print("Spannung:");
        Serial.print(averageVoltage, 2);
        Serial.print("V   ");
        Serial.print("TDS Wert:");
        Serial.print(tdsValue, 0);
        Serial.println("ppm");
    }
}
