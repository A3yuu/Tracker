#include <SparkFunLSM9DS1.h>
#include "sensor.h"

#define LSM9DS1_M 0x1E
#define LSM9DS1_AG 0x6B

LSM9DS1 imu;
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
    imu.readGyro();
    imu.readAccel();
    imu.readMag();
    ret.Accel.x = imu.calcAccel(imu.ax);
    ret.Accel.y = imu.calcAccel(imu.ay);
    ret.Accel.z = imu.calcAccel(imu.az);
    ret.Gyro.x = imu.calcGyro(imu.gx);
    ret.Gyro.y = imu.calcGyro(imu.gy);
    ret.Gyro.z = imu.calcGyro(imu.gz);
    ret.Mag.x = -imu.calcMag(imu.mx);
    ret.Mag.y = imu.calcMag(imu.my);
    ret.Mag.z = imu.calcMag(imu.mz);
    return ret;
  }
  
  void Sensor::begin(uint8_t sdaPin, uint8_t sclPin){
    Wire.begin(sdaPin, sclPin);
    imu.settings.device.commInterface = IMU_MODE_I2C;
    imu.settings.device.mAddress = LSM9DS1_AG;
    imu.settings.device.agAddress = LSM9DS1_M;
    while(connectionState == 0){
        connectionState = imu.begin();
        Serial.print("connectionState: ");
        Serial.println(connectionState);
    }
  }
