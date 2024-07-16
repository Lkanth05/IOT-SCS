const int analogInPin = A0;
const int sensorBuzzerPin = 2; // Buzzer pin for both sensors

const int flamepin = A2;  // Flame sensor pin
const int threshold = 200; // Threshold value for flame sensor

int sensorValue = 0;
int flamesensvalue = 0;

void setup() {
  pinMode(analogInPin, INPUT);
  pinMode(sensorBuzzerPin, OUTPUT);
  
  pinMode(flamepin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Water level sensor code
  sensorValue = analogRead(analogInPin);
  Serial.print("Water sensor = ");
  Serial.println(sensorValue);

  // Flame sensor code
  flamesensvalue = analogRead(flamepin); // reads analog data from flame sensor
  Serial.print("Flame sensor = ");
  Serial.println(flamesensvalue);
  
  // Determine whether to activate the buzzer based on sensor readings
  if (sensorValue >= 100 && sensorValue <= 600) {
    Serial.println("Water level in range, activating buzzer at 1000 Hz");
    tone(sensorBuzzerPin, 1000);
    delay(100);
    noTone(sensorBuzzerPin);
  } else if (sensorValue >= 601 && sensorValue <= 625) {
    Serial.println("Water level in range, activating buzzer at 2000 Hz");
    tone(sensorBuzzerPin, 2000);
    delay(100);
    noTone(sensorBuzzerPin);
  } else if (sensorValue >= 626 && sensorValue <= 700) {
    Serial.println("Water level in range, activating buzzer at 3000 Hz");
    tone(sensorBuzzerPin, 3000);
    delay(100);
    noTone(sensorBuzzerPin);
  } else if (flamesensvalue <= threshold) {
    Serial.println("Flame detected, activating buzzer at 100 Hz for 1 second");
    tone(sensorBuzzerPin, 100);
    delay(1000);
    noTone(sensorBuzzerPin);
  } else {
    Serial.println("No sensor conditions met, turning off buzzer");
    noTone(sensorBuzzerPin);
    delay(100);
  }
}
