#include <SoftwareSerial.h>
#include <DHT.h>

#define HM10_TX 2      // HM-10 TX to Arduino D2
#define HM10_RX 3      // HM-10 RX to Arduino D3
#define LED_PIN 4      // LED connected to D4
#define DHT_PIN 5      // DHT sensor data pin connected to D5
#define DHT_TYPE DHT11 // Change to DHT22 if using a DHT22 sensor

SoftwareSerial mySerial(HM10_TX, HM10_RX); // RX, TX
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(9600);   // Serial Monitor
    mySerial.begin(9600); // HM-10 Bluetooth
    dht.begin();
    
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);  // Ensure LED is OFF initially

    Serial.println("HM-10 Bluetooth Module with DHT Sensor Ready");
}

void loop() {
    static unsigned long lastDHTRead = 0;

    // Check for Bluetooth command
    if (mySerial.available()) {
        String received = mySerial.readString();
        received.trim();  // Remove spaces/newline characters
        Serial.print("Received: ");
        Serial.println(received);

        if (received == "1") {
            digitalWrite(LED_PIN, HIGH);  // Turn LED ON
            Serial.println("LED ON");
            delay(1000);  // Keep LED ON for 1 second
            digitalWrite(LED_PIN, LOW);   // Turn LED OFF
            Serial.println("LED OFF");
        }
    }

    // Send DHT sensor data every 5 seconds
    if (millis() - lastDHTRead >= 5000) {
        lastDHTRead = millis();

        float temperature = dht.readTemperature(); // Celsius
        float humidity = dht.readHumidity();

        if (isnan(temperature) || isnan(humidity)) {
            Serial.println("Failed to read from DHT sensor!");
            mySerial.println("DHT Error");
        } else {
            String data = "Temp: " + String(temperature) + "°C | Humidity: " + String(humidity) + "%";
            Serial.println(data);
            mySerial.println(data); // Send over Bluetooth
        }
    }
}
