int sensorPin = A0;    // select the input pin for the potentiometer
int analogValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  analogValue = analogRead(sensorPin);
  Serial.println(analogValue);
  delay(1000);
}
