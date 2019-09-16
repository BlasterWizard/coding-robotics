//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

int buttonPin = 3;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(buttonPin, INPUT);

}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if(buttonState == LOW){
    song();
  }
}

void lightShiftPinA(int p) {
  int pin;
  pin = 1 << p;
  shiftOut(dataPin, clockPin, pin);

}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (int i = 7; i >= 0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1 << i) ) {
      pinState = 1;
    }
    else {
      pinState = 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

void blinkAllLights(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}

void oneByOne(int delayTime, String directionWay) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  for (int j = 0; j < 8; j++) {
    digitalWrite(latchPin, 0);
    if (directionWay == "UP") {
      lightShiftPinA(7 - j);
      lightShiftPinA(j);
    } else if (directionWay == "DOWN") {
      lightShiftPinA(j);
      lightShiftPinA(7 - j);
    } else if (directionWay == "SAMEUP") {
      lightShiftPinA(j);
      lightShiftPinA(j);
    } else if (directionWay == "SAMEDOWN") {
      lightShiftPinA(7 - j);
      lightShiftPinA(7 - j);
    }
    digitalWrite(latchPin, 1);
    delay(delayTime);

  }
}

void skip(int delayTime, String directionWay) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  for (int i = 0; i < 8; i++) {
    digitalWrite(latchPin, 0);
    if (directionWay == "UP") {
      if (i % 2 != 0) {
        lightShiftPinA(7 - i);
        lightShiftPinA(i);
      }
    } else if (directionWay == "DOWN") {
      if (i % 2 != 0) {
        lightShiftPinA(i);
        lightShiftPinA(7 - i);
      }
    }
    digitalWrite(latchPin, 1);
    delay(delayTime);
  }
}

void oneThree(){
  blinkAllLights(1, 390);
  blinkAllLights(3, 120);
  delay(200);
  blinkAllLights(3, 120);
}

void oddsAllOn(int numOfTimes){
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  for(int i = 0; i < 8; i++){
    if(i % 2 != 0){
      digitalWrite(latchPin, 0);
      lightShiftPinA(i);
      lightShiftPinA(7 - i);
      digitalWrite(latchPin, 1);
      delay(300);
    }
  }
}

void riff(int delayTime){
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  int sum = 0;
  for(int i = 0; i < 8; i++){
    digitalWrite(latchPin, 0);
    sum += pow(2, i);
    shiftOut(dataPin, clockPin, sum);
    shiftOut(dataPin, clockPin, sum);
    digitalWrite(latchPin, 1);
    delay(delayTime);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(delayTime);
  }
 sum = 255;
 for(int i = 0; i < 8; i++){
    digitalWrite(latchPin, 0);
    sum -= pow(2, i);
    shiftOut(dataPin, clockPin, sum);
    shiftOut(dataPin, clockPin, sum);
    digitalWrite(latchPin, 1);
    delay(delayTime);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(delayTime);
 }
 sum = 255;
 for(int i = 8; i > 0; i--){
    digitalWrite(latchPin, 0);
    sum -= pow(2, i - 1);
    shiftOut(dataPin, clockPin, sum);
    shiftOut(dataPin, clockPin, sum);
    digitalWrite(latchPin, 1);
    delay(delayTime);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(delayTime);
    
 }
}

void song(){
  skip(350, "UP");
  skip(350, "DOWN");
  for(int i = 0; i < 2; i++){
    oneThree();
    delay(200);
    oneByOne(120, "UP");
    oneByOne(120, "DOWN");
    oneThree();
    oneByOne(285, "SAMEDOWN");
    oneThree();
    oneByOne(285, "SAMEUP");
    oneThree();
    skip(135, "UP");
    oddsAllOn(2);
  }
  riff(250);
}




