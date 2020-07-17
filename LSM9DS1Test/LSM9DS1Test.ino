#include <SparkFunLSM9DS1.h>

#define LSM9DS1_M 0x1E
#define LSM9DS1_AG 0x6B
#define  SDA1_PIN  21
#define  SCL1_PIN  22


float x,y,z;

struct Vector3{
  float x,y,z;
};
struct SensorData{
  Vector3 Accel, Gyro, Mag;
};

class Sensor{
  LSM9DS1 imu;
  SensorData data;
  uint16_t connectionState = 0;
  public:
  void begin(uint8_t agAddress , uint8_t mAddress, uint8_t sdaPin, uint8_t sclPin){
    Wire.begin(sdaPin, sclPin);
    imu.settings.device.commInterface = IMU_MODE_I2C;
    imu.settings.device.mAddress = agAddress;
    imu.settings.device.agAddress = mAddress;
    while(connectionState == 0){
        connectionState = imu.begin();
        Serial.print("connectionState: ");
        Serial.println(connectionState);
    }
  }
  SensorData getData(){
    SensorData ret;
    imu.readGyro();
    imu.readAccel();
    imu.readMag();
    ret.Accel.x = imu.calcAccel(imu.ax)*10;
    ret.Accel.y = imu.calcAccel(imu.ay)*10;
    ret.Accel.z = imu.calcAccel(imu.az)*10;
    ret.Gyro.x = imu.calcGyro(imu.gx)*10;
    ret.Gyro.y = imu.calcGyro(imu.gy)*10;
    ret.Gyro.z = imu.calcGyro(imu.gz)*10;
    ret.Mag.x = imu.calcMag(imu.mx)*10;
    ret.Mag.y = imu.calcMag(imu.my)*10;
    ret.Mag.z = imu.calcMag(imu.mz)*10;
    return ret;
  }
};

Sensor sensor;

void setup()
{
  Serial.begin(115200);
  sensor.begin(LSM9DS1_AG, LSM9DS1_M, SDA1_PIN, SCL1_PIN);
}


void loop()
{
  SensorData data = sensor.getData();
  Serial.print(data.Accel.x);
  Serial.print(" ");
  Serial.print(data.Accel.y);
  Serial.print(" ");
  Serial.print(data.Accel.z);
  Serial.print(" ");
  Serial.print(data.Gyro.x);
  Serial.print(" ");
  Serial.print(data.Gyro.y);
  Serial.print(" ");
  Serial.print(data.Gyro.z);
  Serial.print(" ");
  Serial.print(data.Mag.x);
  Serial.print(" ");
  Serial.print(data.Mag.y);
  Serial.print(" ");
  Serial.print(data.Mag.z);
  Serial.print("\n");
}
