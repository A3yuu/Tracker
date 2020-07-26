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
  void begin();
  SensorData getData();
};
