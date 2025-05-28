#include <Arduino_BMI270_BMM150.h> // For Rev2 IMU (accelerometer, gyroscope, magnetometer)
#include <Arduino_HS300x.h>        // For temperature and humidity (Rev2)
#include <Arduino_LPS22HB.h>       // For pressure

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  while (!Serial);    // Wait for serial monitor to open
  Serial.println("Arduino is ready! Type a command (a, g, m, t, h, p)."); // Print a startup message to confirm the Arduino is ready
  // Initialize the IMU (accelerometer, gyroscope, magnetometer)
  if (!IMU_BMI270_BMM150.begin()) { // If IMU initialization fails, print error and stop
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  //if (!HS300x.begin()) {
  //  Serial.println("Failed to initialize temperature and humidity sensor!");
  //  while (1);
  //}
  // Initialize the pressure sensor
  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }
}

void loop() {
  // Check if data is available from the Serial Monitor
  if (Serial.available()) {
    // Read the incoming command character
    char cmd = Serial.read();
   // Process the command using a switch statement
    switch (cmd) {
      case 'a': {
        // Indicate the accelerometer case is triggered
        Serial.println("Case is a: accelerometer");
        float ax, ay, az; // Variables to store acceleration values
        if (IMU_BMI270_BMM150.accelerationAvailable()) {
          IMU_BMI270_BMM150.readAcceleration(ax, ay, az); // Read acceleration data into ax, ay, az
          // Print acceleration values in g units
          Serial.print("Accelerometer (g): X = ");
          Serial.print(ax);
          Serial.print(", Y = ");
          Serial.print(ay);
          Serial.print(", Z = ");
          Serial.println(az);
        }
        break;
      }
      case 'g': {
        // Indicate the gyroscope case is triggered
        Serial.println("Case is g: gyroscope");
        float gx, gy, gz; // Variables to store gyroscope values
        // Check if gyroscope data is available
        if (IMU_BMI270_BMM150.gyroscopeAvailable()) {
          // Read gyroscope data into gx, gy, gz
          IMU_BMI270_BMM150.readGyroscope(gx, gy, gz);
          // Print gyroscope values in degrees per second (dps)
          Serial.print("Gyroscope (dps): X = ");
          Serial.print(gx);
          Serial.print(", Y = ");
          Serial.print(gy);
          Serial.print(", Z = ");
          Serial.println(gz);
        }
        break;
      }
      case 'm': {
        // Indicate the magnetometer case is triggered
        Serial.println("Case is m: magnetometer");
        float mx, my, mz; // Variables to store magnetometer values
        // Check if magnetometer data is available
        if (IMU_BMI270_BMM150.magneticFieldAvailable()) {
          // Read magnetometer data into mx, my, mz
          IMU_BMI270_BMM150.readMagneticField(mx, my, mz);
          // Print magnetometer values in microtesla (uT)
          Serial.print("Magnetometer (uT): X = ");
          Serial.print(mx);
          Serial.print(", Y = ");
          Serial.print(my);
          Serial.print(", Z = ");
          Serial.println(mz);
        }
        break;
      }
      case 't': {
        // Indicate the temperature case is triggered
        Serial.println("Case is t: temperature");
        float temperature = HS300x.readTemperature(); // Read pressure value
        // print temperature in C
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");
        break;
      }
      case 'h': {
        // Indicate the humidity case is triggered
        Serial.println("Case is h: humidity");
        float humidity = HS300x.readHumidity(); // Read pressure value
        // print humidity
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
        break;
      }
      case 'p': {
        // Indicate the pressure case is triggered
        Serial.println("Case is p: pressure");
        float pressure = BARO.readPressure(); // Read pressure value
        // Print pressure value in hectopascals (hPa)
        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.println(" hPa");
        break;
      }
    }
  }
}