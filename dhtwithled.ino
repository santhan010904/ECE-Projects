#include <dht.h>

// Define the pin where the DHT sensor is connected
#define DHT_PIN 9
#define LED_PIN 13 // Internal LED pin
dht DHT; // Create an instance of the dht class

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
}

void loop() {
  int chk = DHT.read11(DHT_PIN); // Use read11() for DHT11 or read22() for DHT22

  // Check the status of the DHT sensor reading
  if (chk == DHTLIB_OK) {
    Serial.println("DHT sensor reading successful!");

    // Blink the internal LED to indicate a successful reading
    digitalWrite(LED_PIN, HIGH); // Turn the LED ON
    Serial.println("LED is ON (indicating successful reading)");
    delay(200); // LED ON for 200 milliseconds
    digitalWrite(LED_PIN, LOW); // Turn the LED OFF
    Serial.println("LED is OFF");

    // Print humidity and temperature
    Serial.print("Humidity: ");
    Serial.print(DHT.humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(DHT.temperature);
    Serial.println(" *C");

    // Use if-else statements to categorize temperature
    if (DHT.temperature < 20) {
      Serial.println("It's quite cold!");
    } else if (DHT.temperature >= 20 && DHT.temperature <= 30) {
      Serial.println("The temperature is comfortable.");
    } else {
      Serial.println("It's quite hot!");
    }

    // Use if-else statements to categorize humidity
    if (DHT.humidity < 30) {
      Serial.println("The air is dry.");
    } else if (DHT.humidity >= 30 && DHT.humidity <= 60) {
      Serial.println("Humidity levels are optimal.");
    } else {
      Serial.println("It's very humid!");
    }
  } else {
    // Handle error codes
    if (chk == DHTLIB_ERROR_CHECKSUM) {
      Serial.println("Error: Checksum error.");
    } else if (chk == DHTLIB_ERROR_TIMEOUT) {
      Serial.println("Error: Timeout error.");
    } else {
      Serial.println("Error: Unknown error.");
    }

    // Blink the LED twice to indicate an error
    for (int i = 0; i < 2; i++) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED is ON (indicating error)");
      delay(200);
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED is OFF");
      delay(200);
    }
  }

  // Wait 2 seconds before the next reading
  delay(2000);
}
