#include <MPU6050SI.h>

MPU6050SI mpu;

void setup() {
    Serial.begin(9600);

    if (mpu.begin()) {
        Serial.println("MPU6050 initialized successfully!");
    } else {
        Serial.println("Failed to initialize MPU6050.");
        while (1);
    }
}

void loop() {
    mpu.readData();

    Serial.print("Acceleration (m/s^2): ");
    Serial.print(mpu.getAccelerationX());
    Serial.print(", ");
    Serial.print(mpu.getAccelerationY());
    Serial.print(", ");
    Serial.print(mpu.getAccelerationZ());
    Serial.print(" | Gyro (rad/s): ");
    Serial.print(mpu.getGyroX());
    Serial.print(", ");
    Serial.print(mpu.getGyroY());
    Serial.print(", ");
    Serial.println(mpu.getGyroZ());

    delay(1000);
}
