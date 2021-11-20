#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_Stepper xstep(200, 1);
AF_Stepper ystep(200, 2);
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
    plocation(player);  
    onMagnet();
    comebackline(player);
    sendDistance(destination);
    plocation(player);
    offMagnet();
    comebackline(player);
  }
}

void movexstep(int dir){
  if(dir < 0){
    for (int j = 0; j < (dir * -1);j++){
      for (i=0; i<936; i++) {
        xstep.step(1, FORWARD, INTERLEAVE);
    
        delay(2);
      }
    }
  } else {
    for (int j = 0; j < dir; j++){
      for (i=0; i<936; i++) {
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
  if( fx == 5 && fx == x && fy != y){
    moveystep(1);
    fx += 1;
  }
  if ( fy == 5 && fy == y && fx != x){
    movexstep(1);
    fy += 1;
  }
  if ( fx == 10 && fx == fy){
    if (abs(y - fy) >= abs(x - fx)){
      movexstep(y - fy);
      moveystep(x - fx);
    } else {
      moveystep(x - fx);
      movexstep(y - fy);
    }
  } else {
    if (fx == 0 || fx == 10){
      movexstep(y - fy); // 목적지 - 현재위치
      moveystep(x - fx);
    } else {
      moveystep(x - fx); // 목적지 - 현재위치
      movexstep(y - fy);
    }
  }
  fx = x;
  fy = y;
}

void plocation(int player){
  if (fx == 0 && 0 < fy && fy < 10){ // 1번라인
    switch(player){
      case 0:
        ystep.step(200, BACKWARD, INTERLEAVE);
        xstep.step(200, BACKWARD, INTERLEAVE);
        break;
      case 1:
        ystep.step(400, BACKWARD, INTERLEAVE);
        xstep.step(200, BACKWARD, INTERLEAVE);
        break;
      case 2:
        ystep.step(200, BACKWARD, INTERLEAVE);
        xstep.step(200, FORWARD, INTERLEAVE);
        break;
      case 3:
        ystep.step(400, BACKWARD, INTERLEAVE);
        xstep.step(200, FORWARD, INTERLEAVE);
        break;
      default:
        break;
    }
  } else if (fy == 10 && 0 < fx && fx < 10){ // 2번 라인
    switch(player){
      case 0:
        xstep.step(200, FORWARD, INTERLEAVE);
        ystep.step(200, BACKWARD, INTERLEAVE);
        break;
      case 1:
        xstep.step(400, FORWARD, INTERLEAVE);
        ystep.step(200, BACKWARD, INTERLEAVE);
        break;
      case 2:
        xstep.step(200, FORWARD, INTERLEAVE);
        ystep.step(200, FORWARD, INTERLEAVE);
        break;
      case 3:
        xstep.step(400, FORWARD, INTERLEAVE);
        ystep.step(200, FORWARD, INTERLEAVE);
        break;
      default:
        break;
    }
  } else if (fx == 10 && 10 > fy && fy > 0){ // 3번 라인
    switch(player){
      case 0:
        ystep.step(200, FORWARD, INTERLEAVE);
        xstep.step(200, FORWARD, INTERLEAVE);
        break;
      case 1:
        ystep.step(400, FORWARD, INTERLEAVE);
        xstep.step(200, FORWARD, INTERLEAVE);
        break;
      case 2:
        ystep.step(200, FORWARD, INTERLEAVE);
        xstep.step(200, BACKWARD, INTERLEAVE);
        break;
      case 3:
        ystep.step(400, FORWARD, INTERLEAVE);
        xstep.step(200, BACKWARD, INTERLEAVE);
        break;
      default:
        break;
    }
  } else if (fy == 0 && 0 < fx && fx < 10){ // 4번 라인
    switch(player){
      case 0:
        xstep.step(200, BACKWARD, INTERLEAVE);
        ystep.step(200, FORWARD, INTERLEAVE);
        break;
      case 1:
        xstep.step(400, BACKWARD, INTERLEAVE);
        ystep.step(200, FORWARD, INTERLEAVE);
        break;
      case 2:
        xstep.step(200, BACKWARD, INTERLEAVE);
        ystep.step(200, BACKWARD, INTERLEAVE);
        break;
      case 3:
        xstep.step(400, BACKWARD, INTERLEAVE);
        ystep.step(200, BACKWARD, INTERLEAVE);
        break;
      default:
        break;
    }
  }
}

void comebackline(int player){
  if (fx == 0 && 0 < fy && fy < 10){ // 1번라인
    switch(player){
      case 0:
        xstep.step(200, FORWARD, INTERLEAVE);
        ystep.step(200, FORWARD, INTERLEAVE);
        break;
      case 1:
        xstep.step(200, FORWARD, INTERLEAVE);
        ystep.step(400, FORWARD, INTERLEAVE);
        break;
      case 2:
        xstep.step(200, BACKWARD, INTERLEAVE);
        ystep.step(200, FORWARD, INTERLEAVE);
        break;
      case 3:
        xstep.step(200, BACKWARD, INTERLEAVE);
        ystep.step(400, FORWARD, INTERLEAVE);
        break;
      default:
        break;
    }
  } else if (fy == 10 && 0 < fx && fx < 10){ // 2번 라인
    switch(player){
      case 0:
        ystep.step(200, FORWARD, INTERLEAVE);
        xstep.step(200, BACKWARD, INTERLEAVE);
        break;
      case 1:
        ystep.step(200, FORWARD, INTERLEAVE);
        xstep.step(400, BACKWARD, INTERLEAVE);
        break;
      case 2:
        ystep.step(200, BACKWARD, INTERLEAVE);
        xstep.step(200, BACKWARD, INTERLEAVE);
        break;
      case 3:
        ystep.step(200, BACKWARD, INTERLEAVE);
        xstep.step(400, BACKWARD, INTERLEAVE);
        break;
      default:
        break;
    }
  } else if (fx == 10 && 10 > fy && fy > 0){ // 3번 라인
    switch(player){
      case 0:
        xstep.step(200, BACKWARD, INTERLEAVE);
        ystep.step(200, BACKWARD, INTERLEAVE);
        break;
      case 1:
        xstep.step(200, BACKWARD, INTERLEAVE);
        ystep.step(400, BACKWARD, INTERLEAVE);
        break;
      case 2:
        xstep.step(200, FORWARD, INTERLEAVE);
        ystep.step(200, BACKWARD, INTERLEAVE);
        break;
      case 3:
        xstep.step(200, FORWARD, INTERLEAVE);
        ystep.step(400, BACKWARD, INTERLEAVE);
        break;
      default:
        break;
    }
  } else if (fy == 0 && 0 < fx && fx < 10){ // 4번 라인
    switch(player){
      case 0:
        ystep.step(200, BACKWARD, INTERLEAVE);
        xstep.step(200, FORWARD, INTERLEAVE);
        break;
      case 1:
        ystep.step(200, BACKWARD, INTERLEAVE);
        xstep.step(400, FORWARD, INTERLEAVE);
        break;
      case 2:
        ystep.step(200, BACKWARD, INTERLEAVE);
        xstep.step(200, FORWARD, INTERLEAVE);
        break;
      case 3:
        ystep.step(200, BACKWARD, INTERLEAVE);
        xstep.step(400, FORWARD, INTERLEAVE);
        break;
      default:
        break;
    }
  }
}
