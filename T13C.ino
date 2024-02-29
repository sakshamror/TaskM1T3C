const int temperatureSensorPin = A0;  // Analog pin for temperature sensor simulation
const int motionSensorPin = 2;        // Digital pin for motion sensor simulation
const int ledPinTemperature = 3;      // Digital pin for temperature LED
const int ledPinMotion = 7;           // Digital pin for motion LED

volatile bool motionDetected = false;

void setup() {
  Serial.begin(9600);

  pinMode(ledPinTemperature, OUTPUT);
  pinMode(ledPinMotion, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(motionSensorPin), motionInterrupt, RISING);
}

void loop() {
  // Simulate temperature reading (adjust the values as needed)
  int sensorValue = analogRead(temperatureSensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureCelsius = (voltage - 0.5) * 100.0;

  Serial.print("Temperature: ");
  Serial.print(temperatureCelsius);
  Serial.println(" °C");

  // Check if the temperature is higher than 20 degrees Celsius
  if (temperatureCelsius > 20.0) {
    digitalWrite(ledPinTemperature, HIGH);
    Serial.println("Temperature LED ON");
  } else {
    digitalWrite(ledPinTemperature, LOW);
    Serial.println("Temperature LED OFF");
  }

  // Check if motion is detected
  if (motionDetected) {
    handleMotionEvent();
  }

  delay(1000);
}

void motionInterrupt() {
  motionDetected = true;
}

void handleMotionEvent() {
  // Update the LED for motion sensor
  digitalWrite(ledPinMotion, HIGH);
  
  // Print a message for monitoring
  Serial.println("Motion Detected!");
  
  // Wait for a while to simulate a delay
  delay(5000);
  
  // Turn off the LED for motion sensor after the delay
  digitalWrite(ledPinMotion, LOW);

  // Reset the motion detection flag
  motionDetected = false;
}
