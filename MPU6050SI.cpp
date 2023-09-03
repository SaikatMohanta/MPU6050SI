#include "MPU6050SI.h"

MPU6050SI::MPU6050SI() {
    accelScale = 9.81 / 16384.0; // Sensitivity scale for acceleration (m/s^2 per LSB)
    gyroScale = 3.14159265359 / 180.0 / 131.0; // Sensitivity scale for gyro (rad/s per LSB)
}

bool MPU6050SI::begin() {
    Wire.begin();
    Wire.beginTransmission(0x68); // MPU6050 address
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // Wake up the MPU6050 (reset power management)
    Wire.endTransmission();

    return true;
}

void MPU6050SI::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(0x68);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void MPU6050SI::readRegisters(uint8_t reg, uint8_t count, uint8_t* data) {
    Wire.beginTransmission(0x68);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(0x68, count);

    for (int i = 0; i < count; i++) {
        data[i] = Wire.read();
    }
}

void MPU6050SI::readData() {
    uint8_t rawData[14];
    readRegisters(0x3B, 14, rawData);

    accelerometerRaw[0] = (int16_t)((rawData[0] << 8) | rawData[1]);
    accelerometerRaw[1] = (int16_t)((rawData[2] << 8) | rawData[3]);
    accelerometerRaw[2] = (int16_t)((rawData[4] << 8) | rawData[5]);

    gyroRaw[0] = (int16_t)((rawData[8] << 8) | rawData[9]);
    gyroRaw[1] = (int16_t)((rawData[10] << 8) | rawData[11]);
    gyroRaw[2] = (int16_t)((rawData[12] << 8) | rawData[13]);

    acceleration[0] = accelerometerRaw[0] * accelScale;
    acceleration[1] = accelerometerRaw[1] * accelScale;
    acceleration[2] = accelerometerRaw[2] * accelScale;

    gyro[0] = gyroRaw[0] * gyroScale;
    gyro[1] = gyroRaw[1] * gyroScale;
    gyro[2] = gyroRaw[2] * gyroScale;
}

float MPU6050SI::getAccelerationX() {
    return acceleration[0];
}

float MPU6050SI::getAccelerationY() {
    return acceleration[1];
}

float MPU6050SI::getAccelerationZ() {
    return acceleration[2];
}

float MPU6050SI::getGyroX() {
    return gyro[0];
}

float MPU6050SI::getGyroY() {
    return gyro[1];
}

float MPU6050SI::getGyroZ() {
    return gyro[2];
}
