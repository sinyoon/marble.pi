#include<SoftwareSerial.h>

SoftwareSerial MainboardSerial(18, 19);
SoftwareSerial RaspiSerial(10, 11);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  MainboardSerial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  
  if (RaspiSerial.available()) {
    String inString = RaspiSerial.readStringUntil('\n');
    while(true){
      int blank = inString.indexOf(' ');
      int inStringLength = inString.length();
      if(blank == -1){
        int lastInformation = inString.toInt();
        MainboardSerial.println(lastInformation);
        break;
      }
      String first = inString.substring(0, blank);
      int information = first.toInt();
      inString = inString.substring(blank + 1, inStringLength);
      MainboardSerial.println(information);
      delay(100);
    }
  }
  delay(1000);

}
