#include<SoftwareSerial.h>
#define MainboardSerial Serial1
#define DiceSerial Serial2

SoftwareSerial StepmotorSerial(12, 13);

void setup() {
  Serial.begin(9600);
  MainboardSerial.begin(9600);
  DiceSerial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  StepmotorSerial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  if (DiceSerial.available()){
    int diceNum = DiceSerial.readString().toInt();
    Serial.println(diceNum);
  }
  if (Serial.available()) {
    String inString = Serial.readStringUntil('\n');
    int blank = inString.indexOf(' ');
    String first = inString.substring(0, blank);
    
    if( first == "M" ){
      StepmotorSerial.println(information);
    } else if( first == "L" ){
      MainboardSerial.println(information);
    } else if( first == "B"){
      MainboardSerial.println(information);
    }
  }
  delay(1000);

}
