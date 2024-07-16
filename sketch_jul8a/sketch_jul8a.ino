const int analogInPin = A0; // Gas sensor analog pin
const int gasDigitalPin = 8; // Gas sensor digital pin
const int sensorBuzzerPin = 2; // Buzzer pin for both sensors

const int flamepin = A2;  // Flame sensor pin
const int threshold = 200; // Threshold value for flame sensor

int gasSensorAnalogValue = 0;
int gasSensorDigitalValue = 0;
int flamesensvalue = 0;

void setup() {
  pinMode(analogInPin, INPUT);
  pinMode(gasDigitalPin, INPUT);
  pinMode(sensorBuzzerPin, OUTPUT);
  pinMode(flamepin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Gas sensor code
  gasSensorAnalogValue = analogRead(analogInPin);
  gasSensorDigitalValue = digitalRead(gasDigitalPin);
  Serial.print("Gas sensor (Analog) = ");
  Serial.println(gasSensorAnalogValue);
  Serial.print("Gas sensor (Digital) = ");
  Serial.println(gasSensorDigitalValue);

  // Flame sensor code
  flamesensvalue = analogRead(flamepin); // reads analog data from flame sensor
  Serial.print("Flame sensor = ");
  Serial.println(flamesensvalue);
  
  // Determine whether to activate the buzzer based on sensor readings
  if (gasSensorAnalogValue >= 100 && gasSensorAnalogValue <= 600) {
    // Gas level is in range, activate buzzer at 1000 Hz
    tone(sensorBuzzerPin, 1000);
    delay(100);
    noTone(sensorBuzzerPin);
  } else if (gasSensorAnalogValue >= 601 && gasSensorAnalogValue <= 625) {
    // Gas level is in range, activate buzzer at 2000 Hz
    tone(sensorBuzzerPin, 2000);
    delay(100);
    noTone(sensorBuzzerPin);
  } else if (gasSensorAnalogValue >= 626 && gasSensorAnalogValue <= 700) {
    // Gas level is in range, activate buzzer at 3000 Hz
    tone(sensorBuzzerPin, 3000);
    delay(100);
    noTone(sensorBuzzerPin);
  } else if (flamesensvalue <= threshold) {
    // Flame is detected, activate buzzer at 100 Hz for 1 second
    tone(sensorBuzzerPin, 100);
    delay(1000);
    noTone(sensorBuzzerPin);
  } else if (gasSensorDigitalValue == HIGH) {
    // Gas detected by digital pin, activate buzzer at 4000 Hz
    tone(sensorBuzzerPin, 4000);
    delay(500);
    noTone(sensorBuzzerPin);
  } else {
    // No sensor conditions met, turn off the buzzer
    noTone(sensorBuzzerPin);
    delay(100);
  }
}
