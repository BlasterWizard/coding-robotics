int switchPin = 3;
int buttonPin = 2;
int sensorPin = 0;

int lightCal;
int lightVal;

//          red  blue green yellow red blue
int ledPins[] = {13, 12, 11, 10, 9, 8};

int greenPin = 11;
int yellowPin = 10;
int redPinTwo = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin, INPUT);
  pinMode(buttonPin, INPUT);

  lightCal = analogRead(sensorPin);

  //set all ledpins to OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int switchVal = 0;
  int buttonState = 0;

  switchVal = digitalRead(switchPin);
  buttonState = digitalRead(buttonPin);
  lightVal = analogRead(sensorPin);

  //button
  if (switchVal == HIGH) {
    //light up green
    digitalWrite(greenPin, HIGH);
    if (buttonState == LOW) {//if button is pressed
      buttonSequence();
    }
  } else {//photoresistor
    digitalWrite(greenPin, LOW);
    if (lightVal < lightCal - 150) {//dark
      photoresisterSequence();
    } else {
      for (int i = 0; i < 7; i++) {
        digitalWrite(ledPins[i], LOW);
      }
    }

  }
}
void buttonSequence() {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  delay(1000);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPinTwo, HIGH);
  delay(3000);
  digitalWrite(redPinTwo, LOW);
}

void photoresisterSequence() {
  for (int i = 1; i < 7; i++) {
    if (i % 2 != 0) {
      digitalWrite(ledPins[i - 1], HIGH);
      digitalWrite(ledPins[i], HIGH);
      delay(1000);
    }
  }
  for (int i = 0; i < 7; i++) {
    digitalWrite(ledPins[i], LOW);
    delay(1000);
  }

}
