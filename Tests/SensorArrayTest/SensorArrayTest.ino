#include "sensors.h"

#define  SDA1_PIN  26
#define  SCL1_PIN  32

Sensors sensors;

void setup()
{
  Serial.begin(115200);
  sensors.begin(SDA1_PIN, SCL1_PIN);
}

void loop()
{
  SensorsData data = sensors.getData();
  Serial.println(data.toString());
}
