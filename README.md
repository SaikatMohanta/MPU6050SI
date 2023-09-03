# MPU6050SI
TO GET 3 DoF ACCLERATOMETER AND 3 DoF GYRO DATA, IN SI UNIT
Certainly! Let's break down the `MPU6050SI` library I provided earlier in detail to understand how it works.

### MPU6050SI.h

#ifndef MPU6050SI_h
#define MPU6050SI_h

#include <Arduino.h>
#include <Wire.h>


- The `#ifndef`, `#define`, and `#endif` are include guards that prevent the header file from being included multiple times.

- `#include <Arduino.h>` allows you to use standard Arduino functions and types.

- `#include <Wire.h>` includes the Wire library, which is used for I2C communication with the MPU6050 sensor.


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


- `class MPU6050SI` defines a class named `MPU6050SI` that encapsulates the functionality for interfacing with the MPU6050 sensor.

- The public functions and variables include a constructor, initialization function, functions for reading sensor data, and functions for retrieving the sensor data in SI units.

MPU6050SI.cpp

MPU6050SI::MPU6050SI() {
    accelScale = 9.81 / 16384.0; // Sensitivity scale for acceleration (m/s^2 per LSB)
    gyroScale = 3.14159265359 / 180.0 / 131.0; // Sensitivity scale for gyro (rad/s per LSB)
}


- In the constructor, default values for `accelScale` and `gyroScale` are set. These values are used to convert the raw sensor data into SI units. These values are calculated based on the sensor's datasheet.


bool MPU6050SI::begin() {
    Wire.begin();
    Wire.beginTransmission(0x68); // MPU6050 address
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // Wake up the MPU6050 (reset power management)
    Wire.endTransmission();

    return true;
}


- `begin()` is the initialization function. It sets up the I2C communication, wakes up the MPU6050 by writing to the power management register, and returns `true` if initialization is successful.


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


- `writeRegister()` writes a value to a specific register in the MPU6050.

- `readRegisters()` reads a specified number of registers from the MPU6050.


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

- `readData()` reads both accelerometer and gyro data from the sensor. It reads raw data from the sensor, converts it into SI units using the `accelScale` and `gyroScale` values, and stores the results in the `acceleration` and `gyro` arrays.


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


- These functions allow you to retrieve the converted accelerometer and gyro data in SI units for each axis.

Usage
You can include this library in your Arduino sketch and use it to interface with the MPU6050 sensor, retrieve acceleration and gyro data in SI units, and integrate it into your projects that require motion sensing.
