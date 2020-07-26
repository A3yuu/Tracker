#include "sensors.h"
#include "network.h"

#define  SDA1_PIN  26
#define  SCL1_PIN  32
#define  BUTTON_PIN  39
#define DEVICE_NAME "Tracker"

//#define DEBUG

Sensors sensors;
Network network;

void setup()
{
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  sensors.begin(SDA1_PIN, SCL1_PIN);
  network.begin(DEVICE_NAME);
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  SensorsData data = sensors.getData();
  String str = String(millis()) + " " + String(digitalRead(BUTTON_PIN)) + " " + data.toString();
  #ifdef DEBUG
  Serial.println(str);
  #endif
  network.send(str);
}
