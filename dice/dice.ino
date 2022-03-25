#include<SoftwareSerial.h>

SoftwareSerial TestSerial(2, 3);

int minVal = 265;
int maxVal = 402;
int xTime[5] = {0, }; // 5초를 대기하기 위한 함수(값이 계속 넘어가는것을 방지하기 위함)
int arr_num = 0; // 배열 순서
double x, y, z;
int dice_value[12] = {0 , 213, 107, 352, 247, 142, 310, 68, 180, 279, 26, 0};
bool inited = false;
int check = 0;

void setup() {
  // 시리얼 통신의 속도를 9600으로 설정
  Serial.begin(9600);
  while (!Serial) {
    ; //시리얼통신이 연결되지 않았다면 코드 실행을 멈추고 무한 반복
  }
  //블루투스와 아두이노의 통신속도를 9600으로 설정
  TestSerial.begin(9600);
}

void loop() { //코드를 무한반복합니다.
  int xRead = analogRead(A0);
  int yRead = analogRead(A1);
  int zRead = analogRead(A2);

  int xAng = map(xRead, minVal, maxVal, -180, 180);
  int yAng = map(yRead, minVal, maxVal, -180, 180);
  int zAng = map(zRead, minVal, maxVal, -180, 180);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);

  for (int i = 1; i < 11; i++) {
    if(xAng < -150){
      xTime[arr_num] = 1;
    }else if(xAng > 160){
      xTime[arr_num] = 12;
    }
    if (x >= dice_value[i] - 15 && x <= dice_value[i] + 15) {
      /*if (i == 0 || i == 7 || i == 11)
        if (xAng < 0)
          xTime[arr_num] = 1;
        else if (xAng < 130)
          xTime[arr_num] = 8;
        else
          xTime[arr_num] = 12;
      else*/
        xTime[arr_num] = (i + 1);

    }
  }
  delay(200);

  Serial.println(x);

  if(check != xTime[arr_num]){
    inited = true;
  }
  
  if (xTime[0] == xTime[1] && xTime[1] == xTime[2] && xTime[2] == xTime[3] && xTime[3] == xTime[4] && xTime[4] == xTime[0] && xTime[0] != 0) {

    if (xTime[0] == 1) xTime[0] = (rand() % 12) + 1;
    if(inited){
      TestSerial.println(xTime[0]);
      Serial.println(xTime[0]);
      inited = false;
      check = xTime[0];
    }
    
    for (int i = 0; i < 5; i++)
      xTime[i] = 0;
  }


  arr_num++;

  if (arr_num > 4) {
    arr_num = 0;
  }
}
