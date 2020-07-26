Created by A3
いまだまだテスト

■ライブラリの改造
けっこうヒドイので
https://github.com/Seeed-Studio/Seeed_ICM20600_AK09918/
//ビルドできない･･･
I2Cdev.h:77
        #include <Wire.h>
        #ifndef BUFFER_LENGTH
                #warning "i2c BUFFER_LENGTH not defined. Check the Wire.h file for you hardware. Self-defining as 32."
        	#define BUFFER_LENGTH 32
        #endif
    #endif

I2Cdev.c
for (uint8_t k = 0; k < length; k += min(length, BUFFER_LENGTH)) {
↓
for (uint8_t k = 0; k < length; k += min((int)length, BUFFER_LENGTH)) {

//小数点以下切っちゃうの？しかも何回もI2C読むの？精度悪いし一回で読んでよ･･･
ICM20600.h
	void getAccelerationFloat(float* x, float* y, float* z);
	void getGyroscopeFloat(float* x, float* y, float* z);
//符号ェ･･･
AK09918.h
    AK09918_err_type_t getRawData(int16_t* axis_x, int16_t* axis_y, int16_t* axis_z);
↓

■回路
9DOFSensor × 5
https://www.seeedstudio.com/grove-imu-9dof-icm20600-ak0991-p-3157.html

M5 Atom Lite × 1
https://docs.m5stack.com/#/en/core/atom_lite

I2C Switching Hub
https://m5stack.com/collections/m5-unit/products/pahub-unit

1m Cable × 2

and some bands 
マジックテープとかリストバンドとかで作る