const int numSensors = 3; // Number of ultrasonic sensors
const int trigPins[numSensors] = {2, 4, 6}; // Trig pin for each sensor
const int echoPins[numSensors] = {3, 5, 7}; // Echo pin for each sensor
const int ledPins[numSensors] = {8, 9, 10}; // LED pin for each sensor
const int parkingThreshold = 20; // Adjust this value based on your parking lot size

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < numSensors; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(trigPins[i], LOW); // Ensure trig pins start low
  }
}

void loop() {
  for (int i = 0; i < numSensors; i++) {
    long duration, distance;
    
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);
    
    duration = pulseIn(echoPins[i], HIGH);
    distance = duration * 0.034 / 2;
    
    if (distance < parkingThreshold) {
      // Parking spot occupied
      digitalWrite(ledPins[i], HIGH); // Turn on LED
    } else {
      // Parking spot available
      digitalWrite(ledPins[i], LOW); // Turn off LED
    }
    
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.print("   ");
  }
  
  Serial.println(); // Move to the next line in the serial monitor
  delay(1000); // Adjust the delay as needed for your application
}
