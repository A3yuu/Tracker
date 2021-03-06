#include <Wire.h>
#include "sensors.h"

#define TCAADDR 0x70

String SensorsData::toString(){
  String ret;
  for(SensorData sensor : sensorData){
    ret += sensor.toString() + " ";
  }
  return ret;
}
SensorsData Sensors::getData(){
  SensorsData ret;
  for(int i=0;i<SENSOR_NUM;i++){
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << i);
    Wire.endTransmission();
    ret.sensorData[i] = sensor[i].getData();
  }
  return ret;
}
  
void Sensors::begin(uint8_t sdaPin, uint8_t sclPin){
  Wire.begin(sdaPin, sclPin);
  Wire.setClock(400000);
  for(int i=0;i<SENSOR_NUM;i++){
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << i);
    Wire.endTransmission();
    sensor[i].begin();
  }
}
