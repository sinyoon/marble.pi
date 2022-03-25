#include <Adafruit_NeoPixel.h>
#include<SoftwareSerial.h>

SoftwareSerial StepmotorSerial(12, 13);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(75,7, NEO_GRB+NEO_KHZ800);

int land[11][11] = {
  { -1,72,-1,69,66,65, 62, -1, 59, 56, -1},
  {  0,-1,-1,-1,-1,-1, -1, -1, -1, -1, 53},
  { -1,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1},
  {  1,-1,-1,-1,-1,-1, -1, -1, -1, -1, 50},
  {  4,-1,-1,-1,-1,-1, -1, -1, -1, -1, 47},
  { -1,-1,-1,-1,-1,-1, -1, -1, -1, -1, 46},
  {  7,-1,-1,-1,-1,-1, -1, -1, -1, -1, 43},
  { 10,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1},
  { 13,-1,-1,-1,-1,-1, -1, -1, -1, -1, 40},
  { 14,-1,-1,-1,-1,-1, -1, -1, -1, -1, 37},
  { -1,17,20,21,24,27, 28, 31, -1, 34, -1},
};

int tourland[6] = {65, 46, 27, 20, 13, 0};

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
  if (Serial2.available()){
    int diceNum = Serial2.readString().toInt();
    Serial.println(diceNum);
    delay(1000);
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
        if(i == 0) {
          data[i] = buildingNum(slicing(inString));
        } else {
          data[i] = slicing(inString).toInt();
        }
        inString = inString.substring(blank + 1, slength);
      }
      if(data[1] == 0){
        redPlayer(data[0] + (data[2] - 1));
      } else if (data[1] == 1){
        greenPlayer(data[0] + (data[2] - 1));
      } else if (data[1] == 2){
        bluePlayer(data[0] + (data[2] - 1));
      } else {
        yellowPlayer(data[0] + (data[2] - 1));
      }
    }
    if( first == "B"){
      while(1){
        bool check = true;
        int sell = buildingNum(slicing(inString));
        for(int i = 0; i < 6; i++){
          if(tourland[i] == sell){
            ledOff(sell);
            check = false;
            break;
          }
        }
        if (check){
          for(int i = 0; i < 3; i++){
            ledOff(sell + i);
          }
        }
        blank = inString.indexOf(' ');
        if (blank == -1) break;
        slength = inString.length();
        inString = inString.substring(blank + 1, slength);
      }
    }
  }                                                     
}

void redPlayer(int pixelNum){
  strip.setPixelColor(pixelNum, 255, 0, 0);
  strip.show();
}

void greenPlayer(int pixelNum) {
  strip.setPixelColor(pixelNum, 0, 255, 0);
  strip.show();
}

void bluePlayer(int pixelNum) {
  strip.setPixelColor(pixelNum, 0, 0, 255);
  strip.show();
}

void yellowPlayer(int pixelNum) {
  strip.setPixelColor(pixelNum, 255, 255, 0);
  strip.show();
}

void ledOff(int pixelNum){
  strip.setPixelColor(pixelNum, 0, 0, 0);
  strip.show();
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
