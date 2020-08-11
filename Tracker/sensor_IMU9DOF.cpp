#include "AK09918.h"
#include "ICM20600.h"
#include <Wire.h>
#include "sensor.h"

AK09918 ak09918;
ICM20600 icm20600(true);

String SensorData::toString(){
  return
  String(Accel.x) + " " + 
  String(Accel.y) + " " + 
  String(Accel.z) + " " + 
  String(Gyro.x) + " " + 
  String(Gyro.y) + " " + 
  String(Gyro.z) + " " + 
  String(Mag.x) + " " + 
  String(Mag.y) + " " + 
  String(Mag.z);
}
  SensorData Sensor::getData(){
    SensorData ret;
    
    {
      float x, y, z;
      icm20600.getAccelerationFloat(&x, &y, &z);
      ret.Accel.x = x;
      ret.Accel.y = -y;
      ret.Accel.z = z;
      icm20600.getGyroscopeFloat(&x, &y, &z);
      ret.Gyro.x = x;
      ret.Gyro.y = -y;
      ret.Gyro.z = z;
    }
    {
      int16_t x, y, z;
      ak09918.getRawData(&x, &y, &z);
      ret.Mag.x = (float)x * 0.00015f;
      ret.Mag.y = -(float)y * 0.00015f;
      ret.Mag.z = (float)z * 0.00015f;
    }
    
    return ret;
  }
  
  void Sensor::begin(){
    ak09918.initialize();
    icm20600.initialize();
    ak09918.switchMode(AK09918_CONTINUOUS_100HZ);
    while(ak09918.isDataReady() != AK09918_ERR_OK)delay(100);
  }
