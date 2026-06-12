#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "";
char pass[] = "";

// ADC pin
const int analogPin = 34;

// ACS712 30A
const float sensitivity = 0.066;

// -----------------------------
// Calibration curve (RAW → gerçek voltaj)
// -----------------------------
const int nPoints = 4;

float vAdc[nPoints]  = {0.9, 1.4, 2.3, 2.8};
float vReal[nPoints] = {1.0, 1.5, 2.5, 3.0};

// -----------------------------
// Offset
// -----------------------------
float zeroRaw = 0;

// -----------------------------
// Curve correction
// -----------------------------
float calibrateVoltage(float v)
{
  for (int i = 0; i < nPoints - 1; i++)
  {
    if (v >= vAdc[i] && v <= vAdc[i + 1])
    {
      float ratio =
        (v - vAdc[i]) /
        (vAdc[i + 1] - vAdc[i]);

      return vReal[i] +
             ratio * (vReal[i + 1] - vReal[i]);
    }
  }

  return v;
}

// -----------------------------
// RAW voltage read
// -----------------------------
float readVoltageRaw()
{
  long sum = 0;

  for (int i = 0; i < 100; i++)
  {
    sum += analogRead(analogPin);
    delay(2);
  }

  float adcAvg = sum / 100.0;

  return adcAvg * (3.3 / 4095.0);
}

// -----------------------------
// Offset calibration
// -----------------------------
float calibrateOffset()
{
  long sum = 0;

  for (int i = 0; i < 500; i++)
  {
    sum += analogRead(analogPin);
    delay(2);
  }

  float adcAvg = sum / 500.0;

  return adcAvg * (3.3 / 4095.0);
}

void setup()
{
  Serial.begin(115200);

  analogSetPinAttenuation(analogPin, ADC_11db);

 Serial.println("Blynk baglaniyor...");
Blynk.begin(auth, ssid, pass);

Serial.println("Blynk baglaniyor tamam");;

  delay(2000);

  zeroRaw = calibrateOffset();

  Serial.print("Zero RAW = ");
  Serial.println(zeroRaw);
}

void loop()
{
  Blynk.run();

  float vRaw = readVoltageRaw();

  float v = calibrateVoltage(vRaw);

  float vOffset = calibrateVoltage(zeroRaw);

  float current = (v - vOffset) / sensitivity;

  // Gürültü filtresi
  if (abs(current) < 0.05)
  {
    current = 0;
  }

  Serial.print("Raw: ");
  Serial.print(vRaw);

  Serial.print("  V: ");
  Serial.print(v);

  Serial.print("  Offset: ");
  Serial.print(vOffset);

  Serial.print("  Current: ");
  Serial.println(current);

  Blynk.virtualWrite(V0, current);

  delay(1000);
}
