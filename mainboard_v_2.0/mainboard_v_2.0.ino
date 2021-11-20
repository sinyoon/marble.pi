#include <Adafruit_NeoPixel.h>
#include<SoftwareSerial.h>

SoftwareSerial StepmotorSerial(12, 13);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(75,7, NEO_GRB+NEO_KHZ800);

bool inited = true;

int land[11][11] = {
  { -1, 0,-1, 3, 6, 9, 10, -1, 13, 16, -1},
  { 74,-1,-1,-1,-1,-1, -1, -1, -1, -1, 19},
  { -1,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1},
  { 71,-1,-1,-1,-1,-1, -1, -1, -1, -1, 22},
  { 68,-1,-1,-1,-1,-1, -1, -1, -1, -1, 25},
  { -1,-1,-1,-1,-1,-1, -1, -1, -1, -1, 28},
  { 65,-1,-1,-1,-1,-1, -1, -1, -1, -1, 29},
  { 62,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1},
  { 61,-1,-1,-1,-1,-1, -1, -1, -1, -1, 32},
  { 58,-1,-1,-1,-1,-1, -1, -1, -1, -1, 35},
  { -1,55,54,51,48,47, 44, 41, -1, 38, -1},
};

void setup() {
  strip.setBrightness(180);
  strip.begin();
  strip.show();
  Serial.begin(9600);
  Serial2.begin(9600); //주사위
  StepmotorSerial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
}

void loop() { //코드를 무한반복합니다.
  if (inited){
    if (Serial2.available()){
      int diceNum = Serial2.readString().toInt();
      Serial.println(diceNum);
      inited = false;
    }
  }
  if (Serial.available()) {
    String inString = Serial.readStringUntil('\n');
    int blank = inString.indexOf(' ');
    int slength = inString.length();
    String first = inString.substring(0, blank);
    inString = inString.substring(blank + 1, slength);
      
    if( first == "M" ){
      StepmotorSerial.println(inString);
    }
    if( first == "L" ){
      int data[3] = {0};
      for(int i = 0; i < 3; i++){
        blank = inString.indexOf(' ');
        slength = inString.length();
        if(i == 0) data[i] = buildingNum(slicing(inString));
        data[i] = slicing(inString).toInt();
        inString = inString.substring(blank + 1, slength);
      }
      if(data[1] == 0){
        redPlayer(data[0] + data[2]);
      } else if (data[1] == 1){
        greenPlayer(data[0] + data[2]);
      } else if (data[1] == 2){
        bluePlayer(data[0] + data[2]);
      } else {
        yellowPlayer(data[0] + data[2]);
      }
    }
    if( first == "B"){
      while(1){
        ledOff(buildingNum(slicing(inString)));
        blank = inString.indexOf(' ');
        if (blank == -1) break;
        slength = inString.length();
        inString = inString.substring(blank + 1, slength);
      }
    }
    inited = true;
  }                                                     
}

void redPlayer(int pixelNum){
  strip.setPixelColor(pixelNum, 255, 0, 0);
}

void greenPlayer(int pixelNum) {
  strip.setPixelColor(pixelNum, 0, 255, 0);
}

void bluePlayer(int pixelNum) {
  strip.setPixelColor(pixelNum, 0, 0, 255);
}

void yellowPlayer(int pixelNum) {
  strip.setPixelColor(pixelNum, 255, 255, 0);
}

void ledOff(int pixelNum){
  strip.setPixelColor(pixelNum, 0, 0, 0);
}

String slicing(String inString){
  int   blank = inString.indexOf(" ");
  if (blank == -1){
    return inString;
  }
  String info = inString.substring(0, blank);
  return info;
}

int buildingNum(String data){
  int blank = data.indexOf(',');
  int dataLength = data.length();
  int x = data.substring(0, blank).toInt();
  int y = data.substring(blank + 1, dataLength).toInt();
  return land[x][y];
}
