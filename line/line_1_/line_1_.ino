#include<SoftwareSerial.h>

SoftwareSerial MainboardSerial(10, 11);
SoftwareSerial LineSerial(12, 13);

int taipei_led[9] = {22, 23, 24, 25, 26, 27, 28, 29, 30};
int beijing_led[9] = {31, 32, 33, 36, 37, 38, 39, 40, 41};
int manila_led[9] = {42, 43, 44, 45, 46, 47, 48, 49, 50};
int jeju_island_led[3] = {51, 52, 53};

String pl[4] = {"red", "blue", "yellow", "green"};

String land[11][11] = {
  { "start", "taipei", "golden_key", "beijing", "manila", "jeju_island", "singapore", "golden_key", "cairo", "istanbul", "island"},
  { "seoul", " ", " ", " ", " ", " ", " ", " ", " ", " ", "athens"},
  { "welfarefund", " ", " ", " ", " ", " ", " ", " ", " ", " ", "golden_key"},
  { "new_york", " ", " ", " ", " ", " ", " ", " ", " ", " ", "copenhagen"},
  { "london", " ", " ", " ", " ", " ", " ", " ", " ", " ", "stockholm"},
  { "golden_key", " ", " ", " ", " ", " ", " ", " ", " ", " ", "concorde"},
  { "rome", " ", " ", " ", " ", " ", " ", " ", " ", " ", "bern"},
  { "paris", " ", " ", " ", " ", " ", " ", " ", " ", " ", "golden_key"},
  { "columbia", " ", " ", " ", " ", " ", " ", " ", " ", " ", "berlin"},
  { "tokyo", " ", " ", " ", " ", " ", " ", " ", " ", " ", "athens"},
  { "spacetravel", "madrid", "queen_elizabeth", "lisbon", "hawaii", "busan", "sydney", "sao_paulo", "golden_key", "buenosaires", "welfarefund"},
};

String data = " ";
int blank = 0;

void setup() {
  for (int i = 22; i <= 33; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 36; i <= 53; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
  while (!Serial) {
  }
  MainboardSerial.begin(9600);
  LineSerial.begin(9600);
  Serial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  if (MainboardSerial.available()) {
    data = MainboardSerial.readStringUntil('\n');
    Serial.println(data);
    blank = data.indexOf(' ');
    if( blank == -1 ){
      String country = sendBuyBuilding(data, " ");
      if(country != " "){
        ledOn("off", country, 3);
      }
    } else {
      String country = sendBuyBuilding(slicing(), data);
      if(country != " "){
        int player = slicing().toInt();
        int building = slicing().toInt();
        ledOn(pl[player], country, (building - 1) * 3);
      }
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
  if(country == "taipei"){
    taipei(player, building);
  } else if (country == "jeju_island"){
    jeju_island(player);
  } else if(country == "beijing"){
    beijing(player, building);
  } else{
    manila(player, building);
  }
}

void taipei(String player, int building) {
  if(player == "red"){
    redPlayer(22+building, 23+building, 24+building);
  } else if (player == "green"){
    greenPlayer(22+building, 23+building, 24+building);
  } else if(player == "blue"){
    bluePlayer(22+building, 23+building, 24+building);
  } else if(player =="yellow"){
    yellowPlayer(22+building, 23+building, 24+building);
  } else {
    for(int i = 0;i < building;i++){
      ledOff(22+i*3, 23+i*3, 24+i*3);
    }
  }
}

void jeju_island(String player) {
  if(player == "red"){
    redPlayer(51, 52, 53);
  } else if (player == "green"){
    greenPlayer(51, 52, 53);
  } else if(player == "blue"){
    bluePlayer(51, 52, 53);
  } else if(player =="yellow"){
    yellowPlayer(51, 52, 53);
  } else {
    ledOff(51, 52, 53);
  }
}

void beijing(String player, int building) {
  if(building != 0){
    building += 2;
  }
  if(player == "red"){
    redPlayer(31+building, 32+building, 33+building);
  } else if (player == "green"){
    greenPlayer(31+building, 32+building, 33+building);
  } else if(player == "blue"){
    bluePlayer(31+building, 32+building, 33+building);
  } else if(player =="yellow"){
    yellowPlayer(31+building, 32+building, 33+building);
  } else {
    for(int i = 0;i < 3;i++){
      if(i != 0){
        i = i*3+2;
      }
      ledOff(31+i, 32+i, 33+i);
    }
  }
}

void manila(String player, int building){
  if(player == "red"){
    redPlayer(42+building, 43+building, 44+building);
  } else if (player == "green"){
    greenPlayer(42+building, 43+building, 44+building);
  } else if(player == "blue"){
    bluePlayer(42+building, 43+building, 44+building);
  } else if(player =="yellow"){
    yellowPlayer(42+building, 43+building, 44+building);
  } else {
    for(int i = 0;i < building;i++){
      ledOff(42+i*3, 43+i*3, 44+i*3);
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

String sendBuyBuilding(String data, String info){
  int blank = data.indexOf(',');
  int dataLength = data.length();
  int x = data.substring(0, blank).toInt();
  int y = data.substring(blank + 1, dataLength).toInt();
  if(x > 5){
    if(info == " "){
      LineSerial.println(land[x][y]);
    } else {
      LineSerial.println(land[x][y] + " " + info);
    }
  } else {
    return land[x][y];
  }
  return " ";
}
