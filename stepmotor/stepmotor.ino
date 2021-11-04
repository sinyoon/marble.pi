#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_Stepper ystep(200, 1);
AF_Stepper xstep(200, 2);
SoftwareSerial MainboardSerial(A0, A1);

bool inited = false;
int i = 0;
int blank = 0;
String moveData = "";
int fx = 0;
int fy = 0;

void setup() {

  Serial.begin(9600);           // set up Serial library at 9600 bps
  MainboardSerial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, OUTPUT);
  reset();
}

void loop() {
  if(MainboardSerial.available()){ // 현재 말의 위치(땅 좌표) | 말의 목적지(땅 좌표) | 플레이어 정보
    moveData = MainboardSerial.readStringUntil('\n');
    String currentLocation = slicing();
    String destination = slicing();
    int player = slicing().toInt();
    sendDistance(currentLocation);
    sendDistance(destination);
  }
  delay(1000);
}

void movexstep(int dir){
  if(dir < 0){
    for (int j = 0; j < (dir * -1);j++){
      for (i=0; i<1003; i++) {
        xstep.step(1, FORWARD, INTERLEAVE);
    
        delay(2);
      }
    }
  } else {
    for (int j = 0; j < dir; j++){
      for (i=0; i<1003; i++) {
        xstep.step(1, BACKWARD, INTERLEAVE);
    
        delay(2);
      }
    }
  }
  MainboardSerial.println("start");
}

void moveystep(int dir){
  if(dir < 0){
    for (int j = 0; j < (dir * -1);j++){
      for (i=0; i<1003; i++) {
        ystep.step(1, FORWARD, INTERLEAVE);
    
        delay(2);
      }
    }
  } else {
    for (int j = 0; j < dir; j++){
      for (i=0; i<1003; i++) {
        ystep.step(1, BACKWARD, INTERLEAVE);
    
        delay(2);
      }
    }
  }
  MainboardSerial.println("start");
}

void reset(){
  while (!inited) {
    // 초기화

    int xf = digitalRead(A3);
    int yf = digitalRead(A2);
    
    if (xf && yf) {
      inited = true;
      MainboardSerial.println("start");
      return;
    }
    
    if (!xf) xstep.step(1, FORWARD, INTERLEAVE);
    if (!yf) ystep.step(1, FORWARD, INTERLEAVE);

    delay(2);
  }
}

void onMagnet(){
  digitalWrite(A4, HIGH); 
}

void offMagnet(){
  digitalWrite(A4, LOW);
}

String slicing(){
  blank = moveData.indexOf(" ");
  if (blank == -1){
    return moveData;
  }
  String info = moveData.substring(0, blank);
  int dataLength = moveData.length();
  moveData = moveData.substring(blank + 1, dataLength);
  return info;
}

void sendDistance(String data){
  int blank = data.indexOf(',');
  int dataLength = data.length();
  int x = data.substring(0, blank).toInt();
  int y = data.substring(blank + 1, dataLength).toInt();
  movexstep(x - fx); // 목적지 - 현재위치
  moveystep(y - fy);
  fx = x;
  fy = y;
}
