void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  String inString = "01 02 03 04 05 06 34 23";
  while(true){
    int index = inString.indexOf(' ');
    int inString_length = inString.length();
    if(index == -1){
      int last = inString.toInt();
      Serial.println(last);
      break;
    }
    String first = inString.substring(0, index);
    int string = first.toInt();
    inString = inString.substring(index + 1, inString_length);
    Serial.println(string);
    delay(1000);
  }
  delay(1000);
}
