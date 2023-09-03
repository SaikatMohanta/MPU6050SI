#ifndef MPU6050SI_h
#define MPU6050SI_h

#include <Arduino.h>
#include <Wire.h>

class MPU6050SI {
public:
    MPU6050SI();
    bool begin();
    void readData();
    float getAccelerationX();
    float getAccelerationY();
    float getAccelerationZ();
    float getGyroX();
    float getGyroY();
    float getGyroZ();

private:
    int16_t accelerometerRaw[3];
    int16_t gyroRaw[3];
    float acceleration[3];  // Acceleration in m/s^2
    float gyro[3];          // Gyro in rad/s
    float accelScale;
    float gyroScale;

    void writeRegister(uint8_t reg, uint8_t value);
    void readRegisters(uint8_t reg, uint8_t count, uint8_t* data);
};

#endif
