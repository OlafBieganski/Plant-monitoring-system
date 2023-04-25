#include <dht11.h>
#include <Wire.h>
#include <BH1750.h>

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
  Serial.print("H ");
  Serial.print(float(DHT11.humidity));
  Serial.print(" ");
  Serial.print((float)DHT11.temperature);
  Serial.print(" ");
  Serial.print(analogRead(GROUND_SENSOR));
  Serial.print(" ");
  Serial.print(lightMeter.readLightLevel());
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
