#include<SoftwareSerial.h>

SoftwareSerial TestSerial(10, 11);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }


  Serial.println("Hello World!");

  //블루투스와 아두이노의 통신속도를 9600으로 설정
  TestSerial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  
  TestSerial.write("1");
  TestSerial.write("4");
  delay(1000);//블루투스를 통해 입력된 데이터 전달

}
