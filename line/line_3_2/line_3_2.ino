#include<SoftwareSerial.h>

SoftwareSerial LineSerial(10, 11);

int hawaii_led[9] = {22, 23, 24, 25, 26, 27, 28, 29, 30};
int queen_elizabeth_led[3] = {31, 32, 33};
int lisbon_led[9] = {36, 37, 38, 39, 40, 41, 42, 43, 44};
int madrid_led[9] = {45, 46, 47, 48, 49, 50, 51, 52, 53};
String pl[4] = {"red", "blue", "yellow", "green"};
String data = "";
int blank = 0;

void setup() {
  for (int i = 22; i <= 53; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }


  Serial.println("Hello World!");

  //블루투스와 아두이노의 통신속도를 9600으로 설정
  LineSerial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  if (LineSerial.available()) {
    data = LineSerial.readStringUntil('\n');
    blank = data.indexOf(" ");
    if(blank == -1){
      ledOn("off", data, 3);
    } else {
      String country = slicing();
      int player = slicing().toInt();
      int building = slicing().toInt();
      ledOn(pl[player], country, (building-1)*3);
    }
  }
}

void redPlayer(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void greenPlayer(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void bluePlayer(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

void yellowPlayer(int redPin, int greenPin, int bluePin) {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void ledOff(int redPin, int greenPin, int bluePin){
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void ledOn(String player, String country, int building){
  if(country == "hawaii"){
    hawaii(player, building);
  } else if (country == "queen_elizabeth"){
    queen_elizabeth(player);
  } else if(country == "lisbon"){
    lisbon(player, building);
  } else{
    madrid(player, building);
  }
}

void hawaii(String player, int building) {
  if(player == "red"){
    redPlayer(22+building, 23+building, 24+building);
  } else if (player == "green"){
    greenPlayer(22+building, 23+building, 24+building);
  } else if(player == "blue"){
    bluePlayer(22+building, 23+building, 24+building);
  } else if(player =="yellow"){
    yellowPlayer(22+building, 23+building, 24+building);
  } else {
    for(int i = 0; i < building; i++){
      ledOff(22+i*3, 23+i*3, 24+i*3);
    }
  }
}

void queen_elizabeth(String player) {
  if(player == "red"){
    redPlayer(31, 32, 33);
  } else if (player == "green"){
    greenPlayer(31, 32, 33);
  } else if(player == "blue"){
    bluePlayer(31, 32, 33);
  } else if(player =="yellow"){
    yellowPlayer(31, 32, 33);
  } else {
    ledOff(31, 32, 33);
  }
}

void lisbon(String player, int building) {
  if(player == "red"){
    redPlayer(36+building, 37+building, 38+building);
  } else if (player == "green"){
    greenPlayer(36+building, 37+building, 38+building);
  } else if(player == "blue"){
    bluePlayer(36+building, 37+building, 38+building);
  } else if(player =="yellow"){
    yellowPlayer(36+building, 37+building, 38+building);
  } else {
    for(int i = 0; i < building; i++){
      ledOff(36+i*3, 37+i*3, 38+i*3);
    }
  }
}

void madrid(String player, int building){
  if(player == "red"){
    redPlayer(45+building, 46+building, 47+building);
  } else if (player == "green"){
    greenPlayer(45+building, 46+building, 47+building);
  } else if(player == "blue"){
    bluePlayer(45+building, 46+building, 47+building);
  } else if(player =="yellow"){
    yellowPlayer(45+building, 46+building, 47+building);
  } else {
    for(int i = 0; i < building; i++){
      ledOff(45+i*3, 46+i*3, 47+i*3);
    }
  }
}

String slicing(){
  blank = data.indexOf(" ");
  if (blank == -1){
    return data;
  }
  String info = data.substring(0, blank);
  int dataLength = data.length();
  data = data.substring(blank + 1, dataLength);
  return info;
}
