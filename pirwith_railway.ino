#define RED_A 9
#define GREEN_A 10
#define RED_B 11
#define GREEN_B 12
#define PIR_SENSOR 7 // Define the PIR sensor pin

void setup() {
  pinMode(RED_A, OUTPUT);
  pinMode(GREEN_A, OUTPUT);
  pinMode(RED_B, OUTPUT);
  pinMode(GREEN_B, OUTPUT);
  pinMode(PIR_SENSOR, INPUT); // Set the PIR sensor pin as input
  Serial.begin(9600);
}

void loop() {
  int motionDetected = digitalRead(PIR_SENSOR); // Read PIR sensor state

  if (motionDetected == HIGH) {
    Serial.println("Motion detected! Activating train signals.");

    // Train A starts, Train B stops
    digitalWrite(RED_A, LOW);
    digitalWrite(GREEN_A, HIGH);
    digitalWrite(RED_B, HIGH);
    digitalWrite(GREEN_B, LOW);
    Serial.println("Train on Side A is starting. Side B is stopping.");
    delay(2000);

    // Train B starts, Train A stops
    digitalWrite(RED_A, HIGH);
    digitalWrite(GREEN_A, LOW);
    digitalWrite(RED_B, LOW);
    digitalWrite(GREEN_B, HIGH);
    Serial.println("Train on Side B is starting. Side A is stopping.");
    delay(2000);

    // Both trains stop
    digitalWrite(RED_A, HIGH);
    digitalWrite(GREEN_A, LOW);
    digitalWrite(RED_B, HIGH);
    digitalWrite(GREEN_B, LOW);
    Serial.println("Both trains are stopped.");
    delay(4000);
  } else {
    Serial.println("No motion detected. All trains are stopped.");
    digitalWrite(RED_A, HIGH);
    digitalWrite(GREEN_A, LOW);
    digitalWrite(RED_B, HIGH);
    digitalWrite(GREEN_B, LOW);
    delay(2000);
  }
}