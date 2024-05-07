#include <SoftwareSerial.h>

SoftwareSerial PlantowerSerial(4, 5);  // RX, TX

// Variables to store PM1, PM2.5, and PM10 values
float pm1 = 0.0;
float pm2_5 = 0.0;
float pm10 = 0.0;


void setup() {
  // Initialize serial communication with the Plantower sensor at 9600 baud.
  PlantowerSerial.begin(9600);
  // Initialize the Arduino's serial monitor.
  Serial.begin(9600);
}

void loop() {
  // Check if there's data available to read from the Plantower sensor.
  if (PlantowerSerial.available() >= 32) {  // Check for a complete data packet (32 bytes).
    // Read the data from the sensor into a buffer.
    byte buffer[32];
    PlantowerSerial.readBytes(buffer, 32);

    // Check if the data packet starts with the correct header bytes.
    if (buffer[0] == 0x42 && buffer[1] == 0x4D) {
      // Extract PM1, PM2.5, and PM10 values from the data packet.
      pm1 = ((float)((unsigned int)buffer[10] << 8 | buffer[11]));
      pm2_5 = ((float)((unsigned int)buffer[12] << 8 | buffer[13]));
      pm10 = ((float)((unsigned int)buffer[14] << 8 | buffer[15]));

      // Print the extracted values to the serial monitor in three columns.
      Serial.print("   PM1: ");
      Serial.print(    pm1 );
      Serial.print(" ug/m3\t");

      Serial.print("   PM2.5:  ");
      Serial.print(    pm2_5   );
      Serial.print(" ug/m3\t");

      Serial.print("   PM10:   ");
      Serial.print(   pm10   );
      Serial.println(" ug/m3");
    }
  }
 
  }
