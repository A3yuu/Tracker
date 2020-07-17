#include "sensor.h"
#include "network.h"

#define LSM9DS1_M 0x1E
#define LSM9DS1_AG 0x6B
#define  SDA1_PIN  21
#define  SCL1_PIN  22
#define DEVICE_NAME "Tracker"

Sensor sensor;
Network network;

void setup()
{
  Serial.begin(115200);
  sensor.begin(LSM9DS1_AG, LSM9DS1_M, SDA1_PIN, SCL1_PIN);
  network.begin(DEVICE_NAME);
}


void loop()
{
  SensorData data = sensor.getData();
  String str = data.toString();
  Serial.println(str);
  network.send(str);
}
