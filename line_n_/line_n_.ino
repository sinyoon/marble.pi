#include<SoftwareSerial.h>

SoftwareSerial TestSerial(10, 11);

void setup() {
  for (int i = 42; i <= 53; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }


  Serial.println("Hello World!");

  //블루투스와 아두이노의 통신속도를 9600으로 설정
  TestSerial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  if (TestSerial.available()) {
    char a = (char)TestSerial.read();
    char b = (char)TestSerial.read();
    Serial.println(b);
    if(a == '1'){
      newyork(b);
    }
  }
  delay(1000);
}

void redPlayer(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void greenPlayer(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void bluePlayer(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

void yellowPlayer(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void newyork(int player) {
  switch(player){
    case '1':
      redPlayer(46, 44, 42);
      break;
    case '2':
      greenPlayer(46, 44, 42);
      break;
    case '3':
      bluePlayer(46, 44, 42);
      break;
    case '4':
      yellowPlayer(46, 44, 42);
      break;
  }
}
