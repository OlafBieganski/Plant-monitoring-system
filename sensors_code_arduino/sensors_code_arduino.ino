#include <dht11.h>
#include <Wire.h>
#include <BH1750.h>

template <typename T> 
void valueToBytes(T value, uint8_t *bytes){
    // Typecast the value to a byte pointer
    uint8_t *valueBytes = (uint8_t*)&value;

    // Copy the bytes from the value to the byte array
    for (int i = 0; i < sizeof(T); i++) {
        bytes[i] = valueBytes[i];
    }
}

uint8_t calculateCRC8(const uint8_t *data, uint32_t size) {
    uint8_t crc = 0x00;
    uint8_t polynomial = 0x07;
    for (uint32_t i = 0; i < size; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

dht11 DHT11;
BH1750 lightMeter;

#define DHT11PIN 2
#define GROUND_SENSOR A0

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  /*Serial.println(F("BH1750 Test"));
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();*/
}

void loop()
{
  //Serial.println("\n");

  int chk = DHT11.read(DHT11PIN);
  int ground = analogRead(GROUND_SENSOR);
  int sunlight = lightMeter.readLightLevel();
  float temperature = (float)DHT11.temperature;
  float humidity = float(DHT11.humidity);

  uint8_t temperatureBytes[sizeof(float)];
  valueToBytes<float>(temperature, temperatureBytes);

  uint8_t humidityBytes[sizeof(float)];
  valueToBytes<float>(humidity, humidityBytes);

  uint8_t groundBytes[sizeof(int)];
  valueToBytes<int>(ground, groundBytes);

  uint8_t sunlightBytes[sizeof(int)];
  valueToBytes<int>(sunlight, sunlightBytes);

  int bytesAmount = 2*sizeof(float) + 2*sizeof(int);
  uint8_t dataCRC[bytesAmount];
  memcpy(dataCRC, temperatureBytes, sizeof(float));
  memcpy(dataCRC + sizeof(float), humidityBytes, sizeof(float));
  memcpy(dataCRC + sizeof(float), groundBytes, sizeof(int));
  memcpy(dataCRC + sizeof(int), sunlightBytes, sizeof(int));

  uint8_t crc8 = calculateCRC8(dataCRC, bytesAmount);
  
  Serial.print("H ");
  Serial.print(bytesAmount);
  Serial.print(" ");
  Serial.print(temperature);
  Serial.print(" ");
  Serial.print(humidity);
  Serial.print(" ");
  Serial.print(ground);
  Serial.print(" ");
  Serial.print(sunlight);
  Serial.print(" ");
  Serial.print(crc8);
  Serial.print(" T");
  Serial.print("\n");

  //Serial.print("Read sensor: ");
  /*switch (chk)
  {
    case DHTLIB_OK: 
    Serial.println("OK"); 
  }*/

  /*Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (°C): ");
  Serial.println((float)DHT11.temperature, 2);

  Serial.print("Ground humidity: ");
  Serial.println(analogRead(GROUND_SENSOR));

  Serial.print("Sunlihgt level (lux): ");
  Serial.println(lightMeter.readLightLevel());*/

  delay(1000);
}
