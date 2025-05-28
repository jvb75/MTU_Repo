#include <math.h> // For atan and sqrt functions

float calculateAngle(float x, float y, float z) {
    float angle = 0;

    // Apply calibration (assuming calibrated values are the inputs)
    float ax1 = x; // Calibrated X acceleration
    float ay1 = y; // Calibrated Y acceleration
    float az1 = z; // Calibrated Z acceleration

    // Calculate pitch using Equation 6
    angle = atan2(ax1, sqrt(pow(ay1, 2) + pow(az1, 2))) * 180.0 / PI;

    return angle;
}

void setup() {
    Serial.begin(9600); // Start serial communication at 9600 baud
}

void loop() {
    // Simulated accelerometer readings (replace with actual I2C readings)
    float x = 0.0;  // Example: X acceleration in g
    float y = 0.0;  // Example: Y acceleration in g
    float z = -1.0; // Example: Z acceleration in g (gravity downward when level)

    // Calculate pitch angle
    float pitch = calculateAngle(x, y, z);

    // Print the pitch angle
    Serial.print("Pitch: ");
    Serial.print(pitch);
    Serial.println(" degrees");

    // Delay for 1 second (1000 ms) or 0.2 seconds (200 ms) for 5 times per second
    delay(1000); // Change to 200 for 5 times per second
}