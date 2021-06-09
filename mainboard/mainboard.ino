#include<SoftwareSerial.h>

SoftwareSerial Line1Serial(10, 11);
SoftwareSerial Line2Serial(12, 13);
SoftwareSerial Line3Serial(14, 15);
SoftwareSerial Line4Serial(16, 17);
SoftwareSerial MainboardSerial(18, 19);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }


  Serial.println("Hello World!");

  //블루투스와 아두이노의 통신속도를 9600으로 설정
  TestSerial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  
  if (MainboardSerial.available()) {
    int information = (int)MainboardSerial.read();
    Classification(information);
  }
  delay(1000);

}

void Classification(int information){
  int line = ;
  if(line == ){
    Line1Serial.println(information);
  } else if(line == ){
    Line2Serial.println(information);
  } else if(line == ){
    Line3Serial.println(information);
  } else {
    Line4Serial.println(informarion);
  }
}
