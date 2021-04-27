#include<SoftwareSerial.h>

SoftwareSerial TestSerial(10, 11);

int tokyo[9] = {22, 23, 24, 25, 26, 27, 28, 29, 30};
int columbia[3] = {31, 32, 33};
int paris[9] = {34, 35, 36, 37, 38, 39, 40, 41, 42};
int rome[9] = {43, 44, 45, 46, 47, 48, 49, 50, 51};

void setup() {
  for (int i = 22; i <= 39; i++) {
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
    String player = (String)TestSerial.readString();
    String country = (String)TestSerial.readString();
    int building = (int)TestSerial.read();
    char sell = (char)TestSerial.read();
    if( sell == 'n'){
      ledOn(player, country, building);
    }
    else if( sell == 'y'){
      ledOff(country);
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

void ledOn(String player, String country, int building){
  if(country == "tokyo"){
    tokyo(player, building);
  } else if (country == "coulmbia"){
    columbia(player, building);
  } else if(country == "paris"){
    paris(player, building);
  } else{
    rome(player, building);
  }
}

void ledOff(String coutry){
  
}

void tokyo(String player, int building) {
}

void columbia(String player, int building) {
}

void paris(String player, int building) {
}

void rome(String player, int building){
}
