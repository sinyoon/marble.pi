#include<SoftwareSerial.h>

SoftwareSerial TestSerial(10, 11);

void setup() {
  for (int i = 22; i <= 45; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);


  Serial.println("Hello World!");
}

void loop() { //코드를 무한반복합니다.
  for (int i = 22; i <= 43; i+=3) {
    if(i == 31){
      i = 34;
    }
    red(i, i + 1, i + 2);
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  for (int i = 22; i <= 43; i+=3) {
    if(i == 31){
      i = 34;
    }
    green(i, i + 1, i + 2);
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  for (int i = 22; i <= 43; i+=3) {
    if(i == 31){
      i = 34;
    }
    blue(i, i + 1, i + 2);
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  for (int i = 22; i <= 43; i+=3) {
    if(i == 31){
      i = 34;
    }
    yellow(i, i + 1, i + 2);
    Serial.println(i);
    delay(100);
  }
  delay(1000);
}

void red(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void green(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void blue(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

void yellow(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}
