#include<SoftwareSerial.h>

SoftwareSerial LineSerial(10, 11);

int london[9] = {22, 23, 24, 25, 26, 27, 28, 29, 30};
int newyork[9] = {31, 32, 33, 34, 35, 36, 37, 38, 39};
int seoul[3] = {40, 41, 42};

void setup() {
  for (int i = 22; i <= 42; i++) {
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
  if (LineSerial.available()) {
    String player = (String)TestSerial.readString();
    String country = (String)TestSerial.readString();
    int building = (int)TestSerial.read();
    char sell = (char)TestSerial.read();
    if( sell == 'n'){
      ledOn(player, country, building);
    }
    else if( sell == 'y'){
      player = "ledOff";
      ledOn(player, country, building);
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

void ledOff(int redPin, int greenPin, int bluePin){
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void ledOn(String player, String country, int building){
  if(country == "london"){
    london(player, building);
  } else if (country == "newyork"){
    newyork(player, building);
  } else{
    seoul(player);
  }
}

void london(String player, int building) {
  if(player == "red"){
    redPlayer(22+building, 23+building, 24+building);
  } else if (player == "green"){
    greenPlayer(22+building, 23+building, 24+building);
  } else if(player == "blue"){
    bluePlayer(22+building, 23+building, 24+building);
  } else if(player =="yellow"){
    yellowPlayer(22+building, 23+building, 24+building);
  } else {
    ledOff(22+building, 23+building, 24+building);
  }
}

void newyork(String player, int building) {
  if(player == "red"){
    redPlayer(31+building, 32+building, 33+building);
  } else if (player == "green"){
    greenPlayer(31+building, 32+building, 33+building);
  } else if(player == "blue"){
    bluePlayer(31+building, 32+building, 33+building);
  } else if(player =="yellow"){
    yellowPlayer(31+building, 32+building, 33+building);
  } else {
    ledOff(31+building, 32+building, 33+building);
  }
}

void seoul(String player) {
  if(player == "red"){
    redPlayer(40, 41, 42);
  } else if (player == "green"){
    greenPlayer(40, 41, 42);
  } else if(player == "blue"){
    bluePlayer(40, 41, 42);
  } else if(player =="yellow"){
    yellowPlayer(40, 41, 42);
  } else {
    ledOff(40, 41, 42);
  }
}
