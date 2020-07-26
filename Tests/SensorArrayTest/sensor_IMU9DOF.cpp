#include "AK09918.h"
#include "ICM20600.h"
#include <Wire.h>
#include "sensor.h"

AK09918 ak09918;
ICM20600 icm20600(true);

void ICM20600::getAccelerationFloat(float* x, float* y, float* z) {
  int16_t _x, _y, _z;
  I2Cdev::readBytes(_addr, ICM20600_ACCEL_XOUT_H, 6, _buffer);
  _x = ((int16_t)_buffer[0] << 8) | _buffer[1];
  _y = ((int16_t)_buffer[2] << 8) | _buffer[3];
  _z = ((int16_t)_buffer[4] << 8) | _buffer[5];
  *x = ((float)_x)*_acc_scale/65536;
  *y = ((float)_y)*_acc_scale/65536;
  *z = ((float)_z)*_acc_scale/65536;
}
void ICM20600::getGyroscopeFloat(float* x, float* y, float* z) {
  int16_t _x, _y, _z;
  I2Cdev::readBytes(_addr, ICM20600_GYRO_XOUT_H, 6, _buffer);
  _x = ((int16_t)_buffer[0] << 8) | _buffer[1];
  _y = ((int16_t)_buffer[2] << 8) | _buffer[3];
  _z = ((int16_t)_buffer[4] << 8) | _buffer[5];
  *x = ((float)_x)*_gyro_scale/65536;
  *y = ((float)_y)*_gyro_scale/65536;
  *z = ((float)_z)*_gyro_scale/65536;
}
AK09918_err_type_t AK09918::getRawData(int16_t* axis_x, int16_t* axis_y, int16_t* axis_z) {
    if (_mode == AK09918_NORMAL) {
        AK09918::switchMode(AK09918_NORMAL);
        bool is_end = false;
        int count = 0;
        while (!is_end) {
            if (AK09918::_getRawMode() == 0x00) {
                is_end = true;
            }
            if (count >= 15) {
                return AK09918_ERR_TIMEOUT;
            }
            count ++;
            delay(1);
        }
    }


    if (!I2Cdev::readBytes(_addr, AK09918_HXL, 8, _buffer)) {
        return AK09918_ERR_READ_FAILED;
    } else {
        *axis_x = (((int16_t)_buffer[1]) << 8) | _buffer[0];
        *axis_y = (((int16_t)_buffer[3]) << 8) | _buffer[2];
        *axis_z = (((int16_t)_buffer[5]) << 8) | _buffer[4];
        if (_buffer[7] & AK09918_HOFL_BIT) {
            return AK09918_ERR_OVERFLOW;
        }
        return AK09918_ERR_OK;
    }
}

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
    AK09918_err_type_t  err;
    err = ak09918.initialize();
    icm20600.initialize();
    ak09918.switchMode(AK09918_CONTINUOUS_100HZ);
    err = ak09918.isDataReady();
    while (err != AK09918_ERR_OK) 
    {
        Serial.println("Waiting Sensor");
        delay(100);
        err = ak09918.isDataReady();
    }
  }
