#include "sensor.h"

#define  SDA1_PIN  26
#define  SCL1_PIN  32

Sensor sensor;

void setup()
{
  Serial.begin(115200);
  sensor.begin(SDA1_PIN, SCL1_PIN);
}

void loop()
{
  SensorData data = sensor.getData();
  String str = data.toString()+" " + millis();
  Serial.println(str);
}
