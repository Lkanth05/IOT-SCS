// Define pin connections
const int gasAnalogPin = 34;   // Gas sensor analog pin to GPIO34
const int gasDigitalPin = 35;  // Gas sensor digital pin to GPIO35
const int buzzerPin = 2;       // Buzzer pin to GPIO2

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Set pin modes
  pinMode(gasAnalogPin, INPUT);
  pinMode(gasDigitalPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Read gas sensor values
  int gasAnalogValue = analogRead(gasAnalogPin);
  int gasDigitalValue = digitalRead(gasDigitalPin);
  
  // Print sensor values to the serial monitor
  Serial.print("Gas sensor (Analog) = ");
  Serial.println(gasAnalogValue);
  Serial.print("Gas sensor (Digital) = ");
  Serial.println(gasDigitalValue);
  
  // Determine whether to activate the buzzer based on sensor readings
  if (gasAnalogValue > 400) {
    // Gas level is high, activate buzzer
    tone(buzzerPin, 2000);
    delay(500);
    noTone(buzzerPin);
  } else if (gasDigitalValue == HIGH) {
    // Gas detected by digital pin, activate buzzer
    tone(buzzerPin, 3000);
    delay(500);
    noTone(buzzerPin);
  } else {
    // No conditions met, turn off the buzzer
    noTone(buzzerPin);
  }

  // Add a small delay to avoid flooding the serial monitor
  delay(200);
}
