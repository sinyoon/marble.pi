#include<SoftwareSerial.h>

SoftwareSerial StepmotorSerial(12, 13);
SoftwareSerial Serial1(18, 19); // 메인보드 1
SoftwareSerial Serial2(16, 17); // 주사위

bool inited = true;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  StepmotorSerial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  if (StepmotorSerial.available() || Serial1.available()) {
    inited = true;
  }
  if (Serial.available()) {
    inited = false;
    String inString = Serial.readStringUntil('\n');
    int blank = inString.indexOf(' ');
    String first = inString.substring(0, blank);
    
    if( first == "M" ){  
      StepmotorSerial.println(inString);
    } else if( first == "L" ){
      Serial1.println(inString);
    } else if( first == "B"){
      Serial1.println(inString);
    }
  }
  if (inited){
    if (Serial2.available()){
      int diceNum = Serial2.readString().toInt();
      Serial.println(diceNum);
      inited = false;
    }
  }
  delay(1000);

}
