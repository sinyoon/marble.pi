#include<SoftwareSerial.h>

#define MainboardSerial Serial1

SoftwareSerial Line1Serial(10, 11);
SoftwareSerial Line2Serial(12, 13);
SoftwareSerial Line3Serial(14, 15);
SoftwareSerial Line4Serial(16, 17);

int lnad[11][11] = {
  { "start", "taipei", "golden_key", "beijing", "manila", "jeju_island", "singapore", "golden_key", "cairo", "istanbul", "island"},
  ( "seoul", " ", " ", " ", " ", " ", " ", " ", " ", " ", "athens"},
  ( "welfarefund", " ", " ", " ", " ", " ", " ", " ", " ", " ", "golden_key"},
  ( "new_york", " ", " ", " ", " ", " ", " ", " ", " ", " ", "copenhagen"},
  ( "london", " ", " ", " ", " ", " ", " ", " ", " ", " ", "stockholm"},
  ( "golden_key", " ", " ", " ", " ", " ", " ", " ", " ", " ", "concorde"},
  ( "rome", " ", " ", " ", " ", " ", " ", " ", " ", " ", "bern"},
  ( "paris", " ", " ", " ", " ", " ", " ", " ", " ", " ", "golden_key"},
  ( "columbia", " ", " ", " ", " ", " ", " ", " ", " ", " ", "berlin"},
  ( "tokyo", " ", " ", " ", " ", " ", " ", " ", " ", " ", "athens"},
  ( "spacetravel", "madrid", "queen_elizabeth", "lisbon", "hawaii", "busan", "sydney", "sao_paulo", "golden_key", "buenosaires", "welfarefund"},
}

int cnt = 1;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  MainboardSerial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  
  if (MainboardSerial.available()) {
    String inString = Serial.readStringUntil('\n');
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
      inString = inString.substring(blank + 1, inStringLength);
      sendBuyBuilding(data, inString);
    }
  }
  delay(1000);
}

void setLine(int x, y){
  if(x == 0 && 0 <= y && y < 11){
      Line1Serial.println(land[x][y]);
    } else if(0 <= x && x < 11 && y == 10){
      Line2Serial.println(land[x][y]);
    } else if(x == 10 && 0 <= y && y < 11){
      Line3Serial.println(land[x][y]);
    } else {
      Line4Serial.println(land[x][y]);
    }
}

void split(String inString){
  while(true){
      int blank = inString.indexOf(' ');
      int inStringLength = inString.length();
      if(blank == -1){
        data = inString.toInt();
        sendData(data);
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
  setLine(x, y);
}

void sendBuyBuilding(String data, String inString){
  int blank = data.indexOf(',');
  int dataLength = data.length();
  int x = data.substring(0, blank).toInt();
  int y = data.substring(blank + 1, dataLength).toInt();
  sendtoline(x, y, inString);
}

void sendtoline(int x, int y, String inString){
  if(x == 0 && 0 <= y && y < 11){
      Line1Serial.println(land[x][y] + " " + inString);
    } else if(0 <= x && x < 11 && y == 10){
      Line2Serial.println(land[x][y] + " " + inString);
    } else if(x == 10 && 0 <= y && y < 11){
      Line3Serial.println(land[x][y] + " " + inString);
    } else {
      Line4Serial.println(land[x][y] + " " + inString);
    }
}
