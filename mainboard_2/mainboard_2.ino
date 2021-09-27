#include<SoftwareSerial.h>

SoftwareSerial MainboardSerial(18, 19);
SoftwareSerial RaspiSerial(10, 11);
SoftwareSerial StepmotorSerial(12, 13);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  MainboardSerial.begin(9600);
}

void sendPositionInfo(String information){
  while(true){
      int blank = information.indexOf(' ');
      int inStringLength = information.length();
      if(blank == -1){
        int lastInformation = information.toInt();
        MainboardSerial.println(lastInformation);
        break;
      }
      String first = information.substring(0, blank);
      int positionInfo = first.toInt();
      information = information.substring(blank + 1, inStringLength);
      StepmotorSerial.println(positionInfo);
      delay(100);
    }
}

void sendBuildingInfo(String information){
  while(true){
      int blank = information.indexOf(' ');
      int inStringLength = information.length();
      if(blank == -1){
        int lastInformation = information.toInt();
        MainboardSerial.println(lastInformation);
        break;
      }
      String first = information.substring(0, blank);
      int buildingInfo = first.toInt();
      information = information.substring(blank + 1, inStringLength);
      MainboardSerial.println(buildingInfo);
      delay(100);
  }
}

void loop() { //코드를 무한반복합니다.
  
  if (RaspiSerial.available()) {
    String inString = RaspiSerial.readStringUntil('\n');
    int blank = inString.indexOf(' ');
    int inStringLength = inString.length();
    String first = inString.substring(0, blank);
    inString = inString.substring(blank + 1, inStringLength);
    
    if( first == "M" ){
      sendPositionInfo(inString);
    }
    else if( first == "L" ){
      sendBuildingInfo(inString);
    }
  }
  delay(1000);

}
