#include "sensor.h"

#define  SENSOR_NUM  5

class SensorsData{
  public:
  SensorData sensorData[SENSOR_NUM];
  String toString();
};
class Sensors{
  Sensor sensor[SENSOR_NUM];
  public:
  void begin(uint8_t sdaPin, uint8_t sclPin);
  SensorsData getData();
};
