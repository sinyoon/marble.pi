#include<SoftwareSerial.h>

SoftwareSerial Line1Serial(10, 11);
SoftwareSerial Line2Serial(12, 13);
SoftwareSerial Line3Serial(14, 15);
SoftwareSerial Line4Serial(16, 17);
SoftwareSerial MainboardSerial(18, 19);

int cnt = 1;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  MainboardSerial.begin(9600);
}

void setLine(int buildingNum, int player){
  if(1 <= buildingNum && buildingNum <= 8){
      Line1Serial.println(player);
      Line1Serial.println(buildingNum); 
    } else if(9 <= buildingNum && buildingNum <= 18){
      Line2Serial.println(player);
      Line2Serial.println(buildingNum);
    } else if(19 <= buildingNum && buildingNum <= 28){
      Line3Serial.println(player);
      Line3Serial.println(buildingNum);
    } else {
      Line4Serial.println(player);
      Line4Serial.println(buildingNum);
    }
}

void loop() { //코드를 무한반복합니다.
  
  if (MainboardSerial.available()) {
    if(cnt == 1){
      int player = (int)MainboardSerial.read();
      cnt++;
    } else {
      int information = (int)MainboardSerial.read();
      if(information == 0){
        cnt = 1;
      }
      setLine(information, player);
    }
  }
  delay(1000);

}
