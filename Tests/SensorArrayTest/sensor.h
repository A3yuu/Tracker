struct Vector3{
  float x,y,z;
};
class SensorData{
  public:
  Vector3 Accel, Gyro, Mag;
  String toString();
};

class Sensor{
  public:
  void begin();
  SensorData getData();
};
