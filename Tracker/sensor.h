#include <SparkFunLSM9DS1.h>

struct Vector3{
  float x,y,z;
};
class SensorData{
  public:
  Vector3 Accel, Gyro, Mag;
  String toString();
};

class Sensor{
  LSM9DS1 imu;
  SensorData data;
  uint16_t connectionState = 0;
  public:
  void begin(uint8_t agAddress , uint8_t mAddress, uint8_t sdaPin, uint8_t sclPin);
  SensorData getData();
};
