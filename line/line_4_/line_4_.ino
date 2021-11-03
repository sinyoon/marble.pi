#include<SoftwareSerial.h>

SoftwareSerial MainboardSerial(16, 17);
SoftwareSerial LineSerial(10, 11); 

int tokyo_led[9] = {22, 23, 24, 25, 26, 27, 28, 29, 30};
int columbia_led[3] = {31, 32, 33};
int paris_led[9] = {36, 37, 38, 39, 40, 41, 42, 43, 44};
int rome_led[9] = {45, 46, 47, 48, 49, 50, 51, 52, 53};

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

String data = "";
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
}

void loop() { //코드를 무한반복합니다.
  if (MainboardSerial.available()) {
    data = MainboardSerial.readStringUntil('\n');
    blank = data.indexOf(' ');
    if( blank == -1 ){
      String country = sendBuyBuilding(data, " ");
      if(country != " "){
        ledOn("off", country, 3);
      }
    } else {
      String country = sendBuyBuilding(slicing(), data);
      if(country != " "){
        String player = slicing();
        String building = slicing();
        ledOn(player, country, (building.toInt() - 1) * 3);
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
  if(country == "tokyo"){
    tokyo(player, building);
  } else if (country == "coulmbia"){
    columbia(player);
  } else if(country == "paris"){
    paris(player, building);
  } else{
    rome(player, building);
  }
}

void tokyo(String player, int building) {
  if(player == "red"){
    redPlayer(22+building, 23+building, 24+building);
  } else if (player == "green"){
    greenPlayer(22+building, 23+building, 24+building);
  } else if(player == "blue"){
    bluePlayer(22+building, 23+building, 24+building);
  } else if(player =="yellow"){
    yellowPlayer(22+building, 23+building, 24+building);
  } else {
    for(int i = 0;i < building; i++){
      ledOff(22+i*3, 23+i*3, 24+i*3);      
    }
  }
}

void columbia(String player) {
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

void paris(String player, int building) {
  if(player == "red"){
    redPlayer(36+building, 37+building, 38+building);
  } else if (player == "green"){
    greenPlayer(36+building, 37+building, 38+building);
  } else if(player == "blue"){
    bluePlayer(36+building, 37+building, 38+building);
  } else if(player =="yellow"){
    yellowPlayer(36+building, 37+building, 38+building);
  } else {
    for(int i = 0;i < building; i++){
      ledOff(36+i*3, 37+i*3, 38+i*3);      
    }
  }
}

void rome(String player, int building){
  if(player == "red"){
    redPlayer(45+building, 46+building, 47+building);
  } else if (player == "green"){
    greenPlayer(45+building, 46+building, 47+building);
  } else if(player == "blue"){
    bluePlayer(45+building, 46+building, 47+building);
  } else if(player =="yellow"){
    yellowPlayer(45+building, 46+building, 47+building);
  } else {
    for(int i = 0;i < building; i++){
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
