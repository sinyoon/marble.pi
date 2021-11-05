#include<SoftwareSerial.h>

SoftwareSerial Line1Serial(10, 11);
SoftwareSerial Line2Serial(12, 13);
int cnt = 1;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  Serial1.begin(9600); // 메안
  Serial2.begin(9600); // line4
  Serial3.begin(9600); // line3
  Line1Serial.begin(9600);
  Line2Serial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  
  if (Serial1.available()) {
    String inString = Serial1.readStringUntil('\n');
    int inStringLength = inString.length();
    int blank = inString.indexOf(' ');
    String first = inString.substring(0, blank);
    if (first == "B"){
      inString = inString.substring(blank + 1, inStringLength);
      split(inString);
    }
    if (first == "L"){
      inString = inString.substring(blank + 1, inStringLength);
      blank = inString.indexOf(' ');
      String data = inString.substring(0, blank);
      sendBuyBuilding(data, inString);
    }
  }
}

void setLine(int x, int y, String data){
  if(x == 0 && 0 <= y && y < 11){
      Line1Serial.println(data);
    } else if(0 <= x && x < 11 && y == 10){
      Line2Serial.println(data);
    } else if(x == 10 && 0 <= y && y < 11){
      Serial3.println(data);
    } else {
      Serial2.println(data);
    }
}

void split(String inString){
  while(true){
      int blank = inString.indexOf(' ');
      int inStringLength = inString.length();
      if(blank == -1){
        sendData(inString);
        Serial1.println("start");
        break;
      }
      String data = inString.substring(0, blank);
      sendData(data);
      inString = inString.substring(blank + 1, inStringLength);
      delay(100);
  }
}

void sendData(String data){
  int blank = data.indexOf(',');
  int dataLength = data.length();
  int x = data.substring(0, blank).toInt();
  int y = data.substring(blank + 1, dataLength).toInt();
  setLine(x, y, data);
}

void sendBuyBuilding(String data, String inString){
  int blank = data.indexOf(',');
  int dataLength = data.length();
  int x = data.substring(0, blank).toInt();
  int y = data.substring(blank + 1, dataLength).toInt();
  sendtoline(x, y, inString);
  Serial1.println("start");
}

void sendtoline(int x, int y, String inString){
  if(x == 0 && 0 <= y && y < 11){
      Line1Serial.println(inString);
    } else if(0 <= x && x < 11 && y == 10){
      Line2Serial.println(inString);
    } else if(x == 10 && 0 <= y && y < 11){
      Serial3.println(inString);
    } else {
      Serial2.println(inString);
    }
}
