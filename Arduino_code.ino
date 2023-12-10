#include <DHT.h>

#define DHTPIN 3      // Pin connected to the DHT11 sensor
#define DHTTYPE DHT11 // DHT sensor type

DHT dht(DHTPIN, DHTTYPE);

const int fanModulePin1 = 5;
const int fanModulePin2 = 7;    // Pin connected to the fan module
const int buzzerPin = 6;      // Pin connected to the buzzer

const int thresholdTemperatureFan = 30;   // First set of temperature threshold for fan
const int thresholdHumidityFan = 80;      // First set of humidity threshold for fan

const int thresholdTemperatureBuzzer = 40; // Second set of temperature threshold for buzzer

void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(fanModulePin1, OUTPUT);
  pinMode(fanModulePin2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity))
  {
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Humidity: ");
    Serial.println(humidity);

    // Check if the temperature and humidity exceed the first set of thresholds for the fan
    if (temperature >= thresholdTemperatureFan || humidity >= thresholdHumidityFan)
    {
      Serial.println("Turning on fan");
      turnOnFan();
    }
    else
    {
      Serial.println("Turning off fan");
      turnOffFan();
    }

    // Check if the temperature and humidity exceed the second set of thresholds for the buzzer
    if (temperature >= thresholdTemperatureBuzzer)
    {
      Serial.println("Activating buzzer");
      activateBuzzer();
    }
    else
    {
      Serial.println("Deactivating buzzer");
      deactivateBuzzer();
    }
  }
  else
  {
    Serial.println("Failed to read from DHT sensor!");
  }

  delay(2000); // Adjust the delay as needed
}

void turnOnFan()
{
  digitalWrite(fanModulePin1, HIGH);
  digitalWrite(fanModulePin2, LOW);
}

void turnOffFan()
{
  digitalWrite(fanModulePin1, LOW);
  digitalWrite(fanModulePin2, LOW);
}

void activateBuzzer()
{
  digitalWrite(buzzerPin, HIGH);
}

void deactivateBuzzer()
{
  digitalWrite(buzzerPin, LOW);
}