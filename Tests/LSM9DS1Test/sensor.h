struct Vector3{
  float x,y,z;
};
class SensorData{
  public:
  Vector3 Accel, Gyro, Mag;
  String toString();
};

class Sensor{
  SensorData data;
  uint16_t connectionState = 0;
  public:
  void begin(uint8_t sdaPin, uint8_t sclPin);
  SensorData getData();
};
